/********************************************************************************
 * @file           : fsm.c
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

/********************************************************************************
 * includes
 ********************************************************************************/
#include "fsm.h"
#include "stddef.h"
#include "error.h"

/********************************************************************************
 * public functions
 ********************************************************************************/
/**
 * @brief fsm core handles the fsm states
 */
FsmState_t* fsmRun(const FsmState_t* stateCurrent, FsmInstanceData_t* data)
{
    ASSERT(NULL != stateCurrent);
    ASSERT(NULL != data);

    FsmState_t* stateNext = (FsmState_t*)stateCurrent->event(data);

    if (stateNext != stateCurrent)
    {
        if (NULL != stateCurrent->onExit)
        {
            stateCurrent->onExit(data);
        }
        if (NULL != stateNext->onEntry)
        {
            stateNext->onEntry(data);
        }
    }

    return stateNext;
}
