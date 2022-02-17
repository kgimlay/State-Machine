# Author: Kevin Imlay

CC = gcc
OBJ_COMP_FLAGS = -c -pedantic -Wall -O0
EXE_COMP_FLAGS = -pedantic
SRC_DIR = ./src/
OBJ_DIR = ./obj/

all: FiniteStateMachine

main.o: $(SRC_DIR)main.c
	$(CC) $(OBJ_COMP_FLAGS) $(SRC_DIR)main.c -o $(OBJ_DIR)main.o

fsm_table.o: $(SRC_DIR)fsm_table.c $(SRC_DIR)fsm_table.h
	$(CC) $(OBJ_COMP_FLAGS) $(SRC_DIR)fsm_table.c -o $(OBJ_DIR)fsm_table.o

# fsm_linked.o: $(SRC_DIR)fsm_linked.c $(SRC_DIR)fsm_linked.h
# 	$(CC) $(OBJ_COMP_FLAGS) $(SRC_DIR)fsm_linked.c -o $(OBJ_DIR)fsm_linked.o

interpreter_table.o: $(SRC_DIR)interpreter_table.c $(SRC_DIR)interpreter_table.h
	$(CC) $(OBJ_COMP_FLAGS) $(SRC_DIR)interpreter_table.c -o $(OBJ_DIR)interpreter_table.o

# interpreter_linked.o: $(SRC_DIR)interpreter_linked.c $(SRC_DIR)interpreter_linked.h
# 	$(CC) $(OBJ_COMP_FLAGS) $(SRC_DIR)interpreter_linked.c -o $(OBJ_DIR)interpreter_linked.o

FiniteStateMachine: main.o fsm_table.o interpreter_table.o
	$(CC) $(EXE_COMP_FLAGS) -o FiniteStateMachine \
	$(OBJ_DIR)main.o $(OBJ_DIR)fsm_table.o $(OBJ_DIR)interpreter_table.o

clean:
	rm $(OBJ_DIR)*.o
	rm FiniteStateMachine
