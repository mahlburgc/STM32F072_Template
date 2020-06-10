/*
 * main.h
 *
 *  Created on: Jun 6, 2020
 *      Author: Christian
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "stdint.h"

/**
 * @brief user defines
 */
#define LED3_PORT           GPIOC
#define LED3_PIN            GPIO_PIN_6
#define LED4_PORT           GPIOC
#define LED4_PIN            GPIO_PIN_7
#define LED5_PORT           GPIOC
#define LED5_PIN            GPIO_PIN_8
#define LED6_PORT           GPIOC
#define LED6_PIN            GPIO_PIN_9

/**
 * Wait for number of ticks
 */
static inline void delay(uint32_t ticks)
{
    for(uint32_t i = 0U;  i < ticks; i++);
}

#endif /* MAIN_H_ */
