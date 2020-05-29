#include <stdlib.h>
#include <stdio.h>
#include <string.h> 

char* BIGNUM_ADD(char *num1, char *num2);
char* BIGNUM_SUB(char *num1, char *num2);
char* BIGNUM_MULT(char *num1, char *num2);
char* BIGNUM_DIV(char *num1, char *num2);
char* BIGNUM_SQUAREROOT(char *num);
char* BIGNUM_COMPLEX_MOD_ABS(char *num1, char *num2);

int minimum(int a, int b) {
	if(a < b) {
		return a;
	}
	return b;
}

int maximum(int a, int b) {
	if(a > b) {
		return a;
	}
	return b;
}

int find_decimal_position (char *num) {
	int length = strlen(num);
	for (int i = 0; i < length; i++) {
		if(num[i] == '.') {
			return i;
		}
	}
	return -1;
}

//compare two numbers of equal length which may have decimal point in it
int compare_num(char *num1 , char *num2) {
	int x = 0;
	for (int i = 0; i < strlen(num1); i++) {
		if(num1[i] > num2[i]) {
			x = 1;
			break;
		}
		else if(num1[i] < num2[i]) {
			x = -1;
			break;
		}
		else if (num1[i] == num2[i]) {
			x = 0;
		}
	}
	return x;
}

//compare any two numbers which does not have decimal point 
int any_num_compare(char *num1, char *num2) {
	int x = 0;
	if(strlen(num1) > strlen(num2)) {
		x = 1;
	}
	else if(strlen(num2) > strlen(num1)) {
		x = -1;
	}
	else if(strlen(num1) == strlen(num2)) {
		for (int i = 0; i < strlen(num1); i++) {
			if(num1[i] > num2[i]) {
				x = 1;
				break;
			}
			else if(num1[i] < num2[i]) {
				x = -1;
				break;
			}
			else if (num1[i] == num2[i]) {
				x = 0;
			}
		}
	}
	return x;
}

char* BIGNUM_ADD (char *first, char *second) {
	if(first[0] == '-' && second[0] != '-') {
		char *tfirst = malloc((strlen(first)-1)*sizeof(int));
		for (int i = 1; i < strlen(first); i++) {
			tfirst[i-1] = first[i];
		}
		tfirst[strlen(first)-1] = '\0';
		char* sum = BIGNUM_SUB(second, tfirst);
		return sum;
	}
	if(first[0] == '-' && second[0] == '-') {
		char *tfirst = malloc((strlen(first)-1)*sizeof(int));
		for (int i = 1; i < strlen(first); i++) {
			tfirst[i-1] = first[i];
		}
		tfirst[strlen(first)-1] = '\0';
		char *tsecond = malloc((strlen(second)-1)*sizeof(int));
		for (int i = 1; i < strlen(second); i++) {
			tsecond[i-1] = second[i];
		}
		tsecond[strlen(second)-1] = '\0';
		char* sum = BIGNUM_ADD(tfirst, tsecond);
		char *final_sum = malloc((strlen(sum) + 1)*sizeof(int));
		final_sum[0] = '-';
		for (int i = 0; i < strlen(sum); i++) {
			final_sum[i+1] = sum[i];
		}
		final_sum[strlen(sum)+1] = '\0';
		return final_sum;
	}
	if(first[0] != '-' && second[0] == '-') {
		char *tsecond = malloc((strlen(second)-1)*sizeof(int));
		for (int i = 1; i < strlen(second); i++) {
			tsecond[i-1] = second[i];
		}
		tsecond[strlen(second)-1] = '\0';
		char* sum = BIGNUM_SUB(first, tsecond);
		return sum;
	}
	if(first[0] != '-' && second[0] != '-') {
		int l1 = strlen(first);
		int l2 = strlen(second);
		int bf1 = 0, bf2 = 0, af1 = 0, af2 = 0;
		char *num1 = malloc(l1*sizeof(int));
		char *num2 = malloc(l2*sizeof(int));
		char *sum;
		int bdf = find_decimal_position(first);
		int bds = find_decimal_position(second);
		if(bdf == -1 && bds == -1) {
			char *dec = ".0";
			strcpy(num2, second);
			strcat(first, dec);
			second = num2;
			bdf = find_decimal_position(first);
			l1 = strlen(first);
			strcat(second, dec);
			l2 = strlen(second);
			bds = find_decimal_position(second);
		}
		if(bdf == -1 && bds != -1) {
			char *dec = ".0";
			strcpy(num2, second);
			strcat(first, dec);
			second = num2;
			bdf = find_decimal_position(first);
			l1 = strlen(first);
		}
		if(bds == -1 && bdf != -1) {
			char *dec = ".0";
			strcat(second, dec);
			l2 = strlen(second);
			bds = find_decimal_position(second);
		}
		int adf = l1 - bdf - 1;
		int ads = l2 - bds - 1;
		int bdmax = maximum(bdf, bds);
		int admax = maximum(adf, ads);
		if(adf > ads) {
			af1 = 1;
		}
		else if(adf < ads){
			af2 = 1;
		}
		if(bdf > bds) {
			bf1 = 1;
		}
		else if(bdf < bds) {
			bf2 = 1;
		}
		if(af1 == 1) {
			for(int i = 0; i < admax - ads; i++) {
				char *zero = "0";
				strcat(second, zero);
			}
		}
		else if (af2 == 1) {
			for(int i = 0; i < admax - adf; i++) {
				if(i == 0) {
					strcpy(num2, second);
				}
				char *zero = "0";
				strcat(first, zero);
			}
			second = num2;
		}
		l1 = strlen(first);
		l2 = strlen(second);
		int carry = 0;
		sum = malloc((maximum(l1,l2) + 1)*sizeof(int));
		for (int i = 0; i < minimum(l1, l2); i++) {
			if(first[l1-1-i] != '.') {
				int a = first[l1-1-i] - '0';
				int b = second[l2-1-i] - '0';
				int c = carry + a + b;
				if (c >= 10) {
					c = c-10;
					carry = 1;
				}
				else {
					carry = 0;
				}
				char s = c + '0';
				sum[i] = s;
			}
			else {
				sum[i] = '.';
			}
		}
		if(bf1 == 0 && bf2 == 0 && carry == 1) {
			sum[minimum(l1, l2)] = '1';
			sum[minimum(l1,l2) + 1] = '\0';
		}
		else if (bf1 == 0 && bf2 == 0 && carry == 0) {
			sum[minimum(l1,l2)] = '\0';
		}
		else if(bf1 == 1) {
			for (int i = 0; i < bdmax - bds; i++) {
				int a = first[l1-l2-1-i] - '0';
				int c = carry + a;
				if(c >= 10) {
					c = c-10;
					carry = 1;
				}
				else {
					carry = 0;
				}
				char s = c + '0';
				sum[l2+i] = s;
			}
			if(carry == 1) {
				sum[l2+bdmax-bds] = '1';
				sum[l2+bdmax-bds] = '\0';
			}
			else if (carry == 0) {
				sum[l2+bdmax-bds] = '\0';
			}
		}
		else if(bf2 == 1) {
			for (int i = 0; i < bdmax - bdf; i++) {
				int a = second[l2-l1-1-i] - '0';
				int c = carry + a;
				if(c >= 10) {
					c = c-10;
					carry = 1;
				}
				else {
					carry = 0;
				}
				char s = c + '0';
				sum[l1+i] = s;
			}
			if(carry == 1) {
				sum[l1+bdmax-bdf] = '1';
				sum[l1+bdmax-bdf] = '\0';
			}
			else if (carry == 0) {
				sum[l1+bdmax-bdf] = '\0';
			}
		}
		char *final_sum = malloc(strlen(sum)*sizeof(int));
		for (int i = 0; i < strlen(sum); i++) {
			final_sum[strlen(sum)-1-i] = sum[i];
		}
		final_sum[strlen(sum)] = '\0';
		return final_sum;
	}
}

char* BIGNUM_SUB(char *first, char *second) {
	if(first[0] == '-' && second[0] != '-') {
		char *tfirst = malloc((strlen(first)-1)*sizeof(int));
		for (int i = 1; i < strlen(first); i++) {
			tfirst[i-1] = first[i];
		}
		tfirst[strlen(first)-1] = '\0';
		char* sub = BIGNUM_ADD(tfirst, second);
		char *final_sub = malloc((strlen(sub) + 1)*sizeof(int));
		final_sub[0] = '-';
		for (int i = 0; i < strlen(sub); i++) {
			final_sub[i+1] = sub[i];
		}
		final_sub[strlen(sub)+1] = '\0';
		return final_sub;
	}
	if(first[0] == '-' && second[0] == '-') {
		char *tfirst = malloc((strlen(first)-1)*sizeof(int));
		for (int i = 1; i < strlen(first); i++) {
			tfirst[i-1] = first[i];
		}
		tfirst[strlen(first)-1] = '\0';
		char *tsecond = malloc((strlen(second)-1)*sizeof(int));
		for (int i = 1; i < strlen(second); i++) {
			tsecond[i-1] = second[i];
		}
		tsecond[strlen(second)-1] = '\0';
		char* sub = BIGNUM_SUB(tsecond, tfirst);
		return sub;
	}
	if(first[0] != '-' && second[0] == '-') {
		char *tsecond = malloc((strlen(second)-1)*sizeof(int));
		for (int i = 1; i < strlen(second); i++) {
			tsecond[i-1] = second[i];
		}
		tsecond[strlen(second)-1] = '\0';
		char* sub = BIGNUM_ADD(first, tsecond);
		return sub;
	}
	int l1 = strlen(first);
	int l2 = strlen(second);
	int bf1 = 0, bf2 = 0, af1 = 0, af2 = 0;
	char *num1 = malloc(l1*sizeof(int));
	char *num2 = malloc(l2*sizeof(int));
	char *sub;
	int bdf = find_decimal_position(first);
	int bds = find_decimal_position(second);
	if(bdf == -1 && bds == -1) {
		char *dec = ".0";
		strcpy(num2, second);
		strcat(first, dec);
		second = num2;
		bdf = find_decimal_position(first);
		l1 = strlen(first);
		strcat(second, dec);
		l2 = strlen(second);
		bds = find_decimal_position(second);
	}
	if(bdf == -1 && bds != -1) {
		char *dec = ".0";
		strcpy(num2, second);
		strcat(first, dec);
		second = num2;
		bdf = find_decimal_position(first);
		l1 = strlen(first);
	}
	if(bds == -1 && bdf != -1) {
		char *dec = ".0";
		strcat(second, dec);
		l2 = strlen(second);
		bds = find_decimal_position(second);
	}
	int adf = l1 - bdf - 1;
	int ads = l2 - bds - 1;
	int bdmax = maximum(bdf, bds);
	int admax = maximum(adf, ads);
	if(adf > ads) {
		af1 = 1;
	}
	else if(adf < ads){
		af2 = 1;
	}
	if(bdf > bds) {
		bf1 = 1;
	}
	else if(bdf < bds) {
		bf2 = 1;
	}
	if(af1 == 1) {
		for(int i = 0; i < admax - ads; i++) {
			char *zero = "0";
			strcat(second, zero);
		}
	}
	else if (af2 == 1) {
		for(int i = 0; i < admax - adf; i++) {
			if(i == 0) {
				strcpy(num2, second);
			}
			char *zero = "0";
			strcat(first, zero);
		}
		second = num2;
	}
	int ans_zero = 0;
	l1 = strlen(first);
	l2 = strlen(second);
	int x1signal = 0, x2signal = 0, equal_less = 0;
	for (int we = 0; we < strlen(first); we++) {
		if(first[we] == '0' || first[we] == '.') {
			x1signal = 1;
		}
		else {
			x1signal = 0;
			break;
		}
	}
	for (int we = 0; we < strlen(second); we++) {
		if(second[we] == '0' || second[we] == '.') {
			x2signal = 1;
		}
		else {
			x2signal = 0;
			break;
		}
	}
	if(x1signal == 1) {
		char *ans = malloc((strlen(second)+2)*sizeof(int));
		ans[0] = '-';
		for(int wer = 0; wer < strlen(second); wer++) {
			ans[wer+1] = second[wer]; 
		}
		ans[strlen(second)+1] = '\0';
		return ans;
	}
	if(x2signal == 1) {
		return first;
	}
	int carry = 0;
	sub = malloc(maximum(l1, l2) * sizeof(int));
	if(l1 > l2) {
		for (int i = 0; i < minimum(l1,l2); i++) {
			if(first[l1-i-1] != '.') {
				int a = first[l1-i-1] - '0';
				int b = second[l2-i-1] - '0';
				int diff = a-b+carry;
				if (diff < 0) {
					diff = 10 + diff;
					carry = -1;
				}
				else {
					carry = 0;
				}
				char d = diff + '0';
				sub[i] = d; 
			}
			else {
				sub[i] = '.';
			}
		}
		for (int i = 0; i < bdmax-bds; i++) {
			int a = first[l1-l2-i-1] - '0';
			int diff = a + carry;
			if(diff < 0) {
				diff = diff + 10;
				carry = -1;
			}
			else {
				carry = 0;
			}
			char d = diff + '0';
			sub[l2+i] = d;
		}
		sub[l2+bdmax-bds] = '\0';
	}
	if(l1 < l2) {
		for (int i = 0; i < minimum(l1,l2); i++) {
			if(first[l1-i-1] != '.') {
				int a = first[l1-i-1] - '0';
				int b = second[l2-i-1] - '0';
				int diff = b-a+carry;
				if (diff < 0) {
					diff = 10 + diff;
					carry = -1;
				}
				else {
					carry = 0;
				}
				char d = diff + '0';
				sub[i] = d; 
			}
			else {
				sub[i] = '.';
			}
		}
		for (int i = 0; i < bdmax-bdf; i++) {
			int a = second[l2-l1-i-1] - '0';
			int diff = a + carry;
			if(diff < 0) {
				diff = diff + 10;
				carry = -1;
			}
			else {
				carry = 0;
			}
			char d = diff + '0';
			sub[l1+i] = d;
		}
		sub[l1+bdmax-bdf] = '-';
		sub[l1+bdmax-bdf+1] = '\0';
	}
	if(l1 == l2) {
		int compare = compare_num(first, second);
		if(compare == 1) {
			for (int i = 0; i < l1; i++) {
				if(first[l1-i-1] != '.') {
					int a = first[l1-i-1] - '0';
					int b = second[l2-i-1] - '0';
					int diff = a-b+carry;
					if (diff < 0) {
						diff = 10 + diff;
						carry = -1;
					}
					else {
						carry = 0;
					}
					char d = diff + '0';
					sub[i] = d; 
				}
				else {
					sub[i] = '.';
				}
			}
			sub[l1] = '\0';
		}
		else if(compare == -1 || compare == 0) {
			for (int i = 0; i < l1; i++) {
				if(first[l1-i-1] != '.') {
					int a = first[l1-i-1] - '0';
					int b = second[l2-i-1] - '0';
					int diff = b-a+carry;
					if (diff < 0) {
						diff = 10 + diff;
						carry = -1;
					}
					else {
						carry = 0;
					}
					char d = diff + '0';
					sub[i] = d; 
				}
				else {
					sub[i] = '.';
				}
			}
			if(compare == 0) {
				ans_zero = 1;
				sub[l1] = '\0';
			}
			else {
				equal_less = 1;
				sub[l1] = '\0';
			}
		}
	}
	int p = 0, stop = 0;
	char *final_sub = malloc(strlen(sub)*sizeof(int));
	if(ans_zero == 1) {
		final_sub = "0.0";
	}
	else {
		for (int i = 0; i < strlen(sub); i++) {
			if(sub[strlen(sub)-1-i] != '0' && stop == 0) {
				final_sub[p] = sub[strlen(sub)-1-i];
				p++;
				stop = 1;
			}
			else if(stop == 1) {
				final_sub[p] = sub[strlen(sub)-1-i];
				p++;
			}
		}
		final_sub[p] = '\0';
	}
	if(equal_less == 1) {
		char *tfinal_sub = malloc(strlen(final_sub)*sizeof(int));
		tfinal_sub[0] = '-';
		for(int i = 0; i < strlen(final_sub); i++) {
			tfinal_sub[i+1] = final_sub[i];
		}
		tfinal_sub[strlen(final_sub+1)] = '\0';
		final_sub = malloc(strlen(tfinal_sub)*sizeof(int));
		final_sub = tfinal_sub;
	}
	return final_sub;
}

char* BIGNUM_MULT(char *first, char *second) {
	int sign = 0;
	if(first[0] == '-' && second[0] != '-') {
		char *tfirst = malloc((strlen(first)-1)*sizeof(int));
		for (int i = 1; i < strlen(first); i++) {
			tfirst[i-1] = first[i];
		}
		tfirst[strlen(first)-1] = '\0';
		first = malloc((strlen(first)-1)*sizeof(int));
		first = tfirst;
		first[strlen(tfirst)] = '\0';
		sign = 1;
	}
	else if(first[0] == '-' && second[0] == '-') {
		char *tfirst = malloc((strlen(first)-1)*sizeof(int));
		for (int i = 1; i < strlen(first); i++) {
			tfirst[i-1] = first[i];
		}
		tfirst[strlen(first)-1] = '\0';
		first = malloc((strlen(first)-1)*sizeof(int));
		first = tfirst;
		first[strlen(tfirst)] = '\0';
		char *tsecond = malloc((strlen(second)-1)*sizeof(int));
		for (int i = 1; i < strlen(second); i++) {
			tsecond[i-1] = second[i];
		}
		tsecond[strlen(second)-1] = '\0';
		second = malloc((strlen(first)-1)*sizeof(int));
		second = tsecond;
		second[strlen(tsecond)] = '\0';
	}
	else if(first[0] != '-' && second[0] == '-') {
		char *tsecond = malloc((strlen(second)-1)*sizeof(int));
		for (int i = 1; i < strlen(second); i++) {
			tsecond[i-1] = second[i];
		}
		tsecond[strlen(second)-1] = '\0';
		second = malloc((strlen(first)-1)*sizeof(int));
		second = tsecond;
		second[strlen(tsecond)] = '\0';
		sign = 1;
	}
	int l1 = strlen(first);
	int l2 = strlen(second);
	int bf1 = 0, bf2 = 0, af1 = 0, af2 = 0;
	char *num1 = malloc(l1*sizeof(int));
	char *num2 = malloc(l2*sizeof(int));
	char *sub;
	int bdf = find_decimal_position(first);
	int bds = find_decimal_position(second);
	if(bdf == -1 && bds == -1) {
		char *dec = ".0";
		strcpy(num2, second);
		strcat(first, dec);
		second = num2;
		bdf = find_decimal_position(first);
		l1 = strlen(first);
		strcat(second, dec);
		l2 = strlen(second);
		bds = find_decimal_position(second);
	}
	if(bdf == -1 && bds != -1) {
		char *dec = ".0";
		strcpy(num2, second);
		strcat(first, dec);
		second = num2;
		bdf = find_decimal_position(first);
		l1 = strlen(first);
	}
	if(bds == -1 && bdf != -1) {
		char *dec = ".0";
		strcat(second, dec);
		l2 = strlen(second);
		bds = find_decimal_position(second);
	}
	int adf = l1 - bdf - 1;
	int ads = l2 - bds - 1;
	int bdmax = maximum(bdf, bds);
	int admax = maximum(adf, ads);
	if(adf > ads) {
		af1 = 1;
	}
	else if(adf < ads){
		af2 = 1;
	}
	if(bdf > bds) {
		bf1 = 1;
	}
	else if(bdf < bds) {
		bf2 = 1;
	}
	int k1 = 0;
	char *n1 = malloc((strlen(first)-1)*sizeof(int));
	for (int i = 0; i < strlen(first); i++) {
		if(first[i] != '.') {
			n1[k1] = first[i];
			k1++;
		}
	}
	n1[strlen(first)-1] = '\0';
	int k2 = 0;
	char *n2 = malloc((strlen(second)-1)*sizeof(int));
	for (int i = 0; i < strlen(second); i++) {
		if(second[i] != '.') {
			n2[k2] = second[i];
			k2++;
		}
	}
	n2[strlen(second)-1] = '\0';
	int p1 = strlen(first) - bdf - 1;
	int p2 = strlen(second) - bds - 1;
	l1 = strlen(n1);
	l2 = strlen(n2);
	int carry = 0;
	char *final_mult;
	if (bf1 >= bf2) {
		char *muls = malloc((l1+l2+1)*sizeof(int));
		muls[0] = '0';
		muls[1] = '\0';
		for (int i = 0; i < l2; i++) {
			char *each_row = malloc((strlen(n1)+1)*sizeof(int));
			int a = n2[l2-1-i] - '0';
			for (int j = 0; j < strlen(n1); j++) {
				int b = n1[strlen(n1)-1-j] - '0';
				int mult = (a*b) + carry;
				if(mult >= 10) {
					carry = mult/10;
					mult = mult - carry*10;
				}
				else {
					carry = 0;
				}
				char mu = mult + '0';
				each_row[strlen(n1)-1-j] = mu; 
			}
			if(carry != 0) {
				char* teach_row = malloc((strlen(each_row)+1)*sizeof(int));
				teach_row[0] = carry + '0';
				for (int i = 0; i < strlen(each_row); i++) {
					teach_row[i+1] = each_row[i];  
				}
				teach_row[strlen(each_row)+1] = '\0';
				carry = 0;
				each_row = malloc((strlen(each_row)+1)*sizeof(int));
				each_row = teach_row;
				each_row[strlen(each_row)] = '\0';
				char* tn1 = malloc((strlen(n1)+1)*sizeof(int));
				for(int i = 0; i < strlen(n1); i++) {
					tn1[i] = n1[i];
				}
				tn1[strlen(n1)] = '0';
				tn1[strlen(n1)+1] = '\0';
				n1 = malloc((strlen(n1)+1)*sizeof(int));
				n1 = tn1;
			}
			else {
				each_row[strlen(n1)] = '\0';
				char* tn1 = malloc((strlen(n1)+1)*sizeof(int));
				for(int i = 0; i < strlen(n1); i++) {
					tn1[i] = n1[i];
				}
				tn1[strlen(n1)] = '0';
				tn1[strlen(n1)+1] = '\0';
				n1 = malloc((strlen(n1)+1)*sizeof(int));
				n1 = tn1;
			}
			if (i == 0) {
				muls = each_row;
			}
			else {
				muls = BIGNUM_ADD(muls, each_row);
			}
		}
		char *muls2 = malloc((strlen(muls)-1)*sizeof(int));
		for (int i = 0; i < strlen(muls); i++) {
			if(muls[i] != '.') {
				muls2[i] = muls[i];
			}
		}
		muls2[strlen(muls)] = '\0';
		final_mult = malloc((strlen(muls2) + 1)*sizeof(int));
		int pc = 0, kj = 0;
		for (int i = 0; i <= strlen(muls2); i++) {
			if((strlen(muls2) - p1 - p2) == i && kj == 0) {
				final_mult[pc] = '.'; 
				kj = 1;
				i = i-1;
			}
			else {
				final_mult[pc] = muls2[i];
			}
			pc++;
		}
		final_mult[strlen(muls2)+1] = '\0';
		if (sign == 1) {
			char *tfinal_mult = malloc((strlen(final_mult)+1)*sizeof(int));
			tfinal_mult[0] = '-';
			for (int i = 0; i < strlen(final_mult); i++) {
				tfinal_mult[i+1] = final_mult[i];
			}
			tfinal_mult[strlen(final_mult)+1] = '\0';
			final_mult = malloc(strlen(tfinal_mult)*sizeof(int));
			final_mult = tfinal_mult;
		}
	}
	else if(bf2 > bf1) {
		char *muls = malloc((l1+l2+1)*sizeof(int));
		muls[0] = '0';
		muls[1] = '\0';
		for (int i = 0; i < l1; i++) {
			char *each_row = malloc((strlen(n2)+1)*sizeof(int));
			int a = n1[l1-1-i] - '0';
			for (int j = 0; j < strlen(n2); j++) {
				int b = n2[strlen(n2)-1-j] - '0';
				int mult = (a*b) + carry;
				if(mult >= 10) {
					carry = mult/10;
					mult = mult - carry*10;
				}
				else {
					carry = 0;
				}
				char mu = mult + '0';
				each_row[strlen(n2)-1-j] = mu; 
			}
			if(carry != 0) {
				char* teach_row = malloc((strlen(each_row)+1)*sizeof(int));
				teach_row[0] = carry + '0';
				for (int i = 0; i < strlen(each_row); i++) {
					teach_row[i+1] = each_row[i];  
				}
				teach_row[strlen(each_row)+1] = '\0';
				carry = 0;
				each_row = malloc((strlen(each_row)+1)*sizeof(int));
				each_row = teach_row;
				each_row[strlen(each_row)] = '\0';
				char* tn2 = malloc((strlen(n2)+1)*sizeof(int));
				for(int i = 0; i < strlen(n2); i++) {
					tn2[i] = n2[i];
				}
				tn2[strlen(n2)] = '0';
				tn2[strlen(n2)+1] = '\0';
				n2 = malloc((strlen(n2)+1)*sizeof(int));
				n2 = tn2;
			}
			else {
				each_row[strlen(n2)] = '\0';
				char* tn2 = malloc((strlen(n2)+1)*sizeof(int));
				for(int i = 0; i < strlen(n2); i++) {
					tn2[i] = n2[i];
				}
				tn2[strlen(n2)] = '0';
				tn2[strlen(n2)+1] = '\0';
				n2 = malloc((strlen(n2)+1)*sizeof(int));
				n2 = tn2;
			}
			if (i == 0) {
				muls = each_row;
			}
			else {
				muls = BIGNUM_ADD(muls, each_row);
			}
		}
		char *muls2 = malloc((strlen(muls)-1)*sizeof(int));
		for (int i = 0; i < strlen(muls); i++) {
			if(muls[i] != '.') {
				muls2[i] = muls[i];
			}
		}
		muls2[strlen(muls)] = '\0';
		int pc = 0, kj = 0;
		final_mult = malloc((strlen(muls2) + 1)*sizeof(int));
		for (int i = 0; i <= strlen(muls2); i++) {
			if((strlen(muls2) - p1 - p2) == i && kj == 0) {
				final_mult[pc] = '.'; 
				kj = 1;
				i = i-1;
			}
			else {
				final_mult[pc] = muls2[i];
			}
			pc++;
		}
		final_mult[strlen(muls2)+1] = '\0';
		if(sign == 1) {
			char *tfinal_mult = malloc((strlen(final_mult)+1)*sizeof(int));
			tfinal_mult[0] = '-';
			for (int i = 0; i < strlen(final_mult); i++) {
				tfinal_mult[i+1] = final_mult[i];
			}
			tfinal_mult[strlen(final_mult)+1] = '\0';
			final_mult = malloc(strlen(tfinal_mult) * sizeof(int));
			final_mult = tfinal_mult;
		}
	}
	if(final_mult[0] == '0') {
		int cup = 0;
		char *fds_mult = malloc(strlen(final_mult) * sizeof(int));
		for(int y = 0; y < strlen(final_mult); y++) {
			if(final_mult[y] != '0') {
				cup = y;
				break;
			}
		}
		if(final_mult[cup] == '.') {
			int jh = 0;
			for(int ui = cup-1; ui < strlen(final_mult); ui++) {
				fds_mult[jh] = final_mult[ui];
				jh++;
			}
			fds_mult[jh+1] = '\0';
			final_mult = malloc(strlen(fds_mult) * sizeof(int));
			final_mult = fds_mult;
		}
		else {
			int jh = 0;
			for(int ui = cup; ui < strlen(final_mult); ui++) {
				fds_mult[jh] = final_mult[ui];
				jh++;
			}
			fds_mult[jh+1] = '\0';
			final_mult = malloc(strlen(fds_mult) * sizeof(int));
			final_mult = fds_mult;
		}
	}
	return final_mult;
}

char* BIGNUM_DIV(char *first, char *second) {
	int all_zeroes = -1, dec_pos_first = -1, all_zeroes2 = -1, dec_pos_sec = -1;
	for(int i = 0; i < strlen(first); i++) {
		if(first[i] == '.') {
			dec_pos_first = i;
			break; 
		}
	}
	if(dec_pos_first != -1) {
		for(int i = dec_pos_first+1; i < strlen(first); i++) {
			if(first[i] == '0') {
				all_zeroes = 1;
			}
			else {
				all_zeroes = -1;
				break;
			}
		}
		if(all_zeroes != -1) {
			char *fftemp = malloc(strlen(first)*sizeof(int));
			for(int i = 0; i < dec_pos_first; i++) {
				fftemp[i] = first[i];
			}
			fftemp[dec_pos_first] = '\0';
			first = malloc(strlen(fftemp)*sizeof(int));
			first = fftemp;
		}
	}

	for(int i = 0; i < strlen(second); i++) {
		if(second[i] == '.') {
			dec_pos_sec = i;
			break; 
		}
	}
	if(dec_pos_sec != -1) {
		for(int i = dec_pos_sec+1; i < strlen(second); i++) {
			if(second[i] == '0') {
				all_zeroes2 = 1;
			}
			else {
				all_zeroes2 = -1;
				break;
			}
		}
		if(all_zeroes2 != -1) {
			char *fftemp2 = malloc(strlen(second)*sizeof(int));
			for(int i = 0; i < dec_pos_sec; i++) {
				fftemp2[i] = second[i];
			}
			fftemp2[dec_pos_sec] = '\0';
			second = malloc(strlen(fftemp2)*sizeof(int));
			second = fftemp2;
		}
	}
	int sign = 0;
	if(first[0] == '-' && second[0] != '-') {
		char *tfirst = malloc((strlen(first)-1)*sizeof(int));
		for (int i = 1; i < strlen(first); i++) {
			tfirst[i-1] = first[i];
		}
		tfirst[strlen(first)-1] = '\0';
		first = malloc((strlen(first)-1)*sizeof(int));
		first = tfirst;
		first[strlen(tfirst)] = '\0';
		sign = 1;
	}
	else if(first[0] == '-' && second[0] == '-') {
		char *tfirst = malloc((strlen(first)-1)*sizeof(int));
		for (int i = 1; i < strlen(first); i++) {
			tfirst[i-1] = first[i];
		}
		tfirst[strlen(first)-1] = '\0';
		first = malloc((strlen(first)-1)*sizeof(int));
		first = tfirst;
		first[strlen(tfirst)] = '\0';
		char *tsecond = malloc((strlen(second)-1)*sizeof(int));
		for (int i = 1; i < strlen(second); i++) {
			tsecond[i-1] = second[i];
		}
		tsecond[strlen(second)-1] = '\0';
		second = malloc((strlen(first)-1)*sizeof(int));
		second = tsecond;
		second[strlen(tsecond)] = '\0';
	}
	else if(first[0] != '-' && second[0] == '-') {
		char *tsecond = malloc((strlen(second)-1)*sizeof(int));
		for (int i = 1; i < strlen(second); i++) {
			tsecond[i-1] = second[i];
		}
		tsecond[strlen(second)-1] = '\0';
		second = malloc((strlen(first)-1)*sizeof(int));
		second = tsecond;
		second[strlen(tsecond)] = '\0';
		sign = 1;
	}
	int less_than_mod_one = 0, zero_after_decimal_first = 0, zero_after_decimal_second = 0;
	if(first[0] == '0') {
		less_than_mod_one = 1;
		char *njk1 = malloc(strlen(first)*sizeof(int));
		int cunj = 0, tp1 = 0;
		for(int pl = 0; pl < strlen(first); pl++) {
			if(first[pl] != '0' && first[pl] != '.') {
				cunj = pl;
				break;
			} 
			if(first[pl] == '.') {
				tp1 = pl;
			}
		}
		zero_after_decimal_first = strlen(first)-tp1-1;
		int cntp = 0;
		for(int uiy = cunj; uiy < strlen(first); uiy++) {
			njk1[cntp] = first[uiy];
			cntp++;
		}
		njk1[cntp] = '\0';
		first = malloc(strlen(njk1)*sizeof(int));
		first = njk1;
	}
	if(second[0] == '0') {
		less_than_mod_one = 1;
		char *njk1 = malloc(strlen(second)*sizeof(int));
		int cunj = 0, tp1 = 0;
		for(int pl = 0; pl < strlen(second); pl++) {
			if(second[pl] != '0' && second[pl] != '.') {
				cunj = pl;
				break;
			} 
			if(second[pl] == '.') {
				tp1 = pl;
			}
		}
		zero_after_decimal_second = strlen(second)-tp1-1;
		int cntp = 0;
		for(int uiy = cunj; uiy < strlen(second); uiy++) {
			njk1[cntp] = second[uiy];
			cntp++;
		}
		njk1[cntp] = '\0';
		second = malloc(strlen(njk1)*sizeof(int));
		second = njk1;
	}
	int l1 = strlen(first);
	int l2 = strlen(second);
	int bf1 = 0, bf2 = 0, af1 = 0, af2 = 0;
	char *num1 = malloc(l1*sizeof(int));
	char *num2 = malloc(l2*sizeof(int));
	char *sub;
	int bdf = find_decimal_position(first);
	int bds = find_decimal_position(second);
	int adf = l1 - bdf - 1;
	int ads = l2 - bds - 1;
	int bdmax = maximum(bdf, bds);
	int admax = maximum(adf, ads);
	if(adf > ads) {
		af1 = 1;
	}
	else if(adf < ads){
		af2 = 1;
	}
	if(bdf > bds) {
		bf1 = 1;
	}
	else if(bdf < bds) {
		bf2 = 1;
	}
	int k1 = 0;
	char *n1 = malloc(strlen(first)*sizeof(int));
	for (int i = 0; i < strlen(first); i++) {
		if(first[i] != '.') {
			n1[k1] = first[i];
			k1++;
		}
	}
	n1[k1] = '\0';
	int k2 = 0;
	char *n2 = malloc(strlen(second)*sizeof(int));
	for (int i = 0; i < strlen(second); i++) {
		if(second[i] != '.') {
			n2[k2] = second[i];
			k2++;
		}
	}
	n2[k2] = '\0';
	int p1 = strlen(first) - bdf - 1;
	int p2 = strlen(second) - bds - 1;
	l1 = strlen(n1);
	l2 = strlen(n2);
	char *final_quotient = malloc((l1+l2)*sizeof(int));
	int counter_final_quotient = 0;
	int present_decimal_position = -1;
	int big = 0, less = 0, equal = 0;
	int add_zeroes_le = 0;
	int bdfle = find_decimal_position(first);
	int bdsle = find_decimal_position(second);
	int adfle = 0, adsle = 0;
	if(bdfle != -1) {
		adfle = strlen(first) - bdfle - 1;
	} 
	if(bdsle != -1) {
		adsle = strlen(second) - bdsle -1;
	}
	int mul_factor_le = 0;
	mul_factor_le = adsle - adfle;
	if(l1 < l2) {
		less = 1;
		while(any_num_compare(n1, n2) == -1) {
			char *tempn1 = malloc((strlen(n1)+1)*sizeof(int));
			for(int i = 0; i < strlen(n1); i++) {
				tempn1[i] = n1[i];
			}
			tempn1[strlen(n1)] = '0';
			tempn1[strlen(n1)+1] = '\0';
			n1 = malloc(strlen(tempn1)*sizeof(int));
			n1 = tempn1;
			add_zeroes_le++;
		}
		l1 = strlen(n1);
		l2 = strlen(n2);
	}
	if(l1 == l2) {
		equal = 1;
		char *tempn1 = malloc((strlen(n1)+1)*sizeof(int));
		for(int i = 0; i < strlen(n1); i++) {
			tempn1[i] = n1[i];
		}
		tempn1[strlen(n1)] = '0';
		tempn1[strlen(n1)+1] = '\0';
		n1 = malloc(strlen(tempn1)*sizeof(int));
		n1 = tempn1;
		l1 = strlen(n1);
		l2 = strlen(n2);
	}
	if(l1 > l2) {
		big = 1;
		char *tempn1 = malloc(l2*sizeof(int));
		for (int i = 0; i < l2; i++) {
			tempn1[i] = n1[i];
		}
		tempn1[l2] = '\0';
		char t9 = '9';
		char *t9q = malloc(1*sizeof(int));
		t9q[0] = t9;
		t9q[1] = '\0';
		char *multtempn2 = BIGNUM_MULT(n2, t9q);
		char* tempn2 = malloc(strlen(multtempn2)*sizeof(int));
		int kochi = 0;
		for (int i = 0; i < strlen(multtempn2); i++) {
			if(multtempn2[i] != '.') {
				tempn2[i] = multtempn2[i];
				kochi = i;
			}
			else {
				break;
			}
		}
		tempn2[kochi+1] = '\0';
		for (int i = 0; i <= l1-l2; i++) {
			int quot = 0;
			if(any_num_compare(tempn1, tempn2) == -1) {
				for (int j = 8; j >= 1; j--) {
					if(any_num_compare(tempn1, tempn2) == -1) {
						quot = j;
						char qu = j + '0';
						char *quo = malloc(1*sizeof(int));
						quo[0] = qu;
						quo[1] = '\0';
						int ret = 0;
						char *pd = BIGNUM_MULT(n2, quo);
						tempn2 = malloc(strlen(pd)*sizeof(int));
						for (int i = 0; i < strlen(pd); i++) {
							if(pd[i] != '.') {
								tempn2[i] = pd[i];
								ret = i;
							}
							else {
								break;
							}
						}
						tempn2[ret+1] = '\0';
					}
					else {
						break;
					}
				}
			}
			int quotient = 0;
			if(any_num_compare(tempn1, tempn2) == -1 && quot == 1) {
				char *ttempn1 = malloc((strlen(tempn1)+1)*sizeof(int));
				for (int p = 0; p < strlen(tempn1); p++) {
					ttempn1[p] = tempn1[p];
				}
				ttempn1[strlen(tempn1)] = n1[l2+i];
				tempn1 = malloc(strlen(ttempn1)*sizeof(int));
				tempn1 = ttempn1;
				if(tempn1[0] == '0') {
					char *tr = malloc(1*sizeof(int));
					tr[0] = tempn1[1];
					tr[1] = '\0';
					tempn1 = malloc(1);
					tempn1 = tr;
				}
				tempn2 = malloc(strlen(multtempn2)*sizeof(int));
				int koch = 0;
				for (int i = 0; i < strlen(multtempn2); i++) {
					if(multtempn2[i] != '.') {
						tempn2[i] = multtempn2[i];
						koch = i;
					}
					else {
						break;
					}
				}
				final_quotient[counter_final_quotient] = '0';
				counter_final_quotient++;
			}
			else {
				if(quot == 0) {
					quotient = 9;
				}
				else if(any_num_compare(tempn1, tempn2) == 1 || any_num_compare(tempn1, tempn2) == 0) {
					quotient = quot;
				}
				char qu = quotient + '0';
				char *quo = malloc(1*sizeof(int));
				quo[0] = qu;
				quo[1] = '\0';
				int ret = 0;
				char *pd = BIGNUM_MULT(n2, quo);
				char *subr1 = BIGNUM_SUB(tempn1, pd);
				tempn1 = malloc(strlen(subr1)*sizeof(int));
				for (int h = 0; h < strlen(subr1); h++) {
					if(subr1[h] != '.') {
						tempn1[h] = subr1[h];
						ret = h;
					}
					else {
						break;
					}
				}
				tempn1[ret+1] = n1[l2+i];
				tempn1[ret+2] = '\0';
				if(tempn1[0] == '0') {
					char *tr = malloc(1*sizeof(int));
					tr[0] = tempn1[1];
					tr[1] = '\0';
					tempn1 = malloc(1*sizeof(int));
					tempn1 = tr;
				}
				char quotie = quotient + '0';
				final_quotient[counter_final_quotient] = quotie;
				counter_final_quotient++;
				tempn2 = malloc(strlen(multtempn2)*sizeof(int));
				int koch = 0;
				for (int i = 0; i < strlen(multtempn2); i++) {
					if(multtempn2[i] != '.') {
							tempn2[i] = multtempn2[i];
						koch = i;
					}
					else {
						break;
					}
				}	
			}
		}
		char *trn2 = malloc((strlen(n2)-2)*sizeof(int));
		for (int i = 0; i < strlen(n2)-2; i++) {
			trn2[i] = n2[i];
		}
		trn2[strlen(n2)-2] = '\0';
		n2 = malloc(strlen(trn2)*sizeof(int));
		n2 = trn2;
		int quotient = 0;
		int xwsignal = 0;
		for (int is = 0; is < strlen(tempn1); is++) {
			if(tempn1[is] == '0') {
				xwsignal = 1;
			}
			else {
				xwsignal = 0;
				break;
			}
		}
		if(strlen(tempn1) == 0) {
			final_quotient[counter_final_quotient] = '\0';
		} 
		else if(xwsignal == 1) {
			final_quotient[counter_final_quotient] = '\0';
		}
		else {
			if(tempn1[0] == '0') {
				char *trew = malloc(strlen(tempn1)*sizeof(int));
				for(int iwt = 1; iwt < strlen(tempn1); iwt++) {
					trew[iwt-1] = tempn1[iwt];
				}
				trew[strlen(tempn1)-1] = '\0';
				tempn1 = malloc(strlen(trew)*sizeof(int));
				tempn1 = trew;
			}
			present_decimal_position = counter_final_quotient;
			final_quotient[counter_final_quotient] = '.';
			counter_final_quotient++;
			char *trempn1 = malloc((strlen(tempn1)+1)*sizeof(int));
			for (int i = 0; i < strlen(tempn1); i++) {
				trempn1[i] = tempn1[i];
			}
			trempn1[strlen(tempn1)] = '0';
			trempn1[strlen(tempn1) + 1] = '\0';
			tempn1 = malloc(strlen(trempn1)*sizeof(int));
			tempn1 = trempn1;
			int bds1 = find_decimal_position(second);
			int ads1 = 0;
			if(bds1 != -1) {
				ads1 = strlen(second) - bds -1;
			}
			for (int i = 0; i < 20+ads1; i++) {
				if(strchr(n2, '.')) {
					char *trn3 = malloc((strlen(n2)-2)*sizeof(int));
					for (int i = 0; i < strlen(n2) -2; i++) {
						trn3[i] = n2[i];
					}
					trn3[strlen(n2)-2] = '\0';
					n2 = malloc(strlen(trn3)*sizeof(int));
					n2 = trn3;
				}
				if(any_num_compare(tempn1, n2) == -1) {
					char *tttrempn1 = malloc((strlen(tempn1)+1)*sizeof(int));
					for (int i = 0; i < strlen(tempn1); i++) {
						tttrempn1[i] = tempn1[i];
					}
					tttrempn1[strlen(tempn1)] = '0';
					tttrempn1[strlen(tempn1) + 1] = '\0';
					tempn1 = malloc(strlen(tttrempn1)*sizeof(int));
					tempn1 = tttrempn1;
					final_quotient[counter_final_quotient] = '0';
					counter_final_quotient++;
				}
				else {
					int quot = 0;
					for (int j = 8; j >= 1; j--) {
						if(any_num_compare(tempn1, tempn2) == -1) {
							quot = j;
							char qu = j + '0';
							char *quo = malloc(1*sizeof(int));
							quo[0] = qu;
							quo[1] = '\0';
							int ret = 0;
							char *pd = BIGNUM_MULT(n2, quo);
							tempn2 = malloc(strlen(pd)*sizeof(int));
							for (int i = 0; i < strlen(pd); i++) {
								if(pd[i] != '.') {
									tempn2[i] = pd[i];
									ret = i;
								}
								else {
									break;
								}
							}
							tempn2[ret+1] = '\0';
						}
						else {
							break;
						}
					}
					if(quot == 0) {
						quotient = 9;
					}
					else if(any_num_compare(tempn1, tempn2) == 1 || any_num_compare(tempn1, tempn2) == 0) {
						quotient = quot;
					}
					char qu = quotient + '0';
					char *quo = malloc(1*sizeof(int));
					quo[0] = qu;
					quo[1] = '\0';
					int ret = 0;
					char *pd = BIGNUM_MULT(n2, quo);
					char *subr1 = BIGNUM_SUB(tempn1, pd);
					tempn1 = malloc(strlen(subr1)*sizeof(int));
					for (int h = 0; h < strlen(subr1); h++) {
						if(subr1[h] != '.') {
							tempn1[h] = subr1[h];
							ret = h;
						}
						else {
							break;
						}
					}
					char quotie = quotient + '0';
					final_quotient[counter_final_quotient] = quotie;
					counter_final_quotient++;
					char *ttrempn1 = malloc((strlen(tempn1)+1)*sizeof(int));
					for (int i = 0; i < strlen(tempn1); i++) {
						ttrempn1[i] = tempn1[i];
					}
					ttrempn1[strlen(tempn1)] = '0';
					ttrempn1[strlen(tempn1) + 1] = '\0';
					tempn1 = malloc(strlen(ttrempn1)*sizeof(int));
					tempn1 = ttrempn1;
					tempn2 = malloc(strlen(multtempn2)*sizeof(int));
					int koch = 0;
					for (int i = 0; i < strlen(multtempn2); i++) {
						if(multtempn2[i] != '.') {
							tempn2[i] = multtempn2[i];
							koch = i;
						}
						else {
							break;
						}
					}
					if(tempn1[0] == '0') {
						break;
					}
				}	
			}
		}
		final_quotient[counter_final_quotient] = '\0';
		char *tquote1 = malloc(strlen(final_quotient)*sizeof(int));
		int iter = 0;
		if(final_quotient[0] == '0') {
			present_decimal_position = present_decimal_position -1;
			for (int i = 1; i < strlen(final_quotient); i++) {
				tquote1[i-1] = final_quotient[i]; 
			}
			tquote1[strlen(final_quotient)-1] = '\0';
			final_quotient = malloc(strlen(tquote1)*sizeof(int));
			final_quotient = tquote1;
		}
		if(present_decimal_position <= -1) {
			int bdf1 = find_decimal_position(first);
			int bds1 = find_decimal_position(second);
			int adf1 = 0, ads1 = 0;
			if(bdf1 != -1) {
				adf1 = strlen(first) - bdf - 1;
			} 
			if(bds1 != -1) {
				ads1 = strlen(second) - bds -1;
			}
			int mul_factor = 0;
			mul_factor = ads1 - adf1;
			if(mul_factor > 0) {
				char* ans_f = malloc((strlen(final_quotient) + mul_factor) * sizeof(int));
				for (int we = 0; we < strlen(final_quotient); we++) {
					ans_f[we] = final_quotient[we];
				}
				for (int po = 0 ; po < mul_factor; po++) {
					ans_f[strlen(final_quotient) + po] = '0';
				}
				ans_f[strlen(final_quotient) + mul_factor] = '\0';
				final_quotient = malloc(strlen(ans_f)*sizeof(int));
				final_quotient = ans_f;
			}
			else if(mul_factor < 0) {
				mul_factor = mul_factor * -1;
				char *ans_f = malloc((strlen(final_quotient)+1)*sizeof(int));
				ans_f[strlen(final_quotient)-mul_factor] = '.';
				int cou = 0 ,signa = 0;
				for (int ipo = 0; ipo < strlen(final_quotient); ipo++) {
					if (ipo == strlen(final_quotient)-mul_factor && signa == 0) {
						signa = 1;
						cou++;
					}
					if(ipo != strlen(final_quotient)-mul_factor || signa == 1) {
						ans_f[cou] = final_quotient[ipo];
						cou++;
					}
				}
				ans_f[strlen(final_quotient)+1] = '\0';
				final_quotient = malloc(strlen(ans_f)*sizeof(int));
				final_quotient = ans_f;
			}
		}
		else {
			int bdf1 = find_decimal_position(first);
			int bds1 = find_decimal_position(second);
			int adf1 = 0, ads1 = 0;
			if(bdf1 != -1) {
				adf1 = strlen(first) - bdf1 - 1;
			} 
			if(bds1 != -1) {
				ads1 = strlen(second) - bds1 -1;
			}
			int mul_factor = 0;
			mul_factor = ads1 - adf1;
			if(mul_factor > 0) {
				for (int iyo = present_decimal_position; iyo <= present_decimal_position+mul_factor; iyo++) {
					final_quotient[iyo] = final_quotient[iyo+1];
				}
				final_quotient[present_decimal_position+mul_factor] = '.';
				final_quotient[strlen(final_quotient)-1] = '\0';
			}
			else if(mul_factor < 0) {
				for (int iyo = present_decimal_position; iyo >= present_decimal_position+mul_factor+1; iyo--) {
					final_quotient[iyo] = final_quotient[iyo-1];
				}
				final_quotient[present_decimal_position+mul_factor] = '.';
				final_quotient[strlen(final_quotient)] = '\0';
			}
		}
	}
	if(less == 1 && equal == 0 && big == 1) {
		char *less_final_quotient = malloc((strlen(final_quotient) + add_zeroes_le + 3)*sizeof(int));
		less_final_quotient[0] = '0';
		less_final_quotient[1] = '.';
		for(int is = 0; is < add_zeroes_le-1; is++) {
			less_final_quotient[2+is] = '0';
		}
		less_final_quotient[add_zeroes_le+1] = '1';
		less_final_quotient[add_zeroes_le+2] = '\0';
		char *gfmult = BIGNUM_MULT(less_final_quotient, final_quotient);
		final_quotient = malloc(strlen(gfmult)*sizeof(int));
		final_quotient = gfmult;
	}
	else if(less == 0 && equal == 1 && big == 1) {
		char *ten_factor = malloc(3*sizeof(int));
		ten_factor[0] = '0';
		ten_factor[1] = '.';
		ten_factor[2] = '1';
		ten_factor[3] = '\0';
		char *uy_ans = BIGNUM_MULT(final_quotient, ten_factor);
		final_quotient = malloc(strlen(uy_ans)*sizeof(int));
		final_quotient = uy_ans;
	}
	else if(less == 1 && equal == 1 && big == 1) {
		int digits_before_decimal = 0;
		for(int i = 0; i < strlen(final_quotient); i++) {
			if(final_quotient[i] != '.') {
				digits_before_decimal++;
			}
			else {
				break;
			}
		}
		int num_zeroes_add = add_zeroes_le - digits_before_decimal + 1;
		if(num_zeroes_add < 0) {
			for(int idf = digits_before_decimal; idf >= digits_before_decimal - add_zeroes_le; idf--) {
				final_quotient[idf] = final_quotient[idf-1];
			}
			final_quotient[digits_before_decimal-add_zeroes_le-1] = '.';
		}
		else {
			char *less_final_quotient = malloc((strlen(final_quotient) + num_zeroes_add + 3)*sizeof(int));
			less_final_quotient[0] = '0';
			less_final_quotient[1] = '.';
			for(int is = 0; is < num_zeroes_add; is++) {
				less_final_quotient[2+is] = '0';
			}
			int coup = 2 + num_zeroes_add;
			for(int ip = 0; ip < digits_before_decimal; ip++) {
				less_final_quotient[coup+ip] = final_quotient[ip];
			}
			coup = coup + digits_before_decimal;
			for (int ip = digits_before_decimal+1; ip < strlen(final_quotient); ip++) {
				less_final_quotient[coup] = final_quotient[ip];
				coup++;
			}
			less_final_quotient[coup+1] = '\0';
			final_quotient = malloc(strlen(less_final_quotient)*sizeof(int));
			final_quotient = less_final_quotient;
		}
	}
	if(less_than_mod_one == 1) {
		int shift = zero_after_decimal_second - zero_after_decimal_first;
		if(shift > 0) {
			char *ten_factor = malloc((shift + 2)*sizeof(int));
			ten_factor[0] = '1';
			for(int it = 1; it <= shift; it++) {
				ten_factor[it] = '0';
			}
			char *nb_answer = BIGNUM_MULT(final_quotient, ten_factor);
			final_quotient = malloc(strlen(nb_answer)*sizeof(int));
			final_quotient = nb_answer;
		}
		if(shift < 0) {
			char *ten_factor = malloc((-1*shift+10)*sizeof(int));
			ten_factor[0] = '0';
			ten_factor[1] = '.';
			for(int it = 2; it <= -1*shift; it++) {
				ten_factor[it] = '0';
			}
			ten_factor[-1*shift+1] = '1';
			ten_factor[-1*shift+2] = '\0';
			char *nb_answer = BIGNUM_MULT(final_quotient, ten_factor);
			final_quotient = malloc(strlen(nb_answer)*sizeof(int));
			final_quotient = nb_answer;
		}
	}
	if(sign == 1) {
		char *ansd = malloc((strlen(final_quotient)+1)*sizeof(int));
		ansd[0] = '-';
		for(int iou = 0; iou < strlen(final_quotient); iou++) {
			ansd[iou+1] = final_quotient[iou];
		}
		final_quotient = malloc(strlen(ansd)*sizeof(int));
		final_quotient = ansd;
	}
	for(int i=0;i< strlen(final_quotient);i++){
        if (final_quotient[i]=='.') {
            if(strlen(final_quotient)> i+21){
                final_quotient[i+21]='\0';
            }
        }
    }
	return final_quotient;
}

char* closest_square(char *num1, char *num2) {
	if(num1[0] == '0') {
		char *m_num1 = malloc(strlen(num1)*sizeof(int));
		for(int ix = 1; ix < strlen(num1); ix++) {
			m_num1[ix-1] = num1[ix];
		}
		m_num1[strlen(num1)-1] = '\0';
		num1 = malloc(strlen(m_num1)*sizeof(int));
		num1 = m_num1;
	}
	if(strlen(num2) == 0) {
		for(int i = 9; i >= 0; i--) {
			char pol = i + '0';
			char *polk = malloc(1*sizeof(int));
			char *other = malloc(1*sizeof(int));
			other[0] = pol;
			other[1] = '\0';
			polk[0] = pol;
			polk[1] = '\0';
			char *sq = BIGNUM_MULT(polk, polk);
			char *cr_sq = malloc(strlen(sq)*sizeof(int));
			int coun_cr = 0;
			for(int kj = 0; kj < strlen(sq); kj++) {
				if(sq[kj] != '.') {
					cr_sq[kj] = sq[kj];
					coun_cr = kj;
				}
				else {
					break;
				}
			}
			cr_sq[coun_cr+1] = '\0';
			if(any_num_compare(num1, cr_sq) == 1 || any_num_compare(num1, cr_sq) == 0) {
				return other;
			}
		}
	}
	else {
		char *polk = malloc((strlen(num1)+1)*sizeof(int));
		for(int poi = 0; poi < strlen(num2); poi++) {
			polk[poi] = num2[poi];
		}
		for(int i = 9; i >= 0; i--) {
			char pol = i + '0';
			char *other = malloc(1*sizeof(int));
			other[0] = pol;
			other[1] = '\0';
			polk[strlen(num2)] = pol;
			polk[strlen(num2)+1] = '\0';
			char *sq = BIGNUM_MULT(polk,other);
			char *cr_sq = malloc(strlen(sq)*sizeof(int));
			int coun_cr = 0;
			for(int kj = 0; kj < strlen(sq); kj++) {
				if(sq[kj] != '.') {
					cr_sq[kj] = sq[kj];
					coun_cr = kj;
				}
				else {
					break;
				}
			}
			cr_sq[coun_cr+1] = '\0';
			if(any_num_compare(num1, cr_sq) == 1 || any_num_compare(num1, cr_sq) == 0) {
				return other;
			}
			else {
				char *cr_polk = malloc((strlen(num2)+1)*sizeof(int));
				for(int poi = 0; poi < strlen(num2); poi++) {
					cr_polk[poi] = num2[poi];
				}
				polk = malloc(strlen(cr_polk)*sizeof(int));
				polk = cr_polk;
			}
		}
	}
}

char* BIGNUM_SQUAREROOT(char *num) {
	int before_dec = 0;
	for(int i = 0; i < strlen(num); i++) {
		if(num[i] == '.') {
			before_dec = i;
		}
	}
	int no_decimal_signal = 0;
	if(before_dec == 0) {
		no_decimal_signal = 1;
		char *mk_num = malloc((strlen(num)+3)*sizeof(int));
		for(int ikj = 0; ikj < strlen(num); ikj++) {
			mk_num[ikj] = num[ikj];
		}
		mk_num[strlen(num)] = '.';
		mk_num[strlen(num)+1] = '0';
		mk_num[strlen(num)+2] = '0';
		mk_num[strlen(num)+3] = '\0';
		num = malloc(strlen(mk_num)*sizeof(int));
		num = mk_num;
	}
	for(int i = 0; i < strlen(num); i++) {
		if(num[i] == '.') {
			before_dec = i;
		}
	}
	if(before_dec % 2 != 0) {
		char *mk_num = malloc((strlen(num)+1)*sizeof(int));
		mk_num[0] = '0';
		for(int ikj = 0; ikj < strlen(num); ikj++) {
			mk_num[1+ikj] = num[ikj];
		}
		mk_num[strlen(num)+1] = '\0';
		num = malloc(strlen(mk_num)*sizeof(int));
		num = mk_num;
	}
	for(int i = 0; i < strlen(num); i++) {
		if(num[i] == '.') {
			before_dec = i;
		}
	}
	int after_dec = strlen(num) - before_dec -1;
	if(after_dec % 2 != 0) {
		char *mk_num = malloc((strlen(num)+1)*sizeof(int));
		for(int ikj = 0; ikj < strlen(num); ikj++) {
			mk_num[ikj] = num[ikj];
		}
		mk_num[strlen(num)] = '0';
		mk_num[strlen(num)+1] = '\0';
		num = malloc(strlen(mk_num)*sizeof(int));
		num = mk_num;
	}
	after_dec = strlen(num) - before_dec -1;
	char *mkjh_num = malloc(strlen(num)*sizeof(int));
	int cunjh = 0;
	for(int ikjp = 0; ikjp < strlen(num); ikjp++) {
		if(num[ikjp] != '.') {
			mkjh_num[cunjh] = num[ikjp];
			cunjh++;
		}
	}
	mkjh_num[cunjh] = '\0';
	num = malloc(strlen(mkjh_num)*sizeof(int));
	num = mkjh_num;
	char *tempn1 = malloc(2*sizeof(int));
	int loop_counter = 0;
	if(strlen(num) % 2 == 0) {
		loop_counter = strlen(num)/2;
		tempn1[0] = num[0];
		tempn1[1] = num[1];
		tempn1[2] = '\0';
	}
	if(strlen(num) % 2 != 0) {
		loop_counter = (strlen(num)+1)/2;
		tempn1[0] = num[0];
		tempn1[1] = '\0';
	}
	int tempn1_index = 0;
	char *dummy1 = malloc(1*sizeof(int));
	dummy1[0] = '\0';
	char *f_root = malloc(strlen(num)*sizeof(int));
	int f_root_counter = 0;
	for(int i = 0; i < loop_counter; i++) {
		char* dummy2 = closest_square(tempn1, dummy1);
		f_root[f_root_counter] = dummy2[0];
		f_root_counter++;
		char *tre = malloc(strlen(dummy1)*sizeof(int));
		for(int po = 0; po < strlen(dummy1); po++) {
			tre[po] = dummy1[po];
		}
		tre[strlen(dummy1)] = dummy2[0];
		tre[strlen(dummy1)+1] = '\0';
		dummy1 = malloc(strlen(tre)*sizeof(int));
		dummy1 = tre;
		char *remainder = BIGNUM_SUB(tempn1, BIGNUM_MULT(dummy1, dummy2));
		if(remainder == "0.0") {
			remainder = malloc(1*sizeof(int));
			remainder[0] = '\0';
		}
		else if(remainder[0] == '-') {
			remainder = malloc(1*sizeof(int));
			remainder[0] = '\0';
		}
		else {
			int m_rem_cnt = 0;
			char *m_rem = malloc(strlen(remainder)*sizeof(int));
			for(int il = 0; il < strlen(remainder); il++) {
				if(remainder[il] != '.') {
					m_rem[il] = remainder[il];
					m_rem_cnt = il;
				}
				else {
					break;
				}
			}
			m_rem[m_rem_cnt+1] = '\0';
			remainder = malloc(strlen(remainder)*sizeof(int));
			remainder = m_rem;
		}
		char *make_remainder = malloc((strlen(remainder)+3)*sizeof(int));
		for(int pol = 0; pol < strlen(remainder); pol++) {
			make_remainder[pol] = remainder[pol];
		}
		if(strlen(num)%2 != 0) {
			make_remainder[strlen(remainder)] = num[tempn1_index+1];
			make_remainder[strlen(remainder)+1] = num[tempn1_index+2];
		}
		else if(strlen(num)%2 == 0) {
			make_remainder[strlen(remainder)] = num[tempn1_index+2];
			make_remainder[strlen(remainder)+1] = num[tempn1_index+3];
		}
		tempn1_index = tempn1_index + 2;
		make_remainder[strlen(remainder)+2] = '\0';
		tempn1 = malloc(strlen(make_remainder)*sizeof(int));
		tempn1 = make_remainder;
		char *dummy1_sum = BIGNUM_ADD(dummy1, dummy2);
		int dummy1_sum_cnt = 0;
		char *dummy1_sum_cr = malloc(strlen(dummy1_sum)*sizeof(int));
		for(int ij = 0; ij < strlen(dummy1_sum); ij++) {
			if(dummy1_sum[ij] != '.') {
				dummy1_sum_cr[ij] = dummy1_sum[ij];
				dummy1_sum_cnt = ij;
			}
			else {
				break;
			}
		}
		dummy1_sum_cr[dummy1_sum_cnt+1] = '\0';
		dummy1 = malloc(strlen(dummy1_sum_cr)*sizeof(int));
		dummy1 = dummy1_sum_cr;
	}
	if(strlen(tempn1) == 0 || tempn1[0] == '-' || (strlen(tempn1) == 1 && tempn1[0] == '0')) {
		f_root[f_root_counter] = '\0';
	}
	else {
		int cfg = 0;
		for(int ib = 0; ib < strlen(tempn1); ib++) {
			if(tempn1[ib] != '0') {
				cfg = ib;
				break;
			}
		}
		char *mk_tempn1 = malloc(strlen(tempn1)*sizeof(int));
		int cunti = 0;
		for(int bh = cfg; bh < strlen(tempn1); bh++) {
			mk_tempn1[cunti] = tempn1[bh];
			cunti++;
		}
		mk_tempn1[cunti] = '\0';
		tempn1 = malloc(strlen(tempn1)*sizeof(int));
		tempn1 = mk_tempn1;
		f_root[f_root_counter] = '.';
		f_root_counter++;
		for(int j = 0; j < 20-(after_dec/2); j++) {
			char *m_tempn1 = malloc((strlen(tempn1)+5)*sizeof(int));
			for(int h = 0; h < strlen(tempn1); h++) {
				m_tempn1[h] = tempn1[h];
			}
			m_tempn1[strlen(tempn1)] = '0';
			m_tempn1[strlen(tempn1)+1] = '0';
			m_tempn1[strlen(tempn1)+2] = '\0';
			tempn1 = malloc(strlen(m_tempn1)*sizeof(int));
			tempn1 = m_tempn1;
			char* dummy12 = closest_square(tempn1, dummy1);
			f_root[f_root_counter] = dummy12[0];
			f_root_counter++;
			char *tre1 = malloc(strlen(dummy1)*sizeof(int));
			for(int po = 0; po < strlen(dummy1); po++) {
				tre1[po] = dummy1[po];
			}
			tre1[strlen(dummy1)] = dummy12[0];
			tre1[strlen(dummy1)+1] = '\0';
			dummy1 = malloc(strlen(tre1)*sizeof(int));
			dummy1 = tre1;
			char *remainder1 = BIGNUM_SUB(tempn1, BIGNUM_MULT(dummy1, dummy12));
			if(remainder1 == "0.0") {
				remainder1 = malloc(1*sizeof(int));
				remainder1[0] = '\0';
			}
			else {
				int m_rem_cnt1 = 0;
				char *m_rem1 = malloc(strlen(remainder1)*sizeof(int));
				for(int il = 0; il < strlen(remainder1); il++) {
					if(remainder1[il] != '.') {
						m_rem1[il] = remainder1[il];
						m_rem_cnt1 = il;
					}
					else {
						break;
					}
				}
				m_rem1[m_rem_cnt1+1] = '\0';
				remainder1 = malloc(strlen(remainder1)*sizeof(int));
				remainder1 = m_rem1;
			}
			char *make_remainder1 = malloc((strlen(remainder1)+3)*sizeof(int));
			for(int pol = 0; pol < strlen(remainder1); pol++) {
				make_remainder1[pol] = remainder1[pol];
			}
			make_remainder1[strlen(remainder1)] = '\0';
			tempn1 = malloc(strlen(make_remainder1)*sizeof(int));
			tempn1 = make_remainder1;
			char *dummy1_sum1 = BIGNUM_ADD(dummy1, dummy12);
			int dummy1_sum_cnt1 = 0;
			char *dummy1_sum_cr1 = malloc(strlen(dummy1_sum1)*sizeof(int));
			for(int ij = 0; ij < strlen(dummy1_sum1); ij++) {
				if(dummy1_sum1[ij] != '.') {
					dummy1_sum_cr1[ij] = dummy1_sum1[ij];
					dummy1_sum_cnt1 = ij;
				}
				else {
					break;
				}
			}
			dummy1_sum_cr1[dummy1_sum_cnt1+1] = '\0';
			dummy1 = malloc(strlen(dummy1_sum_cr1)*sizeof(int));
			dummy1 = dummy1_sum_cr1;
		}
		f_root[f_root_counter] = '\0';
	}
	int hunjp = -1;
	for(int ko = 0; ko < strlen(f_root); ko++) {
		if(f_root[ko] == '.') {
			hunjp = ko;
			break;
		}
	}
	if(no_decimal_signal == 1) {
		char *ten = "10";
		char *ans_f_root = BIGNUM_DIV(f_root, ten);
		f_root = malloc(strlen(ans_f_root)*sizeof(int));
		f_root = ans_f_root;
	}
	else if(hunjp == -1) {
		if(f_root[0] == '0') {
			int zero_stop = 0;
			for(int b = 1; b < strlen(f_root); b++) {
				if(f_root[b] == '0') {
					zero_stop = b;
				}
				else {
					break;
				}
			}
			char *ff_root = malloc(strlen(f_root)*sizeof(int));
			int countp = 0;
			for(int b = zero_stop+1; b < strlen(f_root); b++) {
				ff_root[countp] = f_root[b];
				countp++;
			}
			ff_root[countp] = '\0';
			f_root = malloc(strlen(f_root)*sizeof(int));
			f_root = ff_root;
		}
		int shiftr = after_dec/2;
		char *ten_fac = malloc((shiftr+3)*sizeof(int));
		ten_fac[0] = '1';
		for(int i = 0; i < shiftr; i++) {
			ten_fac[i+1] = '0';
		}
		ten_fac[shiftr+1] = '\0';
		char *ans_f_root = BIGNUM_DIV(f_root, ten_fac);
		f_root = malloc(strlen(ans_f_root)*sizeof(int));
		f_root = ans_f_root;
	}
	else {
		int shiftr = after_dec/2;
		for(int yo = hunjp; yo >= hunjp-shiftr+1; yo--) {
			f_root[yo] = f_root[yo-1];
		}
		f_root[hunjp-shiftr] = '.';
	}
	for(int i=0;i< strlen(f_root);i++){
        if (f_root[i]=='.') {
            if(strlen(f_root)> i+21){
                f_root[i+21]='\0';
            }
        }
    }
	return f_root;
}

char *BIGNUM_COMPLEX_MOD_ABS(char *num1, char *num2) {
	char *mod = BIGNUM_SQUAREROOT(BIGNUM_ADD(BIGNUM_MULT(num1, num1), BIGNUM_MULT(num2, num2)));
	return mod;
}