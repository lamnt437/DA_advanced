#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int A[], int a, int b){
	int temp = A[a];
	A[a] = A[b];
	A[b] = temp;
}

int partition(int A[], int low, int high){
	int left = low;
	int right = high;
	int pivot_item = A[low];
	while(left < right){
		while(A[left] <= pivot_item && left < high){
			left++;
		}
		while(A[right] > pivot_item && right > low){
			right--;
		}
		if(left < right)
			swap(A, left, right);
	}

	A[low] = A[right];
	A[right] = pivot_item;
	return right;
}

void quicksort(int A[], int low, int high){
	int pivot;

	if(high > low){
		pivot = partition(A, low, high);
		quicksort(A, low, pivot - 1);
		quicksort(A, pivot + 1, high);
	}
}



void main(){
	srand(time(NULL));
	int arr[20];
	int i;
	printf("Original array:\n");
	for(i = 0; i < 20; i++){
		// arr[i] = 1 + rand() % 100;
		arr[i] = 50 - i;
		printf("%d ", arr[i]);
	}
	quicksort(arr, 0, 19);
	printf("\nSorted array:\n");
	for(i = 0; i < 20; i++){
		printf("%d ", arr[i]);
	}

	// int a[] = {9, 8, 7, 10, 6, 3, 2};
	// quicksort(a, 0, 6);
	// int i;
	// for(i = 0; i < 7; i++){
	// 	printf("%d ", a[i]);
	// }
}