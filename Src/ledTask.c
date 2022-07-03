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

typedef enum
{
    FSM_LED_STATE_ONE = 0,
    FSM_LED_STATE_TWO,
    FSM_LED_STATE_THREE,
    FSM_LED_STATE_FOUR,
    /* do not use as state */
    NUM_OF_FSM_LED_STATES,
} FsmStateId_t;

typedef struct
{
    uint8_t payload;
} FsmData_t;

/* function pointer */
typedef FsmStateId_t FsmEventFunc_t(FsmData_t* data);
typedef void FsmOnEntryFunc_t(FsmData_t* data);
typedef void FsmOnExitFunc_t(FsmData_t* data);

typedef struct
{
    FsmEventFunc_t* const event;
    FsmOnEntryFunc_t* const onEntry;
    FsmOnExitFunc_t* const onExit;
} FsmState_t;

/* state event function prototypes */
static FsmStateId_t eventOne(FsmData_t* data);
static FsmStateId_t eventTwo(FsmData_t* data);
static FsmStateId_t eventThree(FsmData_t* data);
static FsmStateId_t eventFour(FsmData_t* data);

/* on entry function prototypes */
static void onEntryOne(FsmData_t* data);
static void onEntryTwo(FsmData_t* data);
static void onEntryThree(FsmData_t* data);
static void onEntryFour(FsmData_t* data);

static FsmStateId_t fsmRun(const FsmStateId_t stateCurrent, FsmData_t* data);

static FsmState_t fsmTable[NUM_OF_FSM_LED_STATES] =
{
    [FSM_LED_STATE_ONE]    = { eventOne,   onEntryOne,   NULL },
    [FSM_LED_STATE_TWO]    = { eventTwo,   onEntryTwo,   NULL },
    [FSM_LED_STATE_THREE]  = { eventThree, onEntryThree, NULL },
    [FSM_LED_STATE_FOUR]   = { eventFour,  onEntryFour,  NULL },
 };

bool interruptTriggered = false;

/********************************************************************************
 * private functions
 ********************************************************************************/

/* on entry functions */
static void onEntryOne(FsmData_t* data)
{
    gpioToggle(LED5_PORT, LED5_PIN);
}

static void onEntryTwo(FsmData_t* data)
{
    gpioToggle(LED4_PORT, LED4_PIN);
}

static void onEntryThree(FsmData_t* data)
{
    gpioToggle(LED6_PORT, LED6_PIN);
}

static void onEntryFour(FsmData_t* data)
{
    gpioToggle(LED3_PORT, LED3_PIN);
}

/* state event functions*/
static FsmStateId_t eventOne(FsmData_t* data)
{
    FsmStateId_t nextState = FSM_LED_STATE_ONE;

    if (interruptTriggered)
    {
        nextState = FSM_LED_STATE_TWO;
        interruptTriggered = false;
    }

    return nextState;
}

static FsmStateId_t eventTwo(FsmData_t* data)
{
    FsmStateId_t nextState = FSM_LED_STATE_TWO;

    if (interruptTriggered)
    {
        nextState = FSM_LED_STATE_THREE;
        interruptTriggered = false;
    }

    return nextState;
}

static FsmStateId_t eventThree(FsmData_t* data)
{
    FsmStateId_t nextState = FSM_LED_STATE_THREE;

    if (interruptTriggered)
    {
        nextState = FSM_LED_STATE_FOUR;
        interruptTriggered = false;
    }

    return nextState;
}

static FsmStateId_t eventFour(FsmData_t* data)
{
    FsmStateId_t nextState = FSM_LED_STATE_FOUR;

    if (interruptTriggered)
    {
        nextState = FSM_LED_STATE_ONE;
        interruptTriggered = false;
    }

    return nextState;
}

/**
 * @brief fsm core handles the fsm states
 */
static FsmStateId_t fsmRun(const FsmStateId_t stateCurrent, FsmData_t* data)
{
    ASSERT(NULL != data);

    FsmStateId_t stateNext = fsmTable[stateCurrent].event(data);

    if (stateNext != stateCurrent)
    {
        if (NULL != fsmTable[stateCurrent].onExit)
        {
        	fsmTable[stateCurrent].onExit(data);
        }
        if (NULL != fsmTable[stateNext].onEntry)
        {
        	fsmTable[stateNext].onEntry(data);
        }
    }

    return stateNext;
}

/********************************************************************************
 * public functions
 ********************************************************************************/
void ledTask(void)
{
    static FsmData_t data = { 0 };
    static FsmStateId_t state = FSM_LED_STATE_ONE;

    state = fsmRun(state, &data);
}

void fsm_interruptTriggered(void)
{
    interruptTriggered = true;
}

