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
#include "Fsm.h"

/********************************************************************************
 * public variables
 ********************************************************************************/
bool interruptTriggered = false;

typedef enum
{
    FSM_LED_STATE_ONE = 0,
    FSM_LED_STATE_TWO,
    FSM_LED_STATE_THREE,
    FSM_LED_STATE_FOUR,
    /* do not use as state */
    NUM_OF_FSM_LED_STATES,
} FsmLedStateId_t;

/* state event function prototypes */
void* eventOne(FsmInstanceData_t* data);
void* eventTwo(FsmInstanceData_t* data);
void* eventThree(FsmInstanceData_t* data);
void* eventFour(FsmInstanceData_t* data);

/* on entry function prototypes */
void onEntryOne(FsmInstanceData_t* data);
void onEntryTwo(FsmInstanceData_t* data);
void onEntryThree(FsmInstanceData_t* data);
void onEntryFour(FsmInstanceData_t* data);

FsmState_t fsmTable[NUM_OF_FSM_LED_STATES] =
{
    [FSM_LED_STATE_ONE]    = { eventOne,   onEntryOne,   NULL },
    [FSM_LED_STATE_TWO]    = { eventTwo,   onEntryTwo,   NULL },
    [FSM_LED_STATE_THREE]  = { eventThree, onEntryThree, NULL },
    [FSM_LED_STATE_FOUR]   = { eventFour,  onEntryFour,  NULL },
 };

/* on entry functions */
void onEntryOne(FsmInstanceData_t* data)
{
    gpioToggle(LED5_PORT, LED5_PIN);
}

void onEntryTwo(FsmInstanceData_t* data)
{
    gpioToggle(LED4_PORT, LED4_PIN);
}

void onEntryThree(FsmInstanceData_t* data)
{
    gpioToggle(LED6_PORT, LED6_PIN);
}

void onEntryFour(FsmInstanceData_t* data)
{
    gpioToggle(LED3_PORT, LED3_PIN);
}

/* state event functions*/
void* eventOne(FsmInstanceData_t* data)
{
    FsmState_t* nextState = &fsmTable[FSM_LED_STATE_ONE];

    if (interruptTriggered)
    {
        nextState = &fsmTable[FSM_LED_STATE_TWO];
        interruptTriggered = false;
    }

    return nextState;
}

void* eventTwo(FsmInstanceData_t* data)
{
    FsmState_t* nextState = &fsmTable[FSM_LED_STATE_TWO];

    if (interruptTriggered)
    {
        nextState = &fsmTable[FSM_LED_STATE_THREE];
        interruptTriggered = false;
    }

    return nextState;
}

void* eventThree(FsmInstanceData_t* data)
{
    FsmState_t* nextState = &fsmTable[FSM_LED_STATE_THREE];

    if (interruptTriggered)
    {
        nextState = &fsmTable[FSM_LED_STATE_FOUR];
        interruptTriggered = false;
    }

    return nextState;
}

void* eventFour(FsmInstanceData_t* data)
{
    FsmState_t* nextState = &fsmTable[FSM_LED_STATE_FOUR];

    if (interruptTriggered)
    {
        nextState = &fsmTable[FSM_LED_STATE_ONE];
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
    static FsmState_t*      state = &fsmTable[FSM_LED_STATE_ONE];

    state = fsmRun(state, &data);
}

void fsm_interruptTriggered(void)
{
    interruptTriggered = true;
}

