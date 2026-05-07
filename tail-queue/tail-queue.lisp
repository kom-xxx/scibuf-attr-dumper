;;;
;;; TAILQ
;;;
(in-package :cl-user)

(defpackage :tail-queue
  (:nicknames :tq)
  (:use :cl)
  (:export #:tq #:qmake #:qempty #:qhead #:qtail #:qlist
	   #:qpush #:qpull #:qpop #:qappend))

(cl:in-package :tq)

(deftype tq (element-type)
  `(or  (cons (cons ,element-type list) (cons ,element-type null))
	(cons null null)))

(declaim (inline qmake qempty qhead qtail qlist)
	 (ftype (function () (tq t)) qmake)
	 (ftype (function ((tq t)) boolean) qempty)
	 (ftype (function ((tq t)) t) qhead)
	 (ftype (function ((tq t)) boolean) qtail)
	 (ftype (function ((tq t)) list) qlist)
	 (ftype (function (t (tq t)) (tq t)) qpush)
	 (ftype (function ((tq t)) t) qpull)
	 (ftype (function ((tq t)) t) qpop)
	 (ftype (function ((tq t) &rest list) (tq t)) qappend))

(locally
    (declare (optimize (speed 3) (safety 0) (debug 0) (compilation-speed 0)))
  (defun qmake ()
    (cons nil nil))

  (defun qempty (q)
    (declare (type (tq t) q))
    (null (car q)))

  (defun qhead (q)
    (declare (type (tq t) q))
    (caar q))

  (defun qtail (q)
    (declare (type (tq t) q))
    (cadr q))

  (defun qlist (q)
    (declare (type (tq t) q))
    (car q))

  (defun qpush (elt q)
    (declare (type (tq t) q))
    (let ((elt (cons elt nil)))
      (if (car q)
	  (setf (cddr q) elt)
	  (setf (car q) elt))
      (setf (cdr q) elt))
    q)

  (defun qpull (q)
    (declare (type (tq t) q))
    (prog1 (caar q)
      (setf (car q) (cdar q))
      (unless (car q)
	(setf (cdr q) nil))))

  (defun qpop (q)
    (declare (type (tq t) q))
    (if (qempty q)
	nil
	(let ((list (car q)))
	  (declare (type list list))
	  (prog1
	      (cadr q)
	    (if (eq (car q) (cdr q))
		(setf (car q) nil
		      (cdr q) nil)
		(setf (cdr (last list 2)) nil
		      (cdr q) (last list)))))))

  (defun qappend (q &rest args)
    (dolist (q2 args)
      (setf (cddr q) (car q2)
	    (cdr q) (cdr q2)))
    q))
