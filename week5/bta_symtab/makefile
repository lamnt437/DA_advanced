#gan ten bien thay the
CFLAGS = -c -Wall		
CC = gcc
#GNU debug
GNU = -g

all: main
main: genApp.o phonebook.o bta_symtab.o libfdr/libfdr.a bt-5.0.0/lib/libbt.a
	${CC} -g -o main genApp.o phonebook.o bta_symtab.o libfdr/libfdr.a bt-5.0.0/lib/libbt.a 
genApp.o: genApp.c phonebook.h
	${CC} ${CFLAGS} genApp.c
phonebook.o: phonebook.c phonebook.h
	${CC} ${CFLAGS} phonebook.c
jrb_symtab.o: jrb_symtab.c jrb_symtab.h
	${CC} ${CFLAGS} bta_symtab.c
clean:
	rm -f *.o *_
