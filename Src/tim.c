/********************************************************************************
 * @file           : tim.c
 * @author         : Christian Mahlburg
 * @date           : 12.06.2020
 * @brief          : This file contains timer related functions.
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

/********************************************************************************
 * includes
 ********************************************************************************/
#include "tim.h"
#include "error.h"

/********************************************************************************
 * public functions
 ********************************************************************************/
/**
 * @brief timer initialization
 */
void timInit(TIM_TypeDef* TIM, const TimConfig_t* timConfig)
{
    ASSERT(IS_TIM_INSTANCE(TIM));
    ASSERT(0U != timConfig);

    TIM->SR   = 0U;                  /* clear status register */
    TIM->ARR  = timConfig->ARR;      /* set auto-reload register */
    TIM->PSC  = timConfig->PSC;      /* set prescale register */
    TIM->DIER = timConfig->DIER;     /* set DMA/interrupt enable register */
}
