CC = cc
CFLAGS = -ggdb -Wall

default: all

all:
	cd code; ${CC} ${CFLAGS} -shared -fPIC -c *.c
	cd test; ${CC} ${CFLAGS} list.c -o list \
		../code/clads.o \
		../code/list.o -lm
	cd test; ${CC} ${CFLAGS} tree.c -o tree \
		../code/clads.o \
		../code/tree.o -lm
	cd test; ${CC} ${CFLAGS} tgf.c -o tgf \
		../code/clads.o \
		../code/list.o \
		../code/statistic.o \
		../code/graph.o -lm
	cd test; ${CC} ${CFLAGS} hash.c -o hash \
		../code/clads.o \
		../code/list.o \
		../code/hash.o -lm
	cd bind; python setup.py build_ext -f -b clads

clean:
	cd code; rm -rf *.o
	cd test; rm -rf \
		list \
		tree \
		hash
	cd bind; rm -rf clads/*.so clads/*.pyc \
		rm -rf build/
