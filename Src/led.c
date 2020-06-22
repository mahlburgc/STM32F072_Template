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

FsmLedState_t g_ledState = LED_STATE_FIRST;

void ledTask(void)
{
    static FsmLedState_t ledStateOld = LED_STATE_LAST;
    static uint32_t i_testCounter    = 0;                           /* DEBUG */
    static int32_t si_testCounter    = 0;                           /* DEBUG */
    static float f_testCounter       = 0;                           /* DEBUG */

    while (g_ledState == ledStateOld);                              /* wait for FSM state changing */

    print("Test\r\n");                                                                  /* DEBUG */
    printArg("Test with Arg\r\n");                                                      /* DEBUG */
    printArg("Test with int counter: %d\r\n", i_testCounter);                           /* DEBUG */
    printArg("Test signed: %d unsigned: %d\r\n", si_testCounter, i_testCounter);        /* DEBUG */

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
    i_testCounter++;        /* DEBUG */
    si_testCounter--;       /* DEBUG */
    f_testCounter -= 3.1;   /* DEBUG */
}
