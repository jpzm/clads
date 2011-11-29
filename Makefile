default: all

all:
	cd code; cc -ggdb -Wall -shared -fPIC -c *.c
	cd test; cc -Wall list.c -o list -lm \
		../code/clads.o \
		../code/list.o

clean:
	cd code; rm -rf *.o
	cd test; rm -rf \
		list
