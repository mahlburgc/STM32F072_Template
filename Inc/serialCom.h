/*
 * serialCom.h
 *
 *  Created on: 23.06.2020
 *      Author: cma
 */

#ifndef SERIAL_COM_H_
#define SERIAL_COM_H_

#include "stdint.h"
#include "misc.h"

#define RX_BUFFER_SIZE 1

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

void serialComTask(void);

#endif /* SERIAL_COM_H_ */
