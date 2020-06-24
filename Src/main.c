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
#include "led.h"
#include "usart.h"
#include "serialCom.h"

uint32_t g_sysTick = 0U; /* global system Tick in ms */

void sysInit(void);
void sysGpioInit(void);
void sysTimInit(void);
void sysUsartInit(void);

/**
 * @brief  main loop
 *         Main program to test implementation without using HAL.
 */
int main(void)
{
    sysInit();
    sysGpioInit();
    sysTimInit();
    sysUsartInit();

    /* start timer for 1s interrupt */
    timReset(TIM16);
    timStart(TIM16);

    /* enable usart transmission for debug messages */
    usartEnable(USART1);
    usartTxEnable(USART1);
    usartRxEnable(USART1);
    usartReceiveIT(USART1);

    while(1U)
    {
        ledTask();
        serialComTask();
    }
}

/**
 * @brief system initialization
 */
void sysInit(void)
{
    FLASH->ACR |= FLASH_ACR_PRFTBE;          /* Enable the FLASH prefetch buffer */

    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / 1000U); /* configure SysTick_Handler to 1ms interrupt */
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

    /**
     * TIM15 can be used for casual start stop functionality.
     */
    RCC_TIM15_CLK_ENABLE();

    timConfig.ARR   = 0xFFFFU;
    timConfig.PSC   = 8000U;             /* 8000000MHz / 1000Hz = 1F40U -> 1ms tick*/
    timInit(TIM15, &timConfig);

    /**
     * TIM16 is used for 1s interrupt tick.
     */
    RCC_TIM16_CLK_ENABLE();

    timConfig.ARR   = 199U;              /* interrupt should be triggered every sec: 1000 - 1*/
    timConfig.PSC   = 8000U;             /* 8000000MHz / 1000Hz = 8000 -> 1ms tick */
    timConfig.DIER  = TIM_DIER_UIE;     /* enable TIM interrupt update */
    timInit(TIM16, &timConfig);

    NVIC_SetPriority(TIM16_IRQn, 0U);   /* in Cortex M0+ 2 bits are available to set interrupt priority -> priority 0(default) - 3 */
    NVIC_EnableIRQ(TIM16_IRQn);
}

/**
 * @brief system usart initialization
 */
void sysUsartInit(void)
{
    GpioConfig_t gpioConfig   = { 0 };
    UsartConfig_t usartConfig = { 0 };

    /**
     * USART1 initialization for serial transmit to host
     */
    RCC_USART1_CLK_ENABLE();
    RCC_GPIOA_CLK_ENABLE();

    gpioConfig.pin          = GPIO_PIN_9 | GPIO_PIN_10;
    gpioConfig.moder        = GPIO_ALTERNATE_MODE;
    gpioConfig.alternate    = GPIO_AF1;
    gpioConfig.pull         = GPIO_NO_PULL;
    gpioConfig.speed        = GPIO_SPEED_HIGH;
    gpioConfig.type         = GPIO_OUTPUT_PP;
    gpioInit(GPIOA, &gpioConfig);

    usartConfig.BRR     = 0x341U; /* from HAL: (((__PCLK__) + ((__BAUD__)/2U)) / (__BAUD__)) -> (8000000 + (9600 / 2)) / 9600*/
    usartConfig.M1M0    = USART_WORD_LENGTH_8;
    usartConfig.STOP    = USART_STOP_BITS_1;
    usartInit(USART1, &usartConfig);

    NVIC_SetPriority(USART1_IRQn, 0U);   /* in Cortex M0+ 2 bits are available to set interrupt priority -> priority 0(default) - 3 */
    NVIC_EnableIRQ(USART1_IRQn);
}

/**
 * @brief delay in ms.
 *        Therefore g_sysTick is used, which is counting up in SysTick_Handler.
 *        IMPORTANT: This function is not save if device is running longer than 49 days
 *        because g_sysTick will start from zero btw. TIME + DELAY > UINT32_MAX -> Overflow,
 *        value will be very small so g_sysTick < (TIME + DELAY) is immediately false.
 */
void delay(const uint32_t DELAY)
{
    const uint32_t TIME = g_sysTick;

    while (g_sysTick < (TIME + DELAY));
}
