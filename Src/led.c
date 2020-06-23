/*
 * led.c
 *
 *  Created on: 20.06.2020
 *      Author: cma
 *
 *      This file contains the ledTask and related functions.
 */

#include "stdio.h"
#include "main.h"
#include "led.h"
#include "gpio.h"
#include "usart.h"
#include "debug.h"
#include "misc.h"
#include "tim.h"

FsmLedState_t g_ledState = LED_STATE_LAST;

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
