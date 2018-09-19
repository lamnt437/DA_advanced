#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void printArray(int arr[], int n){
	int i = 0;
	printf("\n");
	for(i = 0; i < n; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void swap(void *a, void *b, size_t size){
    void *temp = malloc(size);
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
    free(temp);
}

int int_compare(void *a, void *b){
	return (*((int *)a) - *((int *)b));
}

void sort3way(void *a, size_t eSize, int l, int r, int (*compare)(void *a, void *b)) {
	if (r <= l) return;
	int i = l-1, j = r;
	int p = l-1, q = r;
	int pivotValue = *((int *)(a + r * eSize));
	while(1){
		int status;
		while((status = compare(a + (++i) * eSize, &pivotValue)) < 0);
		while((status = compare(&pivotValue, a + (--j) * eSize)) < 0) if(j == l) break;
		if (i >= j) break;
		swap(a + i *eSize, a + j * eSize, eSize);
		if (compare(a + i * eSize, a + r * eSize) == 0)
			swap(a + (++p) * eSize, a + i * eSize, eSize);
		if (compare(a + j * eSize, a + r * eSize) == 0)
			swap(a + (--q) * eSize, a + j * eSize, eSize);
	}
	swap(a + i * eSize, a + r * eSize, eSize);
	j = i - 1;
	i = i + 1;
	for (int k = l ; k <= p; k++)
		swap(a + k * eSize, a + (j--) * eSize, eSize);
	for (int k = r-1; k >= q; k--)
		swap(a + k * eSize, a + (i++) * eSize, eSize);
	sort3way(a, eSize, l, j, (*compare));
	sort3way(a, eSize, i, r, (*compare));
}

int main(){
    int n, i;
    printf("Enter n: ");
	scanf("%d", &n);

	//randomize array
	srand(time(NULL));
	int arr1[n];

	for(i = 0; i < n; i++){
		arr1[i] = 1 + rand() % 10;
	}
	printArray(arr1, n);
	sort3way(arr1, sizeof(int), 0, n - 1, int_compare);
	printArray(arr1, n);

	return 0;
}
