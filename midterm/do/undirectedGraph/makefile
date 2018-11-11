#gan ten bien thay the
CFLAGS = -c -Wall		
CC = gcc
#GNU debug
GNU = -g

all: main
main: app.o jrb_graph.o libfdr/libfdr.a
	${CC} -g -o main app.o jrb_graph.o libfdr/libfdr.a
app.o: app.c jrb_graph.h
	${CC} ${CFLAGS} app.c
jrb_graph.o: jrb_graph.c jrb_graph.h
	${CC} ${CFLAGS} jrb_graph.c
clean:
	rm -f *.o *_
