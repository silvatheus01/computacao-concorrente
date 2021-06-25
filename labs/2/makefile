all: src test	

src: src.c libmatriz.a
	gcc src.c -I. -L. -lmatriz -pthread -o src

libmatriz.a: matriz.o
	ar -cr libmatriz.a matriz.o

matriz.o: matriz.c
	gcc -c matriz.c -o matriz.o

test: test.c libmatriz.a
	gcc test.c -I. -L. -lmatriz -pthread -o test

clean:
	rm -rf *.o *.a