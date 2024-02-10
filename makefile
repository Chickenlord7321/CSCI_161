FLAGS = -Wall -Wextra -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wredundant-decls -Woverloaded-virtual
CC = g++

go: main.o List.o
	$(CC) -o go List.o main.o
	@echo ready, set, go

main.o : main.cpp
	$(CC) $(FLAGS) -c main.cpp
	@echo main ready

List.o : List.cpp
	$(CC) $(FLAGS) -c List.cpp
	@echo List compiled successfully

clean:
	rm -f core *.o go*
