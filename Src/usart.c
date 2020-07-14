/********************************************************************************
 * @file           : usart.c
 * @author         : Christian Mahlburg
 * @date           : 20.06.2020
 * @brief          : This module implements a basic usart driver for communication.
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
#include "usart.h"

/********************************************************************************
 * static function prototypes
 ********************************************************************************/
static void usartTransmit8Bit(USART_TypeDef* usart, const uint8_t data);
static uint8_t usartReceive8Bit(USART_TypeDef* usart);

/********************************************************************************
 * static functions
 ********************************************************************************/
/**
 * @brief usart 8Bit transmission
 */
static void usartTransmit8Bit(USART_TypeDef* usart, const uint8_t data)
{
    ASSERT(IS_USART_INSTANCE(usart));

    usart->TDR = data;

    while (USART_TX_COMPLETE != (usart->ISR & USART_TX_COMPLETE)); /* wait for transmission complete */
}

/**
 * @brief usart 8Bit receive (without parity bit)
 */
static uint8_t usartReceive8Bit(USART_TypeDef* usart)
{
    ASSERT(IS_USART_INSTANCE(usart));

    if (USART_ISR_ORE == (usart->ISR & USART_ISR_ORE)) /* if overrun was detected, reset overrun bit */
    {
        usart->ICR |= USART_ICR_ORECF;
    }

    while (USART_ISR_RXNE != (usart->ISR & USART_ISR_RXNE)); /* wait for end of reception, TODO Timeout*/

    return (uint8_t)usart->RDR;
}

/********************************************************************************
 * public functions
 ********************************************************************************/
/**
 * @brief basic usart initialization
 */
void usartInit(USART_TypeDef* usart, const UsartConfig_t* conf)
{
    ASSERT(IS_USART_INSTANCE(usart));
    ASSERT(0U != conf);

    /* set word length and parity config */
    usart->CR1 = (conf->M1M0 | conf->PCE | conf->PS);

    /* set STOP bits */
    usart->CR2 = conf->STOP;

    /* set baud rate */
    usart->BRR = conf->BRR;
}

/**
 * @brief usart transmission
 *        To use this function, usart and usart transmission must be enabled first!
 */
void usartTransmit(USART_TypeDef* usart, const uint32_t size, const uint8_t* data)
{
    ASSERT(IS_USART_INSTANCE(usart));
    ASSERT(0U != data);

    for (uint32_t i = 0; i < size; i++)
    {
        usartTransmit8Bit(usart, data[i]);
    }
}

/**
 * @brief usart reception
 *        To use this function, usart and usart reception must be enabled first!
 */
void usartReceive(USART_TypeDef* usart, const uint32_t size, uint8_t* const data)
{
    ASSERT(IS_USART_INSTANCE(usart));
    ASSERT(0U != data);

    for (uint32_t i = 0; i < size; i++)
    {
        data[i] = usartReceive8Bit(usart);
    }
}

/**
 * @brief usart receive with interrupt
 *        This functions activates an interrupt on every character reception.
 *        This can be used to collect a number of characters on usart rx line.
 */
void usartReceiveIT(USART_TypeDef* usart)
{
    ASSERT(IS_USART_INSTANCE(usart));

    usart->CR1 |= USART_CR1_RXNEIE; /* enable rx not empty interrupt */
    usart->CR3 |= USART_CR3_EIE;    /* enable error interrupts framing error, overrun error or noise flag (FE=1 or ORE=1 or NF=1 in the USART_ISR register). */
}
