#ifndef _phonebook_h
#define _phonebook_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char name[80];
	long number;
} PhoneEntry;

typedef struct {
	PhoneEntry * entries;
	int total;
	int size;
} PhoneBook;

PhoneBook createPhoneBook();
void dropPhoneBook(PhoneBook* book);
PhoneEntry * getPhoneNumber(char * name, PhoneBook book);
void addPhoneNumber(char * name, long number, PhoneBook* book);
void printEntry(PhoneEntry entry);
void printPhoneBook(PhoneBook book);

#endif