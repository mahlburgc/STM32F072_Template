/*
 * gpio.c
 *
 *  Created on: 27.05.2020
 *      Author: cma
 */


#include "stdint.h"
#include "stm32f072xb.h"
#include "gpio.h"


/**
 * @brief This functions initializes all used gpios
 */
void gpioInit(void)
{
    uint32_t temp = 0;

    /* first enable AHB peripheral clock for GPIOC */
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

    /* set output level to high (atomic) */
    GPIOC->BSRR |= LED3_PIN;

    /* set output level to low (atomic) */
//    GPIOC->BRR |= LED3_PIN;

    /* Configure IO Direction mode */
    temp = GPIOC->MODER;
    temp &= ~(GPIO_MODER_MODER6_Msk); /* reset the two bits that should be configurated new in MODER */
    GPIOC->MODER = temp | (GPIO_OUTPUT_MODE << GPIO_MODER_MODER6_Pos);
}

/**
 * This function toggles the gpio
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
 * This function sets the gpio output
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
