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