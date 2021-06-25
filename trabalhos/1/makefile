all: src test

src: src.c libintegral.a
	gcc src.c -I. -L. -lintegral -lpthread -lm -o src

libintegral.a: integral.o
	ar -cr libintegral.a integral.o

integral.o: integral.c
	gcc -c integral.c -o integral.o

test: test.c libintegral.a
	gcc test.c -I. -L. -lintegral -lpthread -lm -o test

clean:
	rm -rf *.o *.a