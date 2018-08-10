/*
 * GUI_Types.h
 *
 *  Created on: 2018年5月4日
 *      Author: Administrator
 */

#ifndef _GUI_TYPES_H_
#define _GUI_TYPES_H_

#define I8    	signed char
#define U8  	unsigned char     	/* unsigned 8  bits. */
#define I16   	signed short    	/*   signed 16 bits. */
#define U16 	unsigned short    	/* unsigned 16 bits. */
#define I32   	signed int   		/*   signed 32 bits. */
#define U32 	unsigned int   		/* unsigned 32 bits. */
#define I16P 	I16              	/*   signed 16 bits OR MORE ! */
#define U16P 	U16              	/* unsigned 16 bits OR MORE ! */

#ifndef bool
#define bool	U8
#endif

#ifndef true
#define true	1
#endif

#ifndef false
#define false	0
#endif

#ifndef NULL
#define NULL (void *)0
#endif


#endif /* _GUI_TYPES_H_ */
