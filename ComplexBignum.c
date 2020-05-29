#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include "CB.h"
#include <complex.h>
#include <time.h>

#define MAXCOM 100000
#define MAXLIST 100000

void ParsebySpace(char* st, char **stripe) {
	for (int i = 0; i < MAXLIST; i++) { 
		stripe[i] = strsep(&st, " ");
		if(stripe[i] == NULL) 
			break;
	}
}

char* get_real(char *stripped1) {
	char *rn = malloc(strlen(stripped1)*sizeof(int));
	int counter = 1;
	int index = 0;
	for(counter = 1; counter < strlen(stripped1); counter++) {
		if(stripped1[counter] != ',') {
			rn[index] = stripped1[counter];
			index++;
		}
		else {
			break;
		}
	}
	rn[index] = '\0';
	return rn;
}

char* get_complex(char *stripped2) {
	int counter = 1;
	int index = 0;
	for(counter = 1; counter < strlen(stripped2); counter++) {
		if(stripped2[counter] == ',') {
			break;
		}
	}
	char *cn = malloc(strlen(stripped2)*sizeof(int));
	for(int j = counter + 1; j < strlen(stripped2)-1; j++) {
		cn[index] = stripped2[j];
		index++;
	}
	cn[index] = '\0';
	return cn;
}

char* remove_zeroes (char *num) {
	if(num[0] == '.') {
		char *fnum2 = malloc((strlen(num)+1)*sizeof(int));
		fnum2[0] = '0';
		for(int i = 0; i < strlen(num); i++) {
			fnum2[i+1] = num[i];
		}
		fnum2[strlen(num)+1] = '\0';
		num = malloc(strlen(fnum2)*sizeof(int));
		num = fnum2;
	}
	int dec_pos = -1;
	for(int i = 0; i < strlen(num); i++) {
		if(num[i] == '.') {
			dec_pos = i;
			break;
		}
	}
	if(dec_pos != -1) {
		int last_non_zero = -1;
		for(int i = strlen(num)-1; i > dec_pos; i--) {
			if(num[i] != '0') {
				last_non_zero = i;
				break;
			}
		}
		if(last_non_zero == -1) {
			char *fnum2 = malloc(strlen(num)*sizeof(int));
			for(int i = 0; i < strlen(num); i++) {
				fnum2[i] = num[i];
			}
			fnum2[dec_pos] = '\0';
			num = malloc(strlen(fnum2)*sizeof(int));
			num = fnum2;
		}
		else if(last_non_zero != -1) {
			if(last_non_zero == dec_pos) {
				char *fnum2 = malloc(strlen(num)*sizeof(int));
				for(int  i = 0; i < dec_pos; i++) {
					fnum2[i] = num[i];
				}
				fnum2[last_non_zero+1] = '\0';
				num = malloc(strlen(fnum2)*sizeof(int));
				num = fnum2;
			}
			else if(last_non_zero != dec_pos) {
				char *fnum2 = malloc(strlen(num)*sizeof(int));
				for(int  i = 0; i < last_non_zero+1; i++) {
					fnum2[i] = num[i];
				}
				fnum2[last_non_zero+1] = '\0';
				num = malloc(strlen(fnum2)*sizeof(int));
				num = fnum2;
			}
		}
	}
	return num;
}

void plotGraph(const char gg[]) {
    FILE * pipe = popen ("gnuplot -persistent", "w");	
	fprintf(pipe,"set style data histograms\n");
    fprintf(pipe,"set style fill solid\n");
    fprintf(pipe,"plot 'data.txt' using 2:xtic(1) title 'Own Library' lt rgb '#406090', '' using 3 title 'C Library' lt rgb '#40FF00'\n");
	fprintf(pipe,"set term png\n");
	fprintf(pipe,"set output '%s'\n",gg);	
	fprintf(pipe,"replot\n");
}

int main (int argc, char *argv[]) {
	char *inp = NULL; 
	char* stripped[MAXLIST];
	FILE *fptr1, *fptr2;
	FILE * temp = fopen("data.txt", "w");

	if((fptr1 = fopen(argv[1], "r")) == NULL) {
		printf("%s\n", "Error! opening file");
		exit(1);
	}
	freopen(argv[2], "w", stdout);

	double time_taken1, time_taken2;
	clock_t start, end;
	size_t len = 0;
	while(getline(&inp, &len, fptr1) != 1) {

		inp[strlen(inp)-1] = '\0';
		ParsebySpace(inp, stripped);

		if(strcmp(stripped[0], "ADD") == 0) {
			char *real_first_number = get_real(stripped[1]);
			char *complex_first_number = get_complex(stripped[1]);
			char *real_second_number = get_real(stripped[2]);
			char *complex_second_number = get_complex(stripped[2]);
			start = clock();
			char *sum_real_part = remove_zeroes(BIGNUM_ADD(real_first_number, real_second_number));
			char *sum_complex_part = remove_zeroes(BIGNUM_ADD(complex_first_number, complex_second_number));
			end = clock();
			time_taken1 = (double)(end - start)/(double)(CLOCKS_PER_SEC);

			double rp1 = strtod(real_first_number,NULL);
			double cp1 = strtod(complex_first_number,NULL);
			double rp2 = strtod(real_second_number,NULL);
			double cp2 = strtod(complex_second_number,NULL);
			double complex z1 = rp1 + cp1 * I;
    		double complex z2 = rp2 + cp2 * I;
    		start = clock();
    		double complex sum = z1 + z2;
    		end = clock();
    		time_taken2 = (double)(end-start)/(double)(CLOCKS_PER_SEC);

    		printf("%s", "(");
			printf("%s", sum_real_part);
			printf("%s", ",");
			printf("%s", sum_complex_part);
			printf("%s\n", ")");

			fprintf(temp, "ADD %lf %lf \n", time_taken1,time_taken2);
		}
		if(strcmp(stripped[0], "SUB") == 0) {
			char *real_first_number = get_real(stripped[1]);
			char *complex_first_number = get_complex(stripped[1]);
			char *real_second_number = get_real(stripped[2]);
			char *complex_second_number = get_complex(stripped[2]);
			start = clock();
			char *sub_real_part = remove_zeroes(BIGNUM_SUB(real_first_number, real_second_number));
			char *sub_complex_part = remove_zeroes(BIGNUM_SUB(complex_first_number, complex_second_number));
			end = clock();
			time_taken1 = (double)(end - start)/(double)(CLOCKS_PER_SEC);

			double rp1 = strtod(real_first_number,NULL);
			double cp1 = strtod(complex_first_number,NULL);
			double rp2 = strtod(real_second_number,NULL);
			double cp2 = strtod(complex_second_number,NULL);
			double complex z1 = rp1 + cp1 * I;
    		double complex z2 = rp2 + cp2 * I;
    		start = clock();
    		double complex difference = z1 - z2;
    		end = clock();
    		time_taken2 = (double)(end-start)/(double)(CLOCKS_PER_SEC);

    		printf("%s", "(");
			printf("%s", sub_real_part);
			printf("%s", ",");
			printf("%s", sub_complex_part);
			printf("%s\n", ")");

			fprintf(temp, "SUB %lf %lf \n", time_taken1,time_taken2);
		}
		if(strcmp(stripped[0], "PROD") == 0) {
			char *real_first_number = get_real(stripped[1]);
			char *complex_first_number = get_complex(stripped[1]);
			char *real_second_number = get_real(stripped[2]);
			start = clock();
			char *complex_second_number = get_complex(stripped[2]);
			char *mult_real_part = remove_zeroes(BIGNUM_SUB(BIGNUM_MULT(real_first_number, real_second_number) , BIGNUM_MULT(complex_first_number, complex_second_number)));
			char *mult_complex_part = remove_zeroes(BIGNUM_ADD(BIGNUM_MULT(real_first_number, complex_second_number), BIGNUM_MULT(complex_first_number, real_second_number)));
			end = clock();
			time_taken1 = (double)(end-start)/(double)(CLOCKS_PER_SEC);

			double rp1 = strtod(real_first_number,NULL);
			double cp1 = strtod(complex_first_number,NULL);
			double rp2 = strtod(real_second_number,NULL);
			double cp2 = strtod(complex_second_number,NULL);
			double complex z1 = rp1 + cp1 * I;
    		double complex z2 = rp2 + cp2 * I;
    		start = clock();
    		double complex product = z1 * z2;
    		end = clock();
    		time_taken2 = (double)(end-start)/(double)(CLOCKS_PER_SEC);

    		printf("%s", "(");
			printf("%s", mult_real_part);
			printf("%s", ",");
			printf("%s", mult_complex_part);
			printf("%s\n", ")");

			fprintf(temp, "PROD %lf %lf \n", time_taken1,time_taken2);
		}
		if(strcmp(stripped[0], "ABS") == 0) {
			char *real_first_number = get_real(stripped[1]);
			char *complex_first_number = get_complex(stripped[1]);
			start = clock();
			char *abs_result = remove_zeroes(BIGNUM_COMPLEX_MOD_ABS(real_first_number, complex_first_number));
			end = clock();
			time_taken1 = (double)(end-start)/(double)(CLOCKS_PER_SEC);

			double rp1 = strtod(real_first_number,NULL);
			double cp1 = strtod(complex_first_number,NULL);
			double complex z1 = rp1 + cp1 * I;
			start = clock();
			double complex conjugate = cabs(z1);
    		end = clock();
    		time_taken2 = (double)(end-start)/(double)(CLOCKS_PER_SEC);

    		printf("%s", "(");
    		printf("%s", abs_result);
    		printf("%s\n", ",0)");

			fprintf(temp, "ABS %lf %lf \n", time_taken1,time_taken2);
		}
		if(strcmp(stripped[0], "QUOT") == 0) {
			char *real_first_number = get_real(stripped[1]);
			char *complex_first_number = get_complex(stripped[1]);
			char *real_second_number = get_real(stripped[2]);
			char *complex_second_number = get_complex(stripped[2]);
			start = clock();
			char *div_real_part = remove_zeroes(BIGNUM_DIV(BIGNUM_ADD(BIGNUM_MULT(real_first_number, real_second_number) , BIGNUM_MULT(complex_first_number, complex_second_number)), BIGNUM_MULT(BIGNUM_COMPLEX_MOD_ABS(real_second_number, complex_second_number), BIGNUM_COMPLEX_MOD_ABS(real_second_number, complex_second_number)) ));
			char *div_complex_part = remove_zeroes(BIGNUM_DIV(BIGNUM_SUB(BIGNUM_MULT(complex_first_number, real_second_number), BIGNUM_MULT(real_first_number, complex_second_number)), BIGNUM_MULT(BIGNUM_COMPLEX_MOD_ABS(real_second_number, complex_second_number), BIGNUM_COMPLEX_MOD_ABS(real_second_number, complex_second_number)) ));
			end = clock();
			time_taken1 = (double)(end-start)/(double)(CLOCKS_PER_SEC);
			
			double rp1 = strtod(real_first_number,NULL);
			double cp1 = strtod(complex_first_number,NULL);
			double rp2 = strtod(real_second_number,NULL);
			double cp2 = strtod(complex_second_number,NULL);
			double complex z1 = rp1 + cp1 * I;
    		double complex z2 = rp2 + cp2 * I;
    		start = clock();
    		double complex quotient = z1 / z2;
    		end = clock();
    		time_taken2 = (double)(end-start)/(CLOCKS_PER_SEC);

    		printf("%s", "(");
			printf("%s", div_real_part);
			printf("%s", ",");
			printf("%s", div_complex_part);
			printf("%s\n", ")");

			fprintf(temp, "QUOT %lf %lf \n", time_taken1,time_taken2);
		}
	}
	plotGraph(argv[3]);
	return 0;
}
