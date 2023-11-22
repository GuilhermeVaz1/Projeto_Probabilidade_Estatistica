#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <processthreadsapi.h>
#include "bubble_sort.h"
#include "merge_sort.h"
#include "quick_sort.h"

void generate(unsigned int ptr[], int size){ // gera os elementos do vetor
    for(int i = 0; i < size; i++){
        ptr[i] = i;
    }
}

void shuffle(unsigned int ptr[], int size){ // embaralha o vetor
    for (int i = 0; i < size; i++) {
        int temp = ptr[i];
        int randomIndex = rand() % size;
        ptr[i] = ptr[randomIndex];
        ptr[randomIndex] = temp;
    }
}

void print_vetor(int ptr[], int size){
    for(int i = 0; i < size; i++)
        printf("%d, ", ptr[i]);

    printf("\n");
}

void copy_vector(int ptr[], int size, int copy[]){

    for(int i = 0; i < size; i++){
        copy[i] = ptr[i];
    }
}

long time_bubble_sort(int ptr[], int size){
    // variáveis para medir tempo de execução das funções
    struct timeval start, end;

    int copy[size]; // gera uma cópia do vetor
    copy_vector(ptr, size, copy);

    mingw_gettimeofday(&start, NULL);
    bubble_sort(copy, size);
    mingw_gettimeofday(&end, NULL);
    long elapsed = ((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec);
    //print_vetor(copy, size);
    return elapsed;
}

long time_merge_sort(int ptr[], int size){
    // variáveis para medir tempo de execução das funções
    struct timeval start, end;

    int copy[size]; // gera uma cópia do vetor
    copy_vector(ptr, size, copy);

    mingw_gettimeofday(&start, NULL);
    merge_sort(copy, 0, size - 1);
    mingw_gettimeofday(&end, NULL);
    long elapsed = ((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec);
    //print_vetor(copy, size);
    return elapsed;
}

long time_quick_sort(int ptr[], int size){
    // variáveis para medir tempo de execução das funções
    struct timeval start, end;

    int copy[size]; // gera uma cópia do vetor
    copy_vector(ptr, size, copy);

    mingw_gettimeofday(&start, NULL);
    quick_sort(copy, 0, size - 1);
    mingw_gettimeofday(&end, NULL);
    long elapsed = ((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec);
    //print_vetor(copy, size);
    return elapsed;
}

int main(void){
    // vetor a ser ordenado
    unsigned int* ptr;
    
    // seed da função rand
    srand(time(NULL));

    // arquivo para gravar os tempos de execução das funções
    FILE *fpt = fopen("log.csv", "w");
    fprintf(fpt, "size, bubble_sort, merge_sort\n");


    for (int exp = 5; exp <= 20; exp++){
        int size = pow(2,exp); // tamanho do vetor
        ptr = (unsigned int*)malloc(size * sizeof(unsigned int)); // alocação de memoria para o vetor
        generate(ptr, size); // gera os elementos do vetor
        shuffle(ptr, size); // embaralha o vetor
        printf("%d\n", time_quick_sort(ptr, size));
        free(ptr);
    }
    system("PAUSE");
    free(ptr);
    fclose(fpt);
    return 0;
}