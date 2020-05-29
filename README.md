# Arbitrary-Precision-Arithmetic
Arbitrary-Precision arithmetic, also known as "bignum" or simply "long arithmetic" is a set of data structures and algorithms which allows to process much greater numbers than can be fit in standard data types. In this assignment you will write an efficient  program to implement "bignum".

In this assignment, you have to implement complex arithmetic which works with numbers having arbitrary precison.

Basic operations which are needed to be implemented are: Addition, Subtraction,Product, abs and Quotient.

Your code should run like: ./mainfile input.txt output.txt plot.png

Input.txt (i.e. the input file) will contain the different queries, corresponding to each arithmetic operations.

Query Format: Each line of input file corresponds to a query which is in the format: <Operator><SPACE>(R1,C1)<SPACE>(R2,C2)
Where Ri= Real part and Ci=Imaginary part of the complex number.

Operator can be one of the strings: ADD, SUB,ABS, PROD,QUOT 
Operand will be String(ordered pair) representing a complex number with real and imaginary part.

For each query, you have to print a single lined output in Output.txt which is also a string(ordered pair).

You need to handle the cases where the operand or results are negative values.

Please refer to sample input files with corresponding output files for further details.

For floating point results the precision should be correct up to 20 digits after decimal point.

Moreover, you also need to plot the bar graph that shows the comparison of the running times of the complex arithmetic using arbprecision and the standard C library implementation . The comparison has to be shown for each operation in the same graph
