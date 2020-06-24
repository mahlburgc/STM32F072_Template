/*
 * serialCom.c
 *
 *  Created on: 23.06.2020
 *      Author: cma
 */

#include "serialCom.h"
#include "usart.h"
#include "debug.h"

RxMsg_t g_rxMsg = { 0 };

/**
 * @brief This task manages the serial communication
 */
void serialComTask(void)
{
    /* check for incoming message */
    if (true == g_rxMsg.rxComplete)
    {
        g_rxMsg.rxComplete = false;
        printArg((char*)g_rxMsg.data);
    }
}

