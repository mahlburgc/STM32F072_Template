/********************************************************************************
 * @file           : serialCom.c
 * @author         : Christian Mahlburg
 * @date           : 23.06.2020
 * @brief          : This file contains the serial communication task.
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
#include "serialTask.h"
#include "usart.h"
#include "debug.h"

/********************************************************************************
 * public variables
 ********************************************************************************/
RxMsg_t g_rxMsg = { 0 };

/********************************************************************************
 * public functions
 ********************************************************************************/
/**
 * @brief This task manages the serial communication
 */
void serialComTask(void)
{
    /* check for incoming message */
    if (true == g_rxMsg.rxComplete)
    {
        g_rxMsg.rxComplete = false;
        printArg("RX: %s\r\n", (char*)g_rxMsg.data);
    }
}
