FLAGS = -Wall -Wextra -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wredundant-decls -Woverloaded-virtual
CC = g++

goV : StackV.o main.o 
	$(CC) -o goV StackV.o main.o
	@echo ready, set, goV

goL : StackL.o main.o 
	$(CC) -o goL StackL.o main.o
	@echo ready, set, goL

StackV.o : StackV.cpp
	$(CC) $(CFLAGS) -c StackV.cpp
	@echo StackV compilation successful

StackL.o : StackL.cpp
	$(CC) $(CFLAGS) -c StackL.cpp
	@echo StackLL compilation successful

main.o : main.cpp
	$(CC) $(FLAGS) -c main.cpp
	@echo main ready

clean:
	rm -f core *.o go*
