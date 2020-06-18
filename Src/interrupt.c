/*
 * interrupt.c
 *
 *  Created on: 18.06.2020
 *      Author: cma
 *
 *  This file contains the definition of the interrupt service routines.
 */

#include "main.h"
#include "gpio.h"

extern uint32_t g_sysTick;

/**
 * @brief System Tick
 *        SysTick_Handler is triggered by SYSCLK which should be usually configured to 1ms.
 */
void SysTick_Handler(void)
{
    g_sysTick++;
}

/**
 * @brief Timer 16 ISR
 */
void TIM16_IRQHandler(void)
{
    if (TIM_SR_CC1IF == (TIM16->SR & TIM_SR_CC1IF)) /* check CC1 interrupt flag */
    {
        gpioToggle(LED3_PORT, LED3_PIN);
    }
    TIM16->SR = 0;                                  /* clear status register */
}
