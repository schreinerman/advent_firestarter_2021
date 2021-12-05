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

#define __FIRESTARTER_CPP__

/**
 *******************************************************************************
 ** Include files
 *******************************************************************************
 */


#include <string.h> //required also for memset, memcpy, etc.
#include <stdint.h>
#include <stdbool.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>
#include "firestarter.h"
#include "appconfig.h"


/**
 *******************************************************************************
 ** Local pre-processor symbols/macros ('#define') 
 *******************************************************************************
 */

/**
 *******************************************************************************
 ** Global variable definitions (declared in header file with 'extern') 
 *******************************************************************************
 */

/**
 *******************************************************************************
 ** Local type definitions ('typedef') 
 *******************************************************************************
 */

/**
 *******************************************************************************
 ** Local variable definitions ('static') 
 *******************************************************************************
 */

static Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
static volatile uint32_t u32PosIst = 0;
static volatile uint32_t u32PosSoll = 0;
static uint8_t u8IndexKerze = 0;
static uint8_t u8Advent = 0;
static bool simulate = false;
/**
 *******************************************************************************
 ** Local function prototypes ('static') 
 *******************************************************************************
 */

/**
 *******************************************************************************
 ** Function implementation - global ('extern') and local ('static') 
 *******************************************************************************
 */

void fire(void)
{
  delay(100);
  if (simulate)
  {
    pwm.writeMicroseconds(0, 1100);
  }
  else
  {
    pwm.writeMicroseconds(0, 2200);
  }
  delay(3000);
  pwm.writeMicroseconds(0, 1000);
  delay(1000);
}

void FireStarter_SetAdvent(uint8_t newIndex, bool newSimulate)
{
    u8Advent = newIndex;
    u8IndexKerze = 0;
    u32PosSoll = AppConfig_GetPosKerze1();
    simulate = newSimulate;
}

int FireStarter_Init(void)
{
  Wire.begin(18, 23);
  pwm.begin(); 

  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);  // Analog servos run at ~50 Hz updates

  delay(10);

  u32PosIst = AppConfig_GetPosStart();
  u32PosSoll = u32PosIst;
  pwm.writeMicroseconds(1, u32PosSoll);
  pwm.writeMicroseconds(0, 1000);
}

void endPositionReached(void)
{
    if (u8Advent == 0)
    {
       return;
    }
    u8IndexKerze++;
    fire();
    if (u8IndexKerze < u8Advent)
    {
        switch(u8IndexKerze)
        {
            case 1:
                u32PosSoll = AppConfig_GetPosKerze2();
                break;
            case 2:
                u32PosSoll = AppConfig_GetPosKerze3();
                break;
            case 3:
                u32PosSoll = AppConfig_GetPosKerze4();
                break;
        }
    } else
    {
        u8IndexKerze = 0;
        u8Advent = 0;
        u32PosSoll = AppConfig_GetPosStart();
    }
}

void FireStarter_Update(void)
{
    static uint32_t u32LastUpdate = 0;
    bool bUpdated = false;
    bool bEndReached = false;
    if (u32LastUpdate == 0)
    {
        u32LastUpdate = millis();
    }
    if ((millis() - u32LastUpdate) > 50)
    {
        u32LastUpdate = millis();
        if (u32PosSoll > u32PosIst)
        {
            u32PosIst += 50;
            if (u32PosSoll <= u32PosIst)
            {
               u32PosIst = u32PosSoll;
               bEndReached = true;
            }
            bUpdated = true;
        } else if (u32PosSoll < u32PosIst)
        {
            u32PosIst -= 50;
            if (u32PosSoll >= u32PosIst)
            {
               u32PosIst = u32PosSoll;
               bEndReached = true;
            }
            bUpdated = true;
        }
        if (bUpdated)
        {
           pwm.writeMicroseconds(1, u32PosIst);
        }
        if (bEndReached)
        {
           delay(100);
           endPositionReached();
        }
    }
}


/**
 *******************************************************************************
 ** EOF (not truncated)
 *******************************************************************************
 */
