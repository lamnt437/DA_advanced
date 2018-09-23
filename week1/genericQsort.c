#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

int int_compare(void const *a, void const *b){
    return -(*((int *)a) - *((int *)b));
}

void sort(int arr[], int l, int r, int (*compare)(void const *a, void const *b)) {
	if(r <= l)
		return;
	int i = l;
	int j = r;
	int pivotValue = arr[r];
	while(i < j){
		//while(arr[i] < pivotValue && i < r)
		while((*compare)(&arr[i], &pivotValue) < 0 && i < r)
			i++;
		//while(arr[j] >= pivotValue && j > l)
		while((*compare)(&arr[j], &pivotValue) >= 0 && j > l)
			j--;
		if(i < j)
			swap(&arr[i], &arr[j]);
	}
	arr[r] = arr[i];
	arr[i] = pivotValue;
	sort(arr, l, i - 1, (*compare));
	sort(arr, i + 1, r, (*compare));
}

void printArray(int arr[], int n){
	int i = 0;
	printf("\n");
	for(i = 0; i < n; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main()
{
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
	sort(arr1, 0, n - 1, int_compare);
	printArray(arr1, n);

	return 0;
}
