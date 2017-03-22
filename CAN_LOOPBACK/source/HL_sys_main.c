/* 
* Copyright (C) 2009-2015 Texas Instruments Incorporated - www.ti.com
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
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

/* USER CODE BEGIN (0) */
#include "HL_can.h"
#include "HL_esm.h"
#include "HL_sys_core.h"
/* USER CODE END */

/* Include Files */

#include "HL_sys_common.h"
#include "HL_system.h"

/* USER CODE BEGIN (1) */
uint32 cnt=0, error =0, tx_done =0;
/*	*********************************	TRANSMIT DATA	*****************************	*/
#define D_COUNT  8
uint8 tx_data1[D_COUNT] = {1,2,3,4,5,6,7,8};
uint8 tx_data2[D_COUNT] = {11,12,13,14,15,16,17,18};
uint8 tx_data3[D_COUNT] = {21,22,23,24,25,26,27,28};
uint8 tx_data4[D_COUNT] = {31,32,33,34,35,36,37,38};

/*	*********************************	RECEIVE DATA	*****************************	*/
uint8 rx_data1[D_COUNT] = {0};
uint8 rx_data2[D_COUNT] = {0};
uint8 rx_data3[D_COUNT] = {0};
uint8 rx_data4[D_COUNT] = {0};

uint8 *dptr=0;


/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

void main(void)
{
/* USER CODE BEGIN (3) */
    _enable_IRQ_interrupt_();														// Enable the Interrupts
    canInit();																		// Initialize the CAN module

    canEnableloopback(canREG1, Internal_Lbk);										// Enable the internal loopback mode for CAN1
    canEnableloopback(canREG2, Internal_Lbk);										// Enable the internal loopback mode for CAN2
    canEnableloopback(canREG3, Internal_Lbk);										// Enable the internal loopback mode for CAN3
    canEnableloopback(canREG4, Internal_Lbk);										// Enable the internal loopback mode for CAN4

    canEnableErrorNotification(canREG1);											// Enable Error Notification ISR for CAN1
	canEnableErrorNotification(canREG2);											// Enable Error Notification ISR for CAN2
    canEnableErrorNotification(canREG3);											// Enable Error Notification ISR for CAN3
	canEnableErrorNotification(canREG4);											// Enable Error Notification ISR for CAN4

    canTransmit(canREG1, canMESSAGE_BOX1, (const uint8 *) &tx_data1[0]);			// Transmit Data on MessageBox1 of CAN1
    canTransmit(canREG2, canMESSAGE_BOX1, (const uint8 *) &tx_data2[0]);			// Transmit Data on MessageBox1 of CAN1
    canTransmit(canREG3, canMESSAGE_BOX1, (const uint8 *) &tx_data3[0]);			// Transmit Data on MessageBox1 of CAN1
    canTransmit(canREG4, canMESSAGE_BOX1, (const uint8 *) &tx_data4[0]);			// Transmit Data on MessageBox1 of CAN1

    while(1){ };
/* USER CODE END */
}

/* USER CODE BEGIN (4) */
void canMessageNotification(canBASE_t *node, uint32 messageBox){					// The ISR is called when a Receive Interrupt occurs

     if(node==canREG1){																// If message is received on CAN1
         canGetData(canREG1, canMESSAGE_BOX2, (uint8 * )&rx_data1[0]);				// Save the received message
     }
     if(node==canREG2){																// If message is received on CAN1
         canGetData(canREG2, canMESSAGE_BOX2, (uint8 * )&rx_data2[0]);				// Save the received message
     }
     if(node==canREG3){																// If message is received on CAN1
         canGetData(canREG3, canMESSAGE_BOX2, (uint8 * )&rx_data3[0]);				// Save the received message
     }
     if(node==canREG4){																// If message is received on CAN1
         canGetData(canREG4, canMESSAGE_BOX2, (uint8 * )&rx_data4[0]);				// Save the received message
     }
}
/* USER CODE END */
