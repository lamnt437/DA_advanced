#include "SymbolTable.h"

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

SymbolTable initPhoneBook(){
	SymbolTable book = createSymbolTable();
	book.makeNode = makeNodePhone;
	book.compare = comparePhone;

	return book;
}

void printPBEntry(Entry a){
	printf("Name: %s\n", (char *)a.key);
	printf("Number: %ld\n", *((long *)a.value));
}

void printPhoneBook(SymbolTable book){
	int total = book.total;
	int i;
	for(i = 0; i < total; i++){
		printf("%d.\n", i + 1);
		printPBEntry(book.entries[i]);
		printf("\n");
	}
}

int main(){
	SymbolTable book = initPhoneBook();

	int choice;
	char name[30];
	long number;

	printf("1-add\n2-get\n3-exit...");
	scanf("%d", &choice);

	do{
		switch(choice){
			case 1:
				//add
				getchar();
				printf("Enter name: ");
				fgets(name, 29, stdin);
				name[strlen(name) - 1] = '\0';

				printf("Enter phone: ");
				scanf("%ld", &number);

				addEntry(name, &number, &book);
				break;
			case 2:
				//get
				getchar();
				printf("Enter name: ");
				fgets(name, 29, stdin);
				name[strlen(name) - 1] = '\0';

				Entry *result = getEntry(name, book);
				if(result)
					printPBEntry(*result);
				else
					printf("Not found!\n");

				break;
			default:
				break;
		}
		printPhoneBook(book);
		printf("1-add\n2-get\n3-exit...");
		scanf("%d", &choice);
	}while(choice != 3);
	dropSymbolTable(&book);

	return 0;
}