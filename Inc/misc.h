/*
 * msic.h
 *
 *  Created on: 12.06.2020
 *      Author: Christian Mahlburg
 *
 *      This file contain miscelleanous functions and definitions.
 */

#ifndef MISC_H_
#define MISC_H_

/**
 * @brief calcucalte array length
 */
#define ARRAY_LEN(x) (sizeof(x)/sizeof(x[0]))

/**
 * @brief bool typedef
 */
typedef enum
{
    false = 0,
    true = 1,
} bool;

#endif /* MISC_H_ */
