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
uint8 AppTimerGetMonthValue(uint8 ucmonth[])
{
    MONTH MonthValue = 0;

    if(strcmp((char*)ucmonth, "Jan") == ZERO)
    {
        MonthValue =  MONTH_JAN;
    }
    else if(strcmp((char*)ucmonth, "Feb") == ZERO )
    {
        MonthValue = MONTH_FEB;
    }
    else if(strcmp((char*)ucmonth, "Mar") == ZERO)
    {
        MonthValue = MONTH_MAR;
    }
    else if(strcmp((char*)ucmonth, "Apr") == ZERO)
    {
        MonthValue = MONTH_APR;
    }
    else if(strcmp((char*)ucmonth, "May") == ZERO)
    {
        MonthValue = MONTH_MAY;
    }
    else if(strcmp((char*)ucmonth, "Jun") == ZERO)
    {
        MonthValue = MONTH_JUN;
    }
    else if(strcmp((char*)ucmonth, "Jul") == ZERO)
    {
        MonthValue = MONTH_JUL;
    }
    else if(strcmp((char*)ucmonth, "Aug") == ZERO)
    {
        MonthValue = MONTH_AUG;
    }
    else if(strcmp((char*)ucmonth, "Sep") == ZERO)
    {
        MonthValue = MONTH_SEP;
    }
    else if(strcmp((char*)ucmonth, "Oct") == ZERO)
    {
        MonthValue = MONTH_OCT;
    }
    else if(strcmp((char*)ucmonth, "Nov") == ZERO)
    {
        MonthValue = MONTH_NOV;
    }
    else if(strcmp((char*)ucmonth, "Dec") == ZERO)
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
    uint8   ucDay         = (uint8)ZERO;
    uint8   ucHour        = (uint8)ZERO;
    uint8   ucMin         = (uint8)ZERO;
    uint8   ucSec         = (uint8)ZERO;
    uint16  unYear        = (uint16)ZERO;
    uint8   ucMonthValue  = (uint8)ZERO;

    uint8 ucDate[DATE_STR_LEN]; 
    uint8 ucTimePart[TIME_STR_LEN];
    uint8 ucAmPm[AM_PM_SIZE];
    uint8 ucMonth[SIZE];

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
        uint8 *uctimeStr =(uint8*) ctime(&adjustTime);
        
        sscanf((char*)uctimeStr+SIZE, "%s %hhu %hhu:%hhu:%hhu %hu", \
            ucMonth, &ucDay, &ucHour, &ucMin, &ucSec, &unYear);

        // Convert to 12-hour format and set AM/PM
        if (ucHour == ZERO) 
        {
            ucHour = HOUR_12;
            strcpy((char*)ucAmPm, "AM");
        }
        else if (ucHour < HOUR_12)
        {
            strcpy((char*)ucAmPm, "AM");
        }
        else if (ucHour == HOUR_12) 
        {
            strcpy((char*)ucAmPm, "PM");
        } 
        else 
        {
            ucHour -= HOUR_12;
            strcpy((char*)ucAmPm, "PM");
        }

        sprintf((char*)ucTimePart, "%02d:%02d:%02d %s" , \
                            ucHour, ucMin, ucSec,ucAmPm);

        ucMonthValue = AppTimerGetMonthValue(ucMonth);

        sprintf((char*)ucDate, "%02d/%02d/%d", ucDay, ucMonthValue, unYear);

        // Print results
        printf("Time: %s\n", ucTimePart);
        printf("Date: %s\n", ucDate);
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
    bool    blflag        = FALSE;
    uint8   ucDay         = (uint8)ZERO;
    uint8   ucHour        = (uint8)ZERO;
    uint8   ucMin         = (uint8)ZERO;
    uint8   ucSec         = (uint8)ZERO;
    uint16  unYear        = (uint16)ZERO;
    uint8   ucMonthValue  = (uint8)ZERO;

    uint8 ucDate[DATE_STR_LEN]; 
    uint8 ucTimePart[TIME_STR_LEN];
    uint8 ucAmPm[AM_PM_SIZE];
    uint8 ucMonth[SIZE];

    printf("IST (5:30)\n-----------------\n");
    time_t currentTime = time(NULL);
    // get current time
    time(&currentTime);

    // format: "Wed Jun 18 20:32:42 2025\n"
    uint8 *uctimeStr =(uint8*) ctime(&currentTime);
        
    sscanf((char*)uctimeStr+SIZE, "%s %hhu %hhu:%hhu:%hhu %hu", \
    ucMonth, &ucDay, &ucHour, &ucMin, &ucSec, &unYear);

    // Convert to 12-hour format and set AM/PM
    if (ucHour == ZERO) 
    {
        ucHour = HOUR_12;
        strcpy((char*)ucAmPm, "AM");
    }
    else if (ucHour < HOUR_12)
    {
        strcpy((char*)ucAmPm, "AM");
    }
    else if (ucHour == HOUR_12) 
    {
        strcpy((char*)ucAmPm, "PM");
    } 
    else 
    {
        ucHour -= HOUR_12;
        strcpy((char*)ucAmPm, "PM");
    }

    sprintf((char*)ucTimePart, "%02d:%02d:%02d %s" , ucHour, ucMin, ucSec,ucAmPm);

    ucMonthValue = AppTimerGetMonthValue(ucMonth);

    sprintf((char*)ucDate, "%02d/%02d/%d", ucDay, ucMonthValue, unYear);

    // Print results
    printf("Time: %s\n", ucTimePart);
    printf("Date: %s\n", ucDate);
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
    uint8   ucDay         = (uint8)ZERO;
    uint8   ucHour        = (uint8)ZERO;
    uint8   ucMin         = (uint8)ZERO;
    uint8   ucSec         = (uint8)ZERO;
    uint16  unYear        = (uint16)ZERO;
    uint8   ucMonthValue  = (uint8)ZERO;

    uint8 ucDate[DATE_STR_LEN]; 
    uint8 ucTimePart[TIME_STR_LEN];
    uint8 ucAmPm[AM_PM_SIZE];
    uint8 ucMonth[SIZE];

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
        uint8 *uctimeStr =(uint8*) ctime(&adjustTime);
            
        sscanf((char*)uctimeStr+SIZE, "%s %hhu %hhu:%hhu:%hhu %hu", \
        ucMonth, &ucDay, &ucHour, &ucMin, &ucSec, &unYear);

        // Convert to 12-hour format and set AM/PM
        if (ucHour == ZERO) 
        {
            ucHour = HOUR_12;
            strcpy((char*)ucAmPm, "AM");
        }
        else if (ucHour < HOUR_12)
        {
            strcpy((char*)ucAmPm, "AM");
        }
        else if (ucHour == HOUR_12) 
        {
            strcpy((char*)ucAmPm, "PM");
        } 
        else 
        {
            ucHour -= HOUR_12;
            strcpy((char*)ucAmPm, "PM");
        }

        sprintf((char*)ucTimePart,"%02d:%02d:%02d %s" , \
                            ucHour,ucMin,ucSec,ucAmPm); 

        ucMonthValue = AppTimerGetMonthValue(ucMonth);

        sprintf((char*)ucDate, "%02d/%02d/%d", ucDay, ucMonthValue, unYear);

        // Print results
        printf("Time: %s\n", ucTimePart);
        printf("Date: %s\n", ucDate);
        
        blflag=TRUE;
    }
    
    return blflag;
}

//EOF