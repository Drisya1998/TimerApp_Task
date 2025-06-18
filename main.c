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
#include "appTimer/appTimer.h"

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

        bool blResult = FALSE;

        blResult = AppTimerDisplay("GMT",GMT_HOURS , GMT_MINUTES);
        if(blResult ==  FALSE)
        {
            printf("Invalid Input detected");
        }

        blResult = AppTimerDisplay("IST",IST_HOURS , IST_MINUTES);
        if(blResult ==  FALSE)
        {
            printf("Invalid Input detected");
        }

        blResult = AppTimerDisplay("PST",PST_HOURS , PST_MINUTES);
        if(blResult ==  FALSE)
        {
            printf("Invalid Input detected");
        }
        
    }

    return ZERO;
}

//EOF