#include <stdio.h>
#include "btree.h"
#include <string.h>
// add option -lbt

int main(){
	BTA * dict;
	BTint *ptr = NULL;
	char key[ZKYLEN];
	char search_key[ZKYLEN];
	int val;
	btinit();

	dict = btcrt("test.data", 0, FALSE);
	binsky(dict, "a", 123);
	binsky(dict, "b", 234);//map string to int

	// btins();//map string to buffer + length of buffer
	btpos(dict, ZSTART); //change the position to the beginning
	while(bnxtky(dict, key, &val) == 0){
		printf("%s -> %d\n", key, val);
	}

	// getchar();
	printf("Enter str to search: ");
	fgets(search_key, 30, stdin);
	search_key[strlen(search_key) - 1] = '\0';
	int status = bfndky(dict, search_key, ptr);
	printf("find status: %d\n", status);

	btcls(dict);

	return 0;
}