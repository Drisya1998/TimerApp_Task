//**************************** appTimer ****************************** 
// Copyright (c) 2021 Trenser 
// All Rights Reserved 
//***************************************************************************** 
// 
// Summary : appTimer header File
// Note : 
//
//*****************************************************************************

#ifndef _APP_TIMER_H_ 
#define _APP_TIMER_H_ 

//******************************* Include Files *******************************

//******************************* Global Types ********************************
typedef unsigned short uint16;
typedef signed char int8;
typedef unsigned char uint8;


//***************************** Global Constants ******************************
#define HOUR_12             12
#define HOUR_24             24
#define MINUTES_60          60
#define TIME_STR_LEN        20
#define DATE_STR_LEN        20
#define AM_PM_SIZE          3
#define SIZE                4
#define TRUE                1
#define FALSE               0
#define ZERO                0
#define GMT_HOURS           5
#define GMT_MINUTES         30
#define PST_HOURS           13
#define PST_MINUTES         30
#define OFFSET              3600

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


//***************************** Global Variables ******************************

//***************************** Function Declaration **************************
bool AppTimerDisplayGMT(uint8 , uint8);
void AppTimerDisplayIST();
bool AppTimerDisplayPST(int , int);
uint8 AppTimerGetMonthValue(uint8[]);

//*********************** Inline Method Implementations ***********************

#endif // _APP_TIMER_H_ 

// EOF 
