#ifndef _STATEMACHINE_H
#define _STATEMACHINE_H

typedef void (*event_fn_t)(int event, void *params, int *next_state);
typedef void (*entry_fn_t)(void *params);
typedef void (*exit_fn_t)(void *params);

#define SM_STATE_NULL -1
#define SM_EVENT_NULL -1

typedef struct sm_transition_t
{
    int event;
    event_fn_t event_fn;
    int next_state;
} sm_transition_t;

typedef struct sm_state_t
{
    int state;
    const sm_transition_t *sm_transitions;
    entry_fn_t entry_fn;
    exit_fn_t exit_fn;
} sm_state_t;

typedef struct sm_handle_t
{
    int current_state;
    sm_state_t *states_table;
    int num_states;
} sm_handle_t;

int init_statemachine(sm_handle_t *sm_handle, const sm_state_t *states, int current_state);
int submit_event(sm_handle_t *sm_handle, int next_event, void *params);
int get_hsm_state(sm_handle_t *sm_handle);
#endif