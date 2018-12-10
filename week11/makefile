#gan ten bien thay the
CFLAGS = -c -Wall		
CC = gcc
#GNU debug
GNU = -g

all: huffmanArray
huffmanArray: huffmanArray.o huffman.o jrb_dgraph.o libfdr/libfdr.a
	${CC} -g -o huffmanArray huffmanArray.o huffman.o jrb_dgraph.o libfdr/libfdr.a
huffmanArray.o: huffmanArray.c huffman.h
	${CC} ${CFLAGS} huffmanArray.c
huffman.o: huffman.c jrb_dgraph.h
	${CC} ${CFLAGS} huffman.c
jrb_wgraph.o: jrb_dgraph.c jrb_dgraph.h
	${CC} ${CFLAGS} jrb_dgraph.c
clean:
	rm -f *.o *_
