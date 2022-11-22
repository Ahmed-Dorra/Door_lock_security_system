/******************************************************************************
 *
 * Module: Common - Platform Types Abstraction
 *
 * File Name: std_types.h
 *
 * Description: types for AVR
 *
 * Author: Ahmed_Dorra
 *
 *******************************************************************************/

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

typedef unsigned long 			uint32;
typedef unsigned short 			uint16;
typedef unsigned char	 		uint8;
typedef signed long 			sint32;
typedef signed short 			sint16;
typedef signed char 			sint8;
typedef float 					float32;
typedef double			 		float64;

#define LOGIC_HIGH	(1u)
#define LOGIC_LOW	(0u)
#define NULL_PTR	((void*)0)

#ifndef FALSE
#define FALSE		(0u)
#endif

#ifndef TRUE
#define TRUE		(1u)
#endif


#endif /* STD_TYPES_H_ */
