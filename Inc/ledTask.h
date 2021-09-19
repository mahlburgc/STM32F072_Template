/********************************************************************************
 * @file           : ledTask.h
 * @author         : Christian Mahlburg
 * @date           : 20.06.2020
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
#ifndef LED_TASK_H_
#define LED_TASK_H_

/********************************************************************************
 * includes
 ********************************************************************************/

/********************************************************************************
 * defines
 ********************************************************************************/
#define LED_RX_BUFFER_SIZE 80

/********************************************************************************
 * public types and variables
 ********************************************************************************/
/* state machine test */
typedef enum
{
    FSM_STATE_ONE,
    FSM_STATE_TWO,
    FSM_STATE_THREE,
    FSM_STATE_FOUR,
    FSM_NUM_STATES,
} FsmState_t;

/********************************************************************************
 * public function prototypes
 ********************************************************************************/
void ledTask(void);
void fsm_interruptTriggered(void);
FsmState_t fsm_getCurrentState(void);

#endif /* LED_TASK_H_ */
