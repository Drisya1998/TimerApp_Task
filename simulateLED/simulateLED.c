//*******************************simulateLED***********************************
//Copyright (c) 2025 Trenser Technology Solutions
//All Rights Reserved
//*****************************************************************************
//
//File     : simulateLED.c
//Summary  : LED simulation - print infinite LED ON and LED OFF in the console 
//Note     : None
//Author   : Drisya P
//Date     : 24/Jun/2025
//
//*****************************************************************************

//*********************Include Files*******************************************
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "simulateLED.h"
#include "common.h"

//*********************Local Types*********************************************

//*********************Local Constants*****************************************

//*********************Local Variables*****************************************

//*********************Local Functions*****************************************

//*********************.SimulateLED.*******************************************
//Purpose : inifinite printf of LED ON and LED OFF
//Inputs  : blLEDState - current state of LED TRUE - LED ON or FALSE - LED OFF
//Outputs : Print to the Console that LED ON or LED OFF according to the input 
//Return  : None
//Notes   : None 
//*****************************************************************************
void SimulateLEDDisplay()
{
    static bool sblLEDState = FALSE;

    if(sblLEDState)
    {
        printf("\rLED ON  ");
    }
    else
    {
        printf("\rLED OFF ");
    }

    sblLEDState = !sblLEDState;
    fflush(stdout);
    sleep(1);
}

//EOF