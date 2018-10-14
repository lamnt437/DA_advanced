#include "bta_symtab.h"
#include <stdlib.h>

//need
//jval lib => libfdr.a
//btree lib =>libbta.a

// typedef struct {
// 	Jval key;
// 	Jval value;
// } Entry;

// typedef struct {
// 	BTA * entries;
// 	int total;
// } SymbolTable;

// SymbolTable *createSymbolTable();
// void dropSymbolTable(SymbolTable* tb);
// Entry getEntry(Jval key, SymbolTable *tb);
// void addEntry(Jval key, Jval value, SymbolTable *tb);
// Jval getKeyFromEntry(Entry e);
// Jval getValueFromEntry(Entry e);

SymbolTable *createSymbolTable(char *output_file_name){
	SymbolTable *tb = (SymbolTable *)malloc(sizeof(SymbolTable));
	btinit();
	tb->entries = btcrt(output_file_name, 0, FALSE);
	return tb;
}

void dropSymbolTable(SymbolTable* tb){
	btcls(tb->entries);
	free(tb);
}

Entry getEntry(Jval key, SymbolTable *tb){
	char *search_key = jval_s(key);
	BTint value;
	int search_status = bfndky(tb->entries, search_key, &value);
	// printf("search status: %d\n", search_status);
	Entry result;
	result.key = new_jval_s("e");
	result.value = new_jval_l(-1);
	if(search_status == 0){
		result.key = key;
		result.value = new_jval_l(value);
	}
	return result;
}


void addEntry(Jval key, Jval value, SymbolTable *tb){
	char *ins_key = jval_s(key);
	long ins_val = jval_l(value);
	binsky(tb->entries, ins_key, (BTint) ins_val);
	// printf("insert status: %d\n", status);
}

Jval getKeyFromEntry(Entry e){
	return e.key;
}

Jval getValueFromEntry(Entry e){
	return e.value;
}

void traverseTable(SymbolTable *tb){
	char key[ZKYLEN];
	BTint val;
	btpos(tb->entries, ZSTART); //change the position to the beginning
	while(bnxtky(tb->entries, key, &val) == 0){
		printf("%s -> %ld\n", key, (long) val);
	}
}