//**************************** appTimer ***************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved 
//***************************************************************************** 
// 
// Summary : common header File
// Note    : Added Macros , data types are defined and clearConsole function
//
//*****************************************************************************

#ifndef _COMMON_H_ 
#define _COMMON_H_ 

//******************************* Include Files *******************************

//******************************* Global Types ********************************
typedef unsigned short uint16;
typedef signed char int8;
typedef unsigned char uint8;


//***************************** Global Constants ******************************
#define GMT                 "GMT"
#define IST                 "IST"
#define PST                 "PST"
#define CLEAR_SCREEN        "\x1b[H"

//***************************** Global Variables ******************************

//***************************** Function Declaration **************************
void clearConsole();

//*********************** Inline Method Implementations ***********************

#endif // _COMMON_H_ 

// EOF