all :
	texi2pdf report.tex

clean :
	rm *.aux
	rm *.log
	rm *.blg
	rm *.bbl
