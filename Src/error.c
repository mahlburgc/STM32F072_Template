/*
 * error.c
 *
 *  Created on: Jun 26, 2020
 *      Author: cma
 *
 *      This file contains the definition of the global error list.
 */


#include "Error.h"

/**
 * @brief global error list
 *        This list contains all global errors.
 */
Err_t g_err =
{
    .ERR_OK                     = { 0x00, "NO ERROR" },
    .ERR_USART1_BUFFER_OVERFLOW = { 0x10, "USART1 BUFFER OVERFLOW" },
};






