#ifndef _symboltable_h
#define _symboltable_h

#define INITIAL_SIZE 5
#define INCREMENTAL_SIZE 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfdr/jrb.h"
#include "libfdr/jval.h"

typedef struct {
	Jval key;
	Jval value;
} Entry;

typedef struct {
	JRB entries;
	int total;
	int (*compare)(Jval , Jval);
} SymbolTable;

SymbolTable *createSymbolTable(int (*compare)(Jval , Jval));
void dropSymbolTable(SymbolTable* tb);
Entry getEntry(Jval key, SymbolTable *tb);
void addEntry(Jval key, Jval value, SymbolTable *tb);
Jval getKeyFromEntry(Entry e);
Jval getValueFromEntry(Entry e);

#endif
