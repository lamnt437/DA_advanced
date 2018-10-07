#include "SymbolTable.h"

// typedef struct {
// 	void * key;
// 	void * value;
// } Entry;

// typedef struct {
// 	Entry * entries;
// 	int size, total;
// 	Entry (*makeNode)(void*, void*);
// 	int (*compare)(void*, void*);
// } SymbolTable;

SymbolTable *createSymbolTable(Entry (*makeNode)(void *, void *), int (*compare)(void *, void *)){
	SymbolTable *tb = (SymbolTable *)malloc(sizeof(SymbolTable));
	tb->entries = (Entry *)malloc(sizeof(Entry) * INITIAL_SIZE);
	tb->size = INITIAL_SIZE;
	tb->total = 0;
	tb->makeNode = makeNode;
	tb->compare = compare;

	return tb;
}

void dropSymbolTable(SymbolTable* tb){
	int total = tb->total;
	int i;
	for(i = 0; i < total; i++){
		free(tb->entries[i].key);
		free(tb->entries[i].value);
	}
	free(tb->entries);
	free(tb);
}

Entry* getEntry(void* key, SymbolTable *tb){
	int total = tb->total;
	int i;
	Entry temp;
	temp.key = key;

	for(i = 0; i < total; i++){
		if(tb->compare(&temp, &tb->entries[i]) == 0)
			break;
	}
	if(i < total)
		return &tb->entries[i];
	return NULL;
}

void addEntry(void* key, void* value, SymbolTable *tb){
	//check if key already exists
	Entry *result = getEntry(key, tb);
	if(result != NULL){
		result->value = value;
	}
	else{
		//check if total within size
		if(!(tb->total < tb->size)){
			//increment
			Entry *new_entries = (Entry *)malloc(sizeof(Entry) * (tb->size + INCREMENTAL_SIZE));
			//copy
			memcpy(new_entries, tb->entries, (tb->size) * sizeof(Entry));
			//free old entries
			free(tb->entries);
			//add new entries to tb
			tb->entries = new_entries;
			tb->size += INCREMENTAL_SIZE;
		}
		//insert new entry to "total" index
		Entry new_entry = tb->makeNode(key, value);
		tb->entries[tb->total] = new_entry;
		tb->total++;
	}
}

void *getKeyFromEntry(Entry e){
	return e.key;
}

void *getValueFromEntry(Entry e){
	return e.value;
}