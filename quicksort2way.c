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

void sort(int arr[], int l, int r) {
	if(r <= l)
		return;
	int i = l;
	int j = r;
	int pivotValue = arr[r];
	while(i < j){
		while(arr[i] < pivotValue && i < r)
			i++;
		while(arr[j] >= pivotValue && j > l)
			j--;
		if(i < j)
			swap(&arr[i], &arr[j]);
	}
	arr[r] = arr[i];
	arr[i] = pivotValue;
	printArray(arr, 20);
	sort(arr, l, i - 1);
	sort(arr, i + 1, r);
}

/*Worked*/

void sort3way(int a[], int l, int r) {
	if (r <= l) return;
	int i = l-1, j = r;
	int p = l-1, q = r;
	while(1)	{
		while (a[++i] < a[r]);
		while (a[r] < a[--j]) if (j == l) break;
		if (i >= j) break;
		swap(&a[i], &a[j]);
		if (a[i]==a[r]) swap(&a[++p], &a[i]);
		if (a[j]==a[r]) swap(&a[--q], &a[j]);
	}
	swap(&a[i], &a[r]);
	j = i - 1;
	i = i + 1;
	for (int k = l ; k <= p; k++) swap(&a[k], &a[j--]);
	for (int k = r-1; k >= q; k--) swap(&a[k], &a[i++]);
	printArray(a, 20);
	sort3way(a, l, j);
	sort3way(a, i, r);
}

/*Worked*/

void main(){
	// int a[] = {9, 8, 7, 10, 6, 3, 2};
	// printArray(a, 7);
	// sort(a, 0, 6);
	// int i = 0;

	// for(i = 0; i < 7; i++){
	// 	printf("%d ", a[i]);
	// }

	// gettimeofday(&start, NULL);
	// //running
	// gettimeofday(&stop, NULL);
	// elapsed = (double)(stop.tv_usec - start.tv_usec)/1000000 + (double)(stop.tv_sec - start.tv_sec);
	// printf("%f", elapsed);

	srand(time(NULL));
	int arr[20];
	int i;
	printf("Original array:\n");
	for(i = 0; i < 20; i++){
		// arr[i] = 1 + rand() % 100;
		arr[i] = 50 - i;
		printf("%d ", arr[i]);
	}
	printf("%d ", arr[19]);
	sort3way(arr, 0, 19);
	printf("\nSorted array:\n");
	for(i = 0; i < 20; i++){
		printf("%d ", arr[i]);
	}
}