#gan ten bien thay the
CFLAGS = -c -Wall		
CC = gcc
#GNU debug
GNU = -g

all: main
main: app.o jrb_dgraph.o libfdr/libfdr.a
	${CC} -g -o main app.o jrb_dgraph.o libfdr/libfdr.a
app.o: app.c jrb_dgraph.h
	${CC} ${CFLAGS} app.c
jrb_graph.o: jrb_dgraph.c jrb_dgraph.h
	${CC} ${CFLAGS} jrb_dgraph.c
clean:
	rm -f *.o *_
