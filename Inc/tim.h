/********************************************************************************
 * @file           : tim.h
 * @author         : Christian Mahlburg
 * @date           : 12.06.2020
 * @brief          :
 *
 ********************************************************************************
 * MIT License
 *
 * Copyright (c) 2020 CMA
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ********************************************************************************/
#ifndef TIM_H_
#define TIM_H_

/********************************************************************************
 * includes
 ********************************************************************************/
#include "stdint.h"
#include "stm32f072xb.h"
#include "misc.h"
#include "error.h"

/********************************************************************************
 * defines
 ********************************************************************************/
/**
 * TIM clock enable / disable
 */
#define RCC_TIM15_CLK_ENABLE()     (RCC->APB2ENR |= RCC_APB2ENR_TIM15EN)
#define RCC_TIM15_CLK_DISABLE()    (RCC->APB2ENR &= ~RCC_APB2ENR_TIM15EN)
#define RCC_TIM16_CLK_ENABLE()     (RCC->APB2ENR |= RCC_APB2ENR_TIM16EN)
#define RCC_TIM16_CLK_DISABLE()    (RCC->APB2ENR &= ~RCC_APB2ENR_TIM16EN)

/********************************************************************************
 * public types and variables
 ********************************************************************************/
/**
 * @brief timer config
 */
typedef struct
{
    uint32_t ARR;   /* auto reload register */
    uint32_t PSC;   /* prescale value */
    uint32_t DIER;  /* DMA / interrupt enable register */
} TimConfig_t;

/********************************************************************************
 * public function prototypes
 ********************************************************************************/
void timInit(TIM_TypeDef* TIM, const TimConfig_t* timConfig);

/********************************************************************************
 * inline functions
 ********************************************************************************/
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

#endif /* TIM_H_ */
