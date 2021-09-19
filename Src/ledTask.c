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
static FsmState_t fsm_stateCurrent = FSM_STATE_FOUR;
static FsmState_t fsm_stateNext = FSM_STATE_ONE;

typedef struct
{
    uint8_t payload;
} FsmInstanceData_t;

typedef void FsmStateFunc_t (FsmInstanceData_t* data);

void do_state_one(FsmInstanceData_t* data);
void do_state_two(FsmInstanceData_t* data);
void do_state_three(FsmInstanceData_t* data);
void do_state_four(FsmInstanceData_t* data);

FsmStateFunc_t* const fsm_stateTable[FSM_NUM_STATES] =
{
        do_state_one,
        do_state_two,
        do_state_three,
        do_state_four,
};

void fsm_run(FsmInstanceData_t* data)
{
    if (fsm_stateNext != fsm_stateCurrent)
    {
        fsm_stateCurrent = fsm_stateNext;
        fsm_stateTable[fsm_stateCurrent](data);
    }
}

void fsm_setNextState(FsmState_t stateNext)
{
    fsm_stateNext = stateNext;
}

FsmState_t fsm_getCurrentState(void)
{
    return fsm_stateCurrent;
}

void do_state_one(FsmInstanceData_t* data)
{
    gpioToggle(LED3_PORT, LED3_PIN);
}

void do_state_two(FsmInstanceData_t* data)
{
    gpioToggle(LED5_PORT, LED5_PIN);
}

void do_state_three(FsmInstanceData_t* data)
{
    gpioToggle(LED4_PORT, LED4_PIN);
}

void do_state_four(FsmInstanceData_t* data)
{
    gpioToggle(LED6_PORT, LED6_PIN);
}

/********************************************************************************
 * public functions
 ********************************************************************************/
void ledTask(void)
{
    static FsmInstanceData_t data = { 0 };

    fsm_run(&data);
}
