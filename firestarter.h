/**
 *******************************************************************************
 ** Created by Manuel Schreiner
 **
 ** Copyright © 2021 Manuel Schreiner. All rights reserved.
 **
 ** 1. Redistributions of source code must retain the above copyright notice,
 **    this condition and the following disclaimer.
 **
 ** This software is provided by the copyright holder and contributors "AS IS"
 ** and any warranties related to this software are DISCLAIMED.
 ** The copyright owner or contributors be NOT LIABLE for any damages caused
 ** by use of this software.

 *******************************************************************************
 */

/**
 *******************************************************************************
 **\file firestarter.cpp
 **
 ** Fire Starter
 ** A detailed description is available at
 ** @link FireStarterGroup file description @endlink
 **
 ** History:
 ** - 2021-12-5  1.00  Manuel Schreiner
 *******************************************************************************
 */

#if !defined(__FIRESTARTER_H__)
#define __FIRESTARTER_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup FireStarterGroup Fire Starter
 **
 ** Provided functions of FireStarter:
 **
 **
 *******************************************************************************
 */

//@{

/**
 *******************************************************************************
** \page firestarter_module_includes Required includes in main application
** \brief Following includes are required
** @code
** #include "firestarter.h"
** @endcode
**
 *******************************************************************************
 */

/**
 *******************************************************************************
 ** (Global) Include files
 *******************************************************************************
 */

/**
 *******************************************************************************
 ** Global pre-processor symbols/macros ('#define') 
 *******************************************************************************
 */

/**
 *******************************************************************************
 ** Global type definitions ('typedef') 
 *******************************************************************************
 */


/**
 *******************************************************************************
 ** Global variable declarations ('extern', definition in C source)
 *******************************************************************************
 */

/**
 *******************************************************************************
 ** Global function prototypes ('extern', definition in C source) 
 *******************************************************************************
 */


int FireStarter_Init(void);
int FireStarter_Deinit(void);
void FireStarter_SetAdvent(uint8_t newIndex, bool newSimulate);
void FireStarter_Update(void);

//@} // FireStarterGroup

#ifdef __cplusplus
}
#endif

#endif /* __FIRESTARTER_H__ */

/**
 *******************************************************************************
 ** EOF (not truncated)
 *******************************************************************************
 */
