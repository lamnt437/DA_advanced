#gan ten bien thay the
CFLAGS = -c -Wall		
CC = gcc
#GNU debug
GNU = -g

all: main
main: main.o int_weight_ugraph.o libfdr/libfdr.a
	${CC} -g -o main main.o int_weight_ugraph.o libfdr/libfdr.a
main.o: main.c int_weight_ugraph.h
	${CC} ${CFLAGS} main.c
int_weight_ugraph.o: int_weight_ugraph.c int_weight_ugraph.h
	${CC} ${CFLAGS} int_weight_ugraph.c
clean:
	rm -f *.o *_
