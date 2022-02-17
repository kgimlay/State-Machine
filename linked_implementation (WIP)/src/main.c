// Author: Kevin Imlay

#include <stdlib.h>
#include <stdio.h>

#include "interpreter_table.h"
// #include "interpreter_linked.h"


void green() {
  printf("Green\n");
}

void yellow() {
  printf("Yellow\n");
}

void red() {
  printf("Red\n");
}


int main(int argc, char *argv[]) {
  FSM_table machine_t;
  Interpreter_table interp_t;

  initFSM_table(&machine_t, 3, 1);
  confState_table(&machine_t, 0, STATE_START, green);
  confState_table(&machine_t, 1, STATE_NORMAL, yellow);
  confState_table(&machine_t, 2, STATE_ACCEPT, red);
  addTrans_table(&machine_t, 0, 1, 0);
  addTrans_table(&machine_t, 1, 2, 0);
  addTrans_table(&machine_t, 2, 0, 0);
  initInterpreter_table(&interp_t, &machine_t);

  unsigned int intput[2] = {0,0};

  printf("%d\n", runInterpreter_table(&interp_t, intput, 2));
}
