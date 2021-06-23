/********************************************************************************
 * @file           : i2c.c
 * @author         : Christian Mahlburg
 * @date		   : 23.06.2021
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
#include "i2c.h"
/********************************************************************************
 * defines
 ********************************************************************************/

/********************************************************************************
 * static variables
 ********************************************************************************/

/********************************************************************************
 * static function prototypes
 ********************************************************************************/

/********************************************************************************
 * public variables
 ********************************************************************************/

/********************************************************************************
 * static functions
 ********************************************************************************/

/********************************************************************************
 * public functions
 ********************************************************************************/
/**
 * @brief basic i2c configuration
 */
void i2cInit(I2C_TypeDef* i2c, const I2cConfig_t* conf)
{
    i2c->CR2     |= conf->addressingMode;
    i2c->TIMINGR  = conf->timing & TIMING_CLEAR_MASK;
}
