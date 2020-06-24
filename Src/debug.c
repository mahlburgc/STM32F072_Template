/*
 * debug.c
 *
 *  Created on: 11.07.2020
 *      Author: Christian
 */


#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "misc.h"
#include "debug.h"
#include "usart.h"

#define MAX_DBG_SIZE    80  /* max debug message size */
#define DBG_USART       USART1


/**
 * @brief print debug message to debug usart
 */
void print(const char* dbgMsg)
{
    ASSERT(0U != dbgMsg);

    usartTransmit(DBG_USART, strnlen(dbgMsg, MAX_DBG_SIZE), (uint8_t*)dbgMsg);
}

/**
 * @brief print debug message with additional argument list to debug usart
 *        Important: on MCUs with no floating point unit, printf ( and related print functions) with floating point support can be enabled
 *        using "-u _print_float" under MCU Settings (CubeIDE Project Properties->C/C++ Build->Settings->Tool Settings->MCU Settings).
 *        IMPORTANT: This needs much more space than not using floating point print functions on ROM (see build analyzer).
 *        Remember that using floating points on MCUs without hardware FPU is resource intensive and should be avoided.
 */
void printArg(char* format,...)
{
    ASSERT(0U != format);

    char buffer[MAX_DBG_SIZE] = { 0 };
    va_list argptr;

    va_start(argptr, format);
    vsnprintf(buffer, MAX_DBG_SIZE, format, argptr);

    usartTransmit(DBG_USART, strnlen(buffer, MAX_DBG_SIZE), (uint8_t*)buffer);
    va_end(argptr);
}
