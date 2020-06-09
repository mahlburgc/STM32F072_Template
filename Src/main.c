/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Christian Mahlburg
 * @brief          : Main program body
 ******************************************************************************/

#include "main.h"
#include "stm32f072xb.h"
#include "gpio.h"

void sysInit(void);
void sysGpioInit(void);

/**
 * @brief  main loop
 *         Main program to test implementation without using HAL.
 */
int main(void)
{
    sysInit();
    sysGpioInit();

    while(1U)
    {
        delay(100000U);
        gpioToggle(LED3_PORT, LED3_PIN);
        delay(100000U);
        gpioToggle(LED5_PORT, LED5_PIN);
        delay(100000U);
        gpioToggle(LED4_PORT, LED4_PIN);
        delay(100000U);
        gpioToggle(LED6_PORT, LED6_PIN);
    }
}

/**
 * @brief system initialization
 */
void sysInit(void)
{
    /* Enable the FLASH prefetch buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;
}

/**
 * @brief system gpio initialization
 */
void sysGpioInit(void)
{
    GpioConfig_t gpioConfig = { 0 };

    /* enable AHB peripheral clock for GPIOC */
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

    gpioConfig.pin          = LED3_PIN | LED4_PIN | LED5_PIN | LED6_PIN;
    gpioConfig.moder        = GPIO_OUTPUT_MODE;
    gpioConfig.type         = GPIO_OUTPUT_PP;
    gpioConfig.pull         = GPIO_NO_PULL;
    gpioConfig.speed        = GPIO_SPEED_LOW;
    gpioInit(GPIOC, &gpioConfig);

    gpioSet(GPIOC, LED3_PIN | LED4_PIN | LED5_PIN | LED6_PIN, GPIO_PIN_SET);
}
