/********************************************************************************
 * @file           : spi.h
 * @author         : Christian Mahlburg
 * @date		   : 18.07.2020
 * @brief          : This file contains the spi driver implementation.
 *
 * This is a very simple driver implementation using standard full duplex
 * unidirectional communication configuration of the device.
 * The following configuration is unchanged (default register settings in device):
 * - CRC calculation is disabled
 * - MSB first
 * - full duplex
 * - clock polarity low
 * - fisrt clock transition is first data caputre edge
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
#ifndef SPI_H_
#define SPI_H_

/********************************************************************************
 * includes
 ********************************************************************************/
#include "stm32f072xb.h"
#include "error.h"

/********************************************************************************
 * defines
 ********************************************************************************/
/**
 * @brief SPI clock enable / disable
 */
#define RCC_SPI1_CLK_ENABLE()     (RCC->APB2ENR |= RCC_APB2ENR_SPI1EN)
#define RCC_SPI1_CLK_DISABLE()    (RCC->APB2ENR &= ~RCC_APB2ENR_SPI1EN)
#define RCC_SPI2_CLK_ENABLE()     (RCC->APB1ENR |= RCC_APB1ENR_SPI2EN)
#define RCC_SPI2_CLK_DISABLE()    (RCC->APB1ENR &= ~RCC_APB1ENR_SPI2EN)

/**
 * @brief SPI CR1 baud rate prescaler
 */
#define SPI_BAUD_PRESCALE_2     (0x00U << SPI_CR1_BR_Pos)
#define SPI_BAUD_PRESCALE_4     (0x01U << SPI_CR1_BR_Pos)
#define SPI_BAUD_PRESCALE_8     (0x02U << SPI_CR1_BR_Pos)
#define SPI_BAUD_PRESCALE_16    (0x03U << SPI_CR1_BR_Pos)
#define SPI_BAUD_PRESCALE_32    (0x04U << SPI_CR1_BR_Pos)
#define SPI_BAUD_PRESCALE_64    (0x05U << SPI_CR1_BR_Pos)
#define SPI_BAUD_PRESCALE_128   (0x06U << SPI_CR1_BR_Pos)
#define SPI_BAUD_PRESCALE_256   (0x07U << SPI_CR1_BR_Pos)

/**
 * @brief SPI CR2 Datasize
 */
#define SPI_DATASIZE_4BIT       (0x03U << SPI_CR2_DS_Pos)
#define SPI_DATASIZE_5BIT       (0x04U << SPI_CR2_DS_Pos)
#define SPI_DATASIZE_6BIT       (0x05U << SPI_CR2_DS_Pos)
#define SPI_DATASIZE_7BIT       (0x06U << SPI_CR2_DS_Pos)
#define SPI_DATASIZE_8BIT       (0x07U << SPI_CR2_DS_Pos)
#define SPI_DATASIZE_9BIT       (0x08U << SPI_CR2_DS_Pos)
#define SPI_DATASIZE_10BIT      (0x09U << SPI_CR2_DS_Pos)
#define SPI_DATASIZE_11BIT      (0x0AU << SPI_CR2_DS_Pos)
#define SPI_DATASIZE_12BIT      (0x0BU << SPI_CR2_DS_Pos)
#define SPI_DATASIZE_13BIT      (0x0CU << SPI_CR2_DS_Pos)
#define SPI_DATASIZE_14BIT      (0x0DU << SPI_CR2_DS_Pos)
#define SPI_DATASIZE_15BIT      (0x0EU << SPI_CR2_DS_Pos)
#define SPI_DATASIZE_16BIT      (0x0FU << SPI_CR2_DS_Pos)

/**
 * @brief SPI CR1 master / slave configuration
 */
#define SPI_MODE_SLAVE          0x00
#define SPI_MODE_MASTER         SPI_CR1_MSTR

/********************************************************************************
 * public types and variables
 ********************************************************************************/
/**
 * @brief spi register configuration
 */
typedef struct
{
    uint32_t masterMode;
    uint32_t baudPrescale;
    uint32_t dataLength;
}SpiConfig_t;

/********************************************************************************
 * public function prototypes
 ********************************************************************************/
void spiInit(SPI_TypeDef* SPI, const SpiConfig_t* conf);

/********************************************************************************
 * inline functions
 ********************************************************************************/
/**
 * @brief enable SPI
 */
static inline void spiEnable(SPI_TypeDef* SPI)
{
    ASSERT(IS_SPI_ALL_INSTANCE(SPI));

    SPI->CR1 |= SPI_CR1_SPE;
}

/**
 * @brief enable SPI
 */
static inline void spiDisable(SPI_TypeDef* SPI)
{
    ASSERT(IS_SPI_ALL_INSTANCE(SPI));

    SPI->CR1 &= ~SPI_CR1_SPE;
}

#endif /* SPI_H_ */
