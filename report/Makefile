.PHONY: all clean

PDFFILES=bihel_ferry_7colors.pdf

all: $(PDFFILES)

%.pdf: %.tex
	pdflatex $(@:.pdf=.tex)
	pdflatex $(@:.pdf=.tex)

clean:
	rm -f $(PDFFILES)
	rm *.log *.aux
