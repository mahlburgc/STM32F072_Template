/********************************************************************************
 * @file           : gpio.c
 * @author         : Christian Mahlburg
 * @date           : 27.05.2020
 * @brief          : This file contains the init and helper functions for the GPIO
 *                   usage.
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
#include "stm32f0xx.h"
#include "stm32f072xb.h"
#include "gpio.h"
#include "error.h"

/********************************************************************************
 * public functions
 ********************************************************************************/
/**
 * @ brief This functions initializes the gpio.
 */
void gpioInit(GPIO_TypeDef* gpioPort, GpioConfig_t* gpioConfig)
{
    ASSERT(IS_GPIO_ALL_INSTANCE(gpioPort));
    ASSERT(0U != gpioConfig);

    uint32_t gpioNr = 0U; /* 0 ... 15 */

    while ((gpioConfig->pin >> gpioNr) != 0U)
    {
        if ((gpioConfig->pin >> gpioNr) & 1U)
        {
            /* IO direction mode */
            MODIFY_REG(gpioPort->MODER, (0x03U << (gpioNr * 2U)), (gpioConfig->moder << (gpioNr * 2U)));

            /* output type */
            SET_BIT(gpioPort->OTYPER, (gpioConfig->type << gpioNr));

            /* gpio speed */
            MODIFY_REG(gpioPort->OSPEEDR, (0x03U << (gpioNr * 2U)), (gpioConfig->speed << (gpioNr * 2U)));

            /* pull-up / pull-down */
            MODIFY_REG(gpioPort->PUPDR, (0x03U << (gpioNr * 2U)), (gpioConfig->pull << (gpioNr * 2U)));

            /* configure alternate function, (gpio >> 3) turns to zero (gpio pin0 - pin7) or one (gpio pin8 - 15) */
            MODIFY_REG(gpioPort->AFR[gpioNr >> 3U], (0x0FU << ((gpioNr & 0x07U) * 4U)), (gpioConfig->alternate << ((gpioNr & 0x07U) * 4U)));
        }
        gpioNr++;
    }
}

/**
 * @brief This function toggles the gpio.
 */
void gpioToggle(GPIO_TypeDef* gpioPort, uint32_t gpioPin)
{
    ASSERT(IS_GPIO_ALL_INSTANCE(gpioPort));

    if (gpioPin == (gpioPort->ODR & gpioPin))
    {
        gpioPort->BRR |= gpioPin; /* reset output to low */
    }
    else
    {
        gpioPort->BSRR |= gpioPin; /* set output to high */
    }
}

/**
 * @brief This function sets the gpio output.
 */
void gpioSet(GPIO_TypeDef* gpioPort, uint32_t gpioPin, gpioPinState_t gpioState)
{
    ASSERT(IS_GPIO_ALL_INSTANCE(gpioPort));

    if (GPIO_PIN_SET == gpioState)
    {
        gpioPort->BSRR  |= gpioPin;
    }
    else
    {
        gpioPort->BRR |= gpioPin;
    }
}
