#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int int_compare(void const *a, void const *b){
	return (*((int *) a) - *((int *) b));
}

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

int testSorted(int arr[], int n){
	int i;
	for(i = 1; i < n; i++){
		if(arr[i] < arr[i - 1])
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

void sort3way(int a[], int l, int r) {
	if (r <= l) return;
	int i = l-1, j = r;
	int p = l-1, q = r;
	while(1){
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
	sort3way(a, l, j);
	sort3way(a, i, r);
}

void main(){
	int n;
	double elapsed;
	struct timeval start, stop;

	//input size
	printf("Enter n: ");
	scanf("%d", &n);

	//randomize array
	srand(time(NULL));
	int arr1[n];
	int arr2[n];
	int i;

	for(i = 0; i < n; i++){
		arr1[i] = 1 + rand() % 10;
		arr2[i] = arr1[i];
	}

	//using qsort
	gettimeofday(&start, NULL);
	qsort(arr1, n, sizeof(int), int_compare);
	gettimeofday(&stop, NULL);

	printf("\nCheck: ");
	if(testSorted(arr1, n)){
		printf("%s\n", "true");
	}
	else{
		printf("%s\n", "false");
	}
	elapsed = (double)(stop.tv_usec - start.tv_usec)/1000000 + (double)(stop.tv_sec - start.tv_sec);
	printf("time: %f\n", elapsed);

	//using handmade qsort
	gettimeofday(&start, NULL);
	sort3way(arr2, 0, n - 1);
	gettimeofday(&stop, NULL);
	
	printf("\nCheck handmade: ");
	if(testSorted(arr2, n)){
		printf("%s\n", "true");
	}
	else{
		printf("%s\n", "false");
	}
	elapsed = (double)(stop.tv_usec - start.tv_usec)/1000000 + (double)(stop.tv_sec - start.tv_sec);
	printf("time: %f\n", elapsed);
}