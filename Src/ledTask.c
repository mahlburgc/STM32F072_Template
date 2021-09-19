/********************************************************************************
 * @file           : ledTask.c
 * @author         : Christian Mahlburg
 * @date           : 20.06.2020
 * @brief          : This file contains the ledTask and related functions.
 *
 ********************************************************************************
 * MIT License
 *
 * Copyright (c) 2020 CMA
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ********************************************************************************/

/********************************************************************************
 * includes
 ********************************************************************************/
#include "ledTask.h"
#include "stdio.h"
#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "debug.h"
#include "misc.h"
#include "tim.h"

/********************************************************************************
 * public variables
 ********************************************************************************/
bool interruptTriggered = false;

typedef struct
{
    uint8_t payload;
} FsmInstanceData_t;

typedef FsmState_t FsmStateFunc_t(FsmInstanceData_t* data);
typedef void       FsmTransitionFunc_t(FsmInstanceData_t* data );

/* state event function prototypes*/
FsmState_t do_state_one(FsmInstanceData_t* data);
FsmState_t do_state_two(FsmInstanceData_t* data);
FsmState_t do_state_three(FsmInstanceData_t* data);
FsmState_t do_state_four(FsmInstanceData_t* data);

/* transition function prototypes */
void do_one_to_two(FsmInstanceData_t *data);
void do_two_to_three(FsmInstanceData_t *data);
void do_three_to_four(FsmInstanceData_t *data);
void do_four_to_one(FsmInstanceData_t *data);


FsmStateFunc_t* const fsm_stateTable[FSM_NUM_STATES] =
{
        do_state_one,
        do_state_two,
        do_state_three,
        do_state_four,
};

FsmTransitionFunc_t * const fsm_transitionTable[FSM_NUM_STATES][FSM_NUM_STATES] =
{
    { NULL,              do_one_to_two,     NULL,            NULL             },
    { NULL,              NULL,              do_two_to_three, NULL             },
    { NULL,              NULL,              NULL,            do_three_to_four },
    { do_four_to_one,    NULL,              NULL,            NULL             },

};

FsmState_t fsm_run(FsmState_t stateCurrent, FsmInstanceData_t* data)
{
    FsmState_t stateNext            = fsm_stateTable[stateCurrent](data);
    FsmTransitionFunc_t* transition = fsm_transitionTable[stateCurrent][stateNext];

    if (NULL != transition)
    {
        transition(data);
    }

    return stateNext;
}

/* transitions */
void do_one_to_two(FsmInstanceData_t *data)
{
    gpioToggle(LED5_PORT, LED5_PIN);
}

void do_two_to_three(FsmInstanceData_t *data)
{
    gpioToggle(LED4_PORT, LED4_PIN);
}

void do_three_to_four(FsmInstanceData_t *data)
{
    gpioToggle(LED6_PORT, LED6_PIN);
}

void do_four_to_one(FsmInstanceData_t *data)
{
    gpioToggle(LED3_PORT, LED3_PIN);
}

/* state events */
FsmState_t do_state_one(FsmInstanceData_t* data)
{
    FsmState_t nextState = FSM_STATE_ONE;

    if (interruptTriggered)
    {
        nextState = FSM_STATE_TWO;
        interruptTriggered = false;
    }

    return nextState;
}

FsmState_t do_state_two(FsmInstanceData_t* data)
{

    FsmState_t nextState = FSM_STATE_TWO;

    if (interruptTriggered)
    {
        nextState = FSM_STATE_THREE;
        interruptTriggered = false;
    }

    return nextState;
}

FsmState_t do_state_three(FsmInstanceData_t* data)
{
    FsmState_t nextState = FSM_STATE_THREE;

    if (interruptTriggered)
    {
        nextState = FSM_STATE_FOUR;
        interruptTriggered = false;
    }

    return nextState;
}

FsmState_t do_state_four(FsmInstanceData_t* data)
{
    FsmState_t nextState = FSM_STATE_FOUR;

    if (interruptTriggered)
    {
        nextState = FSM_STATE_ONE;
        interruptTriggered = false;
    }

    return nextState;
}

/********************************************************************************
 * public functions
 ********************************************************************************/
void ledTask(void)
{
    static FsmInstanceData_t data = { 0 };
    static FsmState_t state = FSM_STATE_ONE;

    state = fsm_run(state, &data);
}

void fsm_interruptTriggered(void)
{
    interruptTriggered = true;
}

