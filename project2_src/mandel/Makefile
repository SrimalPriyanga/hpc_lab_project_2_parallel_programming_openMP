CC     ?= gcc
CFLAGS  = -O3 # -I$(CPATH)
LDFLAGS = -O3 # -L$(LIBRARY_PATH)

all: mandel_seq mandel_parallel

mandel_seq: mandel_seq.o pngwriter.o walltime.o
	$(CC) $(LDFLAGS) $^ -lpng -o $@

mandel_parallel: mandel_parallel.o pngwriter.o walltime.o
	$(CC) $(LDFLAGS) -fopenmp $^ -lpng -o $@

mandel_seq.o: mandel_seq.c consts.h pngwriter.h walltime.h
	$(CC) -c $(CFLAGS) $<

mandel_parallel.o: mandel_parallel.c consts.h pngwriter.h walltime.h
	$(CC) -c $(CFLAGS) -fopenmp $<

pngwriter.o: pngwriter.c pngwriter.h
	$(CC) -c $(CFLAGS) $<

walltime.o: walltime.c walltime.h
	$(CC) -c $(CFLAGS) $<

.PHONY: clean
clean:
	$(RM) *.o mandel_seq mandel_parallel