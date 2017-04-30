(defun square (x) (* x x))

(defun times3 (y) (* 3 y))

(times3 (/ 1 (- 
                (+  2 
                    (let ((x 3)) (* x 3))) 
                (square 3))))