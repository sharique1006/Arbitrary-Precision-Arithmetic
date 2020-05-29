all : linklib run

linklib :
	@ gcc -c arbprecision.c
	@ ar cr libCB.a arbprecision.o
	@ gcc ComplexBignum.c -o mainfile -L. -lCB -lm
	
run :
	./mainfile input.txt output.txt plot.png
