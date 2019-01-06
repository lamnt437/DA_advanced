#gan ten bien thay the
CFLAGS = -c -Wall		
CC = gcc
#GNU debug
GNU = -g

all: main
main: main.o int_ungraph.o libfdr/libfdr.a
	${CC} -g -o main main.o int_ungraph.o libfdr/libfdr.a
main.o: main.c int_ungraph.h
	${CC} ${CFLAGS} main.c
int_ungraph.o: int_ungraph.c int_ungraph.h
	${CC} ${CFLAGS} int_ungraph.c
clean:
	rm -f *.o *_
