// Author: Kevin Imlay

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "interpreter.h"

#define NUM_STATES 11
#define NUM_SYMBOLS 10

/* Private Enumeration Definitions */
typedef enum {
  IB_SYMB = 0,    // initialize board         0
  CSS_SYMB,       // check startup            1
  SSS_SYMB,       // startup state set        2
  SSNS_SYMB,      // startup state not set    3
  MS_SYMB,        // mode select              4
  SD_SYMB,        // shutdown                 5
  PD_SYMB,        // powerdown                6
  NM_SYMB,        // normal mode              7
  SM_SYMB,        // sleep mode               8
  IM_SYMB         // interactive mode         9
} TRANSITION_SYMBOL;

typedef enum {
  B_STATE = 0,    // boot state                           0
  IB_STATE,       // initialize board state               1
  CSS_STATE,      // check startup config state           2
  LSS_STATE,      // load startup config state            3
  LDC_STATE,      // load default startup config state    4
  MS_STATE,       // mode select state                    5
  SS_STATE,       // save state/config state              6
  PD_STATE,       // powerdown state                      7
  TEMP_NM_STATE,  // (TEMPORARY) normal mode state        8
  TEMP_SM_STATE,  // (TEMPORARY) sleep mode state         9
  TEMP_IM_STATE,  // (TEMPORARY) interactive mode state   10
} STATE_ID;


/* Private Variables */
unsigned int input_symbol = -1;
unsigned int config_select = SSNS_SYMB;
unsigned int mode_select = NM_SYMB;


/* Private Function Definitions */

/*
 *
 */
void State_Error_Handler(void) {
  printf("ERROR\n");
  while (1) {}
}

/*
 *
 */
void b_state() {
  printf("Powered up!\n");
  printf("Boot State\n");
  input_symbol = IB_SYMB;
}

/*
 *
 */
void ib_state() {
  printf("Initialize Board State\n");
  input_symbol = CSS_SYMB;
}

/*
 *
 */
void css_state() {
  printf("Check Startup Config State\n");
  if (config_select == SSS_SYMB)
	  input_symbol = SSS_SYMB;
  else if (config_select == SSNS_SYMB)
	  input_symbol = SSNS_SYMB;
  else
	  State_Error_Handler();
}

/*
 *
 */
void lss_state() {
  printf("Load Startup Config State\n");
  input_symbol = MS_SYMB;
}

/*
 *
 */
void ldc_state() {
  printf("Load Default Config State\n");
  input_symbol = MS_SYMB;
}

/*
 *
 */
void ms_state() {
  printf("Mode Select State\n");
  if (mode_select == NM_SYMB)
	  input_symbol = NM_SYMB;
  else if (mode_select == SM_SYMB)
	  input_symbol = SM_SYMB;
  else if (mode_select == IM_SYMB)
	  input_symbol = IM_SYMB;
  else if (mode_select == SD_SYMB)
	  input_symbol = SD_SYMB;
  else
	  State_Error_Handler();
}

/*
 *
 */
void ss_state() {
  printf("Shutdown State\n");
  input_symbol = PD_SYMB;
}

/*
 *
 */
void pd_state() {
  printf("Powerdown State\n");
  printf("Powered down!\n");
  while (1) {}
}

/*
 *
 */
void temp_nm_state() {
  printf("Normal Mode State\n");
  input_symbol = MS_SYMB;
  mode_select = SD_SYMB;
}

/*
 *
 */
void temp_sm_state() {
  printf("Sleep Mode State\n");
  input_symbol = MS_SYMB;
  mode_select = SD_SYMB;
}

/*
 *
 */
void temp_im_state() {
  printf("Interactive Mode State\n");
  input_symbol = MS_SYMB;
  mode_select = SD_SYMB;
}


/* Public Function Definitions */

/*
 *
 */
bool createStateMachine(FSM *state_machine, Interpreter *interpreter) {
  // instantiate state machine
	initFSM(state_machine, NUM_STATES, NUM_SYMBOLS);

	// configure machine states
  if (confState(state_machine, B_STATE, START_STATE, b_state) != FSM_OK)
	  State_Error_Handler();
  if (confState(state_machine, IB_STATE, NORMAL_STATE, ib_state) != FSM_OK)
	  State_Error_Handler();
  if (confState(state_machine, CSS_STATE, NORMAL_STATE, css_state) != FSM_OK)
	  State_Error_Handler();
  if (confState(state_machine, LSS_STATE, NORMAL_STATE, lss_state) != FSM_OK)
	  State_Error_Handler();
  if (confState(state_machine, LDC_STATE, NORMAL_STATE, ldc_state) != FSM_OK)
	  State_Error_Handler();
  if (confState(state_machine, MS_STATE, NORMAL_STATE, ms_state) != FSM_OK)
	  State_Error_Handler();
  if (confState(state_machine, SS_STATE, NORMAL_STATE, ss_state) != FSM_OK)
	  State_Error_Handler();
  if (confState(state_machine, PD_STATE, ACCEPT_STATE, pd_state) != FSM_OK)
	  State_Error_Handler();
  if (confState(state_machine, TEMP_NM_STATE, NORMAL_STATE, temp_nm_state) != FSM_OK)
	  State_Error_Handler();
  if (confState(state_machine, TEMP_SM_STATE, NORMAL_STATE, temp_sm_state) != FSM_OK)
	  State_Error_Handler();
  if (confState(state_machine, TEMP_IM_STATE, NORMAL_STATE, temp_im_state) != FSM_OK)
	  State_Error_Handler();

	// configure state transitions
  if (addTrans(state_machine, B_STATE, IB_STATE, IB_SYMB) != FSM_OK)
	  State_Error_Handler();
  if (addTrans(state_machine, IB_STATE, CSS_STATE, CSS_SYMB) != FSM_OK)
	  State_Error_Handler();
  if (addTrans(state_machine, CSS_STATE, LSS_STATE, SSS_SYMB) != FSM_OK)
	  State_Error_Handler();
  if (addTrans(state_machine, CSS_STATE, LDC_STATE, SSNS_SYMB) != FSM_OK)
	  State_Error_Handler();
  if (addTrans(state_machine, LSS_STATE, MS_STATE, MS_SYMB) != FSM_OK)
	  State_Error_Handler();
  if (addTrans(state_machine, LDC_STATE, MS_STATE, MS_SYMB) != FSM_OK)
	  State_Error_Handler();
  if (addTrans(state_machine, MS_STATE, SS_STATE, SD_SYMB) != FSM_OK)
	  State_Error_Handler();
  if (addTrans(state_machine, MS_STATE, TEMP_NM_STATE, NM_SYMB) != FSM_OK)
	  State_Error_Handler();
  if (addTrans(state_machine, MS_STATE, TEMP_SM_STATE, SM_SYMB) != FSM_OK)
	  State_Error_Handler();
  if (addTrans(state_machine, MS_STATE, TEMP_IM_STATE, IM_SYMB) != FSM_OK)
	  State_Error_Handler();
  if (addTrans(state_machine, SS_STATE, PD_STATE, PD_SYMB) != FSM_OK)
	  State_Error_Handler();
  if (addTrans(state_machine, TEMP_NM_STATE, MS_STATE, MS_SYMB) != FSM_OK)
	  State_Error_Handler();
  if (addTrans(state_machine, TEMP_SM_STATE, MS_STATE, MS_SYMB) != FSM_OK)
	  State_Error_Handler();
  if (addTrans(state_machine, TEMP_IM_STATE, MS_STATE, MS_SYMB) != FSM_OK)
	  State_Error_Handler();

	// instantiate state machine interpreter
  initInterpreter(interpreter, state_machine);

  return true;
}


int main(int argc, char *argv[]) {
  FSM machine_t;
  Interpreter interp_t;

  createStateMachine(&machine_t, &interp_t);
  printFSM(&machine_t);

  // run action in start state
  if (runState(&interp_t) != INTERP_OK)
    State_Error_Handler();

  while (1) {
    if (transition(&interp_t, input_symbol, &interp_t.current_state) != INTERP_OK)
      State_Error_Handler();

    if (runState(&interp_t) != INTERP_OK)
      State_Error_Handler();
  }
}
