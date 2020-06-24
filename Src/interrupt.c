/*
 * interrupt.c
 *
 *  Created on: 18.06.2020
 *      Author: cma
 *
 *  This file contains the definition of the interrupt service routines.
 */

#include <string.h>
#include "main.h"
#include "gpio.h"
#include "led.h"
#include "debug.h"
#include "serialCom.h"
#include "error.h"

extern uint32_t g_sysTick;
extern FsmLedState_t g_ledState;
extern RxMsg_t g_rxMsg;

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
        g_ledState++;
        if (g_ledState > LED_STATE_LAST)
        {
            g_ledState = LED_STATE_FIRST;
        }
    }
    TIM16->SR = 0;                                  /* clear status register */
}

/**
 * @brief USART 1 ISR
 */
void USART1_IRQHandler(void)
{
    static RxBuffer_t rxBuffer = { 0 };

    /* check overrun error flag */
    if (USART_ISR_ORE == (USART1->ISR & USART_ISR_ORE))
    {
        ERROR(g_err.ERR_USART1_BUFFER_OVERFLOW);
        USART1->ICR |= USART_ICR_ORECF;
    }

    /* check rx not empty flag */
    if (USART_ISR_RXNE == (USART1->ISR & USART_ISR_RXNE))
    {
        rxBuffer.data[rxBuffer.index] = USART1->RDR;
        rxBuffer.index++;

        if (rxBuffer.index == ARRAY_LEN(rxBuffer.data))
        {
            rxBuffer.index = 0;
            memcpy(g_rxMsg.data, rxBuffer.data, sizeof(g_rxMsg.data));
            g_rxMsg.rxComplete = true;
        }
    }
}
