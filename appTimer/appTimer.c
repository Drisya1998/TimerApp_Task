//*******************************appTimer***********************************
//Copyright (c) 2025 Trenser Technology Solutions
//All Rights Reserved
//*****************************************************************************
//
//File     : appTimer.c
//Summary  : DisplayGMT , DisplayIST , DisplayPST functions implementation
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
//Purpose : Get Month Value 
//Inputs  : string Month
//Outputs : None
//Return  : None
//Notes   : None 
//*****************************************************************************
uint8 AppTimerGetMonthValue(uint8* pmonth)
{
    MONTH MonthValue = 0;

    if(strcmp((char*)pmonth, "Jan") == ZERO)
    {
        MonthValue =  MONTH_JAN;
    }
    else if(strcmp((char*)pmonth, "Feb") == ZERO )
    {
        MonthValue = MONTH_FEB;
    }
    else if(strcmp((char*)pmonth, "Mar") == ZERO)
    {
        MonthValue = MONTH_MAR;
    }
    else if(strcmp((char*)pmonth, "Apr") == ZERO)
    {
        MonthValue = MONTH_APR;
    }
    else if(strcmp((char*)pmonth, "May") == ZERO)
    {
        MonthValue = MONTH_MAY;
    }
    else if(strcmp((char*)pmonth, "Jun") == ZERO)
    {
        MonthValue = MONTH_JUN;
    }
    else if(strcmp((char*)pmonth, "Jul") == ZERO)
    {
        MonthValue = MONTH_JUL;
    }
    else if(strcmp((char*)pmonth, "Aug") == ZERO)
    {
        MonthValue = MONTH_AUG;
    }
    else if(strcmp((char*)pmonth, "Sep") == ZERO)
    {
        MonthValue = MONTH_SEP;
    }
    else if(strcmp((char*)pmonth, "Oct") == ZERO)
    {
        MonthValue = MONTH_OCT;
    }
    else if(strcmp((char*)pmonth, "Nov") == ZERO)
    {
        MonthValue = MONTH_NOV;
    }
    else if(strcmp((char*)pmonth, "Dec") == ZERO)
    {
        MonthValue = MONTH_DEC;
    }
    else{
        //TODO
    }
    
    return MonthValue;
}


//*********************.AppTimerDisplay.************************************
//Purpose : print GMT , IST  and PST zone time,date
//Inputs  : uint8* string represents GMT , IST  or PST ,
            //uint8 GmtHours or IstHours or PstHours  , 
            //uint8 GmtMinutes or IstMinutes or PstMinutes
//Outputs : None
//Return  : None
//Notes   : None 
//*****************************************************************************
bool AppTimerDisplay(uint8* pzone , uint8 ucOffsetHours , uint8 ucOffsetMinutes)
{
    bool blflag = FALSE;
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

        // format: "Wed Jun DD HH:MM:SS YYYY\n"
        ptimeStr =(uint8*) ctime(&lladjustTime); 
        sscanf((char*)ptimeStr+MONTH_SIZE, "%3s %hhu %hhu:%hhu:%hhu %hu", \
                    pucMonth, &sttimer.ucDay, &sttimer.ucHour, \
                    &sttimer.ucMin, &sttimer.ucSec, &sttimer.unYear);

        // Convert to 12-hour format and set AM/PM
        if (sttimer.ucHour == ZERO) 
        {
            sttimer.ucHour = HOUR_12;
            strcpy((char*)pucAmPm, AM);
        }
        else if (sttimer.ucHour < HOUR_12)
        {
            strcpy((char*)pucAmPm, AM);
        }
        else if (sttimer.ucHour == HOUR_12) 
        {
            strcpy((char*)pucAmPm, PM);
        } 
        else 
        {
            sttimer.ucHour -= HOUR_12;
            strcpy((char*)pucAmPm, PM);
        }

        sprintf((char*)pucTimePart,"%02d:%02d:%02d %s" , \
                            sttimer.ucHour,sttimer.ucMin,sttimer.ucSec,pucAmPm); 
        sttimer.ucMonthValue = AppTimerGetMonthValue(pucMonth);
        sprintf((char*)pucDate, "%02d/%02d/%d", \
                        sttimer.ucDay, sttimer.ucMonthValue, sttimer.unYear);

        //Print Result according to GMT , IST , Or PST
        if(strcmp((char*)pzone,GMT) == ZERO)
        {
            printf("\n\n\nUTC (0:00)\n-----------------\n");
            printf("Time: %s\n", pucTimePart);
            printf("Date: %s\n", pucDate);
            printf("epoch:%ld\n", llEpochTime);
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
        blflag=TRUE;
    }
    
    return blflag;
}

//EOF