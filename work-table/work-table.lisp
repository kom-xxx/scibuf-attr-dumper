
(defvar *default-work-table-file* "work-table.txt")

(defun next-month (mm yyyy)
  (multiple-value-bind (dy nmm) (truncate mm 12)
    (values (1+ nmm) (+ yyyy dy))))

(defun last-month (mm yy)
  (multiple-value-bind (s m h dd lm ly)
    (decode-universal-time (1- (encode-universal-time 0 0 0 1 mm yy)))
    (declare (ignore s m h dd))
    (values lm ly)))

(defun inc-dow (dow)
  (mod (1+ dow) 7))

(defun nth-dow (n dow init)
  (let ((1st (1+ (mod (- dow init) 7))))
    (+ 1st (* 7 (1- n)))))

(defun nth-day-of-week (n dow mm yy)
  (let ((ut (encode-universal-time 0 0 0 1 mm yy)))
    (multiple-value-bind (s m h dd mm yy ww) (decode-universal-time ut)
      (declare (ignore s m h dd mm yy))
      (nth-dow n dow ww))))

(defun calc-table-month (&optional (today nil))
  (multiple-value-bind (s m h dd mm yyyy)
      (if today
	  (values 0 0 0 (nth 0 today) (nth 1 today) (nth 2 today))
	  (get-decoded-time))
    (declare (ignore s m h))
    (multiple-value-bind (s m h dd bm by dow)
	(decode-universal-time
	 (if (> dd 15)
	     (encode-universal-time 0 0 0 1 mm yyyy)
	     (multiple-value-bind (nm ny) (last-month mm yyyy)
	       (encode-universal-time 0 0 0 1 nm ny))))
      (declare (ignorable  s m h dd))
      (multiple-value-bind (nm ny) (next-month bm by)
	(multiple-value-bind (s m h ed em ey)
	    (decode-universal-time (1- (encode-universal-time 0 0 0 1 nm ny)))
	  (declare (ignore s m h em ey))
	  (values 1 bm by ed dow))))))

(defvar *vernal-equinox*
  '(((1900 . 1923) (21 21 21 22))
    ((1924 . 1959) (21 21 21 21))
    ((1960 . 1991) (20 21 21 21))
    ((1992 . 2023) (20 20 21 21))
    ((2024 . 2055) (20 20 20 21))
    ((2056 . 2091) (20 20 20 20))
    ((2092 . 2099) (18 20 20 20))))

(defvar *autumnal-equinox*
  '(((1900 . 1919) (23 24 24 24))
    ((1920 . 1947) (23 23 24 24))
    ((1948 . 1979) (23 23 23 24))
    ((1980 . 2011) (23 23 23 23))
    ((2012 . 2043) (22 23 23 23))
    ((2044 . 2075) (22 22 23 23))
    ((2076 . 2099) (22 22 22 23))))

(defun equinox (yy equinox)
  (loop :for elt :in equinox
	:when (<= (caar elt) yy (cdar elt))
	  :return (nth (mod yy 4) (cadr elt))))

(defun vernal-equinox (yy)
  (equinox yy *vernal-equinox*))

(defun autumnal-equinox (yy)
  (equinox yy *autumnal-equinox*))

(defvar *national-holidays*
  '((1 (:fixed 01) "元日")
    (1 (:2nd 0) "成人の日")
    (2 (:fixed 11) "原告記念の日")
    (2 (:fixed 23) "天皇誕生日")
    (3 (:funcall vernal-equinox) "春分の日")
    (4 (:fixed 29) "昭和の日")
    (5 (:fixed 3) "減俸記念日")
    (5 (:fixed 4) "緑の日")
    (5 (:fixed 5) "こどもの日")
    (7 (:3rd 0) "海の日")
    (8 (:fixed 11) "山の日")
    (9 (:3rd 0) "敬老の日")
    (9 (:funcall autumnal-equinox) "秋分の日")
    (10 (:2nd 0) "スポーツの日")
    (11 (:fixed 3) "文化の日")
    (11 (:fixed 23) "勤労感謝の日")))

(defun find-holidays (mm)
  (loop :for elt :in *national-holidays*
	:when (= (car elt) mm)
	  :collect (cdr elt)))

(defun substitute-holiday (dd holidays)
  (let ((dd (1+ dd)))
    (if (assoc dd holidays)
	(substitute-holiday dd holidays)
	dd)))

(defun determin-holidays (mm yy)
  (let* ((holidays (loop :for elt :in (find-holidays mm)
			 :collect (case (caar elt)
				    (:fixed (cons (cadar elt) (cadr elt)))
				    (:2nd (cons (nth-day-of-week 2 (cadar elt)
								 mm yy)
						(cadr elt)))
				    (:3rd (cons (nth-day-of-week 3 (cadar elt)
								 mm yy)
						(cadr elt)))
				    (:funcall (cons (funcall (cadar elt) yy)
						    (cadr elt))))))
	 (dow-list (loop :for dd :in holidays
			 :collect (multiple-value-bind (s m h cdd cmm cyy cwd)
				      (decode-universal-time
				       (encode-universal-time 0 0 9
							      (car dd) mm yy))
				    (declare (ignore s m h cdd cmm cyy))
				    cwd)))
	 (subst (loop :for dd :in holidays
		      :for dow :in dow-list
		      :when (= dow 6)
			:collect (cons (substitute-holiday (car dd) holidays)
				       "振替休日")))
	 (intr (if (< (length holidays) 2)
		   nil
		   (loop :for elt :in holidays
			 :for nxt :in (cdr holidays)
			 :when (= (- (car nxt) (car elt)) 2)
			   :collect (cons (1+ (car elt)) "国民の休日")))))
    #+nil(values holidays subst intr)
    (sort (append holidays subst intr) #'< :key #'car)))

(defvar *day-of-week* #("Mon" "Tue" "Wed" "Thu" "Fri" "Sat" "Sun"))

(let ((fmt-weekdays "~2D(~A)	07:30	17:00	1.0	8.5~%")
      (fmt-holidays  "~2D(~A)					~A~%"))
  (defun make-work-table (&optional (file-name *default-work-table-file*)
			    (today nil))
    (labels
	((make-table (&optional (stream *standard-output*) (today nil))
	   (multiple-value-bind (bdd mm yy edd bdow) (calc-table-month today)
	     (let ((holidays (determin-holidays mm yy)))
	       (format stream "勤務表 ~D年 ~2D月~%" yy mm)
	       (loop :for day :from bdd :to edd
		     :do (let ((dow (mod (+ bdow (1- day)) 7)))
			   (if (and (< dow 5) (not (assoc day holidays)))
			       (format stream fmt-weekdays
				       day (aref *day-of-week* dow))
			       (format stream fmt-holidays
				       day (aref *day-of-week* dow)
				       (or (cdr(assoc day holidays)) "")))))))))
      (with-open-file (stream file-name :direction :output
					:if-does-not-exist :create
					:if-exists :supersede)
	(make-table stream today)))))

(defun split-line (line &optional (pos 0) (acc (make-array 0 :adjustable t
							     :fill-pointer 0)))
  (let ((tab (position #\tab line :start pos)))
    (cond
      ((null tab)
       (vector-push-extend (subseq line pos) acc)
       acc)
      (t
       (vector-push-extend (subseq line pos tab) acc)
       (split-line line (1+ tab) acc)))))

(defun hour+min->sec (string)
  (let* ((colon (position #\: string))
	 (h (* (parse-integer string :end colon :junk-allowed t) 3600))
	 (m (* (parse-integer string :start (1+ colon) :junk-allowed t) 60)))
    (+ h m)))

(defun dulation->sec (string)
  (with-input-from-string (stream string)
    (* (read stream nil nil) 3600)))

(defun sec->dulation (sec)
  (format nil "~3,1F" (/ sec 3600)))

(defun reconstruct-table (&optional (file-name *default-work-table-file*))
  (labels
      ((reconstruct-table (stream &optional
				  (result (make-array 0 :fill-pointer 0
							:adjustable t))
				  (sum-work-time 0.0D0))
	 (let ((line (read-line stream nil nil)))
	   (cond
	     ((null line) (values result sum-work-time))
	     ((or (string= "勤務表" line :end2 3)
		  (string= "TOTAL" line :end2 5))
	      (vector-push-extend line result)
	      (reconstruct-table stream result sum-work-time))
	     (t
	      (let ((words (split-line line)))
		(cond
		  ((string= (aref words 1) "")
		   (vector-push-extend line result)
		   (reconstruct-table stream result sum-work-time))
		  (t
		   (Let ((work-time (- (hour+min->sec (aref words 2))
				       (hour+min->sec (aref words 1))
				       (dulation->sec (aref words 3)))))
		     (vector-push-extend 
		      (format nil "~A	~A	~A	~A	~A	~A"
			      (aref words 0) (aref words 1) (aref words 2)
			      (aref words 3) (sec->dulation work-time)
			      (aref words 5))
		      result)
		     (reconstruct-table stream result
					(+ sum-work-time work-time)))))))))))
    (with-open-file (stream file-name :direction :input
				      :if-does-not-exist :error)
      (multiple-value-bind (result sum-work-time) (reconstruct-table stream)
	(with-open-file (stream (format nil "~A.new" file-name)
				:direction :output
				:if-does-not-exist :create
				:if-exists :supersede)
	  (loop :for line :across result
		:unless (string= "TOTAL" line :end2 5)
		  :do (format stream "~A~%" line))
	  (format stream "TOTAL				~3,1F~%"
		  (/ sum-work-time 3600)))))
    (rename-file (format nil "~A.new" file-name) file-name)
    (values)))

(defun invoke-emacs (&optional (file-name *default-work-table-file*))
  (run-program "emacs" (list file-name) :search t))

(defun main ()
  (let* ((args (cdr sb-ext:*posix-argv*)))
    (multiple-value-bind (file today)
	(multiple-value-bind (s m h dd mm yy) (get-decoded-time)
	  (declare (ignore s m h dd))
	  (case (length args)
	    (0 (values *default-work-table-file* nil))
	    (1 (values (nth 0 args) nil))
	    (2 (values (nth 0 args) `(,(parse-integer (nth 1 args)) ,mm ,yy)))
	    (3 (values (nth 0 args) `(,(parse-integer (nth 2 args))
				      ,(parse-integer (nth 3 args)) ,yy)))
	    (4 (values (nth 0 args) `(,(parse-integer (nth 1 args))
				      ,(parse-integer (nth 2 args))
				      ,(parse-integer (nth 3 args)))))))
      (make-work-table file today)
      (invoke-emacs file)
      (reconstruct-table file))))
