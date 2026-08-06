OUTPUT=ps1
CC=gcc
CFLAGS=-std=c11 -Wall -Werror
LDLIBS=-lm
SOURCES=main.c bmp.c transformations.c

all: codeanalysis ps1

codeanalysis: $(SOURCES)
	cppcheck --enable=unusedFunction --error-exitcode=1 $^

main.o: main.c
	echo "Building object file file main.o"
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

playfair.o: playfair.c
	echo "Building object file file main.o"
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

bmp.o: bmp.c
	echo "Building object file file bmp.o"
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@


tests: bmp.o tests_bmp.c
	$(CC) $(CFLAGS) bmp.o tests_bmp.c $(LDLIBS) -o $@
	./tests

clean:
	qrm -rf *.o $(OUTPUT) tests

push:
	astyle --mode=c --indent=spaces=4 $(SOURCES)
	git commit -a
	git push
