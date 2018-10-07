/* Uses red-black trees to sort like sort -n -- i.e. it treats each
   line as an integer, and sorts it that way.  If the lines are not
   integers, or there are duplicate lines, anything goes.  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfdr/jrb.h"
#include "libfdr/fields.h"

typedef struct {
  Jval key;
  Jval value;
} Entry;

typedef struct {
  JRB entries;
  int total;
  int (*compare)(Jval , Jval);
} SymbolTable;

SymbolTable *createSymbolTable(int (*compare)(Jval , Jval))
{
  SymbolTable *tb = (SymbolTable *)malloc(sizeof(SymbolTable));
  tb->entries = make_jrb();
  tb->total = 0;
  tb->compare = compare;
  return tb;
}
void dropSymbolTable(SymbolTable* tb)
{
  jrb_free_tree(tb->entries);
  free(tb);
}
Entry getEntry(Jval key, SymbolTable *tb)
{
  JRB result = jrb_find_str(tb->entries, jval_s(key));
  Entry result_entry;
  result_entry.key = new_jval_s("e");
  result_entry.value = new_jval_l(-1);

  if(result){
    result_entry.key = result->key;
    result_entry.value = result->val;
  }
  return result_entry;
}
void addEntry(Jval key, Jval value, SymbolTable *tb)
{
  jrb_insert_str(tb->entries, jval_s(key), value);
  tb->total++;
}
Jval getKeyFromEntry(Entry e){
  return e.key;
}
Jval getValueFromEntry(Entry e){
  return e.value;
}


//PHONEBOOK============================================================================================
//PHONEBOOK============================================================================================
//PHONEBOOK============================================================================================
//PHONEBOOK============================================================================================
//PHONEBOOK============================================================================================
//PHONEBOOK============================================================================================


typedef Entry PhoneEntry;

typedef SymbolTable PhoneBook;

int comparePhone(Jval a, Jval b){
  return strcmp(jval_s(a), jval_s(b));
}

PhoneBook* createPhoneBook(){
  PhoneBook *book = createSymbolTable(comparePhone);
  return book;
}

void dropPhoneBook(PhoneBook* book){
  dropSymbolTable(book);
}

PhoneEntry getPhoneEntry(char * name, PhoneBook *book){
  return getEntry(new_jval_s(name), book);
}

void addPhoneEntry(char * name, long number, PhoneBook* book){
  addEntry(new_jval_s(name), new_jval_l(number), book);
}

char *getNameFromPhoneEntry(PhoneEntry e){
  return jval_s(getKeyFromEntry(e));
}

long getNumberFromPhoneEntry(PhoneEntry e){
  return jval_l(getValueFromEntry(e));
}

void traversePhoneBook(PhoneBook *book){
  JRB ptr;
  jrb_traverse(ptr, book->entries) {
      printf("%s: %ld\n", jval_s(ptr->key), jval_l(ptr->val));
    }
}

void printPhoneEntry(PhoneEntry entry){
  printf("Name: %s\n", getNameFromPhoneEntry(entry));
  printf("Phone: %ld\n\n", getNumberFromPhoneEntry(entry));
}


int main()
{
  // JRB b;
  // JRB bn;
  // int choice;
  // b = make_jrb();
  // char ins_name[30];
  
  // long number;

  // do{
  //   printf("1-add\n2-get\n3-exit...");
  //   scanf("%d", &choice);

  //   switch(choice){
  //     case 1:
  //       getchar();
  //       printf("Enter Name: ");
  //       fgets(ins_name, 29, stdin);
  //       ins_name[strlen(ins_name) - 1] = '\0';
  //       strcpy(mem_name, ins_name);

  //       printf("Enter Number: ");
  //       scanf("%ld", &number);

  //       jrb_insert_str(b, mem_name, new_jval_l(number));
  //       break;

  //     case 2:
  //       getchar();
  //       printf("Enter name to search: ");
  //       fgets(find_name, 29, stdin);
  //       find_name[strlen(ins_name) - 1] = '\0';

  //       JRB result = jrb_find_str(b, find_name);
  //       if(result != NULL){
  //         printf("%s: %ld\n", jval_s(result->key), jval_l(result->val));
  //       }
  //       else{
  //         printf("Not found!\n");
  //       }

  //       break;

  //     default:

  //       break;
  //   }
  // }while(choice != 3);

  // jrb_traverse(bn, b) {
  //   printf("%s: %ld\n", jval_s(bn->key), jval_l(bn->val));
  // }

  // // bn = jrb_find_str(b, "11");
  // // printf("\nSearch result: %s: %ld\n", jval_s(bn->key), jval_s(bn->val));

  // // bn = jrb_find_str(b, "12");
  // // printf("\nSearch result: %s: %s\n", jval_s(bn->key), jval_s(bn->val));

  // // bn = jrb_find_str(b, "18");
  // // printf("\nSearch result: %s: %s\n", jval_s(bn->key), jval_s(bn->val));
  // exit(0);

  SymbolTable *tb = createPhoneBook();
  SymbolTable book = *tb;
  JRB tree = make_jrb();

  int choice;
  long number;

  do{
    printf("1-add\n2-get\n3-exit...");
    scanf("%d", &choice);

    switch(choice){
      case 1:
        //add
        getchar();
        char *name = (char *)malloc(sizeof(char) * 30);
        printf("Enter name: ");
        fgets(name, 29, stdin);
        name[strlen(name) - 1] = '\0';

        printf("Enter phone: ");
        scanf("%ld", &number);

        // addPhoneEntry(name, number, &book);
        jrb_insert_str(tree, name, new_jval_l(number));
        name = NULL;
        break;
      case 2:
        getchar();
        char find_name[30];
        printf("Enter name: ");
        fgets(find_name, 29, stdin);
        find_name[strlen(find_name) - 1] = '\0';

        JRB result = jrb_find_str(tree, find_name);
        if(!result){
          printf("%s : %ld\n", jval_s(result->key), jval_l(result->val));
        }
        else{
          printf("Not found!\n");
        }

        break;
      default:
        break;
    }
    // traversePhoneBook(tb);
    JRB ptr;
    jrb_traverse(ptr, tree) {
      printf("%s: %ld\n", jval_s(ptr->key), jval_l(ptr->val));
    }
  }while(choice != 3);
  dropPhoneBook(tb);

  return 0;
}