//*******************************main***********************************
//Copyright (c) 2025 Trenser Technology Solutions
//All Rights Reserved
//**********************************************************************
//
//File     : main.c
//Summary  : Call the DisplayGMT , DisplayIST , DisplayPST functions 
//Note     : None
//Author   : Drisya P
//Date     : 17/Jun/2025
//
//*****************************************************************************

//*********************Include Files*******************************************
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "appTimer.h"

//*********************Local Types*********************************************

//*********************Local Constants*****************************************

//*********************Local Variables*****************************************

//*********************Local Functions*****************************************

//*********************.main.**************************************************
//Purpose : Call the AppTimerDisplayGMT , AppTimerDisplayIST , 
            //AppTimerDisplayPST functions
//Inputs  : None
//Outputs : None 
//Return  : ZERO
//Notes   : None 
//*****************************************************************************
uint8 main()
{
    while(TRUE)
    {
        //clear the screen
        printf("\x1b[H");

        bool blGmtResult = AppTimerDisplayGMT(GMT_HOURS,GMT_MINUTES);
        if(blGmtResult ==  false)
        {
            printf("Invalid Input detected");
        }
        AppTimerDisplayIST();
        bool blPstResult = AppTimerDisplayPST(PST_HOURS,PST_MINUTES);
        if(blPstResult ==  false)
        {
            printf("Invalid Input detected");
        }
    }

    return ZERO;
}

//EOF