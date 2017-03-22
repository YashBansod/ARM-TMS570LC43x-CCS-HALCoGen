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
#include "HL_esm.h"
#include "HL_sys_core.h"
/* USER CODE END */

/* Include Files */

#include "HL_sys_common.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */

/*	**************************	TRANSMIT MESSAGES	********************************	*/
#define F_SIZE 19
uint8_t tx_fault_message[F_SIZE] = {'\n','\r','I','N','V','A','L','I','D',' ','A','D','D','R','E','S','S','\n','\r'};
#define I_SIZE 16
uint8_t tx_init_message[I_SIZE] = {'\n','\r','I','N','I','T','I','A','L','I','Z','I','N','G','.','.'};
#define T_SIZE 16
uint8_t tx_trans_message[T_SIZE] = {'\n','\r','T','R','A','N','S','M','I','T',' ','M','O','D','E',':'};
#define R_SIZE 15
uint8_t tx_rec_message[R_SIZE] = {'\n','\r','R','E','C','E','I','V','E',' ','M','O','D','E',':'};
#define A_SIZE 17
uint8_t tx_addr_message[A_SIZE] = {'\n','\r','E','N','T','E','R',' ','A','D','D','R','E','S','S',':',' '};
#define D_SIZE 17
uint8_t tx_data_message[D_SIZE] = {'\n','\r','E','N','T','E','R',' ','M','E','S','S','A','G','E',':',' '};
#define B_SIZE 20
uint8_t tx_rec_data_message[B_SIZE] = {'\n','\r','R','E','C','E','I','V','E','D',' ','M','E','S','S','A','G','E',':',' '};

/*	**************************	RECEIVE MESSAGES	********************************	*/
#define AI_SIZE 4
uint8_t rx_addr[AI_SIZE] = {0};														// For Storing Address from UART
#define M_SIZE 8
uint8_t rx_data_message[M_SIZE] = {0};												// For Storing Message from UART
uint8 rx_can_data_message[M_SIZE] = {0};											// For Storing Message from CAN

/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
	/*	*********************************	CONFIGURATION	****************************************	*/
	_enable_IRQ_interrupt_();														// Enable Interrupts
	canInit();																		// Initialize the CAN Module
	sciInit();																		// Initialize the SCI (UART) Module
	canEnableErrorNotification(canREG1);											// Enable CAN error notification
	sciSend(sciREG1, I_SIZE, tx_init_message);										// Transmit INITIALIZATION MESSAGE

	while(1){
		/*	**************************************	TRANSMIT MODE	*****************************************	*/
		sciSend(sciREG1, T_SIZE, tx_trans_message);									// Transmit the TRANSMIT MODE message
		sciSend(sciREG1, A_SIZE, tx_addr_message);									// Prompt user for MESSAGE ADDRESS
		sciReceive(sciREG1, AI_SIZE, rx_addr);										// Receive the ADDRESS of the message
		sciSend(sciREG1, AI_SIZE, rx_addr);											// Echo back the ADDRESS back to the user

		if(rx_addr[3] == '1'){														// If the ADDRESS is valid
			sciSend(sciREG1, D_SIZE, tx_data_message);								// Prompt user for MESSAGE DATA
			sciReceive(sciREG1, M_SIZE, rx_data_message);							// Receive the DATA of the message
			sciSend(sciREG1, M_SIZE, rx_data_message);								// Echo back the DATA back to the user
			canTransmit(canREG1, canMESSAGE_BOX1, rx_data_message);					// Transmit the DATA on the appropriate canMessageBox
		}
		else if(rx_addr[3] == '3'){													// If the ADDRESS is valid
			sciSend(sciREG1, D_SIZE, tx_data_message);								// Prompt user for MESSAGE DATA
			sciReceive(sciREG1, M_SIZE, rx_data_message);							// Receive the DATA of the message
			sciSend(sciREG1, M_SIZE, rx_data_message);								// Echo back the DATA back to the user
			canTransmit(canREG1, canMESSAGE_BOX3, rx_data_message);					// Transmit the DATA on the appropriate canMessageBox
		}
		else
			sciSend(sciREG1, F_SIZE, tx_fault_message);								// Transmit a FAULT MESSAGE if address invalid
	};

/* USER CODE END */
}


/* USER CODE BEGIN (4) */
void canMessageNotification(canBASE_t *node, uint32 messageBox){					// The ISR is run when a Receive Interrupt occurs
	/*	**************************************	RECEIVE MODE	*****************************************	*/
	if(canIsRxMessageArrived(canREG1, canMESSAGE_BOX2)){							// If message received on appropriate canMessageBox
		canGetData(canREG1, canMESSAGE_BOX2, rx_can_data_message);					// Receive DATA from CAN and store it
		sciSend(sciREG1, R_SIZE, tx_rec_message);									// Transmit the RECEIVE MODE message
		sciSend(sciREG1, B_SIZE, tx_rec_data_message);								// Notify user that RECEIVED DATA is available
		sciSend(sciREG1, M_SIZE, rx_can_data_message);								// Transmit the DATA to the user
	}
}
/* USER CODE END */
