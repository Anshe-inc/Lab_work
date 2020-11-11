#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ** read(int * size);
void sort(char ** string_arr, int size);
void out_str(char ** string_arr);

int cmp(const void* a, const void * b);
int int_num(char * string);
void clear_arr(char ** string_arr, int size);

int main(){
    char ** string_arr;
    int size;
    
    string_arr = read(&size);

    sort(string_arr, size);

    out_str(string_arr);

    clear_arr(string_arr, size);

    return 0;
}

char ** read(int * size){
    char * string;
    char ** res = malloc(sizeof(char *));
    int max_len, arr_size = 1;
    int i;
    for (i = 0; scanf("%ms %d", &string, &max_len) > 0; ++i) {
        //fprintf(stderr, "%s\n", string);
        if(arr_size <= i){
            res = realloc(res, 2 * arr_size * sizeof(char *));
            arr_size *= 2;
        }
        if ((int)strlen(string) > max_len) {
            string[max_len] = '\0';
        }
        res[i] = string;
    }
    res = realloc(res, i * sizeof(char *));

    *size = i;

    return res;
}

int cmp(const void * a, const void * b){
    char * str1 = *(char **)a;
    char * str2 = *(char **)b;
    int n1 = int_num(str1);
    int n2 = int_num(str2);
    //printf("%d %d\n", n1, n2);

    if(n1 == n2){
        return (int)str1[0] - (int)str2[0];
    }
    else {
        return n1 - n2;
    }
}

void sort(char ** string_arr, int size) {
    qsort(string_arr, size, sizeof(char*), cmp);
}


int int_num(char * string){
    //printf("\n%s\n", string);

    int res = 0;
    for(char *c = string; *c != '\0'; ++c){
        if((*c - '0') < 10){
            ++res;
        }
    }

    return res;
}

void out_str(char ** string_arr){
    printf("%d ", int_num(string_arr[0]));
    char *c = string_arr[0];
    for(int i = 0 ; ; ++c){
        if((*c - '0') < 10){
            ++i;
        }
        if(i == 2){
            printf("%c", *c);
            break;
        }
        if((*c == '\0') && (i < 2)){
            printf("-1");
            break;
        }
    }
    printf("\n");

}

void clear_arr(char ** string_arr, int size){
    for(int i = 0; i < size; ++i){
        free(string_arr[i]);
    }

    free(string_arr);
}