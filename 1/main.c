#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// прототипы функций
char ** read(int * size);                   // считывает данные возвращает массив и размер
void sort(char ** string_arr, int size);    // сортирует массив строк
void out_str(char ** string_arr);           // вывод ланных

int cmp(const void* a, const void * b);     // функция-сравниватель
int int_num(char * string);                 // считает количество цифр
void clear_arr(char ** string_arr, int size);// освобождает память после завершения программы

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
    char * string;                              // для хранения массива
    char ** res = malloc(sizeof(char *));       // выделение 1 элемента
    int max_len, arr_size = 1;
    int i;
    for (i = 0; scanf("%ms %d", &string, &max_len) > 0; ++i) {
        // считываем данные завершаемся, когда конец
        if(arr_size <= i){
            // увеличиваем память при нехватке места в 2 раза
            res = realloc(res, 2 * arr_size * sizeof(char *));
            arr_size *= 2;
        }
        if ((int)strlen(string) > max_len) {
            string[max_len] = '\0';
        }
        res[i] = string;
    }
    // переопределяем размер памяти так как 2^([log_2(N)] + 1) это много 
    res = realloc(res, i * sizeof(char *));
    // записываем размер в size
    *size = i;

    return res;
}

int cmp(const void * a, const void * b){
    // сравниваем строки по количеству цифр
    // иначе лексикографически 
    char * str1 = *(char **)a;
    char * str2 = *(char **)b;
    int n1 = int_num(str1);
    int n2 = int_num(str2);

    if(n1 == n2){
        return strcmp(str1, str2);
    }
    else {
        return n1 - n2;
    }
}

void sort(char ** string_arr, int size) {
    qsort(string_arr, size, sizeof(char*), cmp);
}


int int_num(char * string){
    // функция подсчета количества цифр в строке

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
    // ищет 2 цифру в строке
    // нет цифры -- -1
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