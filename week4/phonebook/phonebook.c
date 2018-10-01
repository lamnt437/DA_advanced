#include "phonebook.h"

#define INITIAL_SIZE 10
#define INCREMENTAL_SIZE 5

PhoneBook createPhoneBook(){
	PhoneBook book;
	book.entries = (PhoneEntry *)malloc(sizeof(PhoneEntry) * INITIAL_SIZE);
	book.total = 0;
	book.size = INITIAL_SIZE;
	return book;
}

int comparePhone(void *key1, void *key2){
	return strcmp((char *)key1, (char *)key2);
}

void dropPhoneBook(PhoneBook* book){
	free(book->entries);
}

PhoneEntry * getPhoneNumber(char * name, PhoneBook book){
	//loop through all entries of phonebook
	int i;
	for(i = 0; i < book.total; i++){
		if(strcmp(book.entries[i].name, name) == 0)
			break;
	}
	if(i < book.total)
		return &(book.entries[i]);
	return NULL;
	//use getEntry function
}

void addPhoneNumber(char * name, long number, PhoneBook* book){
	//check if name already exists in phonebook
	PhoneEntry *entry = getPhoneNumber(name, *book);
	//if yes, overwrite old phone
	if(entry != NULL){
		entry->number = number;
		return;
	}
	//if not
	else{
	//if not (total < size)
		if(!(book->total < book->size)){
			//malloc
			PhoneEntry *new_entries = (PhoneEntry *)malloc(sizeof(PhoneEntry) * (book->size + INCREMENTAL_SIZE));
			//copy
			memcpy(new_entries, book->entries, sizeof(PhoneEntry) * (book->size));
			//free old entries;
			free(book->entries);
			//connect new_entries to old book
			book->entries = new_entries;
			book->size += INCREMENTAL_SIZE;
		}

	//write into book[total]
		PhoneEntry new_entry;
		strcpy(new_entry.name, name);
		new_entry.number = number;

		book->entries[book->total] = new_entry;
		(book->total)++;
	}
}

void printEntry(PhoneEntry entry){
	printf("Name: %s\n", entry.name);
	printf("Phone: %ld\n\n", entry.number);
}

void printPhoneBook(PhoneBook book){
	int i;
	for(i = 0; i < book.total; i++){
		printf("%d.\n", i + 1);
		printEntry(book.entries[i]);
	}
}
