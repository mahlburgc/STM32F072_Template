/*
 * error.h
 *
 *  Created on: 24.06.2020
 *      Author: cma
 *
 *      This module contains the typedef of the global err struct with all available errors.
 *      The initialization is placed in error.c.
 *      This module also provides functions to handle errors and assertions.
 *
 *      To handle an assertion use e.g.
 *          ASSERT(a < b);
 *
 *      To handle occured errors use e.g.
 *          ERROR(g_err.USART1_BUFFER_OVERFLOW)
 *
 *       All valid errors must be added to Err_t typedef and to global error list g_err (error.c).
 */

#ifndef ERROR_H_
#define ERROR_H_

#include "stdint.h"
#include "debug.h"
#include "cmsis_gcc.h"

/**
 * @brief ERROR
 *        This define calls the error handler with file and line where error occures.
 *        This define can be used by user to call error handler with an occured error,
 *        e.g. ERROR(ERR_USART1_BUFFER_OVERFLOW)
 */
#define ERROR(x) (errorHandler(x, (uint8_t*)__FILE__, __LINE__))

/**
 * @brief Use assertions during development process for logical / programming errors.
 */
#ifdef DEBUG
#define ASSERT(x) ((x) ? (void)0U : assertFailed((uint8_t*)__FILE__, __LINE__))
#else
#define ASSERT(x) ((void)0U)
#endif

/**
 * @brief Definition of an error type with id an error message.
 */
typedef struct
{
    uint32_t id;
    const char* const msg;
} ErrType_t;

/**
 * @brief Error struct containing all available errors.
 *        Struct initialization is done in error.c.
 */
typedef struct
{
    const ErrType_t ERR_OK;
    const ErrType_t ERR_USART1_BUFFER_OVERFLOW;
} Err_t;

/**
 * @brief global error list with all available errors.
 */
extern Err_t g_err;

/**
 * @brief If an assertion fails, file and line is transmitted to debug usart
 *        and program is halted.
 */
#ifdef DEBUG
static inline void assertFailed(uint8_t* file, uint32_t line)
{
    printArg("ASSERT: file %s on line %d\r\n", file, line);
    __BKPT(0xBE); /* value 0xBE is ignored */
}
#endif

/**
 * @brief error handler, this handler can be called with ERROR(x) macro to reduce argument list.
 */
static inline void errorHandler(ErrType_t err, uint8_t* file, uint32_t line)
{
    ASSERT(0U != err.msg);

    if (err.id != g_err.ERR_OK.id)
    {
        printArg("[ERROR 0x%2X]\t \"%s\" in file %s, line %d\r\n", err.id, err.msg, file, line);
    }
}


#endif /* ERROR_H_ */
