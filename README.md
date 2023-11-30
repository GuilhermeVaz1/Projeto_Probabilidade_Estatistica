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
// medição e coletas
for (int exp = 1; exp <= 18; exp++){
    int size = pow(2,exp); // tamanho do vetor
    ptr = (unsigned int*)malloc(size * sizeof(unsigned int)); // alocação de memoria para o vetor
    generate(ptr, size); // gera os elementos do vetor
    shuffle(ptr, size); // embaralha o vetor
    system("cls");
    printf("Size: %d\n", size);
    printf("Size in bytes: %d\n\n", size * sizeof(unsigned int));
    printf("timing quick sort...\n");
    fprintf(quick_log, "%d, %d, %d, %d, %d, %d\n", size, time_quick_sort(ptr, size), time_quick_sort(ptr, size), time_quick_sort(ptr, size), time_quick_sort(ptr, size), time_quick_sort(ptr, size));
    fflush(quick_log);
    printf("timing merge sort...\n");
    fprintf(merge_log, "%d, %d, %d, %d, %d, %d\n", size, time_merge_sort(ptr, size), time_merge_sort(ptr, size), time_merge_sort(ptr, size), time_merge_sort(ptr, size), time_merge_sort(ptr, size));
    fflush(merge_log);
    printf("timing bubble sort...\n");
    fprintf(bubble_log, "%d, %d, %d, %d, %d, %d\n", size, time_bubble_sort(ptr, size, 5), time_bubble_sort(ptr, size, 4), time_bubble_sort(ptr, size, 3), time_bubble_sort(ptr, size, 2), time_bubble_sort(ptr, size, 1));
    fflush(bubble_log);
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

## Criação do Banco de Dados

~~~sql
CREATE TABLE IF NOT EXISTS hardware(
	id SERIAL PRIMARY KEY,
	cpu VARCHAR(100) NOT NULL,
	ram real NOT NULL
);

CREATE TABLE IF NOT EXISTS bubble_results(
	id SERIAL PRIMARY KEY,
	hardware_id INT,
	size INT NOT NULL,
	time1 INT NOT NULL,
	time2 INT NOT NULL,
	time3 INT NOT NULL,
	time4 INT NOT NULL,
	time5 INT NOT NULL,
	CONSTRAINT hardware_id FOREIGN KEY(hardware_id) REFERENCES hardware(id)
);

CREATE TABLE IF NOT EXISTS quick_results(
	id SERIAL PRIMARY KEY,
	hardware_id INT,
	size INT NOT NULL,
	time1 INT NOT NULL,
	time2 INT NOT NULL,
	time3 INT NOT NULL,
	time4 INT NOT NULL,
	time5 INT NOT NULL,
	CONSTRAINT hardware_id FOREIGN KEY(hardware_id) REFERENCES hardware(id)
);

CREATE TABLE IF NOT EXISTS merge_results(
	id SERIAL PRIMARY KEY,
	hardware_id INT,
	size INT NOT NULL,
	time1 INT NOT NULL,
	time2 INT NOT NULL,
	time3 INT NOT NULL,
	time4 INT NOT NULL,
	time5 INT NOT NULL,
	CONSTRAINT hardware_id FOREIGN KEY(hardware_id) REFERENCES hardware(id)
);
~~~

São apenas 4 tabelas, uma para o _hardware_ e 3 para os resultados de cada algoritmo. Os resultados possuem uma chave estrangeira que é a **_id_** do _hardware_, podendo relacionar uma linha de resultado a um _hardware_ especifico.

Depois são criadas funções para retornar os resultados a partir de um **_id_** de _hardware_ específico.

~~~sql
CREATE OR REPLACE FUNCTION
bubble(aaa int)
RETURNS TABLE (
	id int,
	hardware_id int,
	size int,
	time1 int,
	time2 int,
	time3 int,
	time4 int,
	time5 int
)
LANGUAGE plpgsql AS
$func$
BEGIN
	RETURN QUERY
	SELECT * FROM bubble_results WHERE bubble_results.hardware_id = aaa
	ORDER BY bubble_results.id;
END
$func$;

CREATE OR REPLACE FUNCTION
merge(aaa int)
RETURNS TABLE (
	id int,
	hardware_id int,
	size int,
	time1 int,
	time2 int,
	time3 int,
	time4 int,
	time5 int
)
LANGUAGE plpgsql AS
$func$
BEGIN
	RETURN QUERY
	SELECT * FROM merge_results WHERE merge_results.hardware_id = aaa
	ORDER BY merge_results.id;
END
$func$;

CREATE OR REPLACE FUNCTION
quick(aaa int)
RETURNS TABLE (
	id int,
	hardware_id int,
	size int,
	time1 int,
	time2 int,
	time3 int,
	time4 int,
	time5 int
)
LANGUAGE plpgsql AS
$func$
BEGIN
	RETURN QUERY
	SELECT * FROM quick_results WHERE quick_results.hardware_id = aaa
	ORDER BY quick_results.id;
END
$func$;
~~~

## Inserção no Banco de Dados

A inserção dos dados no Banco é feita com a ajuda de um _script_ _python_ chamado **_sql.py_**. Primeiro ele se conecta com o banco criado:

~~~python
import psycopg2 as psql
import os
import pandas as pd

# conecta-se ao banco de dados local
conn = psql.connect(
    host='localhost',
    database='algoritmos',
    user='postgres',
    password='ypghck52'
)

cur = conn.cursor()

~~~

Depois, lê as pastas _timestamps_ que contém os dados de hardware, e os tempos de execução de cada algoritmo.

~~~python
# para cada diretório na pasta output
# verifica se a pasta é uma timestamp
# e depois faz as verificações e inserções
# no banco
for dir in os.listdir('./output'):

    if '2023' not in dir: # verifica timestamp
        continue

    # lê o arquivo com as informações de hardware
    f = open(f'./output/{dir}/hardware_info.txt', 'r') 
    f.readline()
    f.readline()
    cpu = f.readline().strip('\n')
    ram = f.readline()
    f.close()
~~~

Realizando verificações para saber se o hardware e os tempos de execução já estão presentes no banco.

~~~python
    # verifica se o banco já contém este hardware
    cur.execute(f"SELECT EXISTS(SELECT 1 FROM hardware WHERE cpu='{cpu}' AND ram={ram})")
    ret = cur.fetchone()
    conn.commit()

    if ret[0]: # contém, então procura o id deste hardware
        cur.execute(f"SELECT id FROM hardware WHERE cpu='{cpu}' AND ram={ram}")
        hardware_id = cur.fetchone()[0]
        conn.commit()
    
    else: # não contém, então insere e busca o id atribuído a ele
        cur.execute(f"INSERT INTO hardware (cpu, ram) VALUES ('{cpu}', {ram})")
        conn.commit()
        cur.execute(f"SELECT id FROM hardware WHERE cpu='{cpu}' AND ram={ram}")
        hardware_id = cur.fetchone()[0]
        conn.commit()
~~~

Por fim, insere os dados no banco

~~~python
    # busca os resultados e insere no banco
    bubble_result = pd.read_csv(f'./output/{dir}/bubble_log.csv')
    for index, row in bubble_result.iterrows():
        cur.execute(f"SELECT EXISTS(SELECT 1 FROM bubble_results WHERE hardware_id={hardware_id} AND size={row['size']} AND time1={row[' time1']} AND time2={row[' time2']} AND time3={row[' time3']} AND time4={row[' time4']} AND time5={row[' time5']})")
        conn.commit()
        ret = cur.fetchone()[0]
        if not ret:
            cur.execute(f"INSERT INTO bubble_results (hardware_id, size, time1, time2, time3, time4, time5) VALUES ({hardware_id}, {row['size']}, {row[' time1']}, {row[' time2']}, {row[' time3']}, {row[' time4']}, {row[' time5']})")
            conn.commit()
~~~
