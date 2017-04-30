(defun square (x) (* x x))

(defun times3 (x) (* 3 x))

(times3 (/ 1 (- 
                (+  2 
                    (let ((x 3)) (* x 3))) 
                (square 4))))