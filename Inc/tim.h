/*
 * tim.h
 *
 *  Created on: 12.06.2020
 *      Author: Christian Mahlburg
 */

#ifndef TIM_H_
#define TIM_H_

#include "stdint.h"
#include "stm32f072xb.h"
#include "misc.h"
#include "error.h"

/**
 * TIM clock enable / disable
 */
#define RCC_TIM15_CLK_ENABLE()     (RCC->APB2ENR |= RCC_APB2ENR_TIM15EN)
#define RCC_TIM15_CLK_DISABLE()    (RCC->APB2ENR &= ~RCC_APB2ENR_TIM15EN)
#define RCC_TIM16_CLK_ENABLE()     (RCC->APB2ENR |= RCC_APB2ENR_TIM16EN)
#define RCC_TIM16_CLK_DISABLE()    (RCC->APB2ENR &= ~RCC_APB2ENR_TIM16EN)

/**
 * @brief timer config
 */
typedef struct
{
    uint32_t ARR;   /* auto reload register */
    uint32_t PSC;   /* prescale value */
    uint32_t DIER;  /* DMA / interrupt enable register */
} TimConfig_t;

/**
 * @brief start timer
 */
static inline void timStart(TIM_TypeDef* TIM)
{
    ASSERT(IS_TIM_INSTANCE(TIM));

    TIM->CR1 |= TIM_CR1_CEN;
}

/**
 * @brief stop timer
 */
static inline void timStop(TIM_TypeDef* TIM)
{
    ASSERT(IS_TIM_INSTANCE(TIM));

    TIM->CR1 &= ~TIM_CR1_CEN;
}

/**
 * @brief resets the timer status and count register
 */
static inline void timReset(TIM_TypeDef* TIM)
{
    ASSERT(IS_TIM_INSTANCE(TIM));

    TIM->SR  = 0U; /* reset status register */
    TIM->CNT = 0U; /* reset count register */
}

/**
 * @brief Check if timer interrupt flag is set.
 */
static inline bool timExceed(TIM_TypeDef* TIM)
{
    ASSERT(IS_TIM_INSTANCE(TIM));

    if (TIM_SR_UIF == (TIM->SR & TIM_SR_UIF))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/* forward declarations */
void timInit(TIM_TypeDef* TIM, const TimConfig_t* timConfig);

#endif /* TIM_H_ */
