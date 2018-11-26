#gan ten bien thay the
CFLAGS = -c -Wall		
CC = gcc
#GNU debug
GNU = -g

all: main
main: main.o jrb_wgraph.o libfdr/libfdr.a
	${CC} -g -o main main.o jrb_wgraph.o libfdr/libfdr.a
main.o: main.c jrb_wgraph.h
	${CC} ${CFLAGS} main.c
jrb_wgraph.o: jrb_wgraph.c jrb_wgraph.h
	${CC} ${CFLAGS} jrb_wgraph.c
clean:
	rm -f *.o *_
