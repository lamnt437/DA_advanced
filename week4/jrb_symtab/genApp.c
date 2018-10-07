#include "phonebook.h"

int main(){
	SymbolTable *tb = createPhoneBook();
	SymbolTable book = *tb;

	int choice;
	char name[30];
	char *ins_name = NULL;
	long number;

	do{
		printf("1-add\n2-get\n3-exit...");
		scanf("%d", &choice);

		switch(choice){
			case 1:
				getchar();
				ins_name = (char *)malloc(sizeof(char) * 30);
				printf("Enter name: ");
				fgets(ins_name, 29, stdin);
				ins_name[strlen(ins_name) - 1] = '\0';

				printf("Enter phone: ");
				scanf("%ld", &number);

				addPhoneEntry(ins_name, number, &book);
				ins_name = NULL;
				traversePhoneBook(tb);
				break;
			case 2:
				getchar();
				printf("Enter name: ");
				fgets(name, 29, stdin);
				name[strlen(name) - 1] = '\0';

				Entry result = getPhoneEntry(name, &book);
				if(jval_l(result.value) != -1){
					printf("\n**Search result: ");
					printPhoneEntry(result);
				}
				else
					printf("Not found!\n");

				break;
			default:
				break;
		}
		
	}while(choice != 3);

	dropPhoneBook(tb);

	return 0;
}