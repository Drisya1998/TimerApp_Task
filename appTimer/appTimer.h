//**************************** appTimer ****************************** 
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved 
//***************************************************************************** 
// 
// Summary : appTimer header File
// Note    : Added Macros and function Declaraions
//
//*****************************************************************************

#ifndef _APP_TIMER_H_ 
#define _APP_TIMER_H_ 

//******************************* Include Files *******************************
#include "common.h"

//******************************* Global Types ********************************

//***************************** Global Constants ******************************
#define HOUR_12             12
#define HOUR_24             24
#define MINUTES_60          60
#define TIME_STR_LEN        20
#define DATE_STR_LEN        20
#define AM_PM_SIZE          3
#define MONTH_SIZE          4
#define TRUE                1
#define FALSE               0
#define ZERO                0
#define GMT_HOURS           5
#define GMT_MINUTES         30
#define PST_HOURS           12
#define PST_MINUTES         30
#define IST_HOURS           0
#define IST_MINUTES         0
#define SECONDS_HOUR        3600
#define AM                  "AM"
#define PM                  "PM"

typedef enum { 
    MONTH_JAN=1, 
    MONTH_FEB,
    MONTH_MAR,
    MONTH_APR, 
    MONTH_MAY,
    MONTH_JUN,
    MONTH_JUL, 
    MONTH_AUG,
    MONTH_SEP,
    MONTH_OCT, 
    MONTH_NOV,
    MONTH_DEC, 
} MONTH;

typedef struct _TIMER_
{
    uint8 ucHour;
    uint8 ucMin;
    uint8 ucSec;
    uint8 ucDay;
    uint8 ucMonthValue;
    uint16 unYear;
}TIMER;

//***************************** Global Variables ******************************

//***************************** Function Declaration **************************
uint8 AppTimerGetMonthValue(uint8*);
bool AppTimerDisplay(uint8*, uint8, uint8);

//*********************** Inline Method Implementations ***********************

#endif // _APP_TIMER_H_ 

// EOF 
