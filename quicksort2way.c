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

void sort(int arr[], int l, int r){
	if(l >= r)
		return;
	int pivotValue = arr[r];
	int i = l;
	int j = r - 1;
	while(1){
		while(arr[i] < pivotValue && i < j)
			i++;
		while(arr[j] > pivotValue && j > i){
			j--;
			if(i == j)
				break;
		}
		
		swap(&arr[i], &arr[j]);
		i++;
		j--;
		if(!(j > i))
			break;
	}

	swap(&arr[r], &arr[j + 1]);
	printArray(arr, 7);
	sort(arr, l, i - 2);
	sort(arr, i, r);
}



void main(){
	int a[] = {9, 8, 7, 10, 6, 3, 2};
	sort(a, 0, 6);
	int i = 0;
	for(i = 0; i < 7; i++){
		printf("%d ", a[i]);
	}
}