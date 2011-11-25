default: all

all:
	cd code; cc -ggdb -Wall -shared -fPIC `pkg-config --cflags gtk+-2.0` -c *.c

clean:
	cd code; rm -rf *.o

