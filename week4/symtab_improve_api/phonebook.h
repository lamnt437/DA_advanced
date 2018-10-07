#ifndef _phonebook_h
#define _phonebook_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SymbolTable.h"

typedef Entry PhoneEntry;

typedef SymbolTable PhoneBook;

PhoneBook *createPhoneBook();
int comparePhone(void *entryA, void *entryB);
Entry makeNodePhone(void *key, void *value);
void dropPhoneBook(PhoneBook* book);
PhoneEntry * getPhoneEntry(char * name, PhoneBook *book);
void addPhoneEntry(char * name, long number, PhoneBook* book);
char *getNameFromPhoneEntry(PhoneEntry e);
long getNumberFromPhoneEntry(PhoneEntry e);
void printPhoneEntry(PhoneEntry entry);
void printPhoneBook(PhoneBook book);

#endif
