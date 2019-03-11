// Баймаканов В.К. АПО-11
// Составить программу построчной обработки текста. Суть обработки - отбор строк, содержащих одинаковое количество открывающих и закрывающих круглых скобок.
// Программа считывает входные данные со стандартного ввода, и печатает результат в стандартный вывод.
// Процедура отбора нужных строк должна быть оформлена в виде отдельной функции, которой на вход подается массив строк (который необходимо обработать), количество переданных строк, а также указатель на переменную, в которой необходимо разместить результат - массив отобранных строк.
// В качестве возвращаемого значения функция должна возвращать количество строк, содержащихся в результирующем массиве.
// Программа должна уметь обрабатывать ошибки - такие как неверные входные данные(отсутствие входных строк) или ошибки выделения памяти и т.п.
// В случае возникновения ошибки нужно выводить об этом сообщение "[error]" и завершать выполнение программы.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

char* getString();
char** getArrayOfStrings(uint32_t*);
uint32_t myFunction(char**, uint32_t);

int main(void){
    uint32_t num_of_strings = 0;
    char** strings = getArrayOfStrings(&num_of_strings);
    if(strings == NULL){
        printf("error");
        return 0;
    }
    myFunction(strings, num_of_strings-1);                  // Последняя строка пустая
    for(uint32_t i = 0; i < num_of_strings; ++i){
        free(strings[i]);
    }
    free(strings);
    return 0;
}

char* getString(){
    uint32_t string_size = 32;
    uint32_t ptr_counter = 0;
    char* string = (char*)malloc(sizeof(char)*string_size);
    do{
        string[ptr_counter++] = getchar();
        if(ptr_counter == string_size && string[ptr_counter-1] != '\n'){
            string_size *= 2;
            char* new_string = (char*)realloc(string, sizeof(char)*string_size);
            if(new_string == NULL){
                free(string);
                return NULL;
            }
            string = new_string;
        }
    }while(string[ptr_counter-1] != '\n' && string[ptr_counter-1] != EOF);
    string[ptr_counter-1] = '\0';

    return string;
}

char** getArrayOfStrings(uint32_t *num_of_strings){
    uint32_t array_size = 8;
    uint32_t str_ptr = 0;

    char** strings = (char**)malloc(sizeof(char*)*array_size);
    do{
        strings[str_ptr++] = getString();
        if(strings[str_ptr-1] == NULL){
            free(strings);
            return NULL;
        }
        if(str_ptr == array_size){
            array_size *= 2;
            char** new_strings = (char**)realloc(strings, sizeof(char*)*array_size);
            if(new_strings == NULL){
                free(strings);
                return NULL;
            }
            strings = new_strings;
        }
        ++(*num_of_strings);
    }while( *(strings[str_ptr-1]) != '\0');

    return strings;
}

uint32_t myFunction(char** strings, uint32_t num_of_strings){
    uint32_t num_of_correct_strings = 0;
    uint32_t left_brackets_num = 0;
    uint32_t right_brackets_num = 0;
    uint32_t ptr_counter = 0;

    if(strings == NULL){
        printf("error");
        return 0;
    }

    for(uint32_t i = 0; i < num_of_strings; ++i){
        ptr_counter = left_brackets_num = right_brackets_num = 0;
        while(strings[i][ptr_counter++] != '\0'){
            if(strings[i][ptr_counter-1] == '('){
                ++left_brackets_num;
            } else if(strings[i][ptr_counter-1] == ')'){
                ++right_brackets_num;
            }
        }
        if(right_brackets_num == left_brackets_num){
            ++num_of_correct_strings;
            printf("%s\n", strings[i]);
        }
    }

    return num_of_correct_strings;
}