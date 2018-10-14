#include "phonebook.h"


PhoneBook* createPhoneBook(){
	PhoneBook *book = createSymbolTable(comparePhone);
	return book;
}

int comparePhone(Jval a, Jval b){
	return strcmp(jval_s(a), jval_s(b));
}

void dropPhoneBook(PhoneBook* book){
	dropSymbolTable(book);
}

PhoneEntry getPhoneEntry(char * name, PhoneBook *book){
	return getEntry(new_jval_s(name), book);
}

void addPhoneEntry(char * name, long number, PhoneBook* book){
	addEntry(new_jval_s(name), new_jval_l(number), book);
}

char *getNameFromPhoneEntry(PhoneEntry e){
	return jval_s(getKeyFromEntry(e));
}

long getNumberFromPhoneEntry(PhoneEntry e){
	return jval_l(getValueFromEntry(e));
}

void traversePhoneBook(PhoneBook *book){
	JRB ptr;
	printf("==PHONEBOOK==\n\n");
	jrb_traverse(ptr, book->entries) {
    	printf("%s: %ld\n", jval_s(ptr->key), jval_l(ptr->val));
  	}
  	printf("\n+++++++++++++\n\n");
}

void printPhoneEntry(PhoneEntry entry){
	printf("Name: %s\n", getNameFromPhoneEntry(entry));
	printf("Phone: %ld\n\n", getNumberFromPhoneEntry(entry));
}
