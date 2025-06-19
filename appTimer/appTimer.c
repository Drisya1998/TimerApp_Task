//*******************************appTimer**************************************
//Copyright (c) 2025 Trenser Technology Solutions
//All Rights Reserved
//*****************************************************************************
//
//File     : appTimer.c
//Summary  : Implementations for calculating and displaying time in GMT, PST 
//           and IST
//Note     : None
//Author   : Drisya P
//Date     : 18/Jun/2025
//
//*****************************************************************************

//*********************Include Files*******************************************
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "appTimer.h"
#include "common.h"

//*********************Local Types*********************************************

//*********************Local Constants*****************************************

//*********************Local Variables*****************************************

//*********************Local Functions*****************************************

//*********************.AppTimerGetMonthValue.*********************************
//Purpose : Get corresponding Month Value from month string 
//Inputs  : string Month like Jun
//Outputs : MonthValue
//Return  : MonthValue
//Notes   : None 
//*****************************************************************************
bool AppTimerGetMonthValue(uint8* pucmonth, uint8* pucMonthValue)
{
    bool blflag=FALSE;
    static const uint8* const pucmonth_names[] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    if(pucmonth != NULL )
    {
        for (int i = 0; i < 12; ++i) {
            if (strcmp((const char*)pucmonth, (char*)pucmonth_names[i]) == 0) {
                *pucMonthValue =i+1;
            }
        }
        blflag = TRUE;
    }
    
    return blflag;
}

//*********************.AppTimerConvertToHourFormat.*********************************
//Purpose : Convert the 24 Hour format to 12 Hour Format and set AM/PM 
//Inputs  : 24 format Hour and AmPm Array that stores "AM" or "PM"
//Outputs : None
//Return  : None
//Notes   : None 
//*****************************************************************************
void AppTimerConvertToHourFormat(uint8* pucHour, uint8* pucAmPm)
{
    // Convert to 12-hour format and set AM/PM
    if (*pucHour == ZERO) 
    {
        *pucHour = HOUR_12;
        strcpy((char*)pucAmPm, AM);
    }
    else if (*pucHour < HOUR_12)
    {
        strcpy((char*)pucAmPm, AM);
    }
    else if (*pucHour == HOUR_12) 
    {
        strcpy((char*)pucAmPm, PM);
    } 
    else 
    {
        *pucHour -= HOUR_12;
        strcpy((char*)pucAmPm, PM);
    }

    return;
}

//*********************.AppTimerPrintToConsole.*********************************
//Purpose : Print to Console int the format given in requirement 
//Inputs  : Zone- GMT or IST or PST
//Outputs : None
//Return  : None
//Notes   : None 
//*****************************************************************************
void AppTimerPrintToConsole(uint8* pzone, uint8* pucTimePart, uint8* pucDate,
                             time_t llEpochTime)
{
    if(strcmp((char*)pzone,GMT) == ZERO)
    {
        printf("\n\n\nUTC (0:00)\n-----------------\n");
        printf("Time: %s\n", pucTimePart);
        printf("Date: %s\n", pucDate);
        printf("epoch:%lld\n", llEpochTime);
        printf("\n\n");
    }
    else if(strcmp((char*)pzone,IST)==ZERO)
    {
        printf("IST (5:30)\n-----------------\n");
        printf("Time: %s\n", pucTimePart);
        printf("Date: %s\n", pucDate);
        printf("\n\n");
    }
    else
    {
        printf("PST (-8:00)\n-----------------\n");
        printf("Time: %s\n", pucTimePart);
        printf("Date: %s\n", pucDate);
        printf("\n\n");
    }

    return;
}

//*********************.AppTimerDisplay.************************************
//Purpose : print GMT , IST  and PST zone time,date
//Inputs  : uint8* string represents GMT , IST  or PST ,
//          uint8 GmtHours or IstHours or PstHours  , 
//          uint8 GmtMinutes or IstMinutes or PstMinutes
//Outputs : None
//Return  : Exit status succes or Failure
//Notes   : None 
//*****************************************************************************
bool AppTimerDisplay(uint8* pzone, uint8 ucOffsetHours, uint8 ucOffsetMinutes)
{
    bool blflag = FALSE;
    bool blreturnflag = FALSE;
    uint8 pucDate[DATE_STR_LEN] = {0}; 
    uint8 pucTimePart[TIME_STR_LEN] = {0};
    uint8 pucAmPm[AM_PM_SIZE] = {0};
    uint8 pucMonth[MONTH_SIZE] = {0};
    time_t llcurrentTime = time(NULL);
    time_t llEpochTime = time(NULL);
    time_t lladjustTime = time(NULL);
    TIMER sttimer = {0,0,0,0,0,0};

    uint8 *ptimeStr = NULL;

    //To Avoid Static Analysis Violations
    (void)lladjustTime;
    (void*)pucDate;
    (void*)pucTimePart;
    (void*)pucAmPm;
    (void*)pucMonth;

    if((ucOffsetHours <= HOUR_24) && (ucOffsetMinutes <= MINUTES_60))
    {
        // get current time
        time(&llcurrentTime);
        lladjustTime = llcurrentTime -  \
            ((ucOffsetHours * SECONDS_HOUR) + (ucOffsetMinutes * MINUTES_60));

        ptimeStr =(uint8*) ctime(&lladjustTime);

        sscanf((char*)ptimeStr+MONTH_SIZE, "%3s %hhu %hhu:%hhu:%hhu %hu", \
                    pucMonth, &sttimer.ucDay, &sttimer.ucHour, \
                    &sttimer.ucMin, &sttimer.ucSec, &sttimer.unYear);

        AppTimerConvertToHourFormat(&sttimer.ucHour , pucAmPm);

        sprintf((char*)pucTimePart,"%02d:%02d:%02d %s" , \
                        sttimer.ucHour,sttimer.ucMin,sttimer.ucSec,pucAmPm); 

        blreturnflag = AppTimerGetMonthValue(pucMonth , &sttimer.ucMonthValue);
        
        if(blreturnflag != FALSE){
            sprintf((char*)pucDate, "%02d/%02d/%d", \
                    sttimer.ucDay, sttimer.ucMonthValue, sttimer.unYear);
        }
        //Print Result according to GMT , IST , Or PST
        AppTimerPrintToConsole(pzone, pucTimePart, pucDate, llEpochTime);
        blflag=TRUE;
    }
    
    return blflag;
}

//EOF