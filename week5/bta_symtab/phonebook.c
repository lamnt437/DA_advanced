#include "phonebook.h"


PhoneBook* createPhoneBook(char *output_file_name){
	PhoneBook *book = createSymbolTable(output_file_name);
	return book;
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
	printf("==PHONEBOOK==\n\n");
	traverseTable(book);
  	printf("\n+++++++++++++\n\n");
}

void printPhoneEntry(PhoneEntry entry){
	printf("Name: %s\n", getNameFromPhoneEntry(entry));
	printf("Phone: %ld\n\n", getNumberFromPhoneEntry(entry));
}
