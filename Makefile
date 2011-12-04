CC = cc
CFLAGS = -ggdb -Wall

default: all

all:
	cd code; ${CC} ${CFLAGS} -shared -fPIC -c *.c
	cd test; ${CC} ${CFLAGS} list.c -o list -lm \
		../code/clads.o \
		../code/list.o

clean:
	cd code; rm -rf *.o
	cd test; rm -rf \
		list
