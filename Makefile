CC = cc
CFLAGS = -ggdb -Wall

default: all

all:
	cd code; ${CC} ${CFLAGS} -shared -fPIC -c *.c
	cd test; ${CC} ${CFLAGS} list.c -o list -lm \
		../code/clads.o \
		../code/list.o
	cd test; ${CC} ${CFLAGS} tree.c -o tree -lm \
		../code/clads.o \
		../code/tree.o
	cd test; ${CC} ${CFLAGS} hash.c -o hash -lm \
		../code/clads.o \
		../code/list.o \
		../code/hash.o

clean:
	cd code; rm -rf *.o
	cd test; rm -rf \
		list \
		tree \
		hash
