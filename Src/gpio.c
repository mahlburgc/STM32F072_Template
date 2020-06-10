/*
 * gpio.c
 *
 *  Created on: 27.05.2020
 *      Author: cma
 */


#include "stm32f0xx.h"
#include "stm32f072xb.h"
#include "gpio.h"


/**
 * @ brief This functions initializes the gpio.
 */
void gpioInit(GPIO_TypeDef* gpioPort, GpioConfig_t* gpioConfig)
{
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
            MODIFY_REG(gpioPort->AFR[gpioNr >> 3U], (0x07U << (gpioNr * 4U)), (gpioConfig->alternate << (gpioNr * 4U)));
        }
        gpioNr++;
    }
}

/**
 * @brief This function toggles the gpio.
 */
void gpioToggle(GPIO_TypeDef* gpioPort, uint32_t gpioPin)
{
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
    if (GPIO_PIN_SET == gpioState)
    {
        gpioPort->BSRR  |= gpioPin;
    }
    else
    {
        gpioPort->BRR |= gpioPin;
    }
}
