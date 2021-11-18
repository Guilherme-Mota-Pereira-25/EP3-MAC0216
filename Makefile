CC=gcc
CFLAGS=-Wall
DYNAMIC=-c -fPIC
IPATH=./include/
LPATH=./lib/
PPATH=./prog/
BINS= $(LPATH)libcsvexternalmain $(LPATH)libcsvlocalmain

all: libcsvexternalmain libcsvlocalmain

# Criação da libcsv

libcsv.o: $(LPATH)libcsv.c
	$(CC) $(DYNAMIC) $(CFLAGS) $< -o $@ -I$(IPATH)

libcsv.so: libcsv.o $(IPATH) $(IPATH)libcsv.h
	$(CC) -o $@ -shared $<

# Criação da csvlocal

libcsvlocal.o: $(LPATH)libcsvlocal.c 
	$(CC) $(DYNAMIC) $(CFLAGS) $< -o $@ -I$(IPATH)

libcsvlocal.so: libcsvlocal.o $(IPATH)libcsvreader.h
	$(CC) -o $@ -shared $<

libcsvlocalmain: libcsvlocal.so libcsv.so
	$(CC) $(CFLAGS) -o $(PPATH)main_local $(PPATH)main.c -I$(IPATH) -L. -lcsvlocal -lcsv

# Criação da csvexternal 

libcsvexternal.o: $(LPATH)libcsvexternal.c 
	$(CC) $(DYNAMIC) $(CFLAGS) $< -o $@ -I$(IPATH)

libcsvexternal.so: libcsvexternal.o $(IPATH)libcsvreader.h
	$(CC) -o $@ -shared $<

libcsvexternalmain: libcsvexternal.so libcsv.so
	$(CC) $(CFLAGS) -o $(PPATH)main_external $(PPATH)main.c -I$(IPATH) -L. -lcsvexternal -lcsv -lcurl

clean:
	rm *.o *.so $(BINS)