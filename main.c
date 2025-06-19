//*******************************main******************************************
//Copyright (c) 2025 Trenser Technology Solutions
//All Rights Reserved
//*****************************************************************************
//
//File     : main.c
//Summary  : Call the functionsfor DisplayGMT , DisplayIST , DisplayPST,
//           clear the console 
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
#include "common.h"

//*********************Local Types*********************************************

//*********************Local Constants*****************************************

//*********************Local Variables*****************************************

//*********************Local Functions*****************************************

//*********************.main.**************************************************
//Purpose : Call the AppTimerDisplayGMT , AppTimerDisplayIST , 
//          AppTimerDisplayPST functions
//Inputs  : None
//Outputs : None 
//Return  : 0 - exit success- send status code to OS
//Notes   : None 
//*****************************************************************************
int main()
{
    bool blResult = FALSE;
    while(TRUE)
    {
        clearConsole();
        blResult = AppTimerDisplay((unsigned char*)GMT, GMT_HOURS, GMT_MINUTES);
        if(blResult ==  FALSE)
        {
            printf("Displaying the time in GMT failed");
        }

        blResult = AppTimerDisplay((unsigned char*)IST, IST_HOURS, IST_MINUTES);
        if(blResult ==  FALSE)
        {
            printf("Displaying the time in IST failed");
        }

        blResult = AppTimerDisplay((unsigned char*)PST, PST_HOURS, PST_MINUTES);
        if(blResult ==  FALSE)
        {
            printf("Displaying the time in PST failed");
        }
    }

    return 0;
}

void clearConsole()
{
    //clear the screen
    printf(CLEAR_SCREEN);
}

//EOF