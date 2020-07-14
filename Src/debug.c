/********************************************************************************
 * @file           : debug.c
 * @author         : Christian Mahlburg
 * @date           : 11.07.2020
 * @brief          : This file contains helper functions for debugging purposes.
 *
 ********************************************************************************
 * MIT License
 *
 * Copyright (c) 2020 Christian Mahlburg
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
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "misc.h"
#include "debug.h"
#include "usart.h"

/********************************************************************************
 * defines
 ********************************************************************************/
#define MAX_DBG_SIZE    80  /* max debug message size */
#define DBG_USART       USART1

/********************************************************************************
 * public functions
 ********************************************************************************/
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
