(defun gps-line ()
  "Print the current buffer line number and narrowed line number of point."
  (interactive)
  (let ((start (point-min))
	(n (line-number-at-pos)))
    "Pull total lines from page--...command and use the 1st element(total lines)"
    (setq x (nth 0 (page--count-lines-page)))
    (if (= start 1)
	(message "Line %d/%d" n x)
      (save-excursion
	(save-restriction
	  (widen)
	  (message "line %d (narrowed line %d)"
		   (+ n (line-number-at-pos start) -1) n))))))
  
