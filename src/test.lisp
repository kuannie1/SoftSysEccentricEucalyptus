(defun square (x) (* x x))

(/ 1 (- (+ 2 (let ((x 3)) (* x 3))) (square 3)))