//*******************************main******************************************
//Copyright (c) 2025 Trenser Technology Solutions
//All Rights Reserved
//*****************************************************************************
//
//File     : main.c
//Summary  : Infinitely Display time of different Zones GMT , IST and PST by 
//           clear the console every second and LED simulation for Linux and 
//           LED Blinking in Raspberry Pi
//Note     : None
//Author   : Drisya P
//Date     : 17/Jun/2025
//
//*****************************************************************************

//*********************Include Files*******************************************
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "appTimer.h"
#include "LED.h"
#include "common.h"

//*********************Local Types*********************************************

//*********************Local Constants*****************************************

//*********************Local Variables*****************************************

//*********************Local Functions*****************************************
static void ClearConsole();

//*********************.main.**************************************************
//Purpose : Infinitely Display time of different Zones GMT , IST and PST by 
//          clear the console every second and LED simulation for Linux and 
//          LED Blinking in Raspberry Pi
//Inputs  : None
//Outputs : None 
//Return  : 0 - exit success- send status code to OS
//Notes   : None 
//*****************************************************************************
int main()
{
    bool blResult = FALSE;

    //To avoid static analysis violations
    (void)blResult;

    #ifdef _RPIBOARD
    blResult = LEDInit();

    if(blResult == FALSE)
    {
        printf("RPI Initialization Failed\n\n");
    }

    #endif /*_RPIBOARD*/

    while(TRUE)
    {
        ClearConsole();
        blResult = AppTimerDisplay();

        if(blResult ==  FALSE)
        {
            printf("Displaying the time failed\n");
        }

        blResult = LEDBlink();

        if(blResult == FALSE)
        {
            printf("\nLED Blinking Failed\n");
        }
        else
        {
            printf("\nLED Blinking\n");
        }
    }

    #ifdef _RPIBOARD
    LEDDeInit();
    #endif /*_RPIBOARD*/

    return 0;
}

//*********************.ClearConsole.******************************************
//Purpose : clear the console
//Inputs  : None
//Outputs : None 
//Return  : None
//Notes   : None 
//*****************************************************************************
static void ClearConsole()
{
    //clear the screen
    printf(CLEAR_SCREEN);
}

//EOF