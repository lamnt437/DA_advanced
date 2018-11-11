#gan ten bien thay the
CFLAGS = -c -Wall		
CC = gcc
#GNU debug
GNU = -g

all: main
main: graph_traversal.o jrb_graph.o libfdr/libfdr.a
	${CC} -g -o main graph_traversal.o jrb_graph.o libfdr/libfdr.a
graph_traversal.o: graph_traversal.c jrb_graph.h
	${CC} ${CFLAGS} graph_traversal.c
jrb_graph.o: jrb_graph.c jrb_graph.h
	${CC} ${CFLAGS} jrb_graph.c
clean:
	rm -f *.o *_
