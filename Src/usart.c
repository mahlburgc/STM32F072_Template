/*
 * usart.c
 *
 *  Created on: 20.06.2020
 *      Author: cma
 *
 *      This module implements a basic usart driver for communication.
 */

#include "usart.h"

static void usartTransmit8Bit(USART_TypeDef* usart, const uint8_t data);
static uint8_t usartReceive8Bit(USART_TypeDef* usart);

/**
 * @brief basic usart initialization
 */
void usartInit(USART_TypeDef* usart, const UsartConfig_t* conf)
{
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
    for (uint32_t i = 0; i < size; i++)
    {
        usartTransmit8Bit(usart, data[i]);
    }
}

/**
 * @brief usart 8Bit transmission
 */
static void usartTransmit8Bit(USART_TypeDef* usart, const uint8_t data)
{
    usart->TDR = data;

    while (USART_TX_COMPLETE != (usart->ISR & USART_TX_COMPLETE)); /* wait for transmission complete */
}

/**
 * @brief usart reception
 *        To use this function, usart and usart reception must be enabled first!
 */
void usartReceive(USART_TypeDef* usart, const uint32_t size, uint8_t* const data)
{
    for (uint32_t i = 0; i < size; i++)
    {
        data[i] = usartReceive8Bit(usart);
    }
}

/**
 * @brief usart 8Bit receive (without parity bit)
 */
static uint8_t usartReceive8Bit(USART_TypeDef* usart)
{
//    while (USART_ISR_BUSY != (usart->ISR & USART_ISR_BUSY)); /* wait for start of reception, TODO Timeout */

    if (USART_ISR_ORE == (usart->ISR & USART_ISR_ORE)) /* if overrun was detected, reset overrun bit */
    {
        usart->ICR |= USART_ICR_ORECF;
    }

    while (USART_ISR_RXNE != (usart->ISR & USART_ISR_RXNE)); /* wait for end of reception, TODO Timeout*/

    return (uint8_t)usart->RDR;
}

/**
 * @brief usart receive with interrupt
 *        This functions activates an interrupt on every character reception.
 *        This can be used to collect a number of characters on usart rx line.
 */
void usartReceiveIT(USART_TypeDef* usart)
{
    usart->CR1 |= USART_CR1_RXNEIE; /* enable rx not empty interrupt */
    usart->CR3 |= USART_CR3_EIE;    /* enable error interrupts framing error, overrun error or noise flag (FE=1 or ORE=1 or NF=1 in the USART_ISR register). */
}
