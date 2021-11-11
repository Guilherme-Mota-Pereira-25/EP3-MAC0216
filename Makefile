CC=gcc
CFLAGS=-Wall

all: libcsvlocal

libcsvlocal.o: libcsvlocal.c 
	$(CC) $(CFLAGS) -fPIC -c libcsvlocal.c

libcsvlocal.so: libcsvlocal.o libcsvreader.h
	$(CC) -shared -o $@ libcsvlocal.o 

libcsvlocalmain: libcsvlocal.c libcsvreader.h
	$(CC) $(CFLAGS) -fPIC -shared -o $@ libcsvlocal.c -lc 

setldpath: 
	export LD_LIBRARY_PATH=../libs