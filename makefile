CFLAGS = -Wall -Wextra -Wwrite-strings -Wredundant-decls
CC = g++

go : main.o Maze.o Dispenser.o
		$(CC) -o go main.o Maze.o Dispenser.o
		@echo ready, set, go

main.o : main.cpp Maze.o Dispenser.o 
		$(CC) -c main.cpp
		@echo main compiled

Maze.o : Maze.cpp
		$(CC) $(FLAGS) -c Maze.cpp
		@echo Maze compilation successful

Dispenser.o : Dispenser.cpp 
		$(CC) $(CFLAGS) -c Dispenser.cpp
		@echo Deque compiled

clean :
	rm -f *.o
	rm -f go*
