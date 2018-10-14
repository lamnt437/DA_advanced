#include <stdio.h>
#include "btree.h"
// add option -lbt when compile to auto locate lib

int main(){
	BTA * dict;
	char key[ZKYLEN];
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
	btcls(dict);

	return 0;
}