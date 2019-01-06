#gan ten bien thay the
CFLAGS = -c -Wall		
CC = gcc
#GNU debug
GNU = -g

all: main
main: main.o str_weight_dgraph.o libfdr/libfdr.a
	${CC} -g -o main main.o str_weight_dgraph.o libfdr/libfdr.a
main.o: main.c str_weight_dgraph.h
	${CC} ${CFLAGS} main.c
str_weight_dgraph.o: str_weight_dgraph.c str_weight_dgraph.h
	${CC} ${CFLAGS} str_weight_dgraph.c
clean:
	rm -f *.o *_
