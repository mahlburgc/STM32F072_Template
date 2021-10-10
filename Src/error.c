/********************************************************************************
 * @file           : error.c
 * @author         : Christian Mahlburg
 * @date           : 26.06.2020
 * @brief          : This file contains the definition of all system errors.
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
#include "Error.h"

/********************************************************************************
 * foreward declarations
 ********************************************************************************/
void sevHandler(Err_t err);

/********************************************************************************
 * public variables
 ********************************************************************************/
/**
 * @brief error list
 *        This list contains the definition of all errors.
 */
ErrType_t errTable[NUM_OF_ERRORS] =
{
    [ERR_OK]                     = { 0x00, ERR_SEV_LOW,  "NO ERROR"                      },
    [ERR_USART1_BUFFER_OVERFLOW] = { 0x10, ERR_SEV_HIGH, "USART1 BUFFER OVERFLOW"        }, /* severity high,error messages may not be send anymore */
    [ERR_USART1_FRAMIG_OR_NOISE] = { 0x11, ERR_SEV_HIGH, "USART1 FRAMING OR NOISE ERROR" }, /* severity high,error messages may not be send anymore */
};

/********************************************************************************
 * private functions
 ********************************************************************************/
/**
 * @brief Handle the error severity.
 */
void sevHandler(Err_t err)
{
    switch (errTable[err].severity)
    {
    case ERR_SEV_LOW:
        break;

    case ERR_SEV_MID:
        break;

    case ERR_SEV_HIGH:
        __disable_irq();
        while (1)
        {
            __BKPT(0xBE); /* dead end, device may not run as intended, e.g. error messages are not shown on terminal */
        }
        break;
    }
}

/********************************************************************************
 * public functions
 ********************************************************************************/
/**
 * @brief error handler, this handler can be called with ERROR(x) macro to reduce argument list.
 */
void errHandler(Err_t err, uint8_t* file, uint32_t line)
{
    ASSERT(0U != errTable[err].msg);

    if (ERR_OK != err)
    {
        sevHandler(err);
        printArg("[ERROR 0x%2X]\t \"%s\" in file %s, line %d\r\n", errTable[err].id, errTable[err].msg, file, line);
    }
}

/**
 * @brief If an assertion fails, file and line is transmitted to debug usart
 *        and program is halted.
 */
void assertFailed(uint8_t* file, uint32_t line)
{
    __disable_irq();
    while (1)
    {
        __BKPT(0xBE); /* value 0xBE is ignored */
    }
}
