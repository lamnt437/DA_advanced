#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

typedef struct phonebook{
	char name[30];
	char phone[12];
}Phonebook;

int phonebookCompare(void const *a, void const *b){
	return strcmp(((Phonebook *) a)->name, ((Phonebook *) b)->name);
}

void printPhone(Phonebook book){
	printf("name: %s\n", book.name);
	printf("phone: %s\n", book.phone);
}

void printPhonebook(Phonebook book[], int n){
	int i;
	for(i = 0; i < n; i++){
		printf("Book %d:\n", i + 1);
		printPhone(book[i]);
		printf("\n");
	}
}

void main(){
	//input size
	int n;
	int i;
	printf("Enter size: ");
	scanf("%d", &n);

	Phonebook book[n];
	srand(time(NULL));
	for(i = 0; i < n; i++){
		//randomize name size;
		int size = 15 + rand() % 10;
		char temp_name[size];
		//randomize character
		int j;
		for(j = 0; j < size - 1; j++){
			temp_name[j] = 'a' + rand() % 26;
		}
		temp_name[size - 1] = '\0';

		strcpy(book[i].name, temp_name);
		strcpy(book[i].phone, "0123456789");
	}

	printf("**List:\n\n");
	printPhonebook(book, n);

	//sort
	qsort(book, n, sizeof(Phonebook), phonebookCompare);
	printf("**Sorted:\n\n");
	printPhonebook(book, n);
}