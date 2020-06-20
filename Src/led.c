/*
 * led.c
 *
 *  Created on: 20.06.2020
 *      Author: cma
 *
 *      This file contains the ledTask and related functions.
 */

#include "main.h"
#include "led.h"
#include "gpio.h"

FsmLedState_t g_ledState = LED_STATE_FIRST;

void ledTask(void)
{
    static FsmLedState_t ledStateOld = LED_STATE_LAST;

    while (g_ledState == ledStateOld); /* wait for FSM state changing */

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
