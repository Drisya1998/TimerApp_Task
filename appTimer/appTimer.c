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
static const int8* const pucMonthNames[NUMBER_MONTHS] = 
        {
            (const int8*)JAN, (const int8*)FEB, (const int8*)MAR, 
            (const int8*)APR,(const int8*)MAY, (const int8*)JUN, 
            (const int8*)JUL, (const int8*)AUG,(const int8*)SEP, 
            (const int8*)OCT, (const int8*)NOV, (const int8*)DEC
        };

//*********************Local Variables*****************************************

//*********************Local Functions*****************************************
static bool AppTimerGetMonthValue(uint8*, uint8*);
static bool AppTimerConvertToHourFormat(uint8*, uint8*);
static bool AppTimerPrintToConsole(uint8*, uint8*, uint8*, time_t);

//*********************.AppTimerGetMonthValue.*********************************
//Purpose : Get corresponding Month Value from month string 
//Inputs  : Month - Month in string like Jun 
//          pucMonthValue - address of variable ucMonthValue
//Outputs : Update MonthValue corresponds to the string Month
//Return  : TRUE - exit status success
//          FALSE - Failure
//Notes   : None 
//*****************************************************************************
static bool AppTimerGetMonthValue(uint8* pucMonth, uint8* pucMonthValue)
{
    bool blFlag = FALSE;
    uint8 ucIndex = 0;

    if((pucMonth != NULL) && (pucMonthValue != NULL))
    {
        for(ucIndex = 0; ucIndex < NUMBER_MONTHS; ++ucIndex)
        {
            if(strcmp((const char*)pucMonth, 
                        (char*)pucMonthNames[ucIndex]) == OK)
            {
                *pucMonthValue = ++ucIndex;
            }
        }
        blFlag = TRUE;
    }

    return blFlag;
}

//*********************.AppTimerConvertToHourFormat.***************************
//Purpose : Convert the 24 Hour format to 12 Hour Format and set AM/PM 
//Inputs  : pucHour - address of 24 format Hour
//          pucAmPm - AmPm Array that stores "AM" or "PM"
//Outputs : pucHour - Hour Update in 12-Hour Format, 
//          pucAmPm - ampm array update with "AM" or "PM"
//Return  : TRUE - exit status success
//          FALSE - Failure
//Notes   : None 
//*****************************************************************************
static bool AppTimerConvertToHourFormat(uint8* pucHour, uint8* pucAmPm)
{
    bool blFlag = FALSE;

    if((pucHour != NULL) && (pucAmPm != NULL))
    {
        // Convert to 12-hour format and set AM/PM
        if(*pucHour == HOUR_ZERO) 
        {
            *pucHour = HOUR_12;
            strcpy((char*)pucAmPm, AM);
        }
        else if(*pucHour < HOUR_12)
        {
            strcpy((char*)pucAmPm, AM);
        }
        else if(*pucHour == HOUR_12) 
        {
            strcpy((char*)pucAmPm, PM);
        } 
        else 
        {
            *pucHour -= HOUR_12;
            strcpy((char*)pucAmPm, PM);
        }
        blFlag = TRUE;
    }

    return blFlag;
}

//*********************.AppTimerPrintToConsole.********************************
//Purpose : Print to Console int the format given in requirement 
//Inputs  : pZone- GMT or IST or PST
//          pucTimerPart - time string HH:MM:SS
//          pucDate - Date string DD/MM/YYYY
//          time_t llEpoxhTime - epochtime
//Outputs : Print to the console Time and Date of GMT , IST , PST
//          pucTimerPart - time string HH:MM:SS
//          pucDate - Date string DD/MM/YYYY
//          llEpoxhTime - epochtime 
//Return  : TRUE - exit status success
//          FALSE - Failure
//Notes   : None 
//*****************************************************************************
static bool AppTimerPrintToConsole(uint8* pZone, uint8* pucTimePart, 
                                    uint8* pucDate,time_t llEpochTime)
{
    bool blFlag = FALSE;

    if((pZone != NULL) && (pucTimePart != NULL) && (pucDate != NULL))
    {
        if(strcmp((char*)pZone, GMT) == OK)
        {
            printf("\n\n\nUTC (0:00)\n-----------------\n");
        }
        else if(strcmp((char*)pZone, IST) == OK)
        {
            printf("IST (5:30)\n-----------------\n");
        }
        else
        {
            printf("PST (-8:00)\n-----------------\n");
        }

        printf("Time: %s\n", pucTimePart);
        printf("Date: %s\n", pucDate);

        if(strcmp((char*)pZone, GMT) == OK)
        {
            printf("epoch:%lld\n", llEpochTime);
        }

        printf("\n\n");
        blFlag = TRUE;
    }

    return blFlag;
}

//*********************.AppTimerDisplay.***************************************
//Purpose : print GMT , IST  and PST zone time,date
//Inputs  : pZone - string represents GMT , IST  or PST ,
//          ucOffsetHours- GmtOffsetHours,IstOffsetHours,PstOffsetHours 
//          ucOffsetMinutes- GmtMinutes or IstMinutes or PstMinutes
//Outputs : None
//Return  : TRUE - exit status success
//          FALSE - Failure
//Notes   : None 
//***************************************************************************** 
bool AppTimerDisplay(uint8* pZone, uint8 ucOffsetHours, uint8 ucOffsetMinutes)
{
    bool blFlag = FALSE;
    uint8 pucDate[DATE_STR_LEN] = {0}; 
    uint8 pucTimePart[TIME_STR_LEN] = {0};
    uint8 pucAmPm[AM_PM_SIZE] = {0};
    uint8 pucMonth[MONTH_SIZE] = {0};
    time_t llCurrentTime = time(NULL);
    time_t llEpochTime = time(NULL);
    time_t llAdjustTime = time(NULL);
    TIMER stTimer = {0, 0, 0, 0, 0, 0};
    uint8 *pTimeStr = NULL;

    //To Avoid Static Analysis Violations
    (void)llAdjustTime;
    (void)pucDate;
    (void)pucTimePart;
    (void)pucAmPm;
    (void)pucMonth;

    if((ucOffsetHours <= HOUR_24) && (ucOffsetMinutes <= MINUTES_60))
    {
        // get current time
        time(&llCurrentTime);
        llAdjustTime = llCurrentTime -  \
            ((ucOffsetHours * SECONDS_HOUR) + (ucOffsetMinutes * MINUTES_60));

        pTimeStr = (uint8*) ctime(&llAdjustTime);

        sscanf((char*)pTimeStr + MONTH_SIZE, "%3s %hhu %hhu:%hhu:%hhu %hu", \
                    pucMonth, &stTimer.ucDay, &stTimer.ucHour, \
                    &stTimer.ucMin, &stTimer.ucSec, &stTimer.unYear);

        if(AppTimerConvertToHourFormat(&stTimer.ucHour, pucAmPm))
        {
            sprintf((char*)pucTimePart, "%02d:%02d:%02d %s", \
                        stTimer.ucHour, stTimer.ucMin, stTimer.ucSec, pucAmPm);
        }

        if(AppTimerGetMonthValue(pucMonth, &stTimer.ucMonthValue))
        {
            sprintf((char*)pucDate, "%02d/%02d/%d", \
                    stTimer.ucDay, stTimer.ucMonthValue, stTimer.unYear);
        }

        //Print Result according to GMT , IST , Or PST
        if(AppTimerPrintToConsole(pZone, pucTimePart, pucDate, llEpochTime))
        {
            blFlag = TRUE;
        }
    }

    return blFlag;
}

//EOF