#include "phonebook.h"

// PhoneBook createPhoneBook();
// void dropPhoneBook(PhoneBook* book);
// PhoneEntry * getPhoneNumber(char * name, PhoneBook book);
// void addPhoneNumber(char * name, long number, PhoneBook* book);
// void printPhoneBook(PhoneBook book);

void main(){
	PhoneBook book = createPhoneBook();
	// addPhoneNumber("Nguyen Tung Lam", 123123123, &book);
	// printPhoneBook(book);
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

				addPhoneNumber(name, number, &book);
				break;
			case 2:
				//get
				getchar();
				printf("Enter name: ");
				fgets(name, 29, stdin);
				name[strlen(name) - 1] = '\0';

				PhoneEntry *result = getPhoneNumber(name, book);
				if(result)
					printEntry(*result);
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
	dropPhoneBook(&book);
}