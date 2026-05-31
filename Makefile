CC = g++
CFLAGS = -g -Wall -Wextra -Werror -pedantic
OBJ = main.o abey.o
PROGRAM = abey

all: $(PROGRAM)

$(PROGRAM): main.o abey.o
	$(CC) -o $(PROGRAM) $^ $(CFLAGS)

main.o: main.cpp
	$(CC) -c $^ $(CFLAGS)

abey.o: abey.cpp abey.hpp
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -rf *.gch *.o $(PROGRAM)