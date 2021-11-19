CC=gcc
CFLAGS=-Wall
DYNAMIC=-c -fPIC
IPATH=./include/
LPATH=./lib/
PPATH=./prog/
BINS= $(LPATH)libcsvexternalmain $(LPATH)libcsvlocalmain

all: liblocalascii libextascii liblocalimg libextimg liblocalextra libextextra

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

# Criação da libgraficoimg

libgraficoimg.o: $(LPATH)libgraficoimg.c 
	$(CC) -c $(CFLAGS) $< -o $@ -I$(IPATH)

libgraficoimg.a: libgraficoimg.o $(IPATH)libgraficos.h 
	ar -rcv $@ $< 

# Criação da libgraficoimg

libgraficoascii.o: $(LPATH)libgraficoascii.c 
	$(CC) -c $(CFLAGS) $< -o $@ -I$(IPATH)

libgraficoascii.a: libgraficoascii.o $(IPATH)libgraficos.h 
	ar -rcv $@ $< 

# Criação da libgraficoextra

libgraficoextra.o: $(LPATH)libgraficoextra.c 
	$(CC) -c $(CFLAGS) $< -o $@ -I$(IPATH)

libgraficoextra.a: libgraficoextra.o $(IPATH)libgraficos.h 
	ar -rcv $@ $< 

# Binarios csv + graficos

libextimg: libgraficoimg.a libcsvexternal.so libcsv.so
	$(CC) $(CFLAGS) -o $(PPATH)main_ext_img $(PPATH)main.c -I$(IPATH) -L. -lgraficoimg -lcsvexternal -lcsv -lcurl 

liblocalimg: libgraficoimg.a libcsvlocal.so libcsv.so
	$(CC) $(CFLAGS) -o $(PPATH)main_local_img $(PPATH)main.c -I$(IPATH)  -L. -lgraficoimg -lcsvlocal -lcsv 

libextascii: libgraficoascii.a libcsvexternal.so libcsv.so
	$(CC) $(CFLAGS) -o $(PPATH)main_ext_ascii $(PPATH)main.c -I$(IPATH) -L. -lgraficoascii -lcsvexternal -lcsv -lcurl 

liblocalascii: libgraficoascii.a libcsvlocal.so libcsv.so
	$(CC) $(CFLAGS) -o $(PPATH)main_local_ascii $(PPATH)main.c -I$(IPATH)  -L. -lgraficoascii -lcsvlocal -lcsv 

libextextra: libgraficoextra.a libcsvexternal.so libcsv.so
	$(CC) $(CFLAGS) -o $(PPATH)main_ext_extra $(PPATH)main.c -I$(IPATH) -L. -lgraficoextra -lcsvexternal -lcsv -lcurl 

liblocalextra: libgraficoextra.a libcsvlocal.so libcsv.so
	$(CC) $(CFLAGS) -o $(PPATH)main_local_extra $(PPATH)main.c -I$(IPATH)  -L. -lgraficoextra -lcsvlocal -lcsv 

clean:
	rm *.o *.so *.a $(PPATH)main_local_ascii $(PPATH)main_local_extra $(PPATH)main_local_img $(PPATH)main_ext_ascii $(PPATH)main_ext_extra $(PPATH)main_ext_img graph.png