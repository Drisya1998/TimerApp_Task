//**************************** LED ********************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved 
//***************************************************************************** 
// 
// Summary : LED header File - Supprting LED operations.
// Note    : 
//
//*****************************************************************************

#ifndef _LED_H_ 
#define _LED_H_ 

//******************************* Include Files *******************************

//******************************* Global Types ********************************

//***************************** Global Constants ******************************
#define GPIO_DEVICE             "/dev/gpiochip0"
#define LED_CONSUMER_NAME       "led_blink"
#define GPIO_LINE               17
#define GPIO_STATE_HIGH         1
#define GPIO_STATE_LOW          0
#define DELAY_ON_MS             840000
#define DELAY_OFF_MS            532000

//***************************** Global Variables ******************************

//***************************** Function Declaration **************************
bool LEDBlink();
bool LEDInit();
void LEDDeInit();

//*********************** Inline Method Implementations ***********************

#endif // _LED_H_ 

// EOF