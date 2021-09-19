/********************************************************************************
 * @file           : spi.c
 * @author         : Christian Mahlburg
 * @date		   : 18.07.2020
 * @brief          : This file contains the implementation of the spi driver.
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
#include "spi.h"
#include "stm32f0xx.h"

/********************************************************************************
 * defines
 ********************************************************************************/

/********************************************************************************
 * static variables
 ********************************************************************************/

/********************************************************************************
 * static function prototypes
 ********************************************************************************/

/********************************************************************************
 * public variables
 ********************************************************************************/

/********************************************************************************
 * static functions
 ********************************************************************************/

/********************************************************************************
 * public functions
 ********************************************************************************/
/**
 * @brief basic SPI initialization
 */
void spiInit(SPI_TypeDef* SPI, const SpiConfig_t* conf)
{
    SPI->CR1 = conf->baudPrescale | conf->masterMode;
    SPI->CR2 = conf->dataLength;
}

/**
 * @brief SPI transmit
 */
void spiTransmit(SPI_TypeDef* SPI)
{
    /* TODO */
}

/**
 * @brief SPI receive
 */
void spiReceive(SPI_TypeDef* SPI)
{
    /* TODO */
}

/**
 * @brief SPI Transmit and Receive (full-duplex)
 */
void spiTransmitReceive(SPI_TypeDef* SPI)
{
    /* TODO */
}
