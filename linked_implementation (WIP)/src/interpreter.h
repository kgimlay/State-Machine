// Author: Kevin Imlay

/*
The interpreter is what actually runs a state machine: keeping track of the current state, handling
transitions, and handling exceptions.
*/

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "fsm.h"


/* ----- Enumerations ----- */

/*
Status codes for the interpreter.
*/
typedef enum {
  INTERP_NOT_IMPL = 2000,
  INTERP_OK,
  INTERP_ALLOC_ERR,
  INTERP_SYMB_ERR,
  INTERP_TRANS_ERR,
  INTERP_NO_INTERP,
  INTERP_NO_MACHINE,
  INTERP_MACHINE_NOT_INIT,
  INTERP_MACHINE_NO_START,
  INTERP_ACCEPT,
  INTERP_NO_ACCEPT
} INTERP_STATUS;


/* ----- Structures ----- */

/*
Interpreter structure.
*/
typedef struct {
  State *current_state;
} Interpreter;


#endif
