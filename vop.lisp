(defpackage :mp4-12
  (:use :cl :sb-ext :sb-alien :sb-c))

(in-package :mp4-12)

(defknown %make-4cc (simple-string sb-impl::index) (unsigned-byte 32)
    (movable foldable flushable)
  :overwrite-fndb-silently t)

#+nil
(eval-when (:compile-toplevel :load-toplevel :execute)
  (defparameter *saved-package* *package*))

(in-package :sb-vm)

(define-vop (mp4-12::%make-4cc)
  (:policy :fast-safe)
  (:translate mp4-12::%make-4cc)
  (:args (object :scs (descriptor-reg control-stack))
	 (index :scs (unsigned-reg control-stack)))
  (:arg-types * positive-fixnum)
  (:temporary (:sc unsigned-reg :offset rdx-offset) acc)
  (:temporary (:sc unsigned-reg) base)
  (:results (value :scs (unsigned-reg)))
  (:result-types unsigned-num)
  (:vop-var vop)
  (:generator 1
    (inst xor :dword acc acc)
    (inst lea base
	  (ea (- (* vector-data-offset n-word-bytes) other-pointer-lowtag)
	      object index 4))
    (inst mov :dword value (ea 0 base))
    (inst shl :dword value 24)
    (inst or :dword acc value)
    (inst mov :dword value (ea 4 base))
    (inst shl :dword value 16)
    (inst or :dword acc value)
    (inst mov :dword value (ea 8 base))
    (inst shl :dword value 8)
    (inst or :dword acc value)
    (inst mov :dword value (ea 12 base))
    (inst shl :dword value 0)
    (inst or :dword acc value)
    (move value acc)))

;(in-package :wb)
(in-package :mp4-12)

(defun make-4cc (object index)
  (declare (type simple-array object)
	   (type fixnum index))
  (%make-4cc object index))

