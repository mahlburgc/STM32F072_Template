/*
 * main.h
 *
 *  Created on: Jun 6, 2020
 *      Author: Christian
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "stdint.h"

/**
 * Wait for number of ticks
 */
static inline void delay(uint32_t ticks)
{
    for(uint32_t i = 0;  i < ticks; i++);
}

#endif /* MAIN_H_ */
