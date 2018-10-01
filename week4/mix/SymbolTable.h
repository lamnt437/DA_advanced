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

SymbolTable createSymbolTable();
void dropSymbolTable(SymbolTable* tab);
void addEntry(void* key, void* value, SymbolTable* book);
Entry* getEntry(void* key, SymbolTable book);

#endif