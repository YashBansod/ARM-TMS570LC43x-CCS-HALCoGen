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
#include "HL_esm.h"
#include "HL_adc.h"
#include "HL_sci.h"
#include "HL_gio.h"
/* USER CODE END */

/* Include Files */

#include "HL_sys_common.h"

/* USER CODE BEGIN (1) */
#define  TSIZE1 12
uint8  TEXT1[TSIZE1]= {'\r','|','\n','\t','C','H','.','I','D','=','0','x'};
#define  TSIZE2 9
uint8  TEXT2[TSIZE2]= {'\t','V','A','L','U','E','=','0','x'};

	adcData_t adc_data[2];
	uint32 ch_count=0;
	uint32 id    =0;
	uint32 value =0;
	uint32_t i;
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
void sciDisplayText(sciBASE_t *sci, uint8 *text, uint32 length);
void sciDisplayData(sciBASE_t *sci, uint8 *text,uint32 length);
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
	    gioInit();														// Initialize GIO
	    gioSetDirection(gioPORTB, 0x01);								// Set GIOB pin 0 (HW trigger source)
	    sciInit();														// Initialize SCI: 9600 baud, 8 bit length & 1 stop bit
	    adcInit();														// Initialize ADC: 12bit Resolution, Enable Channel Id in result
	    adcStartConversion(adcREG1,adcGROUP1);							// Start ADC conversion

	    while(1) 														// Infinite loop for contineous operation
	    {	gioSetBit(gioPORTB, 0, 1);									// Trigger using GIOB, Pin 0
	        while((adcIsConversionComplete(adcREG1,adcGROUP1))==0);		// Wait till conversion is complete
	        ch_count = adcGetData(adcREG1, adcGROUP1,&adc_data[0]);

	        /* 	conversion results :
	         	adc_data[0] -> should have conversions for Group1 Pin 0 (Channel 0)
	        	adc_data[1] -> should have conversions for Group1 Pin 1 (Channel 1)*/

	        id    = adc_data[0].id;
	        value = adc_data[0].value;

	        gioSetBit(gioPORTB, 0, 0);									// Clear GIOB, Pin 0 to remove trigger

	        sciDisplayText(sciREG1,&TEXT1[0],TSIZE1);   				// Send TEXT1
	        sciDisplayData(sciREG1,(uint8*)&id,4);						// Send DATA1
	        sciDisplayText(sciREG1,&TEXT2[0],TSIZE2);					// Send TEXT2
	        sciDisplayData(sciREG1,(uint8*)&value,4);					// Send DATA1

	        id    = adc_data[1].id;
	        value = adc_data[1].value;

	        sciDisplayText(sciREG1,&TEXT1[0],TSIZE1);					// Send TEXT1
	        sciDisplayData(sciREG1,(uint8*)&id,4);    					// Send DATA2
	        sciDisplayText(sciREG1,&TEXT2[0],TSIZE2);   				// Send TEXT2
	        sciDisplayData(sciREG1,(uint8*)&value,4);					// Send DATA2

	        for (i=0; i<2727273; i++);									// 100mS delay by wasting machine cycles
	    };

/* USER CODE END */
}


/* USER CODE BEGIN (4) */
void sciDisplayData(sciBASE_t *sci, uint8 *text,uint32 length)	// The code
{
    uint8 txt = 0;
    uint8 txt1 = 0;

#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
text = text + (length -1);
#endif

    while(length--)
    {
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
        txt = *text--;
#else
        txt = *text++;
#endif

        txt1 = txt;

        txt  &= ~(0xF0);
        txt1 &= ~(0x0F);
        txt1  =txt1>>4;

        if(txt<=0x9)
        {
            txt +=0x30;
        }
        else if(txt > 0x9 && txt <=0xF)
        {
            txt +=0x37;
        }
        else
        {
            txt = 0x30;
        }

        if(txt1 <= 0x9)
        {
            txt1 +=0x30;
        }
        else if((txt1 > 0x9) && (txt1 <= 0xF))
        {
            txt1 +=0x37;
        }
        else
        {
            txt1 = 0x30;
        }

        while ((sciREG1->FLR & 0x4) == 4); 								// Wait till transmission channel busy
        sciSendByte(sciREG1,txt1);      								// Send out the text
        while ((sciREG1->FLR & 0x4) == 4);								// Wait till transmission channel busy
        sciSendByte(sciREG1,txt);										// Send out the text
/* The purpose of that routine is to convert a number into an ASCII string that is put out the SCI one character at a time.
 * The function takes each byte of the number and converts it into a two ASCII characters.
 * The first call to sciSendByte() prints the character that represents the most significant nibble (4-bits) of the data byte.
 * The second call prints the least significant nibble. It takes two ASCII characters, each character is a byte, to represent one byte of data.*/
    };
}

void sciDisplayText(sciBASE_t *sci, uint8 *text,uint32 length)
{
    while(length--)
    {
        while ((sciREG1->FLR & 0x4) == 4); 								// Wait till transmission channel busy
        sciSendByte(sciREG1,*text++);									// Send out the text
    };
}
/* USER CODE END */
