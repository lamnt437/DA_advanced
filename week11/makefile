#gan ten bien thay the
CFLAGS = -c -Wall		
CC = gcc
#GNU debug
GNU = -g

# all: huffmanArray
# huffmanArray: huffmanArray.o huffman.o jrb_dgraph.o libfdr/libfdr.a
# 	${CC} -g -o huffmanArray huffmanArray.o huffman.o jrb_dgraph.o libfdr/libfdr.a
compress: compress.o huffman.o huffmanArray.o jrb_dgraph.o
	${CC} -g -o compress compress.o huffman.o huffmanArray.o jrb_dgraph.o libfdr/libfdr.a
decompress: decompress.o huffman.o huffmanArray.o jrb_dgraph.o
	${CC} -g -o decompress decompress.o huffman.o huffmanArray.o jrb_dgraph.o libfdr/libfdr.a
huffmanArray.o: huffmanArray.c huffman.h
	${CC} ${CFLAGS} huffmanArray.c
huffman.o: huffman.c jrb_dgraph.h
	${CC} ${CFLAGS} huffman.c
jrb_dgraph.o: jrb_dgraph.c jrb_dgraph.h
	${CC} ${CFLAGS} jrb_dgraph.c

compress.o: compress.c huffmanArray.c
	${CC} ${CFLAGS} compress.c
decompress.o: decompress.c huffmanArray.c
	${CC} ${CFLAGS} decompress.c

clean:
	rm -f *.o *_
	rm compress
	rm decompress