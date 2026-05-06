(require :tail-queue)

(defparameter *struct-name-list* nil)
(defparameter *enum-name-list* nil)
(defparameter *array-type-list* nil)

(defun skip-space (line start)
  #+nil(print 'skip-space)
  (let ((c (char line start)))
    (cond
      ((char= c #\Space) (skip-space line (1+ start)))
      (t start))))

(defun parse-spec (line)
  (cond
   ((or (search "Accessibility:" line) (search "Type:" line))
    #+nil(print `(parse-spec ,line))
    (let* ((colon (position #\: line))
	   (word (skip-space line (1+ colon)))
	   (space (position #\Space line :start word)))
      (subseq line word space)))
   ((search "Value:" line)
    #+nil(print `(parse-spec ,line))
    (let* ((colon (position #\: line))
	   (@ (position #\@ line :start colon))
	   (spc0 (if @ (position #\Space line :start @) (1+ colon)))
	   (word (skip-space line spc0))
	   (token (subseq line word)))
      (when (position #\[ token)
	(pushnew (subseq token 0 (position #\[ token)) *array-type-list*
		 :test #'string=))
      (if (string/= token "None") token nil)))
   ((search "Datatype:" line)
    #+nil(print `(parse-spec ,line))
    (let* ((colon (position #\: line))
	   (word (skip-space line (1+ colon))))
      (when (position #\[ line)
	(pushnew (subseq line word (position #\[ line)) *array-type-list*
		 :test #'string=))
      (subseq line word)))
   (t nil)))

(defun parse-enum (is acc &optional (sub-acc (tq:qmake)) (element (tq:qmake)))
  (let ((line (read-line is nil nil)))
    #+nil(print `(parse-enum line ,line acc ,acc sub-acc ,sub-acc))
    (cond
      ((null line) (error "mulformed input"))
      (t
       (let ((line (string-left-trim '(#\Space #\Tab) line)))
	 (cond
	   ((string= "" line)
	    (parse-enum is acc sub-acc element))
	   ((string= "*" line :end2 1)
	    (let ((spec (parse-spec line)))
	      (when spec
		(tq:qpush spec element))
	      (parse-enum is acc sub-acc element)))
	   ((string= "}" line :end2 1)
	    (let* ((semicolon (position #\; line))
		   (type-name (subseq line 2 semicolon)))
	      #+nil(print `(semicolon ,semicolon type-name ,type-name))
	      (push type-name *enum-name-list*)
	      (tq:qpush `(,type-name (:enum ,(tq:qlist sub-acc))) acc)
	      (parse-enum-or-struct is acc)))
	   ((string= "/*" line :end2 2)
	    (unless (tq:qempty element)
	      (tq:qpush (tq:qlist element) sub-acc))
	    (parse-enum is acc sub-acc))
	   ((search "NvSciBufAttrKey_LowerBound" line)
	    (parse-enum is acc sub-acc))
	   ((search "NvSciBufAttrKey_UpperBound" line)
	    (tq:qpush (tq:qlist element) sub-acc)
	    (parse-enum is acc sub-acc))
	   ((or (alpha-char-p (char line 0)) (char= #\_ (char line 0)))
	    (let* ((end (or (position #\Space line) (position #\, line)))
		   (symbbol (subseq line 0 end)))
	      (if (tq:qempty element)
		  (tq:qpush symbbol sub-acc)
		  (tq:qpush symbbol element))
	      (parse-enum is acc sub-acc element)))
	   (t (error "syntax error '~a'" line))))))))

(defun parse-struct (is acc &optional (sub-acc (tq:qmake)))
  #+nil(print 'parse-struct)
  (let ((line (read-line is nil nil)))
    (cond
      ((null line) (error "mulformed input"))
      (t
       (let ((line (string-left-trim '(#\Space #\Tab) line)))
	 (cond
	   ((string= "" line)
	    (parse-struct is acc sub-acc))
	   ((or (string= "*" line :end2 1) (string= "/*" line :end2 2))
	    (parse-struct is acc sub-acc))
	   ((string= "}" line :end2 1)
	    (let* ((semicolon (position #\; line))
		   (type-name (subseq line 2 semicolon)))
	      (unless (string= type-name "NvSciBufAttrKeyValuePair")
		(pushnew type-name *struct-name-list*)
		(tq:qpush `(,type-name (:struct ,(tq:qlist sub-acc))) acc))
	      (parse-enum-or-struct is acc)))
	   ((or (alpha-char-p (char line 0)) (char= #\_ (char line 0)))
	    (let* ((word (subseq line 0 (position #\Space line)))
		   (line (if (string= word "const")
			     (string-left-trim "const " line)
			     line))
		   (space (position #\Space line))
		   (type (subseq line 0 space))
		   (next (skip-space line space))
		   (end (or (position #\Space line :start next)
			    (position #\; line :start next)))
		   (name (subseq line next end))
		   ([ (position #\[ name))
		   (type (if [ (format nil "~A~A" type (subseq name [)) type))
		   (name (if [ (subseq name 0 [) name)))
	      (tq:qpush `(,type ,name) sub-acc)
	      (parse-struct is acc sub-acc)))
	   (t (error "syntax error '~A'" line))))))))

(defun parse-packed (is acc &optional (sub-acc (tq:qmake)))
  #+nil(print 'parse-packed)
  (let ((line (read-line is nil nil)))
    (cond
      ((null line) (error "mulformed input"))
      (t
       (let ((line (string-left-trim '(#\Space #\Tab) line)))
	 (cond
	   ((string= "" line)
	    (parse-packed is acc sub-acc))
	   ((or (string= "*" line :end2 1) (string= "/*" line :end2 2))
	    (parse-packed is acc sub-acc))
	   ((string= "})" line :end2 2)
	    (let* ((semicolon (position #\; line))
		   (type-name (subseq line 3 semicolon)))
	      (push type-name *struct-name-list*)
	      (tq:qpush `(,type-name (:struct ,(tq:qlist sub-acc))) acc)
	      (parse-enum-or-struct is acc)))
	   ((or (alpha-char-p (char line 0)) (char= #\_ (char line 0)))
	    (let* ((space (position #\Space line))
		   (type (subseq line 0 space))
		   (next (skip-space line space))
		   (end (or (position #\Space line :start next)
			    (position #\; line :start next)))
		   (name (subseq line next end)))
	      (tq:qpush `(,type ,name) sub-acc)
	      (parse-packed is acc sub-acc)))
	   (t (error "syntax error '~A'" line))))))))

(defun parse-enum-or-struct (is &optional (acc (tq:qmake)))
  #+nil(print `(parse-enum-or-struct ,acc))
  (let ((line (read-line is nil nil)))
    (cond
      ((null line) (tq:qlist acc))
      (t
       (let ((line (string-left-trim '(#\Space #\Tab) line)))
	 (cond
	   ((string= "" line) (parse-enum-or-struct is acc))
	   ((string= "#" line :end2 1) (parse-enum-or-struct is acc))
	   ((or (string= "*" line :end2 1) (string= "/*" line :end2 2))
	    (parse-enum-or-struct is acc))
	   ((string= "typedef enum {" line :end2 14)
	    (parse-enum is acc))
	   ((string= "typedef struct {" line :end2 16)
	    (parse-struct is acc))
	   ((string= "PACK_BUF" line :end2 8)
	    (parse-packed is acc))
	   (t
	    (parse-enum-or-struct is acc))))))))

(defun parse-header-file (file-name)
  (setf *struct-name-list* nil
	*enum-name-list* nil
	*array-type-list* nil)
  (with-open-file (is file-name :direction :input :if-does-not-exist :error)
    (parse-enum-or-struct is)))

;;;
;;; PRINTER generation
;;;
;;  utils
(defun make-type-id-list (name-list)
  (let* ((elements (cadadr (assoc "NvSciBufAttrKey" name-list
				  :test #'string=))))
    (loop :with types := nil
	  :for elt :in elements
	  :do (when (cadr elt)
		(pushnew (cadr elt) types :test #'string=))
	  :finally (return (sort types #'string<)))))

(defun make-typespec-list (name-list)
  (let* ((hash (make-hash-table :test #'equal)))
    (loop :for elt :in name-list
	  :when (string= (car elt) "NvSciBufAttrKey")
	    :do (loop :for elt* :in (cadadr elt)
		      :do (let* ((type (cadr elt*))
				 ([ (position #\[ type))
				 (] (position #\] type))
				 (suffix (if [ (subseq type (1+ [) ]) nil))
				 (type (if [ (subseq type 0 [) type)))
			    (multiple-value-bind (entry valid)
				(gethash type hash)
			      (unless valid
				(setf entry (vector nil nil))
				(setf (gethash type hash) entry))
			      (if [
				  (setf (aref entry 1) suffix)
				  (setf (aref entry 0) t)))))
	  :when (eq (caadr elt) :struct)
	    :do (loop :for ent :in (cadadr elt)
		      :do (let* ((type (car ent))
				 ([ (position #\[ type))
				 (] (position #\] type))
				 (suffix (if [ (subseq type (1+ [) ]) nil))
				 (type (if [ (subseq type 0 [) type)))
			    (multiple-value-bind (entry valid)
				(gethash type hash)
			      (unless valid
				(setf entry (vector nil nil))
				(setf (gethash type hash) entry))
			      (if suffix
				  (setf (aref entry 1) suffix)
				  (setf (aref entry 0) t))))))
    (loop :for key :being :each :hash-key :of hash
	  :nconc (multiple-value-bind (e v) (gethash key hash)
		   (when v `((,key ,e)))))))
    
(defun make-attr-name-table (name-list)
  (format t "struct name_list {
    int32_t value;
    char *name;
};~2%")
  (loop :for elt :in name-list
	:do (let* ((name (car elt))
		   (body (cadr elt))
		   (type (car body))
		   (enum-list (cadr body)))
	      (when (eq type :enum)
		(format t "struct name_list ~A_names[] = {~%" name)
		(loop :for elt :in enum-list
		      :do (cond
			    ((stringp elt)
			     (format t "    {~A, \"~A\"},~%" elt elt))
			    (t
			     (let ((names (cddr elt)))
			       (loop :for elt :in names
				     :do (format t "    {~A, \"~A\"},~%"
						 elt elt))))))
		(format t "};~2%"))))
  (format t "char *lookup_attr_name_table(int32_t value,
                        struct name_list *table, size_t len) {
    size_t i; 
    for (i = 0; i < len; ++i)
        if (table[i].value == value)
            return table[i].name;
    return \"UnknownEnumerator\";
}~2%"))


;; the printer 
(defun make-scalar-printer (name-list typespecs)
  (declare (ignorable name-list))
  (loop :for elt :in typespecs
	:when (aref (cadr elt) 0)
	  :do (let ((elt (car elt)))
		(cond
		  ((string= elt "bool")
		   (format t "~
static void bool_printer(char *label, const void *flob_, size_t len, char *pfix_)
{
    ~A *flob = (~A *)flob_;
    char pfix[1024];
    sprintf(pfix, \"%s    \", pfix_);
    fprintf(dbgout, \"%s%s:%s\\n\", pfix, label, ~
                      *flob ? \"true\" : \"false\");
}~2%" elt elt))

		  ((string= elt "float")
		   (format t "~
static void ~A_printer(char *label, const void *flob_, size_t len, char *pfix_)~%"
			   elt)
		   (format t "{
    ~A *flob = (~A *)flob_;
    char pfix[1024];
    sprintf(pfix, \"%s    \", pfix_);
    fprintf(dbgout, \"%s%s:%f\\n\", pfix, label, *flob);
}~2%" elt elt))

		  ((search "int" elt :test #'char=)
		   (let* ((sign (if (char= (char elt 0) #\u) "u" "d"))
			  (long (if (position #\6 elt) "l" ""))
			  (spec (concatenate 'string long sign)))
		     (format t "~
static void ~A_printer(char *label, const void *flob_, size_t len, char *pfix_)~%"
			     elt)
		     (format t "{
    ~A *flob = (~A *)flob_;
    char pfix[1024];
    sprintf(pfix, \"%s    \", pfix_);
    fprintf(dbgout, \"%s%s:%~A\\n\", pfix, label, *flob);
}~2%" elt elt spec)))

		  (t
		   nil)))))

(defun make-scalar-array-printer (name-list typespecs)
  (declare (ignorable name-list))
  (loop :for elt :in typespecs
	:when (aref (cadr elt) 1)
	  :do (let ((elt (car elt)))
		(cond
		  ((string= elt "bool")
		   (format t "~
static void bool_array_printer(char *label, const void *flob_, size_t len, char *pfix_)
{
    ~A *flob = (~A *)flob_;
    char pfix[1024];
    sprintf(pfix, \"%s    \", pfix_);
    size_t n = len / sizeof (bool);
    fprintf(dbgout, \"%s%s:[\", pfix, label);
    for (size_t i = 0; i < n; ++i)
        if (i != n - 1)
            fprintf(dbgout, \"%s \", flob[i] ? \"truw\" : \"false\");
        else
            fprintf(dbgout, \"%s]\\n\", flob[i] ? \"truw\" : \"false\");
}~2%" elt elt))

		  ((string= elt "float")
		   (format t "~
static void float_array_printer(char *label, const void *flob_, size_t len, ~
                        char *pfix_)
{
    ~A *flob = (~A *)flob_;
    char pfix[1024];
    sprintf(pfix, \"%s    \", pfix_);
    size_t n = len / sizeof (float);
    fprintf(dbgout, \"%s%s:[\", pfix, label);
    for (size_t i = 0; i < n; ++i)
        if (i != n - 1)
            fprintf(dbgout, \"%f \", flob[i]);
        else
            fprintf(dbgout, \"%f]\\n\", flob[i]);
}~2%" elt elt))

		  ((search "uint8" elt)
		   (let ((type (subseq elt 0 (position #\[ elt))))
		     (format t "~
static void uint8_t_array_printer(char *label, const void *flob_, size_t len, ~
                           char *pfix_)
{
    ~A *flob = (~A *)flob_;
    char pfix[1024];
    sprintf(pfix, \"%s    \", pfix_);
    size_t n = len / sizeof (uint8_t);
    fprintf(dbgout, \"%s%s:[\", pfix, label);
    for (size_t i = 0; i < n; ++i)
        if (i != n - 1)
            fprintf(dbgout, \"%02x \", flob[i]);
        else
            fprintf(dbgout, \"%02x]\\n\", flob[i]);~%};~2%" type type)))
		  ((search "int" elt)
		   (let* ((sign (if (char= (char elt 0) #\u) "u" "d"))
			  (long (if (position #\6 elt) "l" ""))
			  (spec (concatenate 'string long sign))
			  (type (subseq elt 0 (position #\[ elt))))
		     (format t "~
static void ~A_array_printer(char *label, const void *flob_, size_t len, char *pfix_)~%"
			     type)
		     (format t "{
    ~A *flob = (~A *)flob_;
    char pfix[1024];
    sprintf(pfix, \"%s    \", pfix_);
    size_t n = len / sizeof (~A);
    fprintf(dbgout, \"%s%s:[\", pfix, label);
    for (size_t i = 0; i < n; ++i) 
        if (i != n - 1)
            fprintf(dbgout, \"%~A \", flob[i]);
        else
            fprintf(dbgout, \"%~A]\\n\", flob[i]);
}~2%" type type type spec spec)))
		  (t nil)))))

(defun make-enum-printer (name-list typespecs)
  (declare (ignorable name-list))
  (loop :for elt :in typespecs
	:when (and (member (car elt) *enum-name-list* :test #'string=)
		   (aref (cadr elt) 0))
	  :do (let ((elt (car elt)))
		(format t "~
static void ~A_printer(char *label, const void *flob_, size_t len, char *pfix)
{
    ~A *flob = (~A *)flob_;
    size_t alen = ARRAY_LENGTH(~A_names);

    char *name = lookup_attr_name_table(*flob, ~A_names, alen);
    fprintf(dbgout, \"%s%s:%s\\n\", pfix, label, name);
}~2%" elt elt elt elt elt))
	:when (and (member (car elt) *enum-name-list* :test #'string=)
		   (aref (cadr elt) 1))
	  :do (let ((elt (car elt)))
		(format t "~
static void ~A_array_printer(char *label, const void *flob_, size_t len, char *pfix)
{
    ~A *flob = (~A *)flob_;
    size_t alen = ARRAY_LENGTH(~A_names);

    fprintf(dbgout, \"%s%s:[\", pfix, label);
    size_t n = len / sizeof (~A);
    for (size_t i = 0; i < n; ++i) {
        char *name = lookup_attr_name_table(flob[i], ~A_names, alen);
        if (i != n - 1)
            fprintf(dbgout, \"%s \", name);
        else
            fprintf(dbgout, \"%s]\\n\", name);
    }
}~2%" elt elt elt elt elt elt))))

(defun %make-struct-printer (name fields typespecs)
  (declare (ignorable typespecs))
  (format t "~
static void ~A_printer(char *label, const void *flob_, size_t len, char *pfix_)~%" name)
  (format t "{
    ~A *flob = (~A *)flob_;
    char pfix[1024];
    sprintf(pfix, \"%s    \", pfix_);
    fprintf(dbgout, \"%s%s: {\", pfix_, label);~%" name name)
  (loop :for elt :in fields
	;;:when (member (cadr elt) type-list :test #'string=)
	:do (let* ((type (car elt))
		   ([ (position #\[ type))
		   (type (if [ (subseq type 0 [) type))
		   (field (cadr elt)))
	      (cond
		((member type *struct-name-list* :test #'string=)
		 (format t "~:
    ~A_printer(\"~A\", &flob->~A, sizeof flob->~A, pfix);~%"
			 type field field field))
		((member type *enum-name-list* :test #'string=)
		 (format t "~:
    ~A_printer(\"~A\", &flob->~A, sizeof flob->~A, pfix);~%"
			 type field field field))
		((and (string= type "uint8_t") [)
		 (format t "~:
    ~A_array_printer(\"~A\", flob->~A, sizeof flob->~A, pfix);~%"
			 type field field field))
		((string= type "bool")
		 (format t "~:
    bool_printer(\"~A\", &flob->~A, sizeof flob->~A, pfix);~%"
			 field field field))
		(t
		 (format t "~:
    ~A_printer(\"~A\", &flob->~A, sizeof flob->~A, pfix);~%"
			 type field field field)))))
  (format t "    fprintf(dbgout, \"%s}\", pfix_);~%")
  (format t "}~2%"))

(defun make-struct-printer (name-list typespecs)
  (loop :for elt :in name-list
	:do (let* ((name (car elt))
		   (body (cadr elt))
		   (type (car body))
		   (fields (cadr body)))
	      (when (eq type :struct)
		(unless (or (string= name "NvSciBufRect")
			    (string= name "NvSciBufObjIpcExportDescriptor"))
		  (format t "/* >>>>>>>>> ~A_printer */~%" name)
		  (%make-struct-printer name fields typespecs))))))

(defun make-struct-array-printer (name-list typespecs)
  (declare (ignorable name-list))
  (loop :for elt :in *struct-name-list*
	:when (and (member elt typespecs :key #'car  :test #'string=)
		   (aref (cadr (assoc elt typespecs :test #'string=)) 1))
	  :do (format t "~
static void ~A_array_printer(char *label, const void *flob_, size_t len, char *pfix_)~%" elt)
	      (format t "~
{
    ~A *flob = (~A *)flob_;
    char pfix[1024];
    sprintf(pfix, \"%s    \", pfix_);
    size_t n = len / sizeof flob[0];
    fprintf(dbgout, \"%s%s: [\\n\", pfix_, label);
    for (size_t i = 0; i < n; ++i)
        ~A_printer(\"\", &flob[i], sizeof flob[i], pfix);
    fprintf(dbgout, \"%s]\\n\", pfix_);
};~2%" elt elt elt)))

;; dumpers
(defun make-attr-printer-list (name-list)
  (labels ((fmt (type keys)
	     (if (null keys)
		 (values)
		 (let ((key (car keys)))
		   (format t "        {~A, ~A},~%" key type)
		   (fmt type (cdr keys))))))
    (let* ((elements (assoc "NvSciBufAttrKey" name-list :test #'string=))
	   (prt-key-list
	     (loop :for elt :in (cadadr elements)
		   :collect (let* ((type (nth 1 elt))
				   ([ (position #\[ type))
				   (type (subseq type 0 [)))
			      (list (if [
					(format nil "~A_array_printer" type)
					(format nil "~A_printer" type))
				    (cddr elt))))))
      (format t "~
struct attrKey_printer_entry {
    NvSciBufAttrKey key;
    void (*printer)(char *, const void *, size_t, char *);
};~2%")

      (format t "~
int dump_kvp(NvSciBufAttrKey key, char *label, const void *value, size_t len)
{~%")
      (format t "~:
    struct attrKey_printer_entry key_printer_table[] = {~%")
      (loop :for elt :in prt-key-list
	    :do (fmt (car elt) (cadr elt)))
      (format t "    };~2%")
      (format t "~:
    for (size_t i = 0; i < ARRAY_LENGTH(key_printer_table); ++i)
        if (key_printer_table[i].key == key) {
            key_printer_table[i].printer(label, value, len, \"\");
            return 0;
        }
    return -1;
}

int dump_kvp_list(NvSciBufAttrKeyValuePair *kvp_list, size_t len)
{
    int rc = 0;
    size_t nr_err;

    for (size_t i = 0; i < len; ++i)
        if (kvp_list[i].len != 0) {
            char *label =
                 lookup_attr_name_table(kvp_list[i].key,
                                        NvSciBufAttrKey_names,
                                        ARRAY_LENGTH(NvSciBufAttrKey_names));
            rc = dump_kvp(kvp_list[i].key, label, kvp_list[i].value, kvp_list[i].len);
            if (rc == -1)
                nr_err -= 1;
        }

    return nr_err;
}~2%"))))

(defun make-preanble ()
  (format t "~
#include <stdio.h>

#include <nvscibuf.h>

extern FILE *dbgout;

#define ARRAY_LENGTH(a) (sizeof a / sizeof a[0])~2%"))

(defun make-attrkey-direction-list (name-list)
  (let ((name-list (assoc "NvSciBufAttrKey" name-list :test #'string=)))
    (labels ((make-key-list ()
	       (let ((attr-keys (cadadr name-list))
		     (in-keys (tq::qmake))
		     (out-keys (tq::qmake))
		     (io-keys (tq:qmake)))
		 (flet ((pushq (elt q)
			  (if (atom elt)
			      (tq:qpush elt q)
			      (loop :for elt :in elt
				    :do (tq:qpush elt q)))))
		   (loop :for elt :in attr-keys
			 :when (string= (car elt) "Input")
			   :do (pushq (nth 2 elt) in-keys)
			 :when (string= (car elt) "Output")
			   :do (pushq (nth 2 elt) out-keys)
			 :when (string= (car elt) "Input/Output")
			   :do (pushq (nth 2 elt) io-keys)
			 :finally (return (values (tq:qlist in-keys)
						  (tq:qlist out-keys)
						  (tq:qlist io-keys)))))))
	     (fmt-list (dir list)
	       (format t "    NvSciBufAttrKeyValuePair ~A_attr_kvp[] = {~%" dir)
	       (loop :for elt :in list
		     :do (format t "        {~A, NULL, 0},~%" elt))
	       (format t "    };~2%")))
      (multiple-value-bind (in out io) (make-key-list)
	(format t "~
void dump_attr_list(NvSciBufModule module, NvSciBufAttrList attr_list)
{~%")
	(fmt-list "in" in)
	(fmt-list "out" out)
	(fmt-list "io" io)
	(format t "~:
    NvSciError rc;

    rc = NvSciBufAttrListGetAttrs(attr_list, io_attr_kvp, ARRAY_LENGTH(io_attr_kvp));
    if (rc != NvSciError_Success) {
        fprintf(dbgout, \"%s: NvSciBufAttrListGetAttrs(io_attr_kvp): error:%x\\n\", __func__, rc);
        return;
    }
    dump_kvp_list(io_attr_kvp, ARRAY_LENGTH(io_attr_kvp));

    bool reconciled;
    rc = NvSciBufAttrListIsReconciled(attr_list, &reconciled);
    if (rc != NvSciError_Success) {
        fprintf(dbgout, \"%s: NvSciBufAttrListIsReconciled: error:%x\\n\", __func__, rc);
        return;
    }

    if (reconciled)
        rc = NvSciBufAttrListGetAttrs(attr_list, out_attr_kvp, ARRAY_LENGTH(out_attr_kvp));
    else
        rc = NvSciBufAttrListGetAttrs(attr_list, in_attr_kvp, ARRAY_LENGTH(in_attr_kvp));
    if (rc != NvSciError_Success) {
        fprintf(dbgout, \"%s: NvSciBufAttrListGetAttrs(%s): error:%x\\n\",
                __func__, reconciled ? \"out_attr_kvp\" : \"in_attr_kvp\", rc);
        return;
    }
    dump_kvp_list(reconciled ? out_attr_kvp : in_attr_kvp,
                  reconciled ? ARRAY_LENGTH(out_attr_kvp) : ARRAY_LENGTH(in_attr_kvp));
}~2%")))))

(defun make-printer (file-name)
  (let* ((name-list (parse-header-file file-name))
	 (typespecs (make-typespec-list name-list)))
    (make-preanble)
    (make-attr-name-table name-list)
    (make-scalar-printer name-list typespecs)
    (make-scalar-array-printer name-list typespecs)
    (make-enum-printer name-list typespecs)
    (make-struct-printer name-list typespecs)
    (make-struct-array-printer name-list typespecs)
    (make-attr-printer-list name-list)
    (make-attrkey-direction-list name-list)))

  
(defun main ()
  (with-open-file (os "c/scibuf_attr_printer.c" :direction :output
						:if-does-not-exist :create
						:if-exists :supersede)
    (let ((*standard-output* os))
      (make-printer "c/scibuf_types.h"))))
