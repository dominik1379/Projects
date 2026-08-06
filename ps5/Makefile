OUTPUT=ps5
CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wconversion
LDLIBS=-lm
SOURCES=main.c backpack.c command.c container.c game.c item.c parser.c room.c world.c

all: codeanalysis ps5

codeanalysis: $(SOURCES)
	cppcheck --enable=unusedFunction --error-exitcode=1 $^

$(OUTPUT): main.o backpack.o command.o container.o game.o item.o parser.o room.o world.o
	echo "Running compilation"
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $(OUTPUT)

main.o: main.c
	echo "Building object file file main.o"
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

backpack.o: backpack.c
	echo "Building object file file backpack.o"
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

command.o: command.c
	echo "Building object file file command.o"
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

container.o: container.c
	echo "Building object file file container.o"
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

game.o: game.c
	echo "Building object file file game.o"
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

item.o: item.c
	echo "Building object file file item.o"
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

parser.o: parser.c
	echo "Building object file file parser.o"
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

room.o: room.c
	echo "Building object file file room.o"
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

world.o: world.c
	echo "Building object file file world.o"
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

tests: game.o tests_game.c
	$(CC) $(CFLAGS) game.o tests_game.c $(LDLIBS) -o $@
	./tests



clean:
	qrm -rf *.o $(OUTPUT) tests

push:
	astyle --mode=c --indent=spaces=4 $(SOURCES)
	git commit -a
	git push
