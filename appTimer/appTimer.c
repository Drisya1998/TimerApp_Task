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
    bool    blflag        = FALSE;
    uint8   ucDay         = 0u;
    uint8   ucHour        = 0u;
    uint8   ucMin         = 0u;
    uint8   ucSec         = 0u;
    uint16  unYear        = 0u;
    uint8   ucMonthValue  = 0u;

    uint8 pDate[DATE_STR_LEN]={0}; 
    uint8 pTimePart[TIME_STR_LEN]={0};
    uint8 pAmPm[AM_PM_SIZE]={0};
    uint8 pMonth[SIZE]={0};

    //To Avoid Static Analysis Violations
    (void)ucDay;
    (void)ucHour;
    (void)ucMin;
    (void)ucSec;
    (void)unYear;
    (void)ucMonthValue;

    (void*)pDate;
    (void*)pTimePart;
    (void*)pAmPm;
    (void*)pMonth;

    if(ucOffsetHours <= HOUR_24 && ucOffsetMinutes <= MINUTES_60)
    {
        
        time_t currentTime = time(NULL);
        time_t EpochTime= currentTime;
        // get current time
        time(&currentTime);

        time_t adjustTime = currentTime -  \
                        ucOffsetHours * OFFSET + ucOffsetMinutes * MINUTES_60;

        // format: "Wed Jun DD HH:MM:SS YYYY\n"
        uint8 *ptimeStr =(uint8*) ctime(&adjustTime);
            
        sscanf((char*)ptimeStr+SIZE, "%3s %hhu %hhu:%hhu:%hhu %hu", \
                    pMonth, &ucDay, &ucHour, &ucMin, &ucSec, &unYear);

        // Convert to 12-hour format and set AM/PM
        if (ucHour == ZERO) 
        {
            ucHour = HOUR_12;
            strcpy((char*)pAmPm, "AM");
        }
        else if (ucHour < HOUR_12)
        {
            strcpy((char*)pAmPm, "AM");
        }
        else if (ucHour == HOUR_12) 
        {
            strcpy((char*)pAmPm, "PM");
        } 
        else 
        {
            ucHour -= HOUR_12;
            strcpy((char*)pAmPm, "PM");
        }

        sprintf((char*)pTimePart,"%02d:%02d:%02d %s" , \
                            ucHour,ucMin,ucSec,pAmPm); 

        ucMonthValue = AppTimerGetMonthValue(pMonth);

        sprintf((char*)pDate, "%02d/%02d/%d", ucDay, ucMonthValue, unYear);

        //Print Result according to GMT , IST , Or PST
        if(strcmp((char*)pzone,"GMT") == ZERO)
        {
            printf("\n\n\nUTC (0:00)\n-----------------\n");
            printf("Time: %s\n", pTimePart);
            printf("Date: %s\n", pDate);
            printf("epoch:%ld\n" ,EpochTime);
            printf("\n\n");
        }
        else if(strcmp((char*)pzone,"IST")==ZERO)
        {
            printf("IST (5:30)\n-----------------\n");
            printf("Time: %s\n", pTimePart);
            printf("Date: %s\n", pDate);
            printf("\n\n");
        }
        else
        {
            printf("PST (-8:00)\n-----------------\n");
            printf("Time: %s\n", pTimePart);
            printf("Date: %s\n", pDate);
            printf("\n\n");
        }
        blflag=TRUE;
    }
    
    return blflag;
}

//EOF