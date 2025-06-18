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

//*********************.AppTimerDisplayGMT.***********************************
//Purpose : print GMT zone time,date, epoch
//Inputs  : uint8 GmtHours,uint8 GmtMinutes
//Outputs : None
//Return  : None
//Notes   : None 
//*****************************************************************************
bool AppTimerDisplayGMT(uint8 ucGmtHours , uint8 ucGmtMinutes)
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

    //check Inputs are valid or Not
    if(ucGmtHours > ZERO && ucGmtHours <= HOUR_24 && \
        ucGmtMinutes > ZERO && ucGmtMinutes < MINUTES_60)
    {
        printf("\n\n\nUTC (0:00)\n-----------------\n");

        time_t currentTime = time(NULL);
        time_t EpochTime= currentTime;
        // get current time
        time(&currentTime);

        time_t adjustTime = currentTime - \
                (ucGmtHours * OFFSET+ucGmtMinutes * MINUTES_60);
        // format: "Wed Jun 18 20:32:42 2025\n"
        uint8 *ptimeStr =(uint8*) ctime(&adjustTime);
        
        sscanf((char*)ptimeStr+SIZE, "%9s %hhu %hhu:%hhu:%hhu %hu", \
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

        sprintf((char*)pTimePart, "%02d:%02d:%02d %s" , \
                            ucHour, ucMin, ucSec,pAmPm);

        ucMonthValue = AppTimerGetMonthValue(pMonth);

        sprintf((char*)pDate, "%02d/%02d/%d", ucDay, ucMonthValue, unYear);

        // Print results
        printf("Time: %s\n", pTimePart);
        printf("Date: %s\n", pDate);
        printf("epoch:%ld\n" ,EpochTime);
        printf("\n\n");

        blflag= TRUE;
    }

    return blflag;
}

//*********************.AppTimerDisplayIST.***********************************
//Purpose : print IST zone time,date
//Inputs  : None
//Outputs : None
//Return  : None
//Notes   : None 
//*****************************************************************************
void AppTimerDisplayIST()
{
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

    printf("IST (5:30)\n-----------------\n");
    time_t currentTime = time(NULL);
    // get current time
    time(&currentTime);

    // format: "Wed Jun 18 20:32:42 2025\n"
    uint8 *ptimeStr =(uint8*) ctime(&currentTime);
        
    sscanf((char*)ptimeStr+SIZE, "%9s %hhu %hhu:%hhu:%hhu %hu", \
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

    sprintf((char*)pTimePart, "%02d:%02d:%02d %s" , ucHour, ucMin, ucSec,pAmPm);

    ucMonthValue = AppTimerGetMonthValue(pMonth);

    sprintf((char*)pDate, "%02d/%02d/%d", ucDay, ucMonthValue, unYear);

    // Print results
    printf("Time: %s\n", pTimePart);
    printf("Date: %s\n", pDate);
    printf("\n\n");

    return;
}

//*********************.ApptimerDisplayPST.************************************
//Purpose : print PST zone time,date
//Inputs  : uint8 PstHours , uint8 PstMinutes
//Outputs : None
//Return  : None
//Notes   : None 
//*****************************************************************************
bool AppTimerDisplayPST(int PstHours,int PstMinutes)
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

    if(PstHours > ZERO && PstHours <= HOUR_24 && \
        PstMinutes > ZERO && PstMinutes < MINUTES_60)
    {
        printf("PST (-8:00)\n-----------------\n");
        time_t currentTime = time(NULL);
        // get current time
        time(&currentTime);

        time_t adjustTime = currentTime -  \
                            PstHours * OFFSET + PstMinutes * MINUTES_60;

        // format: "Wed Jun 18 20:32:42 2025\n"
        uint8 *ptimeStr =(uint8*) ctime(&adjustTime);
            
        sscanf((char*)ptimeStr+SIZE, "%9s %hhu %hhu:%hhu:%hhu %hu", \
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

        // Print results
        printf("Time: %s\n", pTimePart);
        printf("Date: %s\n", pDate);
        
        blflag=TRUE;
    }
    
    return blflag;
}

//EOF