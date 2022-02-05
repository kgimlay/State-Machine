# Author: Kevin Imlay

CC = gcc
OBJ_COMP_FLAGS = -c -pedantic -Wall -O0
EXE_COMP_FLAGS = -pedantic
SRC_DIR = ./src/
OBJ_DIR = ./obj/

all: FiniteStateMachine_TableImplementation

main.o: $(SRC_DIR)main.c
	$(CC) $(OBJ_COMP_FLAGS) $(SRC_DIR)main.c -o $(OBJ_DIR)main.o

fsm.o: $(SRC_DIR)fsm.c $(SRC_DIR)fsm.h
	$(CC) $(OBJ_COMP_FLAGS) $(SRC_DIR)fsm.c -o $(OBJ_DIR)fsm.o

interpreter.o: $(SRC_DIR)interpreter.c $(SRC_DIR)interpreter.h
	$(CC) $(OBJ_COMP_FLAGS) $(SRC_DIR)interpreter.c -o $(OBJ_DIR)interpreter.o

FiniteStateMachine_TableImplementation: main.o fsm.o interpreter.o
	$(CC) $(EXE_COMP_FLAGS) -o FiniteStateMachine_TableImplementation \
	$(OBJ_DIR)main.o $(OBJ_DIR)fsm.o $(OBJ_DIR)interpreter.o

clean:
	rm $(OBJ_DIR)*.o
	rm FiniteStateMachine_TableImplementation
