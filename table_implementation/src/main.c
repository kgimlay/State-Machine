// Author: Kevin Imlay

#include <stdlib.h>
#include <stdio.h>

#include "interpreter.h"


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
  FSM machine_t;
  Interpreter interp_t;

  initFSM(&machine_t, 3, 1);
  confState(&machine_t, 0, STATE_START, green);
  confState(&machine_t, 1, STATE_NORMAL, yellow);
  confState(&machine_t, 2, STATE_ACCEPT, red);
  addTrans(&machine_t, 0, 1, 0);
  addTrans(&machine_t, 1, 2, 0);
  addTrans(&machine_t, 2, 0, 0);
  initInterpreter(&interp_t, &machine_t);

  unsigned int intput[2] = {0,0};

  printf("%d\n", runInterpreter(&interp_t, intput, 2));
}
