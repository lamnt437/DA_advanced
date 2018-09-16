#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int int_compare(void const *a, void const *b){
	return -(*((int *) a) - *((int *) b));
}

int testSortedDesc(int arr[], int n){
	int i;
	for(i = 1; i < n; i++){
		if(arr[i] > arr[i - 1])
			return 0;
	}
	return 1;
}

void printArray(int arr[], int n){
	int i;
	printf("\n");
	for(i = 0; i < n; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void main(){
	int n;
	//input size
	printf("Enter n: ");
	scanf("%d", &n);

	//randomize array
	srand(time(NULL));
	int arr[n];
	int i;

	printf("Original:\n");
	for(i = 0; i < n; i++){
		arr[i] = 1 + rand() % 10;
		// printf("%d ", arr[i]);
	}
	printf("\n");

	qsort(arr, n, sizeof(int), int_compare);
	printf("Sorted: ");
	// printArray(arr, n);

	//check
	printf("\nCheck: ");
	if(testSortedDesc(arr, n)){
		printf("%s\n", "true");
	}
	else{
		printf("%s\n", "false");
	}
}