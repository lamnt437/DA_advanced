#include "huffmanArray.h"
#include <stdio.h>

int main(int argc, char *argv[]){
	if(argc != 3){
		puts("Wrong number of arguments!");
		return 1;
	}

	FILE *input = fopen(argv[1], "r");
	if(input == NULL){
		puts("Input file doesn't exist!");
		return 2;
	}

	FILE *output = fopen(argv[2], "w");
	compressFile(input, output);

	fclose(input);
	fclose(output);

	return 0;
}