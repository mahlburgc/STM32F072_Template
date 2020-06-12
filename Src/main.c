/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Christian Mahlburg
 * @brief          : Main program body
 ******************************************************************************/

#include "main.h"
#include "stm32f072xb.h"
#include "gpio.h"
#include "tim.h"

extern uint32_t SystemCoreClock;

void sysInit(void);
void sysGpioInit(void);
void sysTimInit(void);
void delay(const uint16_t delay_ms);

/**
 * @brief  main loop
 *         Main program to test implementation without using HAL.
 */
int main(void)
{
    const uint16_t LED_DELAY = 200; /* ms */

    sysInit();
    sysGpioInit();
    sysTimInit();

    while(1U)
    {
        delay(LED_DELAY);
        gpioToggle(LED3_PORT, LED3_PIN);

        delay(LED_DELAY);
        gpioToggle(LED5_PORT, LED5_PIN);

        delay(LED_DELAY);
        gpioToggle(LED4_PORT, LED4_PIN);

        delay(LED_DELAY);
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

    RCC_GPIOC_CLK_ENABLE();

    gpioConfig.pin          = LED3_PIN | LED4_PIN | LED5_PIN | LED6_PIN;
    gpioConfig.moder        = GPIO_OUTPUT_MODE;
    gpioConfig.type         = GPIO_OUTPUT_PP;
    gpioConfig.pull         = GPIO_NO_PULL;
    gpioConfig.speed        = GPIO_SPEED_LOW;
    gpioInit(GPIOC, &gpioConfig);

    gpioSet(GPIOC, LED3_PIN | LED4_PIN | LED5_PIN | LED6_PIN, GPIO_PIN_SET);
}

/**
 * @brief system timer initialization
 */
void sysTimInit(void)
{
    TimConfig_t timConfig = { 0 };

    RCC_TIM15_CLK_ENABLE();

    /* SystemClockCore is initialized with 8MHz by default, prescaler is configured for counting up in ms tick */
    timConfig.ARR   = 0xFFFFU;
    timConfig.PSC   = 0x1F40U; /* 8000000MHz / 1000ms = 1F401 */
    timInit(TIM15, &timConfig);
}

/**
 * @brief Timer delay in ms. Timer 15 is configured for counting from
 * 0 to 65.535 ms.
 */
void delay(const uint16_t delay_ms)
{
    TIM15->ARR = delay_ms;

    timReset(TIM15);
    timStart(TIM15);
    while (!timExceed(TIM15));
    timStop(TIM15);
}
