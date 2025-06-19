//**************************** appTimer *************************************** 
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved 
//***************************************************************************** 
// 
// Summary : appTimer header File - Added Macros and function Declaraions of 
//           AppTimerDisplay,ApptimerGetMonthValue,AppTimerConvertToHourFormat,
//           AppTimerPrintToConsole
// Note    :
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
#define ONE                 1
#define GMT_HOURS           5
#define GMT_MINUTES         30
#define PST_HOURS           12
#define PST_MINUTES         30
#define IST_HOURS           0
#define IST_MINUTES         0
#define SECONDS_HOUR        3600
#define AM                  "AM"
#define PM                  "PM"
#define NUMBER_MONTHS       12
#define JAN                 "Jan"
#define FEB                 "Feb"
#define MAR                 "Mar"
#define APR                 "Apr"
#define MAY                 "May"
#define JUN                 "Jun"
#define JUL                 "Jul"
#define AUG                 "Aug"
#define SEP                 "Sep"
#define OCT                 "Oct"
#define NOV                 "Nov"
#define DEC                 "Dec"

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
bool AppTimerGetMonthValue(uint8*, uint8*);
bool AppTimerDisplay(uint8*, uint8, uint8);
void AppTimerConvertToHourFormat(uint8*, uint8*);
void AppTimerPrintToConsole(uint8*, uint8*, uint8* , time_t);
//*********************** Inline Method Implementations ***********************

#endif // _APP_TIMER_H_ 

// EOF 
