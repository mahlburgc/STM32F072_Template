/********************************************************************************
 * @file           : error.h
 * @author         : Christian Mahlburg
 * @date           : 24.06.2020
 * @brief          : This module contains the typedef of the global err struct with all available errors.
 *
 * The initialization is placed in error.c.
 * This module also provides functions to handle errors and assertions.
 *
 * To handle an assertion use e.g.
 *  ASSERT(a < b);
 *
 * To handle occured errors use e.g.
 *  ERROR(g_err.USART1_BUFFER_OVERFLOW)
 *
 * All valid errors must be added to Err_t typedef and to global error list g_err (error.c).
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
#ifndef ERROR_H_
#define ERROR_H_

/********************************************************************************
 * includes
 ********************************************************************************/
#include "stdint.h"
#include "debug.h"
#include "cmsis_gcc.h"

/********************************************************************************
 * public types and variables
 ********************************************************************************/
/**
 * @brief Enum contains all available errors.
 */
typedef enum
{
    ERR_OK,
    ERR_USART1_BUFFER_OVERFLOW,
    /* do not use as error */
    NUM_OF_ERRORS,
} Err_t;

typedef enum
{
    ERR_SEV_LOW,
    ERR_SEV_MID,
    ERR_SEV_HIGH
} ErrSeverity_t;

/**
 * @brief Definition of an error type with id, severity level and error message.
 */
typedef struct
{
    uint32_t id;
    ErrSeverity_t severity;
    const char* const msg;
} ErrType_t;

/********************************************************************************
 * function prototypes
 ********************************************************************************/
void assertFailed(uint8_t* file, uint32_t line);
void errHandler(Err_t err, uint8_t* file, uint32_t line);

/********************************************************************************
 * user macros
 ********************************************************************************/
/**
 * @brief ERROR
 *        This define calls the error handler with file and line where error occures.
 *        This define can be used by user to call error handler with an occured error,
 *        e.g. ERROR(ERR_USART1_BUFFER_OVERFLOW)
 */
#define ERROR(x) (errHandler(x, (uint8_t*)__FILE__, __LINE__))

/**
 * @brief Use assertions during development process for logical / programming errors.
 */
#ifdef DEBUG
#define ASSERT(x) ((x) ? (void)0U : assertFailed((uint8_t*)__FILE__, __LINE__))
#else
#define ASSERT(x) ((void)0U)
#endif


#endif /* ERROR_H_ */
