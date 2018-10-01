#ifndef _symboltable_h
#define _symboltable_h

#define INITIAL_SIZE 5
#define INCREMENTAL_SIZE 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	void * key;
	void * value;
} Entry;

typedef struct {
	Entry * entries;
	int size, total;
	Entry (*makeNode)(void*, void*);
	int (*compare)(void*, void*);
} SymbolTable;

SymbolTable *createSymbolTable(Entry (*makeNode)(void *, void *), int (*compare)(void *, void *));
void dropSymbolTable(SymbolTable* tb);
Entry* getEntry(void* key, SymbolTable *tb);
void addEntry(void* key, void* value, SymbolTable *tb);
void *getKeyFromEntry(Entry e);
void *getValueFromEntry(Entry e);

#endif
