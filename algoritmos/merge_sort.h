// void merge(int arr[], int p, int q, int r) {

//   int n1, n2, i, j, k;

//   n1 = q - p + 1;
//   n2 = r - q;

//   int L[n1], M[n2];

//   for (i = 0; i < n1; i++)
//     L[i] = arr[p + i];
//   for (j = 0; j < n2; j++)
//     M[j] = arr[q + 1 + j];

//   i = 0;
//   j = 0;
//   k = p;

//   while (i < n1 && j < n2) {
//     if (L[i] <= M[j]) {
//       arr[k] = L[i];
//       i++;
//     } else {
//       arr[k] = M[j];
//       j++;
//     }
//     k++;
//   }

//   while (i < n1) {
//     arr[k] = L[i];
//     i++;
//     k++;
//   }

//   while (j < n2) {
//     arr[k] = M[j];
//     j++;
//     k++;
//   }
// }

// void merge_sort(int arr[], int l, int r) {
//   if (l < r) {

//     int m = l + (r - l) / 2;

//     merge_sort(arr, l, m);
//     merge_sort(arr, m + 1, r);

//     merge(arr, l, m, r);
//   }
// }



void merge(int *v, int *c, int i, int m, int f) {
  	int z,
      	iv = i, ic = m + 1;

  	for (z = i; z <= f; z++) c[z] = v[z];

  	z = i;

  	while (iv <= m && ic <= f) {

    	if (c[iv] <= c[ic]) v[z++] = c[iv++];
    	else v[z++] = c[ic++];
  	}

  	while (iv <= m) v[z++] = c[iv++];

  	while (ic <= f) v[z++] = c[ic++];
}

void sort(int *v, int *c, int i, int f) {
	if (i >= f) return;

  	int m = (i + f) / 2;

  	sort(v, c, i, m);
  	sort(v, c, m + 1, f);

  	if (v[m] <= v[m + 1]) return;

  	merge(v, c, i, m, f);
}

void merge_sort(int *v, int n) {
  	int *c = malloc(sizeof(int) * n);
  	sort(v, c, 0, n - 1);
  	free(c);
}