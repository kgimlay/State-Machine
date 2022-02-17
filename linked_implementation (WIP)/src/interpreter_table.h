// Author: Kevin Imlay

/*
The interpreter is what actually runs a state machine.
*/

#ifndef INTERPRETER_TABLE
#define INTERPRETER_TABLE

#include <stdlib.h>

#include "fsm.h"
#include "fsm_table.h"
#include "interpreter.h"

/* ----- Structures ----- */

/*
Interpreter (table-based).
*/
typedef struct {
  Interpreter *interpreter;
  FSM_table *fsm;
} Interpreter_table;


/* ----- Public Function Prototypes ----- */

/*
Initialize Interpreter
Initializes an interpreter to default values and primes for operation.

Arguments:
  • interp - pointer to the interpreter to be initialized.
      Note: must not be null.
  • machine - pointer to the FSM to run the interpreter on.
      Note: must not be null.

Returns:
  • INTERP_OK - if successful.
  • INTERP_NO_INTERP - if the interpreter provided is null.
  • INTERP_NO_MACHINE - if the machine provided is null.
  • INTERP_MACHINE_NOT_INIT - if the machine provided is not initialized.
  • INTERP_MACHINE_NO_START - if the machine provided has no start state.
*/
INTERP_STATUS initInterpreter_table(Interpreter_table *interp, FSM_table *machine);


/*
Run State
Executes the action in the current state.

Arguments:
  • interp - pointer to the interpreter.
      Note: must not be null.

Returns:
  • INTERP_OK - if successful.
  • INTERP_NO_INTERP - if the interpreter provided is null.
  • INTERP_NO_MACHINE - if the machine is null (not initialized).
*/
INTERP_STATUS runState_table(Interpreter_table *interp);


/*
Input Symbol
Inputs a symbol to the interpreter. Performs the action in the state, if present.

Arguments:
  • interp - pointer to the interpreter.
      Note: must not be null.
  • symbol - unsigned integer symbol.
      Note: must not be null.
  • new_state - [pass back] pointer to State of the state transitioned to.
      Note: will be overwritten if data is present.
      Note: returns null if transition is invalid.

Returns:
  • INTERP_OK - if successful.
  • INTERP_SYMB_ERR - if the symbol provided is invalid.
  • INTERP_TRANS_ERR - if the symbol provided does not have a transition out of the current state.
  • INTERP_NO_INTERP - if the interpreter provided is null.
  • INTERP_NO_MACHINE - if the machine is null (not initialized).
*/
INTERP_STATUS transition_table(Interpreter_table *interp, unsigned int symbol, State *new_state);


/*
Interpret Input Sequence
Runs the interpreter on the given interpreter sequence.

Arguments:
  • interp - pointer to the interpreter.
      Note: must not be null.
  • input - array of unsigned integers as symbol inputs.
  • input_length - unsigned integer length of the input array.

Returns:
  • INTERP_ACCEPT - if ends in a final state.
  • INTERP_NO_ACCEPT - if does not end in a final state.
  • INTERP_SYMB_ERR - if the symbol provided is invalid.
  • INTERP_TRANS_ERR - if the symbol provided does not have a transition out of the current state.
  • INTERP_NO_INTERP - if the interpreter provided is null.
  • INTERP_NO_MACHINE - if the machine is null (not initialized).
*/
INTERP_STATUS runInterpreter_table(Interpreter_table *interp, unsigned int *input, unsigned int input_length);


#endif
