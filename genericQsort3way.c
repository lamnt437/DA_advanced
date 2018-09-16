#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArray(int arr[], int n){
	int i = 0;
	printf("\n");
	for(i = 0; i < n; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

int int_compare(void const *a, void const *b){
	return (*((int *)a) - *((int *)b));
}

void sort3way(int a[], int l, int r, int (*compare)(void const *a, void const *b)) {
	if (r <= l) return;
	int i = l-1, j = r;
	int p = l-1, q = r;
	while(1){
		// while (a[++i] < a[r]);
		while(compare(&a[++i], &a[r]) < 0);
		// while (a[r] < a[--j]) if (j == l) break;
		while(compare(&a[r], &a[--j]) < 0) if(j == l) break;
		if (i >= j) break;
		swap(&a[i], &a[j]);
		if (compare(&a[i], &a[r]) == 0) swap(&a[++p], &a[i]);
		if (compare(&a[j], &a[r]) == 0) swap(&a[--q], &a[j]);
	}
	swap(&a[i], &a[r]);
	j = i - 1;
	i = i + 1;
	for (int k = l ; k <= p; k++) swap(&a[k], &a[j--]);
	for (int k = r-1; k >= q; k--) swap(&a[k], &a[i++]);
	sort3way(a, l, j, (*compare));
	sort3way(a, i, r, (*compare));
}

void main(){
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
	sort3way(arr1, 0, n - 1, int_compare);
	printArray(arr1, n);
}