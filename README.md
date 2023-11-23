# Projeto - Probabilidade e Estatística

## Análise de Desempenho de Algoritmo - Ordenação

O intuito deste projeto é analisar estatísticamento o desempenho de três tipos diferentes de algoritmos de ordenação em diferentes situações de hardware e tamanho de vetores a serem ordenados. Os três tipos de algoritmos analisados são:

* **Bubble sort**;
* **Quick sort**;
* **Merge sort**;

## Como funciona a coleta de dados (no momento)

Temos os três algoritmos implementados em arquivos .h (_header files_) separados. O arquivo log.c realizará as medições de tempo de execução para cada um dos algoritmos.

O programa inicia com a geração do vetor a partir de um ponteiro **_unsigned int \*ptr_**, que armazena os endereços do vetor, mais a inicialização da **_seed_** (função **_srand()_**) para a geração de números pseudo-aleatórios e a abertura dos arquivos **_.csv_** para o registro dos dados de tempo de execução:

~~~c
int main(void){
    // vetor a ser ordenado
    unsigned int* ptr;
    
    // seed da função rand
    srand(time(NULL));

    // arquivo para gravar os tempos de execução das funções
    FILE *fpt = fopen("log.csv", "w");
    fprintf(fpt, "size, bubble_sort, merge_sort\n");
~~~

Depois, o algoritmo entra em um laço _for_, para gerar os vetores de diferentes tamanhos a cada ciclo de execução do laço. Os tamanhos são potências de base dois a começar por 2<sup>5</sup> = 32 elementos e termina com 2<sup>20</sup> = 1.048.576 elementos para ordenar. **_(Isso é passível de alteração no futuro)_**.

~~~c
for (int exp = 5; exp <= 20; exp++){
        int size = pow(2,exp); // tamanho do vetor
        ptr = (unsigned int*)malloc(size * sizeof(unsigned int)); // alocação de memoria para o vetor
        generate(ptr, size); // gera os elementos do vetor
        shuffle(ptr, size); // embaralha o vetor
        printf("%d\n", time_quick_sort(ptr, size));
        free(ptr);
    }
~~~

As funções **_generate()_** e **_shuffle()_** são responsáveis por gerar os elementos do vetor e depois embaralhá-lo.

~~~c
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
~~~

As funções **_time\_\*_** são as responsáveis por aferir o tempo de execução de cada algoritmo de ordenação. Elas recebem o vetor para ordenar além de seu tamanho atual. Elas realizam a cópia do vetor com a chamada da função **_copy\_vector()_**. As funções **_time\_\*_** devolvem o tempo de execução em microsegundos.

### time\_quick\_sort():

~~~c
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
~~~

Um exemplo de um arquivo **_.csv_** gerado (_merge\_log_):

|size  |time1 |time2 |time3 |time4 |time5 |
|------|------|------|------|------|------|
|32    | 1    | 1    | 1    | 2    | 2    |
|64    | 2    | 3    | 3    | 4    | 4    |
|128   | 6    | 8    | 8    | 8    | 11   |
|256   | 21   | 44   | 18   | 19   | 22   |
|512   | 51   | 54   | 60   | 51   | 48   |
|1024  | 103  | 107  | 100  | 102  | 114  |
|2048  | 186  | 216  | 204  | 173  | 195  |
|4096  | 398  | 455  | 411  | 407  | 398  |
|8192  | 866  | 886  | 829  | 828  | 845  |
|16384 | 1770 | 1771 | 1748 | 1744 | 1749 |
|32768 | 3889 | 3900 | 3853 | 3861 | 3898 |
|65536 | 8213 | 8272 | 8911 | 8394 | 9246 |
|131072| 19414| 17547| 17742| 17423| 17392|
|262144| 37069| 37696| 37151| 37056| 38512|

~~~csv
size, time1, time2, time3, time4, time5
32, 2, 1, 2, 3, 3
64, 4, 5, 4, 5, 6
128, 10, 11, 11, 12, 13
256, 29, 29, 29, 29, 30
512, 56, 57, 59, 60, 64
1024, 92, 115, 125, 137, 141
2048, 285, 202, 208, 215, 283
4096, 433, 435, 432, 437, 469
8192, 934, 933, 935, 938, 977
16384, 1991, 1991, 1989, 1994, 2128
32768, 6000, 4237, 4253, 4307, 4376
65536, 9084, 8950, 8915, 9921, 9271
131072, 20780, 18967, 18888, 19165, 19218
~~~

## A fazer

* A execução do **_.exe_** será realizada pelo _script_ _python_ **_main.py_** que ainda será modificado para também ler os arquivos **_.csv_** e organizá-los em _dataframes_ do _pandas_.
* O _script_ _python_ será modificado para também ler as informações do hardware em que os dados foram obtidos.
* Acredito que a inserção no banco de dados deve ser feita por um outro _script_ _python_ a ser desenvolvido.
