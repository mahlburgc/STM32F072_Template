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
#include "fsm.h"
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
} FsmStateId_t;

/* state event function prototypes */
static uint8_t eventOne(void);
static uint8_t eventTwo(void);
static uint8_t eventThree(void);
static uint8_t eventFour(void);

/* on entry function prototypes */
static void onEntryOne(void);
static void onEntryTwo(void);
static void onEntryThree(void);
static void onEntryFour(void);

static FsmHandle_t fsmHandle;

bool interruptTriggered = false;

/********************************************************************************
 * private functions
 ********************************************************************************/

/* on entry functions */
static void onEntryOne(void)
{
    gpioToggle(LED5_PORT, LED5_PIN);
}

static void onEntryTwo(void)
{
    gpioToggle(LED4_PORT, LED4_PIN);
}

static void onEntryThree(void)
{
    gpioToggle(LED6_PORT, LED6_PIN);
}

static void onEntryFour(void)
{
    gpioToggle(LED3_PORT, LED3_PIN);
}

/* state event functions*/
static uint8_t eventOne(void)
{
    uint8_t nextState = FSM_LED_STATE_ONE;

    if (interruptTriggered)
    {
        nextState = FSM_LED_STATE_TWO;
        interruptTriggered = false;
    }

    return nextState;
}

static uint8_t eventTwo(void)
{
    uint8_t nextState = FSM_LED_STATE_TWO;

    if (interruptTriggered)
    {
        nextState = FSM_LED_STATE_THREE;
        interruptTriggered = false;
    }

    return nextState;
}

static uint8_t eventThree(void)
{
    uint8_t nextState = FSM_LED_STATE_THREE;

    if (interruptTriggered)
    {
        nextState = FSM_LED_STATE_FOUR;
        interruptTriggered = false;
    }

    return nextState;
}

static uint8_t eventFour(void)
{
    uint8_t nextState = FSM_LED_STATE_FOUR;

    if (interruptTriggered)
    {
        nextState = FSM_LED_STATE_ONE;
        interruptTriggered = false;
    }

    return nextState;
}

/********************************************************************************
 * public functions
 ********************************************************************************/
void ledTaskInit(void)
{
    fsmInit(&fsmHandle, FSM_LED_STATE_ONE);

    fsmAdd(&fsmHandle, FSM_LED_STATE_ONE, eventOne, onEntryOne, NULL);
    fsmAdd(&fsmHandle, FSM_LED_STATE_TWO, eventTwo, onEntryTwo, NULL);
    fsmAdd(&fsmHandle, FSM_LED_STATE_THREE, eventThree, onEntryThree, NULL);
    fsmAdd(&fsmHandle, FSM_LED_STATE_FOUR, eventFour, onEntryFour, NULL);
}

void ledTask(void)
{
    fsmRun(&fsmHandle);
}

void fsm_interruptTriggered(void)
{
    interruptTriggered = true;
}

