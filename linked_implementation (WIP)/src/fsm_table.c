// Author: Kevin Imlay

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fsm_table.h"

/* ----- Private Function Prototypes ----- */


/* ----- Public Function Definitions ----- */

/*
Print Transition Table
For debugging use!
*/
void printFSM(FSM_table *fsm) {
  // check that fsm exists
  if (fsm == NULL) {
    printf("FSM provided is NULL!\n");
    return;
  }
  else if (fsm->D == NULL) {
    printf("FSM has not been initialized yet!\n");
    return;
  }

  // define
  char temp_row[100];
  for (int i = 0; i < 100; i++)
    temp_row[i] = '\0';

  // print symbols
  strcat(temp_row, "___");
  for (int i = 0; i < fsm->Ec; i++) {
    strcat(temp_row, "|_%d_");
    sprintf(temp_row, temp_row, i);
  }
  printf("%s\n", temp_row);

  // print states
  for (int i = 0; i < fsm->Qc; i++) {
    for (int i = 0; i < 100; i++)
      temp_row[i] = '\0';
    strcat(temp_row, " %d ");
    sprintf(temp_row, temp_row, i);
    for (int j = 0; j < fsm->Ec; j++) {
      if (fsm->D[i*fsm->Ec+j] == NULL) {
        strcat(temp_row, "| %c ");
        sprintf(temp_row, temp_row, '.');
      }
      else {
        strcat(temp_row, "| %d ");
        sprintf(temp_row, temp_row, (fsm->D[i*fsm->Ec+j])->id);
      }
    }
    printf("%s\n", temp_row);
  }
  printf("\n");
  for (int i = 0; i < 100; i++)
    temp_row[i] = '\0';
}


/*
Initialize FSM
Actions:
  • allocate the transition table and state list
  • set the starting state to NULL
  • set count of states and symbols to 0
*/
FSM_STATUS initFSM_table(FSM_table *fsm, unsigned int state_count, unsigned int symbol_count) {
  // validate inputs
  if (fsm == NULL)
    return FSM_NO_MACHINE;
  if (state_count == 0 || symbol_count == 0)
    return FSM_SIZE_ERR;

  // allocate
  fsm->Q = calloc(state_count, sizeof(State));
  fsm->D = malloc(state_count * symbol_count * sizeof(State*));
  for (int i = 0; i < state_count * symbol_count; i++)
    fsm->D[i] = NULL;

  // check if allocation was successful
  if (fsm->Q == NULL || fsm->D == NULL)
    return FSM_ALLOC_ERR;

  // set defaults
  fsm->Qc = state_count;
  fsm->Ec = symbol_count;
  for (int i = 0; i < state_count; i++) {
    State temp_state;
    temp_state.id = i;
    temp_state.type = STATE_NORMAL;
    temp_state.action = NULL;
    fsm->Q[i] = temp_state;
    // printf("%d Func Ptr: %d\n", temp_state.id, temp_state.action);
  }
  fsm->Qs = NULL;

  // successful
  return FSM_OK;
}


/*
Configure State

Actions:
  • sets designation, setting appropriate stuff in fsm if needed
  • sets action function pointer
*/
FSM_STATUS confState_table(FSM_table *fsm, unsigned int state_id, STATE_TYPE designation, void (*action_fnc_ptr)(void)) {
  // validate inputs
  if (fsm == NULL)
    return FSM_NO_MACHINE;

  // set designation and action
  fsm->Q[state_id].type = designation;
  fsm->Q[state_id].action = action_fnc_ptr;
  // printf("%d Func Ptr: %u\n", fsm->Q[state_id].id, fsm->Q[state_id].action);

  // set machine start if needed
  if (designation == STATE_START)
    fsm->Qs = &(fsm->Q[state_id]);

  // successful
  return FSM_OK;
}


/*
Add Transition
Actions:
  • find location in transition table from given from state and symbol
  • put pointer of to-state in location
*/
FSM_STATUS addTrans_table(FSM_table *fsm, unsigned int from_state_id, unsigned int to_state_id, unsigned int symbol) {
  // validate inputs
  if (fsm == NULL)
    return FSM_NO_MACHINE;
  if (from_state_id >= fsm->Qc || to_state_id >= fsm->Qc)
    return FSM_NO_STATE;
  if (symbol >= fsm->Ec)
    return FSM_SIZE_ERR;

  // set transition
  fsm->D[from_state_id * fsm->Ec + symbol] = &(fsm->Q[to_state_id]);

  // successful
  return FSM_OK;
}


/*
Remove Transition
Actions:
  • find location in transition table from given from state and symbol
  • remove pointer of to-state in location
*/
FSM_STATUS remTrans_table(FSM_table *fsm, unsigned int from_state_id, unsigned int symbol) {
  // validate inputs
  if (fsm == NULL)
    return FSM_NO_MACHINE;
  if (from_state_id >= fsm->Qc)
    return FSM_NO_STATE;
  if (symbol >= fsm->Ec)
    return FSM_SIZE_ERR;

  // set transition
  fsm->D[from_state_id * fsm->Ec + symbol] = NULL;

  // successful
  return FSM_OK;
}
