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
//Return  : 0
//Notes   : None 
//*****************************************************************************
uint8 main()
{
    while(1)
    {
        //clear the screen
        printf("\x1b[H");

        bool GmtResult = AppTimerDisplayGMT(5,30);
        if(GmtResult ==  false)
        {
            printf("Invalid Input detected");
        }
        AppTimerDisplayIST();
        bool PstResult = AppTimerDisplayPST(13,30);
        if(PstResult ==  false)
        {
            printf("Invalid Input detected");
        }
    }

    return 0;
}

//EOF