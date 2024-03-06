FLAGS = -Wall -Wextra -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wredundant-decls -Woverloaded-virtual
CC = g++

goV : QueueV.o main.o 
	$(CC) -o goV QueueV.o main.o
	@echo ready, set, goV

goL : QueueL.o main.o 
	$(CC) -o goL QueueL.o main.o
	@echo ready, set, goL

QueueV.o : QueueV.cpp
	$(CC) $(CFLAGS) -c QueueV.cpp
	@echo QueueV compilation successful

QueueL.o : QueueL.cpp
	$(CC) $(CFLAGS) -c QueueL.cpp
	@echo QueueL compilation successful

main.o : main.cpp
	$(CC) $(FLAGS) -c main.cpp
	@echo main ready

clean:
	rm -f core *.o go*
