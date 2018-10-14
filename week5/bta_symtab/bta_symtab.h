#ifndef _bta_symtab_h
#define _bta_symtab_h

#include "bt-5.0.0/inc/btree.h"
#include "libfdr/jval.h"

typedef struct {
	Jval key;
	Jval value;
} Entry;

typedef struct {
	BTA * entries;
	int total;
} SymbolTable;

SymbolTable *createSymbolTable(char *output_file_name);
void dropSymbolTable(SymbolTable* tb);
Entry getEntry(Jval key, SymbolTable *tb);
void addEntry(Jval key, Jval value, SymbolTable *tb);
Jval getKeyFromEntry(Entry e);
Jval getValueFromEntry(Entry e);
void traverseTable(SymbolTable *tb);

#endif