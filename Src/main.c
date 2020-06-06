/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Christian Mahlburg
 * @brief          : Main program body
 ******************************************************************************/

#include "main.h"
#include "stm32f072xb.h"
#include "gpio.h"

/**
 * @brief  main loop
 *         Main program to test implementation without using HAL.
 */
int main(void)
{
    /* Enable the FLASH prefetch buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    gpioInit();

    while(1)
    {
        gpioToggle(LED3_PORT, LED3_PIN);
        delay(800000);
    }
}
