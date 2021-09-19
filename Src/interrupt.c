/********************************************************************************
 * @file           : interrupt.c
 * @author         : Christian Mahlburg
 * @date           : 18.06.2020
 * @brief          : This file contains all interrupt service routines.
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
#include <ledTask.h>
#include <serialTask.h>
#include <string.h>
#include "main.h"
#include "gpio.h"
#include "debug.h"
#include "error.h"

/********************************************************************************
 * public variables
 ********************************************************************************/
extern uint32_t g_sysTick;
extern RxMsg_t g_rxMsg;

/********************************************************************************
 * public functions
 ********************************************************************************/
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
    static FsmState_t currentState = FSM_STATE_ONE;

    if (TIM_SR_CC1IF == (TIM16->SR & TIM_SR_CC1IF)) /* check CC1 interrupt flag */
    {
        currentState = fsm_getCurrentState();

        if (currentState >= (FSM_NUM_STATES - 1))
        {
            currentState = FSM_STATE_ONE;
        }
        else
        {
            currentState++;
        }
        fsm_setNextState(currentState);
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
