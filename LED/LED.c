//*******************************LED*******************************************
//Copyright (c) 2025 Trenser Technology Solutions
//All Rights Reserved
//*****************************************************************************
//
//File     : LED.c
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

#ifdef _RPIBOARD
#include <gpiod.h>
#endif /* _RPIBOARD*/

#include "LED.h"
#include "common.h"

//*********************Local Types*********************************************

//*********************Local Constants*****************************************

//*********************Local Variables*****************************************
static struct gpiod_line *stLine = NULL;
static struct gpiod_chip *stChip = NULL;
static bool sblLEDFlag = FALSE;
static bool sblLEDState = FALSE;

#ifdef _RPIBOARD
//*********************Local Functions*****************************************
static bool LEDGPIOConnect();
static void LEDGPIOSetValue();

//*********************.LEDInit.***********************************************
//Purpose : To Initialize the Hardware setup 
//Inputs  : None
//Outputs : None
//Return  : blLEDFlag - TRUE - successfully Initialized
//          FALSE - No Initialized
//Notes   : None
//*****************************************************************************
bool LEDInit()
{
    sblLEDFlag = FALSE;

    if ((stLine == NULL) || (stChip == NULL))
    {
        if(!LEDGPIOConnect())
        {
            sblLEDFlag = FALSE;
        }
        else
        {
            sblLEDFlag = TRUE;
        }

        if(gpiod_line_request_output(stLine, LED_CONSUMER_NAME, \
                                        GPIO_STATE_LOW) != OK)
        {
            sblLEDFlag = FALSE;
        }
        else
        {
            sblLEDFlag = TRUE;
        }
    }

    return sblLEDFlag;
}

//*********************.LEDDeInit.*********************************************
//Purpose : To DeInitialize the Hardware setup - close the connection 
//Inputs  : None
//Outputs : None
//Return  : None
//Notes   : None 
//*****************************************************************************
void LEDDeInit()
{
    if(stLine != NULL)
    {
        gpiod_line_release(stLine);
        stLine = NULL;
    }

    if (stChip != NULL)
    {
        gpiod_chip_close(stChip);
        stChip = NULL;
    }
}

//*********************.LEDGPIOConnect.****************************************
//Purpose : To connect the GPIO Pin
//Inputs  : None
//Outputs : None
//Return  : blConnectFlag - conection success or not
//          TRUE - success , FALSE - failed
//Notes   : None
//*****************************************************************************
static bool LEDGPIOConnect()
{
    bool blConnectFlag = FALSE;
    stChip = gpiod_chip_open(GPIO_DEVICE);

    if(stChip != NULL)
    {
        stLine = gpiod_chip_get_line(stChip, GPIO_LINE);

        if(stLine != NULL)
        {
            blConnectFlag = TRUE;
        }
    }

    return blConnectFlag;
}

//*********************.LEDGPIOSetValue.***************************************
//Purpose : To set value to the GPIO Pin -  HIGH-1 or LOW-0
//Inputs  : None
//Outputs : None
//Return  : None
//Notes   : None 
//*****************************************************************************
static void LEDGPIOSetValue()
{
    if(sblLEDState == FALSE)
    {
        gpiod_line_set_value(stLine, GPIO_STATE_HIGH);
        sblLEDState = TRUE;
        usleep(DELAY_ON_MS);
    }
    else
    {
        gpiod_line_set_value(stLine, GPIO_STATE_LOW);
        sblLEDState = FALSE;
        usleep(DELAY_OFF_MS);
    }
}

#endif /*_RPIBOARD*/

//*********************.LEDBlink.**********************************************
//Purpose : LED Blinking ON -OFF with delay of 840ms ON and 532ms OFF in 
//          Raspberry Pi Board and inifinite printf of LED ON and LED OFF 
//Inputs  : None
//Outputs : set the GPIO pin -ON and clear the GPIO Pin OFF with the delay 
//Return  : None
//Notes   : None 
//*****************************************************************************
bool LEDBlink()
{
    #ifdef _RPIBOARD
    if(sblLEDFlag != FALSE)
    {
        LEDGPIOSetValue();
        sblLEDFlag = TRUE;
    }

    #else
    /*To avoid static Anlysis violations*/
    (void)stLine;
    (void)stChip;

    sblLEDFlag = FALSE;

    if(sblLEDState)
    {
        printf("\rLED ON  ");
        sblLEDFlag = TRUE;
    }
    else
    {
        printf("\rLED OFF ");
        sblLEDFlag = TRUE;
    }

    sblLEDState = !sblLEDState;
    fflush(stdout);
    sleep(1);
    #endif /* _RPIBOARD*/

    return sblLEDFlag;
}

//EOF