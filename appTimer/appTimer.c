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
//Inputs  : string Month like Jun and address of variable monthValue
//Outputs : Update MonthValue
//Return  : exit status success or Failure
//Notes   : None 
//*****************************************************************************
bool AppTimerGetMonthValue(uint8* pucMonth, uint8* pucMonthValue)
{
    bool blFlag=FALSE;
    static const int8* const pucMonthNames[] = {
    (const int8*)JAN, (const int8*)FEB, (const int8*)MAR, 
    (const int8*)APR,(const int8*)MAY, (const int8*)JUN, 
    (const int8*)JUL, (const int8*)AUG,(const int8*)SEP, 
    (const int8*)OCT, (const int8*)NOV, (const int8*)DEC};

    if(pucMonth != NULL )
    {
        for(int i = ZERO; i < NUMBER_MONTHS; ++i)
        {
            if(strcmp((const char*)pucMonth,(char*)pucMonthNames[i]) == ZERO){
                *pucMonthValue =i+ONE;
            }
        }
        blFlag = TRUE;
    }
    
    return blFlag;
}

//*********************.AppTimerConvertToHourFormat.***************************
//Purpose : Convert the 24 Hour format to 12 Hour Format and set AM/PM 
//Inputs  : 24 format Hour and AmPm Array that stores "AM" or "PM"
//Outputs : Hour Update in 12-Hour Format, ampm array update 
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

//*********************.AppTimerPrintToConsole.********************************
//Purpose : Print to Console int the format given in requirement 
//Inputs  : Zone- GMT or IST or PST
//Outputs : Print to the console Time and Date of GMT , IST , PST
//Return  : None
//Notes   : None 
//*****************************************************************************
void AppTimerPrintToConsole(uint8* pZone, uint8* pucTimePart, uint8* pucDate,
                             time_t llEpochTime)
{
    if(strcmp((char*)pZone,GMT) == ZERO)
    {
        printf("\n\n\nUTC (0:00)\n-----------------\n");
        printf("Time: %s\n", pucTimePart);
        printf("Date: %s\n", pucDate);
        printf("epoch:%lld\n", llEpochTime);
        printf("\n\n");
    }
    else if(strcmp((char*)pZone,IST)==ZERO)
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

//*********************.AppTimerDisplay.***************************************
//Purpose : print GMT , IST  and PST zone time,date
//Inputs  : uint8* string represents GMT , IST  or PST ,
//          uint8 GmtHours or IstHours or PstHours  , 
//          uint8 GmtMinutes or IstMinutes or PstMinutes
//Outputs : None
//Return  : Exit status succes or Failure
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
    TIMER stTimer = {0,0,0,0,0,0};

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

        pTimeStr =(uint8*) ctime(&llAdjustTime);

        sscanf((char*)pTimeStr+MONTH_SIZE, "%3s %hhu %hhu:%hhu:%hhu %hu", \
                    pucMonth, &stTimer.ucDay, &stTimer.ucHour, \
                    &stTimer.ucMin, &stTimer.ucSec, &stTimer.unYear);

        AppTimerConvertToHourFormat(&stTimer.ucHour , pucAmPm);

        sprintf((char*)pucTimePart,"%02d:%02d:%02d %s" , \
                        stTimer.ucHour,stTimer.ucMin,stTimer.ucSec,pucAmPm);

        if(AppTimerGetMonthValue(pucMonth , &stTimer.ucMonthValue))
        {
            sprintf((char*)pucDate, "%02d/%02d/%d", \
                    stTimer.ucDay, stTimer.ucMonthValue, stTimer.unYear);
        }
        //Print Result according to GMT , IST , Or PST
        AppTimerPrintToConsole(pZone, pucTimePart, pucDate, llEpochTime);
        blFlag=TRUE;
    }
    
    return blFlag;
}

//EOF