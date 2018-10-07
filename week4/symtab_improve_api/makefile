#gan ten bien thay the
CFLAGS = -c -Wall		
CC = gcc
#GNU debug
GNU = -g

#lenh make mac dinh chay dong dau tien cua makefile
#de chay cac dong khac: make + ten. Vi du: make clean, make linkedlist.o
#cau truc:
#ten: input
	#<tab> output
#clean: ko co input nen se chay ngay khi goi make clean
	#lenh rm -f la xoa cac file co duoi .o

all: main
main: genApp.o phonebook.o SymbolTable.o
	${CC} -o main genApp.o phonebook.o SymbolTable.o
genApp.o: genApp.c phonebook.h
	${CC} ${CFLAGS} genApp.c
phonebook.o: phonebook.c phonebook.h SymbolTable.h
	${CC} ${CFLAGS} phonebook.c
SymbolTable.o: SymbolTable.c SymbolTable.h
	${CC} ${CFLAGS} SymbolTable.c
clean:
	rm -f *.o *_
