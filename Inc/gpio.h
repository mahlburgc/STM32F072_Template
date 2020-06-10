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
#define GPIO_PIN_0          (uint16_t)0x0001U
#define GPIO_PIN_1          (uint16_t)0x0002U
#define GPIO_PIN_2          (uint16_t)0x0004U
#define GPIO_PIN_3          (uint16_t)0x0008U
#define GPIO_PIN_4          (uint16_t)0x0010U
#define GPIO_PIN_5          (uint16_t)0x0020U
#define GPIO_PIN_6          (uint16_t)0x0040U
#define GPIO_PIN_7          (uint16_t)0x0080U
#define GPIO_PIN_8          (uint16_t)0x0100U
#define GPIO_PIN_9          (uint16_t)0x0200U
#define GPIO_PIN_10         (uint16_t)0x0400U
#define GPIO_PIN_11         (uint16_t)0x0800U
#define GPIO_PIN_12         (uint16_t)0x1400U
#define GPIO_PIN_13         (uint16_t)0x2400U
#define GPIO_PIN_14         (uint16_t)0x4400U
#define GPIO_PIN_15         (uint16_t)0x8400U

/**
 * @brief GPIO input/output mode
 */
#define GPIO_INPUT_MODE     (uint32_t)0x00U
#define GPIO_OUTPUT_MODE    (uint32_t)0x01U
#define GPIO_ALTERNATE_MODE (uint32_t)0x10U
#define GPIO_ANALOG_MODE    (uint32_t)0x11U

/**
 * @brief GPIO push pull / open drain
 */
#define GPIO_OUTPUT_PP      (uint32_t)0x00U
#define GPIO_OUTPUT_OD      (uint32_t)0x01U
#define GPIO_NO_PULL        (uint32_t)0x00U
#define GPIO_PULLUP         (uint32_t)0x01U
#define GPIO_PULLDOWN       (uint32_t)0x02U

/**
 * @brief GPIO frequency
 */
#define GPIO_SPEED_LOW      (uint32_t)0x00U
#define GPIO_SPEED_MIDDLE   (uint32_t)0x01U
#define GPIO_SPEED_HIGH     (uint32_t)0x03U

/**
 * @brief GPIO alternate function / connected peripheral (spi, i2c etc.)
 *        Refer to alternate function table in device datasheet!
 */
#define GPIO_AF0            (uint32_t)0x0000U
#define GPIO_AF1            (uint32_t)0x0001U
#define GPIO_AF2            (uint32_t)0x0002U
#define GPIO_AF3            (uint32_t)0x0003U
#define GPIO_AF4            (uint32_t)0x0004U
#define GPIO_AF5            (uint32_t)0x0005U
#define GPIO_AF6            (uint32_t)0x0006U
#define GPIO_AF7            (uint32_t)0x0007U

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
