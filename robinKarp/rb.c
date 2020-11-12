#define  _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include<string.h>
#include<malloc.h>
#define SIZE_OF_BLOCK 150

typedef unsigned long long big_int;
big_int  arr_pow_3[SIZE_OF_BLOCK];

big_int init_hash(char* str, int begin, int len_temp) {
	big_int result = 0;

	for (int i = 0; i < len_temp; i++) {
		result = result + (((unsigned char)str[begin + i] % 3) * (arr_pow_3[begin + i]));
	}
	return result;
}
void recount_hash(big_int* hash, int  length_temp, char first_c, char last_c) {
	*hash -= ((unsigned char)first_c % 3);
	*hash /= 3;
	*hash += (((unsigned char)last_c % 3) * (arr_pow_3[length_temp - 1]));
}
void init_array_pow_3(int n) {
	big_int result = 1;
	for (int i = 0; i < n + 1; i++) {
		arr_pow_3[i] = result;
		result *= 3;
	}
}
void  re_init_array(char* line, int len, int number) {
	for (int i = 0; i < len - number; i++)
		line[i] = line[number + i];
}
void robin_karp(FILE* file, char* temp) {
	big_int hash_s, hash_t;

	char line[SIZE_OF_BLOCK] = { 0 };

	size_t len_temp = strlen(temp) - 1;
	size_t start_write_with = 0;
	size_t number = 0;

	char past_firs_char;
	init_array_pow_3(len_temp);
	hash_t = init_hash(temp, 0, len_temp);

	printf("%llu ", hash_t);

	while (!feof(file)) {
		//последовательное считывание строки начиная с последнего элемента,который храниться в буфере
		size_t len_read = fread(&line[start_write_with], sizeof(char), SIZE_OF_BLOCK - start_write_with, file);
		if (len_read + start_write_with < len_temp)
			break;

		if (start_write_with != 0)
			recount_hash(&hash_s, len_temp, past_firs_char, line[len_temp - 1]);
		else
			hash_s = init_hash(line, 0, len_temp);

		for (size_t i = 0; i <= len_read + start_write_with - len_temp; i++) {
			if (i != 0)
				recount_hash(&hash_s, len_temp, line[i - 1], line[i + len_temp - 1]);
			if (hash_s == hash_t) {
				for (size_t j = 0; j < len_temp; j++) {
					int res = i + number + 1 + j;
					printf("%d ", res);
					if (line[i + j] != temp[j])
						break;
				}
			}
		}
		if (feof(file))
			break;
		past_firs_char = line[SIZE_OF_BLOCK - len_temp - 1];
		re_init_array(line, SIZE_OF_BLOCK, SIZE_OF_BLOCK - len_temp + 1);

		start_write_with = len_temp - 1;
		number += (SIZE_OF_BLOCK - len_temp + 1);
	}
}
int main()
{
	char temp[SIZE_OF_BLOCK] = { 0 };
	 //считаывание шаблона
	if (!fgets(temp, SIZE_OF_BLOCK, stdin))
		return 1;
	robin_karp(stdin, temp);
	fclose(stdin);
	return 0;
}
