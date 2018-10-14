#ifndef _phonebook_h
#define _phonebook_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bta_symtab.h"

typedef Entry PhoneEntry;

typedef SymbolTable PhoneBook;

PhoneBook* createPhoneBook(char *output_file_name);
// int comparePhone(Jval a, Jval b);
void dropPhoneBook(PhoneBook* book);
PhoneEntry getPhoneEntry(char * name, PhoneBook *book);
void addPhoneEntry(char * name, long number, PhoneBook* book);
char *getNameFromPhoneEntry(PhoneEntry e);
long getNumberFromPhoneEntry(PhoneEntry e);
void traversePhoneBook(PhoneBook *book);
void printPhoneEntry(PhoneEntry entry);

#endif
