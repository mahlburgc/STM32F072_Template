/*
 * debug.h
 *
 *  Created on: 22.06.2020
 *      Author: Christian
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include "usart.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "misc.h"

#define MAX_DBG_SIZE    80  /* max debug message size */

/**
 * @brief print debug message to usart 1
 */
static inline void print(const char* dbgMsg)
{
    usartTransmit(USART1, strnlen(dbgMsg, MAX_DBG_SIZE), (uint8_t*)dbgMsg);
}

/**
 * @brief print debug message with additional argument list to usart 1
 *        Important: on MCUs with no floating point unit, printf ( and related print functions) with floating point support can be enabled
 *        using "-u _print_float" under MCU Settings (CubeIDE Project Properties->C/C++ Build->Settings->Tool Settings->MCU Settings).
 *        IMPORTANT: This needs much more space than not using floating point print functions on ROM (see build analyzer).
 *        Remember that using floating points on MCUs without hardware FPU is resource intensive and should be avoided.
 */
static inline void printArg(char* format,...)
{
    char buffer[MAX_DBG_SIZE] = { 0 };
    va_list argptr;

    va_start(argptr, format);
    vsnprintf(buffer, MAX_DBG_SIZE, format, argptr);

    usartTransmit(USART1, strnlen(buffer, MAX_DBG_SIZE), (uint8_t*)buffer);
    va_end(argptr);
}

#endif /* DEBUG_H_ */
