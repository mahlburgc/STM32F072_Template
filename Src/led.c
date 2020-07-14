/********************************************************************************
 * @file           : led.c
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
#include "stdio.h"
#include "main.h"
#include "led.h"
#include "gpio.h"
#include "usart.h"
#include "debug.h"
#include "misc.h"
#include "tim.h"

/********************************************************************************
 * public variables
 ********************************************************************************/
FsmLedState_t g_ledState = LED_STATE_LAST;

/********************************************************************************
 * public functions
 ********************************************************************************/
void ledTask(void)
{
    static FsmLedState_t ledStateOld = LED_STATE_LAST;

    /* check for FSM state changing */
    if (g_ledState != ledStateOld)
    {
        /* simple state machine, state is changed by TIM16 interrupt */
        switch (g_ledState)
        {
        case LED_STATE_FIRST:
            gpioToggle(LED3_PORT, LED3_PIN);
            break;
        case LED_STATE_TWO:
            gpioToggle(LED5_PORT, LED5_PIN);
            break;
        case LED_STATE_THREE:
            gpioToggle(LED4_PORT, LED4_PIN);
            break;
        case LED_STATE_LAST:
            gpioToggle(LED6_PORT, LED6_PIN);
            break;
        }

        ledStateOld = g_ledState;
    }
}
