#replace the basename of the file below (w/o .tex extention)
bname=example
src=${bname}.tex
tgt=${bname}.pdf

default:	${src}
	@pdflatex ${src}
	@pdflatex ${src}
	@ls -ltr ${tgt}

open:	default
	-@[ "$(shell uname -s)" == "Darwin" ] && open ${tgt} || echo "[e] Open failed - should work on OS X."

clean:
	@rm -rfv *.out *.log *.aux *.gz

cleanall: clean
	@rm -rfv ${tgt}
