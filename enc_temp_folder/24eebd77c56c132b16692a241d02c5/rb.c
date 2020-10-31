#define  _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <locale.h>
#include<string.h>
#include<malloc.h>
#include <stdbool.h>
#define SIZE_OF_BLOCK 100
typedef   unsigned long long big_int;
big_int init_hash(char* str,int len , big_int* arr_pow_3) {
    big_int result = 0;

    for (int i = 0; i < len; i++) {
        result = result + ((str[i] % 3) * (arr_pow_3[i]));
    }
    return result;
}

big_int new_hash(big_int hash, int len, char first_c, char last_c, big_int* arr_pow_3) {
    hash -= (first_c % 3);
    hash /= 3;
     
    hash += ((last_c % 3) * (arr_pow_3[len-1]));
    return hash;
}
bool is_matching(char* str, char* template,int len) {
    if (str == NULL || template == NULL || strlen(str)== strlen(template)) return false;
    for (int i = 0; i < len ; i++) {
        if (str[i] != template[i])
            return false;

    }
    return true;
}

big_int * init_array_pow_3(int n) {
    big_int result = 1;
    big_int * arr = (big_int*)malloc(n * sizeof(big_int));
    for (int i = 0; i < n+1; i++) {
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
char * re_init_array(char* line,int number) {
   
    for (int i = 0; i < strlen(line)-number; i++) {
        line[i] = line[number + i];
    }

}
int main()
{
    setlocale(LC_ALL, "Russian");
    
    big_int hash_s,hash_t;
    
    char line[SIZE_OF_BLOCK] = { 0 };
    char temp[SIZE_OF_BLOCK] = { 0 };
  
 
    FILE* file = fopen("file.txt", "r");
    
    fgets(temp, SIZE_OF_BLOCK, file);
    int len_temp = strlen(temp)-1;
    int here_ = 0;
    int num = 0;
    big_int arr_pow_3 = init_array_pow_3(len_temp);
    hash_t = init_hash(temp, len_temp, arr_pow_3);
    bool flag = true;
    while ( flag) {
        if (feof(file))
            flag = false;
        size_t f = fread(&line[here_], sizeof(char), SIZE_OF_BLOCK-here_, file);

        char* buffer = str_cut(line, 0, len_temp);

       

        hash_s = init_hash(buffer,len_temp, arr_pow_3);
  

        for (int i = 0; i <= f  +here_ - len_temp; i++) {
            if (hash_s == hash_t) {
                if (is_matching(str_cut(line, i, len_temp), temp, len_temp)) {
                    printf("yes %d", num + i);
                }

                
            }
            hash_s = new_hash(hash_s, len_temp, line[i], line[i + len_temp], arr_pow_3);
        }
        re_init_array(line, f - len_temp);
        here_ = len_temp;
        num += f - len_temp;
    }
    fclose(file);
    return 0;
}