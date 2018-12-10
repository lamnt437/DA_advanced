#include <stdio.h>

void main(){
	char c = EOF;
	int i = 1;
	char arr[10];
	for(i = 0; i < 10; i++){
		if(i % 2 == 0)
			arr[i] = 'y';
		else
			arr[i] = EOF;
	}

	for(i = 0; i < 10; i++){
		// if(arr[i] != EOF)
			printf("%c\n", arr[i]);
	}
}