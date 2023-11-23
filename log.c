#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <processthreadsapi.h>
#include "algoritmos/bubble_sort.h"
#include "algoritmos/merge_sort.h"
#include "algoritmos/quick_sort.h"

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

    // arquivo para gravar os tempos de execução
    FILE* quick_log = fopen("quick_log.csv", "w+");
    fprintf(quick_log, "size, time1, time2, time3, time4, time5\n");
    fflush(quick_log);

    FILE* merge_log = fopen("merge_log.csv", "w");
    fprintf(merge_log, "size, time1, time2, time3, time4, time5\n");
    fflush(merge_log);

    FILE* bubble_log = fopen("bubble_log.csv", "w");
    fprintf(bubble_log, "size, time1, time2, time3, time4, time5\n");
    fflush(bubble_log);

    //quick_sort
    for (int exp = 5; exp <= 20; exp++){
        int size = pow(2,exp); // tamanho do vetor
        ptr = (unsigned int*)malloc(size * sizeof(unsigned int)); // alocação de memoria para o vetor
        generate(ptr, size); // gera os elementos do vetor
        shuffle(ptr, size); // embaralha o vetor
        fprintf(quick_log, "%d, %d, %d, %d, %d, %d\n", size, time_quick_sort(ptr, size), time_quick_sort(ptr, size), time_quick_sort(ptr, size), time_quick_sort(ptr, size), time_quick_sort(ptr, size));
        fflush(quick_log);
        fprintf(merge_log, "%d, %d, %d, %d, %d, %d\n", size, time_merge_sort(ptr, size), time_merge_sort(ptr, size), time_merge_sort(ptr, size), time_merge_sort(ptr, size), time_merge_sort(ptr, size));
        fflush(merge_log);
        fprintf(bubble_log, "%d, %d, %d, %d, %d, %d\n", size, time_bubble_sort(ptr, size), time_bubble_sort(ptr, size), time_bubble_sort(ptr, size), time_bubble_sort(ptr, size), time_bubble_sort(ptr, size));
        fflush(bubble_log);
        free(ptr);
    }

    fclose(quick_log);
    fclose(merge_log);

    

    free(ptr);
    fclose(merge_log);
    return 0;
}