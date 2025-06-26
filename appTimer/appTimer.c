//*******************************appTimer**************************************
//Copyright (c) 2025 Trenser Technology Solutions
//All Rights Reserved
//*****************************************************************************
//
//File     : appTimer.c
//Summary  : Implementations for calculating and displaying time in different 
//           zones GMT, PST and IST
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
static bool AppTimerPrintZone(int8*, int8, uint8);
static bool AppTimerZoneTimeDisplay(uint8*, uint8, uint8);

//*********************.AppTimerGetMonthValue.*********************************
//Purpose : Get corresponding Month Value from month string 
//Inputs  : Month - Month in string like Jun 
//Inputs  : pucMonthValue - address of variable ucMonthValue
//Outputs : Update MonthValue corresponds to the string Month
//Return  : TRUE - exit status success
//          FALSE - Failure
//Notes   : None 
//*****************************************************************************
static bool AppTimerGetMonthValue(uint8* pucMonth, uint8* pucMonthValue)
{
    bool blFlag = FALSE;
    uint8 ucIndex = 0;

    //To avoid static Analysis violations
    (void)ucIndex;

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
//Inputs  : pucAmPm - AmPm Array that stores "AM" or "PM"
//Outputs : pucHour - Hour Update in 12-Hour Format, 
//Outputs : pucAmPm - ampm array update with "AM" or "PM"
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

//*********************.AppTimerPrintZone.*************************************
//Purpose : Print to Console the Zone Name and details
//Inputs  : pZone- GMT or IST or PST
//Inputs  : ucZoneHour - Hours to display related to the Zone
//Inputs  : ucZoneMinutes - Minutes to display related to the Zone 
//Outputs : print the Zone name to the console
//Return  : TRUE - exit status success
//          FALSE - Failure
//Notes   : None 
//*****************************************************************************
static bool AppTimerPrintZone(int8 *pZoneName, int8 ucZoneHour, \
                                uint8 ucZoneMinutes)
{
    bool blFlag = FALSE;

    if(pZoneName != NULL)
    {
        printf("\n%s (%d:%02d)\n--------------------\n",pZoneName, ucZoneHour,\
                                    ucZoneMinutes);
        blFlag = TRUE;
    }

    return blFlag;
}

//*********************.AppTimerPrintToConsole.********************************
//Purpose : Print to Console int the format given in requirement 
//Inputs  : pZone- GMT or IST or PST
//Inputs  : pucTimerPart - time string HH:MM:SS
//Inputs  : pucDate - Date string DD/MM/YYYY
//Inputs  : time_t llEpoxhTime - epochtime
//Outputs : Print to the console Time and Date of GMT , IST , PST
//Outputs : pucTimerPart - time string HH:MM:SS
//Outputs : pucDate - Date string DD/MM/YYYY
//Outputs : llEpoxhTime - epochtime 
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
            blFlag = AppTimerPrintZone((int8*)GMT, IST_HOURS, IST_MINUTES);
        }
        else if(strcmp((char*)pZone, IST) == OK)
        {
            blFlag = AppTimerPrintZone((int8*)IST, GMT_HOURS, GMT_MINUTES);
        }
        else
        {
            blFlag = AppTimerPrintZone((int8*)PST, PST_HOURS_DIFF, \
                                            PST_MINUTES_DIFF);
        }

        printf("Time: %s\n", pucTimePart);
        printf("Date: %s\n", pucDate);

        if(strcmp((char*)pZone, GMT) == OK)
        {
            printf("epoch:%ld\n", (long)llEpochTime);
        }

        printf("\n\n");
    }

    return blFlag;
}

//*********************.AppTimerZoneTimeDisplay.*******************************
//Purpose : print GMT , IST  and PST zone time,date
//Inputs  : pZone - string represents GMT , IST  or PST ,
//inputs  : ucOffsetHours- GmtOffsetHours,IstOffsetHours,PstOffsetHours 
//Inputs  : ucOffsetMinutes- GmtMinutes or IstMinutes or PstMinutes
//Outputs : None
//Return  : TRUE - exit status success
//          FALSE - Failure
//Notes   : None 
//***************************************************************************** 
static bool AppTimerZoneTimeDisplay(uint8* pZone, uint8 ucOffsetHours, \
                                        uint8 ucOffsetMinutes)
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

//*********************.AppTimerDisplay.***************************************
//Purpose : Print to Console int the format given in requirement 
//Inputs  : None
//Outputs : Print to the console if Display Time is failed.
//Return  : TRUE - exit status success
//          FALSE - Failure
//Notes   : None 
//*****************************************************************************
bool AppTimerDisplay()
{
    bool blResult = FALSE;

    blResult = AppTimerZoneTimeDisplay((unsigned char*)GMT, GMT_HOURS, 
                                            GMT_MINUTES);
    if(blResult ==  FALSE)
    {
        printf("Displaying the time in GMT failed");
    }

    blResult = AppTimerZoneTimeDisplay((unsigned char*)IST, IST_HOURS, 
                                            IST_MINUTES);
    if(blResult ==  FALSE)
    {
        printf("Displaying the time in IST failed");
    }

    blResult = AppTimerZoneTimeDisplay((unsigned char*)PST, PST_HOURS, 
                                        PST_MINUTES);
    if(blResult ==  FALSE)
    {
        printf("Displaying the time in PST failed");
    }

    return blResult;
}

//EOF