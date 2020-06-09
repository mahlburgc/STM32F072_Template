/*
 * pinmux.c
 *
 *  Created on: Jun 9, 2020
 *      Author: cma
 *
 *      This file containts the low level configuration / the pin muxing.
 */

#include "gpio.h"
#include "pinmux.h"

/**
 * This function initializes the pin muxing.
 */
void pinmux(void)
{
    GpioConfig_t gpioConfig = { 0 };

    gpioConfig.pin          = LED3_PIN | LED4_PIN | LED5_PIN | LED6_PIN;
    gpioConfig.moder        = GPIO_OUTPUT_MODE;
    gpioConfig.type         = GPIO_OUTPUT_PP;
    gpioConfig.pull         = GPIO_NO_PULL;
    gpioConfig.speed        = GPIO_SPEED_LOW;
    gpioInit(GPIOC, &gpioConfig);
}




