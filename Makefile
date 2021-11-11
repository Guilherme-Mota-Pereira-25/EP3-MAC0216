CC=gcc
CFLAGS=-Wall
DYNAMIC=-c -fPIC
IPATH=./include/
LPATH=./lib/
PPATH=./prog/
BINS= $(LPATH)libcsvexternalmain $(LPATH)libcsvlocalmain

all: libcsvexternalmain libcsvlocalmain

# Creation of csvlocal library

libcsvlocal.o: $(LPATH)libcsvlocal.c 
	$(CC) $(DYNAMIC) $(CFLAGS) $< -o $(LPATH)$@ -I$(IPATH)

libcsvlocal.so: libcsvlocal.o $(IPATH)libcsvreader.h
	$(CC) -o $(LPATH)$@ -shared $(LPATH)$<

libcsvlocalmain: libcsvexternal.so libcsvlocal.so 
	$(CC) $(CFLAGS) -o $(PPATH)main_local $(PPATH)main.c -I$(IPATH) -L$(LPATH) -lcsvlocal

# Creation of csvexternal library

libcsvexternal.o: $(LPATH)libcsvexternal.c 
	$(CC) $(DYNAMIC) $(CFLAGS) $< -o $(LPATH)$@ -I$(IPATH)

libcsvexternal.so: libcsvexternal.o $(IPATH)libcsvreader.h
	$(CC) -o $(LPATH)$@ -shared $(LPATH)$<

libcsvexternalmain: libcsvexternal.so 
	$(CC) $(CFLAGS) -o $(PPATH)main_external $(PPATH)main.c -I$(IPATH) -L$(LPATH) -lcsvexternal

clean:
	rm $(LPATH)*.o $(LPATH)*.so $(BINS)