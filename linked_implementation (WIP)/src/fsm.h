// Author: Kevin Imlay

#ifndef FINITE_STATE_MACHINE_H
#define FINITE_STATE_MACHINE_H


/* ----- Enumerations ----- */
/* Enumerations for all implementations of FSMs */

/*
Generic return codes for any FSM functions.
*/
typedef enum {
  FSM_NOT_IMPL = 4000,  // not implemented yet
  FSM_OK,               // success
  FSM_ALLOC_ERR,        // there was a problem allocating the necessary memory
  FSM_SIZE_ERR,         // the size provided was invalid or impossible
  FSM_NO_STATE,         // the state does not exist
  FSM_NO_MACHINE        // the machine does not exist
} FSM_STATUS;

/*
Codes for the type of a state.
*/
typedef enum {
  STATE_START = 8000, // starting state for the machine
  STATE_ACCEPT,       // an accepting state for the machine
  STATE_NORMAL        // neither a start state or a accepting state
} STATE_TYPE;


/* ----- Structures ----- */
/* Structures for all implementations of FSMs */

/*
State.
*/
typedef struct {
  unsigned int id;
  STATE_TYPE type;
  void (*action)(void);
} State;

/* API for all implementations of FSMs */


#endif
