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
void usartTransmit(USART_TypeDef* usart, const uint8_t* data, const uint32_t size)
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

