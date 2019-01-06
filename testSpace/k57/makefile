#gan ten bien thay the
CFLAGS = -c -Wall		
CC = gcc
#GNU debug
GNU = -g

all: main
main: main.o str_weight_ugraph.o libfdr/libfdr.a
	${CC} -g -o main main.o str_weight_ugraph.o libfdr/libfdr.a
main.o: main.c str_weight_ugraph.h
	${CC} ${CFLAGS} main.c
str_weight_ugraph.o: str_weight_ugraph.c str_weight_ugraph.h
	${CC} ${CFLAGS} str_weight_ugraph.c
clean:
	rm -f *.o *_
