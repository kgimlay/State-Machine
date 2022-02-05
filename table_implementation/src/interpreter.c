// Author: Kevin Imlay

#include <stdio.h>

#include "interpreter.h"

/* ----- Private Function Prototypes ----- */


/* ----- Public Function Definitions ----- */

/*
Initialize Interpreter
Actions:
  • create a generic interpreter struct and add to the interpreter
  • add the machine to the interpreter
  • set default values
*/
INTERP_STATUS initInterpreter(Interpreter *interp, FSM *machine) {
  // validate inputs
  if (interp == NULL)
    return INTERP_NO_INTERP;
  if (machine == NULL)
    return INTERP_NO_MACHINE;
  if (machine->D == NULL)
    return INTERP_MACHINE_NOT_INIT;
  if (machine->Qs == NULL)
    return INTERP_MACHINE_NO_START;

  // fill interpreter
  interp->current_state = machine->Qs;
  interp->fsm = machine;

  // successful
  return INTERP_OK;
}


/*
Start Interpreter
Actions:
  • calls state's action if applicable
*/
INTERP_STATUS runState(Interpreter *interp) {
  // validate inputs
  if (interp == NULL)
    return INTERP_NO_INTERP;
  if (interp->fsm == NULL)
    return INTERP_NO_MACHINE;

  // call action
  if (interp->current_state->action != NULL)
    (*interp->current_state->action)();

  // successful
  return INTERP_OK;
}


/*
Input Symbol
Actions:
  • validates symbol
  • performs transition if possible
  • calls state's action if applicable
  • returns new state
*/
INTERP_STATUS transition(Interpreter *interp, unsigned int symbol, State **new_state) {
  // validate inputs
  if (interp == NULL)
    return INTERP_NO_INTERP;
  if (interp->fsm == NULL)
    return INTERP_NO_MACHINE;
  if (symbol >= interp->fsm->Ec)
    return INTERP_SYMB_ERR;

  // perform transition
  unsigned int current_state_id = interp->current_state->id;
  *new_state = interp->fsm->D[current_state_id * interp->fsm->Ec + symbol];
  if (*new_state == NULL) {
    // TODO: define behavior for if transition is invalid
    printf("  :::: Invalid transition out of state %d on symbol %d!\n  :::: Further behavior is undefined!\n", current_state_id, symbol);
    printFSM(interp->fsm);
    return INTERP_TRANS_ERR;
  }
  interp->current_state = *new_state;

  // successful
  return INTERP_OK;
}


/*
Run Input
Actions:
  • input each symbol into the machine, running action on each state.
*/
INTERP_STATUS runInterpreter(Interpreter *interp, unsigned int *input, unsigned int input_length) {
  // operation variables
  INTERP_STATUS interp_status;
  State *current_state = NULL;

  // validate input
  if (interp == NULL)
    return INTERP_NO_INTERP;
  if (interp->fsm == NULL)
    return INTERP_NO_MACHINE;

  // run action in start state
  interp_status = runState(interp);
  if (interp_status != INTERP_OK)
    return interp_status;

  // for each input, transition and run action
  for (int i = 0; i < input_length; i++) {
    interp_status = transition(interp, input[i], &current_state);
    if (interp_status != INTERP_OK)
      return interp_status;

    interp_status = runState(interp);
    if (interp_status != INTERP_OK)
      return interp_status;
  }

  // check accept state
  if (current_state->type == STATE_ACCEPT)
    return INTERP_ACCEPT;
  else
    return INTERP_NO_ACCEPT;
}
