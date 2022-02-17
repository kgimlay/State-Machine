// Author: Kevin Imlay

/*
The table-based finite state machine makes use of a table to define transitions. This requires one transition
table to be global to the entire state machine (as compared to the linked-based implementation). Due to this,
a few simplifications are made to reduce redundancy where possible, minimizing memory usage. These
simplifications are as follows:
  • the input alphabet is restricted to unsigned integers, incrementing from 0, to allow use directly in the
      transition table's array access,
  • states are given an unsigned integer ID, incrementing from 0, to allow for use directly in the transition
      table's array access.
The transition table is a 3-dimensional table, two input dimensions and one output dimension. The two inputs
are the current state and the input symbol.
*/

#ifndef FSM_TABLE_H
#define FSM_TABLE_H

#include "fsm.h"


/* ----- Structures ----- */

/*
Table implementation of a generic finite state machine.

Assumptions made:
  • all states may be transitioned from or to.
*/
typedef struct {
  // count of states in the machine
  unsigned int Qc;

  // list of states in the machine
  State *Q;

  // count of input alphabet symbols
  unsigned int Ec;

  // transition table (continuous array for 2d array)
  State **D;

  // starting state
  State *Qs;

} FSM_table;


/* ----- Public Function Prototypes ----- */

/*
Print Transition Table
For debugging purposes, prints the transition table.

Arguments:
  • fsm - pointer to a FSM

Returns:
  • table with symbols across the top, state IDs down the left, and State IDs in the fields.
  • if no State ID is in a field, a '-1' is printed instead.
  • if the transition table has not yet been allocated, prints an error message.
*/
void printFSM(FSM_table *fsm);


/*
Initialize FSM
Allocates memory needed for a FSM and sets default values needed.

Arguments:
  • fsm - pointer to the fsm to initialize.
  • state_count - number of states in the machine.
      Must be greater than 0 (machine cannot be empty).
  • symbol_count - number of symbols in the machine.
      Must be greater than 0 (machine needs to accept input).

Returns:
  • FSM_OK - if successful.
  • FSM_ALLOC_ERR - if needed memory was not able to be allocated.
  • FSM_SIZE_ERR - either the number of states or number of symbols provided were 0.
  • FSM_NO_MACHINE - the machine pointer provided was null.
*/
FSM_STATUS initFSM_table(FSM_table *fsm, unsigned int state_count, unsigned int symbol_count);


/*
Configure State
Changes a state's designation (start, accepting, neither), set the action function pointer.

Arguments:
  • fsm - pointer to the fsm to initialize.
  • state_id - unsigned integer ID of the state who's designation is to be changed.
  • designation - designation to assign to the state.
      Note: if assigning as the start state, overwrites the current start state.
  • action_fnc_ptr - function pointer for action to be performed while in state.
      Note: may be null.

Returns:
  • FSM_OK - if successful
  • FSM_NO_STATE - if the state ID provided does not correspond to a state in the machine.
  • FSM_NO_MACHINE - the machine pointer provided was null.
*/
FSM_STATUS confState_table(FSM_table *fsm, unsigned int state_id, STATE_TYPE designation, void (*action_fnc_ptr)(void));


/*
Add Transition
Adds a transition between two states in the machine.
Note: does not check if a transition is being overwritten.

Arguments:
  • fsm - pointer to the fsm to initialize.
  • from_state_id - unsigned integer ID of the state that the transition travels from.
  • to_state_id - unsigned integer ID of the state that the transition travels to.
  • symbol - unsigned integer symbol of the transition.

Returns:
  • FSM_OK - if successful.
  • FSM_NO_STATE - if either the from or to state IDs are not in the machine.
  • FSM_SIZE_ERR - if the symbol is larger than the number of symbols set in the machine.
  • FSM_NO_MACHINE - the machine pointer provided was null.
*/
FSM_STATUS addTrans_table(FSM_table *fsm, unsigned int from_state_id, unsigned int to_state_id, unsigned int symbol);


/*
Remove Transition
Removes a transition between two states in the machine.
Note: does not warn if transition does not exist.

Arguments:
  • fsm - pointer to the fsm to initialize.
  • from_state_id - unsigned integer ID of the state that the transition travels from.
  • symbol - unsigned integer symbol of the transition.

Returns:
  • FSM_OK - if successful.
  • FSM_NO_STATE - if the from state ID is not in the machine.
  • FSM_SIZE_ERR - if the symbol is larger than the number of symbols set in the machine.
  • FSM_NO_MACHINE - the machine pointer provided was null.
*/
FSM_STATUS remTrans_table(FSM_table *fsm, unsigned int from_state_id, unsigned int symbol);

#endif
