/********************************************************************************
 * @file           : usart.h
 * @author         : Christian Mahlburg
 * @date           : 20.06.2020
 * @brief          :
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
#ifndef USART_H_
#define USART_H_

/********************************************************************************
 * includes
 ********************************************************************************/
#include "stm32f072xb.h"
#include "error.h"

/********************************************************************************
 * defines
 ********************************************************************************/
/**
 * @brief USART port clock enable / disable
 */
#define RCC_USART1_CLK_ENABLE()     (RCC->APB2ENR |= RCC_APB2ENR_USART1EN)
#define RCC_USART1_CLK_DISABLE()    (RCC->APB2ENR &= ~RCC_APB2ENR_USART1EN)

/**
 * @brief USART word length (CR1 M1 and M0)
 */
#define USART_WORD_LENGTH_7     0x10000000U
#define USART_WORD_LENGTH_8     0x00000000U
#define USART_WORD_LENGTH_9     0x00001000U

/**
 * @brief USART parity selection (CR1)
 */
#define USART_PARITY_EN         (uint32_t)(0x01U << 9U)
#define USART_PARITY_EVEN       (uint32_t)(0x00U << 10U)
#define USART_PARITY_ODD        (uint32_t)(0x01U << 10U)

/**
 * @brief USART enable and transmission enable and receive enable (CR1)
 */
#define USART_EN                (uint32_t)(0x01U << 0U)
#define USART_TX_EN             (uint32_t)(0x01U << 3U)
#define USART_RX_EN             (uint32_t)(0x01U << 2U)

/**
 * @brief USART STOP bits (CR2)
 */
#define USART_STOP_BITS_0_5     (uint32_t)(0x01U << 12U)
#define USART_STOP_BITS_1       (uint32_t)(0x00U << 12U)
#define USART_STOP_BITS_1_5     (uint32_t)(0x02U << 12U)
#define USART_STOP_BITS_2       (uint32_t)(0x03U << 12U)

/**
 * @brief USART transmission data register empty and complete (ISR)
 */
#define USART_TX_COMPLETE       (uint32_t)(0x01U << 6U)
#define USART_TX_DATA_REG_EMPTY (uint32_t)(0x01U << 7U)

/********************************************************************************
 * public types and variables
 ********************************************************************************/
/**
 * @brief USART configuration struct with very basic configuration to transmit usart messages
 */
typedef struct
{
    uint32_t M1M0;      /* word length, can only be written when the USART is disabled (UE=0) */
    uint32_t PCE;       /* parity control enable, can only be written when the USART is disabled (UE=0) */
    uint32_t PS;        /* parity even or odd, can only be written when the USART is disabled (UE=0) */
    uint32_t STOP;      /* STOP bits, can only be written when the USART is disabled (UE=0) */
    uint32_t BRR;       /* baud rate, can only be written when the USART is disabled (UE=0) */
} UsartConfig_t;

/********************************************************************************
 * public function prototypes
 ********************************************************************************/
void usartInit(USART_TypeDef* usart, const UsartConfig_t* conf);
void usartTransmit(USART_TypeDef* usart, const uint32_t size, const uint8_t* data);
void usartReceive(USART_TypeDef* usart, const uint32_t size, uint8_t* const data);
void usartReceiveIT(USART_TypeDef* usart);

/********************************************************************************
 * public function prototypes
 ********************************************************************************/
static inline void usartEnable(USART_TypeDef* usart)
{
    ASSERT(IS_USART_INSTANCE(usart));

    usart->CR1 |= USART_EN;
}

static inline void usartDisable(USART_TypeDef* usart)
{
    ASSERT(IS_USART_INSTANCE(usart));

    usart->CR1 &= ~USART_EN;
}

static inline void usartTxEnable(USART_TypeDef* usart)
{
    ASSERT(IS_USART_INSTANCE(usart));

    usart->CR1 |= USART_TX_EN;
}

static inline void usartTxDisable(USART_TypeDef* usart)
{
    ASSERT(IS_USART_INSTANCE(usart));

    usart->CR1 &= ~USART_TX_EN;
}

static inline void usartRxEnable(USART_TypeDef* usart)
{
    ASSERT(IS_USART_INSTANCE(usart));

    usart->CR1 |= USART_RX_EN;
}

static inline void usartRxDisable(USART_TypeDef* usart)
{
    ASSERT(IS_USART_INSTANCE(usart));

    usart->CR1 &= ~USART_RX_EN;
}

#endif /* USART_H_ */
