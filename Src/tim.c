/*
 * tim.c
 *
 *  Created on: 12.06.2020
 *      Author: Christian Mahlburg
 */

#include "tim.h"

/**
 * @brief timer initialization
 */
void timInit(TIM_TypeDef* TIM, const TimConfig_t* timConfig)
{
    TIM->SR   = 0U;                  /* clear status register */
    TIM->ARR  = timConfig->ARR;      /* set auto-reload register */
    TIM->PSC  = timConfig->PSC;      /* set prescale register */
    TIM->DIER = timConfig->DIER;     /* set DMA/interrupt enable register */
}