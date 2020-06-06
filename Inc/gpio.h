/*
 * gpio.h
 *
 *  Created on: 24.05.2020
 *      Author: Christian Mahlburg
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "stdint.h"

/**
 * @brief GPIO pin definitions
 */
#define GPIO_PIN_0  (uint16_t)0x0001
#define GPIO_PIN_1  (uint16_t)0x0002
#define GPIO_PIN_2  (uint16_t)0x0004
#define GPIO_PIN_3  (uint16_t)0x0008
#define GPIO_PIN_4  (uint16_t)0x0010
#define GPIO_PIN_5  (uint16_t)0x0020
#define GPIO_PIN_6  (uint16_t)0x0040
#define GPIO_PIN_7  (uint16_t)0x0080
#define GPIO_PIN_8  (uint16_t)0x0100
#define GPIO_PIN_9  (uint16_t)0x0200
#define GPIO_PIN_10 (uint16_t)0x0400
#define GPIO_PIN_11 (uint16_t)0x0800
#define GPIO_PIN_12 (uint16_t)0x1400
#define GPIO_PIN_13 (uint16_t)0x2400
#define GPIO_PIN_14 (uint16_t)0x4400
#define GPIO_PIN_15 (uint16_t)0x8400

#define LED3_PORT   GPIOC
#define LED3_PIN    GPIO_PIN_6
#define LED4_PORT   GPIOC
#define LED4_PIN    GPIO_PIN_7
#define LED5_PORT   GPIOC
#define LED5_PIN    GPIO_PIN_8
#define LED6_PORT   GPIOC
#define LED6_PIN    GPIO_PIN_9

#define GPIO_INPUT_MODE     (uint32_t)0x00
#define GPIO_OUTPUT_MODE    (uint32_t)0x01
#define GPIO_ALTERNATE_MODE (uint32_t)0x10
#define GPIO_ANALOG_MODE    (uint32_t)0x11

/**
 * @brief GPIO pin states
 */
typedef enum
{
    GPIO_PIN_RESET,
    GPIO_PIN_SET,
} gpioPinState_t;

void gpioInit(void);
void gpioToggle(GPIO_TypeDef* gpioPort, uint32_t gpioPin);
void gpioSet(GPIO_TypeDef* gpioPort, uint32_t gpioPin, gpioPinState_t gpioState);

#endif /* GPIO_H_ */
