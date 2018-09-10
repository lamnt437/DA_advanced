#include <stdio.h>

void main(){
	int arr[] = {1, 2, 3};
	if(arr[3] < 0)
		printf("%d", arr[3]);
	else
		printf("!arr[3] < 0");
}