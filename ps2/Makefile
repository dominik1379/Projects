OUTPUT=game
CC=gcc
CFLAGS=-std=c11 -Wall -Werror -lncurses
LDLIBS=-lm -lncurses
SOURCES=main.c hof.c k.c ui.c

all: codeanalysis game

codeanalysis: $(SOURCES)
	cppcheck --enable=unusedFunction --error-exitcode=1 $^

$(OUTPUT): main.o hof.o k.o ui.o 
	echo "Running compilation"
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $(OUTPUT)

main.o: main.c
	echo "Building object file file main.o"
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

hof.o: hof.c
	echo "Building object file file bmp.o"
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

k.o: k.c
	echo "Building object file file bmp.o"
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

ui.o: ui.c
	echo "Building object file file playfair.o"
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

tests: k.o tests_k.c
	$(CC) $(CFLAGS) k.o tests_k.c $(LDLIBS) -o $@
	./tests
	

clean:
	qrm -rf *.o $(OUTPUT) tests

push:
	astyle --mode=c --indent=spaces=4 $(SOURCES)
	git commit -a
	git push
