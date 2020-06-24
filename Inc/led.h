/*
 * led.h
 *
 *  Created on: 20.06.2020
 *      Author: Christian
 */

#ifndef LED_H_
#define LED_H_

#define LED_RX_BUFFER_SIZE 80

typedef enum
{
    LED_STATE_FIRST,
    LED_STATE_TWO,
    LED_STATE_THREE,
    LED_STATE_LAST,
} FsmLedState_t;

void ledTask(void);

#endif /* LED_H_ */
