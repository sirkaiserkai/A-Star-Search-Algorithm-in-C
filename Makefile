CC = gcc
DEPENDENCIES = Point.c Grid.c Player.c PriorityQueue.c List.c 
MAIN = Main.c
EXE_FILE = Main.out
FLAGS = -lm -Wall -std=c99  -g

build: $(MAIN)
	$(CC) $(MAIN) -o $(EXE_FILE) $(DEPENDENCIES) $(FLAGS)

clean:
	rm -f *.o core

rebuild: clean build 
