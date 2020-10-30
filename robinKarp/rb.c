#define  _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <locale.h>
#include<string.h>
#include<malloc.h>
#include <stdbool.h>
#define SIZE_OF_BLOCK 1000
typedef   unsigned long long big_int;
big_int init_hash(char* str, big_int* arr_pow_3) {
    big_int result = 0;

    for (int i = 1; i < strlen(str) + 1; i++) {
        result = result + ((str[i] % 3) * (arr_pow_3[i]));
    }
    return result;
}
big_int new_hash(big_int hash, int len, char first_c, char last_c, big_int* arr_pow_3) {
    hash /= 3;
    hash -= (first_c % 3);
    hash += ((last_c % 3) * (arr_pow_3[len]));
    return hash;
}
bool is_matching(char* str, char* template) {
    if (str == NULL || template == NULL || strlen(str)== strlen(template)) return false;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] != template[i])
            return false;

    }
    return true;
}

big_int * init_array_pow_3(int n) {
    big_int result = 1;
    big_int * arr = (big_int*)malloc(n * sizeof(big_int));
    for (int i = 0; i < n; i++) {
        arr[i] = result;
        result *= 3;
    }
    return arr;
}
char * str_cut(char* str, int begin, int len)
{
    int l = strlen(str);
    char* res = (char*)malloc(sizeof(char) * len);
    for (int i = 0; i < len;i++) {
        res[i] = str[i + begin];
    }

    return res;
}
int main()
{
    setlocale(LC_ALL, "Russian");
    
    big_int hash_s,hash_t;
    
    char line[SIZE_OF_BLOCK] = { 0 };
    char tm[] = "example";
    int n = strlen(tm);
 
    FILE* ptrFile = fopen("file.txt", "r");
  // while(!feof(ptrFile)) {
    size_t f
        ;
   f= fread(line, sizeof(char), 100, ptrFile);
        char *buffer = str_cut(line, 0, n);

        big_int arr_pow_3 = init_array_pow_3(n);
        hash_s = init_hash(buffer,arr_pow_3);
        hash_t = init_hash(tm,arr_pow_3);

        for (int i = 1; i < SIZE_OF_BLOCK - n; i++) {
            if (hash_s == hash_t) {
                if (is_matching(str_cut(line, i, n), tm)) {
                    printf("yes");

                }
            }
            hash_s = new_hash(hash_s, n, line[i], line[i + n], arr_pow_3);
        }
     
    fclose(ptrFile);
    return 0;
}