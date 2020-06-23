/*
 * usart.h
 *
 *  Created on: 20.06.2020
 *      Author: cma
 */

#ifndef USART_H_
#define USART_H_

#include "stm32f072xb.h"

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

static inline void usartEnable(USART_TypeDef* usart)
{
    usart->CR1 |= USART_EN;
}

static inline void usartDisable(USART_TypeDef* usart)
{
    usart->CR1 &= ~USART_EN;
}

static inline void usartTxEnable(USART_TypeDef* usart)
{
    usart->CR1 |= USART_TX_EN;
}

static inline void usartTxDisable(USART_TypeDef* usart)
{
    usart->CR1 &= ~USART_TX_EN;
}

static inline void usartRxEnable(USART_TypeDef* usart)
{
    usart->CR1 |= USART_RX_EN;
}

static inline void usartRxDisable(USART_TypeDef* usart)
{
    usart->CR1 &= ~USART_RX_EN;
}

void usartInit(USART_TypeDef* usart, const UsartConfig_t* conf);
void usartTransmit(USART_TypeDef* usart, const uint32_t size, const uint8_t* data);
void usartReceive(USART_TypeDef* usart, const uint32_t size, uint8_t* const data);

#endif /* USART_H_ */
