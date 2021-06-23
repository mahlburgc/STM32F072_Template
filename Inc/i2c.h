/********************************************************************************
 * @file           : i2c.h
 * @author         : Christian Mahlburg
 * @date		   : 23.06.2021
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
#ifndef I2C_H_
#define I2C_H_

/********************************************************************************
 * includes
 ********************************************************************************/
#include "stm32f072xb.h"
#include "error.h"

/********************************************************************************
 * defines
 ********************************************************************************/
/**
 * @brief I2C port clock enable/disable
 */
#define RCC_I2C1_CLK_ENABLE()       (RCC->APB1ENR |= RCC_APB1ENR_I2C1EN)
#define RCC_I2C1_CLK_DISABLE()      (RCC->APB1ENR &= ~RCC_APB1ENR_I2C1EN)
#define RCC_I2C2_CLK_ENABLE()       (RCC->APB1ENR |= RCC_APB1ENR_I2C2EN)
#define RCC_I2C2_CLK_DISABLE()      (RCC->APB1ENR &= ~RCC_APB1ENR_I2C2EN)

/**
 * @brief I2C slave address mode (CR2)
 */
#define I2C_ADDRESSINGMODE_7BIT     (uint32_t)(0x01U << 11U)
#define I2C_ADDRESSINGMODE_10BIT    (uint32_t)(0x02U << 11U)

/**
 * @brief Timing clear mask, used to clear reserved bits in TIMINGR
 */
#define TIMING_CLEAR_MASK           0xF0FFFFFFU

/********************************************************************************
 * public types and variables
 ********************************************************************************/
/**
 * @brief I2C configuration struct with the very basic configuration for master to slave communication
 */
typedef struct
{
    uint32_t timing;             /* configure i2c master clock in TIMINGR, calculated by referring to I2C initialization in ref man */
    uint32_t addressingMode;     /* 7-bit or 10-bit addressing mode */
}I2cConfig_t;

/********************************************************************************
 * public function prototypes
 ********************************************************************************/
void i2cInit(I2C_TypeDef* i2c, const I2cConfig_t* conf);

/********************************************************************************
 * public inline functions
 ********************************************************************************/
/**
 * @brief enable i2c peripheral
 *        Changing the filter configuration is not allowed when the I2C is enabled.
 */
static inline void i2cEnable(I2C_TypeDef* i2c)
{
    ASSERT(IS_I2C_ALL_INSTANCE(i2c));

    i2c->CR1 |= I2C_CR1_PE;
}

/**
 * @brief disable i2c peripheral, I2C SCL and SDA lines are released and i2c software reset
 *        When cleared, PE must be kept low for at least 3 APB clock cycles (see f0 ref man).
 */
static inline void i2cDisable(I2C_TypeDef* i2c)
{
    ASSERT(IS_I2C_ALL_INSTANCE(i2c));

    i2c->CR1 &= ~I2C_CR1_PE;
}

#endif /* I2C_H_ */
