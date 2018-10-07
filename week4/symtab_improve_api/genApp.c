#include "phonebook.h"

int main(){
	SymbolTable *tb = createPhoneBook();
	SymbolTable book = *tb;

	int choice;
	char name[30];
	long number;

	do{
		printf("1-add\n2-get\n3-exit...");
		scanf("%d", &choice);

		switch(choice){
			case 1:
				//add
				getchar();
				printf("Enter name: ");
				fgets(name, 29, stdin);
				name[strlen(name) - 1] = '\0';

				printf("Enter phone: ");
				scanf("%ld", &number);

				addPhoneEntry(name, number, &book);
				break;
			case 2:
				//get
				getchar();
				printf("Enter name: ");
				fgets(name, 29, stdin);
				name[strlen(name) - 1] = '\0';

				Entry *result = getPhoneEntry(name, &book);
				if(result)
					printPhoneEntry(*result);
				else
					printf("Not found!\n");

				break;
			default:
				break;
		}
		printPhoneBook(book);
	}while(choice != 3);
	dropPhoneBook(tb);

	return 0;
}