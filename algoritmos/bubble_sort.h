void bubble_sort (int vector[], int size){
    int k, j, aux;

    for (k = size - 1; k > 0; k--) {
        for (j = 0; j < k; j++) {
            if(vector[j] > vector[j + 1]) {
                aux = vector[j];
                vector[j] = vector[j + 1];
                vector[j + 1] = aux;
            }
        }
    }
}