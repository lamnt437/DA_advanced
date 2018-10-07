#include "phonebook.h"

PhoneBook* createPhoneBook(){
	PhoneBook *book = createSymbolTable(makeNodePhone, comparePhone);
	return book;
}

int comparePhone(void *entryA, void *entryB){
	char *keyA = (char *)(((Entry *)entryA)->key);
	char *keyB = (char *)(((Entry *)entryB)->key);
	return strcmp(keyA, keyB);
}

Entry makeNodePhone(void *key, void *value){
	Entry new_entry;
	new_entry.key = strdup(key);
	new_entry.value = (long *)malloc(sizeof(long));
	memcpy(new_entry.value, value, sizeof(long));

	return new_entry;
}

void dropPhoneBook(PhoneBook* book){
	dropSymbolTable(book);
}

PhoneEntry * getPhoneEntry(char * name, PhoneBook *book){
	return getEntry(name, book);
}

void addPhoneEntry(char * name, long number, PhoneBook* book){
	addEntry(name, &number, book);
}

char *getNameFromPhoneEntry(PhoneEntry e){
	return (char *)getKeyFromEntry(e);
}

long getNumberFromPhoneEntry(PhoneEntry e){
	return *((long *)getValueFromEntry(e));
}

void printPhoneEntry(PhoneEntry entry){
	printf("Name: %s\n", getNameFromPhoneEntry(entry));
	printf("Phone: %ld\n\n", getNumberFromPhoneEntry(entry));
}

void printPhoneBook(PhoneBook book){
	int i;
	for(i = 0; i < book.total; i++){
		printf("%d.\n", i + 1);
		printPhoneEntry(book.entries[i]);
	}
}
