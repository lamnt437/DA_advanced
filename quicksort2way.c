#include <stdio.h>
#include <stdlib.h>

void printArray(int arr[], int n){
	int i = 0;
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

// void sort(int arr[], int l, int r){
// 	if(l >= r)
// 		return;
// 	int pivotValue = arr[r];
// 	int i = l;
// 	int j = r - 1;
// 	while(1){
// 		while(arr[i] < pivotValue && i < j)
// 			i++;
// 		while(arr[j] > pivotValue && j > i){
// 			j--;
// 			if(i == j)
// 				break;
// 		}
		
// 		swap(&arr[i], &arr[j]);
// 		i++;
// 		j--;
// 		if(!(j > i))
// 			break;
// 	}

// 	swap(&arr[r], &arr[j + 1]);
// 	printArray(arr, 7);
// 	sort(arr, l, i - 2);
// 	sort(arr, i, r);
// }

void sort(int arr[], int l, int r) {
	if (r <= l) return;
	int i = l-1, j = r;
	int p = l-1, q = r;
	while(1)	{
		while (arr[++i] < arr[r]);
		while (arr[r] < arr[--j]) if (j == l) break;
		if (i >= j) break;
		// exch(a, i, j);
		swap(&arr[i], &arr[j]);
		// if (a[i]==a[r]) exch(a, ++p, i);
		// if (a[j]==a[r]) exch(a, --q, j);
	}
	// exch(a, i, r);
	swap(&arr[i], &arr[r]);
	j = j - 1;
	i = i + 1;
	// for (int k = l ; k <= p; k++) exch(a, k, j--);
	// for (int k = r-1; k >= q; k--) exch(a, k, i++);
	sort(arr, l, j);
	sort(arr, i, r);
}

void sort3way(int a[], int l, int r) {
	if (r <= l) return;
	int i = l-1, j = r;
	int p = l-1, q = r;
	while(1)	{
		while (a[++i] < a[r]);
		while (a[r] < a[--j]) if (j == l) break;
		if (i >= j) break;
		// exch(a, i, j);
		swap(&a[i], &a[j]);
		if (a[i]==a[r]) 
			// exch(a, ++p, i);
			swap(&a[++p], &a[i]);
		if (a[j]==a[r]) 
			// exch(a, --q, j);
			swap(&a[--q], &a[j]);
	}
	// exch(a, i, r);
	swap(&a[i], &a[r]);
	j = j - 1;
	i = i + 1;
	for (int k = l ; k <= p; k++) 
		// exch(a, k, j--);
		swap(&a[k], &a[j--]);
	for (int k = r-1; k >= q; k--) 
		// exch(a, k, i++);
		swap(&a[k], &a[i++]);
	sort3way(a, l, j);
	sort3way(a, i, r);
}

void main(){
	int a[] = {9, 8, 7, 10, 6, 3, 2};
	sort3way(a, 0, 6);
	int i = 0;
	for(i = 0; i < 7; i++){
		printf("%d ", a[i]);
	}
}