/********************************************************************************
 * @file           : fsm.h
 * @author         : Christian Mahlburg
 * @date		   : 10.10.2021
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
#ifndef FSM_H_
#define FSM_H_

/********************************************************************************
 * includes
 ********************************************************************************/
#include "stdint.h"

/********************************************************************************
 * public types and variables
 ********************************************************************************/
typedef struct
{
    uint8_t payload;
} FsmInstanceData_t;

/* function pointer */
/* TODO can not use FsmState_t* as retval because can*t be declared first -> using void pointer here */
typedef void *         FsmEventFunc_t(FsmInstanceData_t* data);
typedef void           FsmOnEntryFunc_t(FsmInstanceData_t* data);
typedef void           FsmOnExitFunc_t(FsmInstanceData_t* data);

typedef struct
{
    FsmEventFunc_t*   const event;
    FsmOnEntryFunc_t* const onEntry;
    FsmOnExitFunc_t*  const onExit;
} FsmState_t;


/********************************************************************************
 * public function prototypes
 ********************************************************************************/
FsmState_t* fsmRun(const FsmState_t* stateCurrent, FsmInstanceData_t* data);

#endif /* FSM_H_ */
