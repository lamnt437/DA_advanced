#include "jrb_symtab.h"

SymbolTable *createSymbolTable(int (*compare)(Jval , Jval))
{
	SymbolTable *tb = (SymbolTable *)malloc(sizeof(SymbolTable));
	tb->entries = make_jrb();
	tb->total = 0;
	tb->compare = compare;
	return tb;
}

void dropSymbolTable(SymbolTable* tb)
{
	jrb_free_tree(tb->entries);
	free(tb);
}

Entry getEntry(Jval key, SymbolTable *tb)
{
	JRB result = jrb_find_str(tb->entries, jval_s(key));
	Entry result_entry;
	result_entry.key = new_jval_s("e");
	result_entry.value = new_jval_l(-1);

	if(result){
		result_entry.key = result->key;
		result_entry.value = result->val;
	}
	return result_entry;
}

void addEntry(Jval key, Jval value, SymbolTable *tb)
{
	jrb_insert_str(tb->entries, jval_s(key), value);
	tb->total++;
}

Jval getKeyFromEntry(Entry e){
	return e.key;
}

Jval getValueFromEntry(Entry e){
	return e.value;
}