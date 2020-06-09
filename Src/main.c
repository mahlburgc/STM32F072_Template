/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Christian Mahlburg
 * @brief          : Main program body
 ******************************************************************************/

#include "main.h"
#include "stm32f072xb.h"
#include "gpio.h"
#include "pinmux.h"

/**
 * @brief  main loop
 *         Main program to test implementation without using HAL.
 */
int main(void)
{
    /* Enable the FLASH prefetch buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* first enable AHB peripheral clock for GPIOC */
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

    pinmux();

    while(1)
    {
        gpioToggle(LED3_PORT, LED3_PIN);
        gpioToggle(LED4_PORT, LED4_PIN);
        gpioToggle(LED5_PORT, LED5_PIN);
        gpioToggle(LED6_PORT, LED6_PIN);
        delay(800000);
    }
}
