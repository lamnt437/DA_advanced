#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int int_compare(void *a, void *b){
	return (*((int *)a) - *((int *)b));
}

int binSearch(int arr[], int key, int l, int r, int (*compare)(void *a, void *b)){
	if(l >= r)
		return - 1;
	int m = (l + r)/2;
	int result = compare(&key, &arr[m]);
	printf("%d\n", result);
	if(result == 0)
		return m;
	if(result < 0)
		return binSearch(arr, key, l, m - 1, compare);
	return binSearch(arr, key, m + 1, r, compare);
}

// int search(  void* buf,int size,int l, int r,void * item,int (*compare)(void*, void*)) {
// 	if (r < l) return -1;
// 	int i = (l + r)/2;
// 	int res = compare( item, (char*)buf+(size*i) );
// 	if (res==0)
// 		return i;
// 	else if (res < 0)
// 		return search(buf, size, l, i-1, item, compare);
// 	else
// 		return search(buf, size, i+1, r, item, compare);
// }


void main(){
	int arr[] = {1, 2, 3, 4, 5, 6, 7};
	int key = 7;
	// int result = search(arr, sizeof(int), 0, 6, &key, int_compare);
	int result = binSearch(arr, key, 0, 6, int_compare);
	printf("%d", result);
}