#include "statemachine.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <debug.h>
#include <nuttx/i2c/i2c_master.h>
#include "rgbMatrixI2CDriver/rgbMatrix.h"
#include <pthread.h>
#include "pubsub-c/pubsub.h"

typedef enum
{
    SM_TEST_STATE_ONE,
    SM_TEST_STATE_TWO,
    SM_TEST_STATE_THREE,
    SM_TEST_STATE_END
} tests_states_t;

typedef enum
{
    SM_TEST_EVENT_ONE,
    SM_TEST_EVENT_TWO,
    SM_TEST_EVENT_THREE,
    SM_TEST_EVENT_END
} tests_events_t;

static const sm_transition_t state_one_transitions[] = {
    {SM_TEST_EVENT_ONE, NULL, SM_TEST_STATE_TWO},
    {SM_TEST_EVENT_TWO, NULL, SM_TEST_STATE_ONE},
    {SM_TEST_EVENT_THREE, NULL, SM_TEST_STATE_THREE},
    {SM_EVENT_NULL, NULL, SM_STATE_NULL}};

static const sm_transition_t state_two_transitions[] = {
    {SM_TEST_EVENT_ONE, NULL, SM_TEST_STATE_TWO},
    {SM_TEST_EVENT_TWO, NULL, SM_TEST_STATE_ONE},
    {SM_TEST_EVENT_THREE, NULL, SM_TEST_STATE_THREE},
    {SM_EVENT_NULL, NULL, SM_STATE_NULL}};

static const sm_transition_t state_three_transitions[] = {
    {SM_TEST_EVENT_ONE, NULL, SM_TEST_STATE_TWO},
    {SM_TEST_EVENT_TWO, NULL, SM_TEST_STATE_ONE},
    {SM_TEST_EVENT_THREE, NULL, SM_TEST_STATE_THREE},
    {SM_EVENT_NULL, NULL, SM_STATE_NULL}};

static const sm_state_t test_sm_tattes[] = {
    [SM_TEST_STATE_ONE] = {SM_TEST_STATE_ONE, state_one_transitions, NULL, NULL},
    [SM_TEST_STATE_TWO] = {SM_TEST_STATE_TWO, state_two_transitions, NULL, NULL},
    [SM_TEST_STATE_THREE] = {SM_TEST_STATE_THREE, state_two_transitions, NULL, NULL},
    [SM_TEST_STATE_END] = {SM_STATE_NULL, NULL, NULL, NULL},
};

void test_sm(void)
{
}