/** @file HL_sys_main.c 
*   @brief Application main file
*   @date 05-Oct-2016
*   @version 04.06.00
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2016 Texas Instruments Incorporated - www.ti.com  
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
#include "HL_sys_common.h"
#include "HL_can.h"
#include "HL_sci.h"
#include "HL_system.h"

/* USER CODE END */

/* Include Files */

#include "HL_sys_common.h"

/* USER CODE BEGIN (1) */
#define D_SIZE 9
uint8_t tx_data[D_SIZE] = {'H','E','R','C','U','L','E','S','\0'};						// Data expected to be received
uint8_t rx_data[D_SIZE] = {0};
uint32_t error = 0;																		// Initialize the no. of errors = 0
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
uint32_t checkPackets(uint8_t *src_packet, uint8_t *dst_packet, uint32_t psize);	// Function to check error in received data (prototype)
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
	canInit();																		// Initialize the CAN Module
	sciInit();																		// Initialize the SCI (UART) Module

	while(!canIsRxMessageArrived(canREG1, canMESSAGE_BOX1));						// Wait till a message is received on CAN1, Msg Box1
	canGetData(canREG1, canMESSAGE_BOX1, rx_data);									// Store the received data  in rx_data

	error = checkPackets(&tx_data[0], &rx_data[0], D_SIZE);							// Check if the message received is same as expected
	sciSend(sciREG1, D_SIZE, rx_data);												// Send the received message through UART

	while(1);																		// Infinite Loop
/* USER CODE END */
}


/* USER CODE BEGIN (4) */
uint32_t checkPackets(uint8_t *src_packet, uint8_t *dst_packet, uint32_t psize){	// Function to check error in received data
	uint32_t err=0;
	uint32_t cnt=psize;
	while(cnt--){
		if((*src_packet++) != (*dst_packet++))										// Check if source packet == destination packet
			err++;																	// If true increment the error variable
	}
	return (err);																	// Return error, used to monitor no. of errors occured
}

void canMessageNotification(canBASE_t *node, uint32_t messageBox)					// Declared to prevent compilation errors
{
	return;
}

void canErrorNotification(canBASE_t *node, uint32_t notification)					// Declared to prevent compilation errors
{
	return;
}

void esmGroup1Notification(unsigned channel)										// Declared to prevent compilation errors
{
	return;
}

void esmGroup2Notification(unsigned channel)										// Declared to prevent compilation errors
{
	return;
}
/* USER CODE END */
