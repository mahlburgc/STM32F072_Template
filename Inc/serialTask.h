/********************************************************************************
 * @file           : serialTask.h
 * @author         : Christian Mahlburg
 * @date           : 23.06.2020
 * @brief          :
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
#ifndef SERIAL_TASK_H_
#define SERIAL_TASK_H_

/********************************************************************************
 * includes
 ********************************************************************************/
#include "stdint.h"
#include "misc.h"

/********************************************************************************
 * defines
 ********************************************************************************/
#define RX_BUFFER_SIZE 1

/********************************************************************************
 * public types and variables
 ********************************************************************************/
/**
 * @brief USART rxBuffer type for interrupt reception
 */
typedef struct
{
    uint8_t data[RX_BUFFER_SIZE];
    uint32_t index;
} RxBuffer_t;

/**
 * @breif USART rxMsg type for received message
 */
typedef struct
{
    uint8_t data[RX_BUFFER_SIZE];
    bool rxComplete;
} RxMsg_t;

/********************************************************************************
 * public function prototypes
 ********************************************************************************/
void serialComTask(void);

#endif /* SERIAL_TASK_H_ */
