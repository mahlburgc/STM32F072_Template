/*
 * gpio.h
 *
 *  Created on: 24.05.2020
 *      Author: Christian Mahlburg
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "stdint.h"
#include "stm32f072xb.h"

/**
 * @brief GPIO definitions
 */
#define GPIO_PIN_0          (uint16_t)0x0001
#define GPIO_PIN_1          (uint16_t)0x0002
#define GPIO_PIN_2          (uint16_t)0x0004
#define GPIO_PIN_3          (uint16_t)0x0008
#define GPIO_PIN_4          (uint16_t)0x0010
#define GPIO_PIN_5          (uint16_t)0x0020
#define GPIO_PIN_6          (uint16_t)0x0040
#define GPIO_PIN_7          (uint16_t)0x0080
#define GPIO_PIN_8          (uint16_t)0x0100
#define GPIO_PIN_9          (uint16_t)0x0200
#define GPIO_PIN_10         (uint16_t)0x0400
#define GPIO_PIN_11         (uint16_t)0x0800
#define GPIO_PIN_12         (uint16_t)0x1400
#define GPIO_PIN_13         (uint16_t)0x2400
#define GPIO_PIN_14         (uint16_t)0x4400
#define GPIO_PIN_15         (uint16_t)0x8400

/**
 * @brief User defined GPIOs
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
 * @brief GPIO input/output mode
 */
#define GPIO_INPUT_MODE     (uint32_t)0x00
#define GPIO_OUTPUT_MODE    (uint32_t)0x01
#define GPIO_ALTERNATE_MODE (uint32_t)0x10
#define GPIO_ANALOG_MODE    (uint32_t)0x11

/**
 * @brief GPIO push pull / open drain
 */
#define GPIO_OUTPUT_PP      (uint32_t)0x00
#define GPIO_OUTPUT_OD      (uint32_t)0x01
#define GPIO_NO_PULL        (uint32_t)0x00
#define GPIO_PULLUP         (uint32_t)0x01
#define GPIO_PULLDOWN       (uint32_t)0x02

/**
 * @brief GPIO frequency
 */
#define GPIO_SPEED_LOW      (uint32_t)0x00
#define GPIO_SPEED_MIDDLE   (uint32_t)0x01
#define GPIO_SPEED_HIGH     (uint32_t)0x03

/**
 * @brief bit mask definitions for gpio config
 */
#define GPIO_MODER_MSK          (uint32_t)0x03
#define GPIO_MODER_MSK_LEN      (uint32_t)0x02
#define GPIO_OSPEEDER_MSK       (uint32_t)0x03
#define GPIO_OSPEEDER_MSK_LEN   (uint32_t)0x02
#define GPIO_AF_MSK             (uint32_t)0x07
#define GPUI_AF_MSK_LEN         (uint33_t)0x04

/**
 * @brief GPIO alternate function / connected peripheral (spi, i2c etc.)
 *        Refer to alternate function table in device datasheet!
 */
#define GPIO_AF0            (uint32_t)0x0000
#define GPIO_AF1            (uint32_t)0x0001
#define GPIO_AF2            (uint32_t)0x0002
#define GPIO_AF3            (uint32_t)0x0003
#define GPIO_AF4            (uint32_t)0x0004
#define GPIO_AF5            (uint32_t)0x0005
#define GPIO_AF6            (uint32_t)0x0006
#define GPIO_AF7            (uint32_t)0x0007

/**
 * @brief GPIO pin states
 */
typedef enum
{
    GPIO_PIN_RESET,
    GPIO_PIN_SET,
} gpioPinState_t;

/**
 * @brief GPIO pin configuration
 */
typedef struct
{
    uint32_t pin;
    uint32_t port;
    uint32_t moder;
    uint32_t type;
    uint32_t pull;
    uint32_t alternate;
    uint32_t speed;
} GpioConfig_t;

void gpioInit(GPIO_TypeDef* gpioPort, GpioConfig_t* gpioConfig);
void gpioToggle(GPIO_TypeDef* gpioPort, uint32_t gpioPin);
void gpioSet(GPIO_TypeDef* gpioPort, uint32_t gpioPin, gpioPinState_t gpioState);

#endif /* GPIO_H_ */
