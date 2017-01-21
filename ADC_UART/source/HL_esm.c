/** @file HL_esm.c
*   @brief Esm Driver Source File
*   @date 05-Oct-2016
*   @version 04.06.00
*
*   This file contains:
*   - API Functions
*   .
*   which are relevant for the Esm driver.
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
/* USER CODE END */

/* Include Files */

#include "HL_esm.h"
#include "HL_sys_vim.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */


/** @fn void esmInit(void)
*   @brief Initializes Esm Driver
*
*   This function initializes the Esm driver.
*
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

void esmInit(void)
{
/* USER CODE BEGIN (3) */
/* USER CODE END */

    /** - Disable error pin channels */
    esmREG->DEPAPR1 = 0xFFFFFFFFU;
    esmREG->IEPCR4  = 0xFFFFFFFFU;
    esmREG->IEPCR7  = 0xFFFFFFFFU;

    /** - Disable interrupts */
    esmREG->IECR1   = 0xFFFFFFFFU;
    esmREG->IECR4   = 0xFFFFFFFFU;
    esmREG->IECR7   = 0xFFFFFFFFU;

    /** - Clear error status flags */
    esmREG->SR1[0U] = 0xFFFFFFFFU;
    esmREG->SR1[1U] = 0xFFFFFFFFU;
    esmREG->SSR2    = 0xFFFFFFFFU;
    esmREG->SR1[2U] = 0xFFFFFFFFU;

    esmREG->SR4[0U] = 0xFFFFFFFFU;

    esmREG->SR7[0U] = 0xFFFFFFFFU;

    /** - Setup LPC preload */
    esmREG->LTCPR = 16384U - 1U;

    /** - Reset error pin */
    if (esmREG->EPSR == 0U)
    {
        esmREG->EKR = 0x00000005U;
    }
    else
    {
        esmREG->EKR = 0x00000000U;
    }

    /** - Clear interrupt level */
    esmREG->ILCR1 = 0xFFFFFFFFU;
    esmREG->ILCR4 = 0xFFFFFFFFU;
    esmREG->ILCR7 = 0xFFFFFFFFU;

    /** - Set interrupt level */
    esmREG->ILSR1 = (uint32)((uint32)0U << 31U)
                  | (uint32)((uint32)0U << 30U)
                  | (uint32)((uint32)0U << 29U)
                  | (uint32)((uint32)0U << 28U)
                  | (uint32)((uint32)0U << 27U)
                  | (uint32)((uint32)0U << 26U)
                  | (uint32)((uint32)0U << 25U)
                  | (uint32)((uint32)0U << 24U)
                  | (uint32)((uint32)0U << 23U)
                  | (uint32)((uint32)0U << 22U)
                  | (uint32)((uint32)0U << 21U)
                  | (uint32)((uint32)0U << 20U)
                  | (uint32)((uint32)0U << 19U)
                  | (uint32)((uint32)0U << 18U)
                  | (uint32)((uint32)0U << 17U)
                  | (uint32)((uint32)0U << 16U)
                  | (uint32)((uint32)0U << 15U)
                  | (uint32)((uint32)0U << 14U)
                  | (uint32)((uint32)0U << 13U)
                  | (uint32)((uint32)0U << 12U)
                  | (uint32)((uint32)0U << 11U)
                  | (uint32)((uint32)0U << 10U)
                  | (uint32)((uint32)0U <<  9U)
                  | (uint32)((uint32)0U <<  8U)
                  | (uint32)((uint32)0U <<  7U)
                  | (uint32)((uint32)0U <<  6U)
                  | (uint32)((uint32)0U <<  5U)
                  | (uint32)((uint32)0U <<  4U)
                  | (uint32)((uint32)0U <<  3U)
                  | (uint32)((uint32)0U <<  2U)
                  | (uint32)((uint32)0U <<  1U)
                  | (uint32)((uint32)0U <<  0U);

    esmREG->ILSR4 = (uint32)((uint32)0U << 31U)
                  | (uint32)((uint32)0U << 30U)
                  | (uint32)((uint32)0U << 29U)
                  | (uint32)((uint32)0U << 28U)
                  | (uint32)((uint32)0U << 27U)
                  | (uint32)((uint32)0U << 26U)
                  | (uint32)((uint32)0U << 25U)
                  | (uint32)((uint32)0U << 24U)
                  | (uint32)((uint32)0U << 23U)
                  | (uint32)((uint32)0U << 22U)
                  | (uint32)((uint32)0U << 21U)
                  | (uint32)((uint32)0U << 20U)
                  | (uint32)((uint32)0U << 19U)
                  | (uint32)((uint32)0U << 18U)
                  | (uint32)((uint32)0U << 17U)
                  | (uint32)((uint32)0U << 16U)
                  | (uint32)((uint32)0U << 15U)
                  | (uint32)((uint32)0U << 14U)
                  | (uint32)((uint32)0U << 13U)
                  | (uint32)((uint32)0U << 12U)
                  | (uint32)((uint32)0U << 11U)
                  | (uint32)((uint32)0U << 10U)
                  | (uint32)((uint32)0U <<  9U)
                  | (uint32)((uint32)0U <<  8U)
                  | (uint32)((uint32)0U <<  7U)
                  | (uint32)((uint32)0U <<  6U)
                  | (uint32)((uint32)0U <<  5U)
                  | (uint32)((uint32)0U <<  4U)
                  | (uint32)((uint32)0U <<  3U)
                  | (uint32)((uint32)0U <<  2U)
                  | (uint32)((uint32)0U <<  1U)
                  | (uint32)((uint32)0U <<  0U);

    esmREG->ILSR7 = (uint32)((uint32)0U << 31U)
                  | (uint32)((uint32)0U << 30U)
                  | (uint32)((uint32)0U << 29U)
                  | (uint32)((uint32)0U << 28U)
                  | (uint32)((uint32)0U << 27U)
                  | (uint32)((uint32)0U << 26U)
                  | (uint32)((uint32)0U << 25U)
                  | (uint32)((uint32)0U << 24U)
                  | (uint32)((uint32)0U << 23U)
                  | (uint32)((uint32)0U << 22U)
                  | (uint32)((uint32)0U << 21U)
                  | (uint32)((uint32)0U << 20U)
                  | (uint32)((uint32)0U << 19U)
                  | (uint32)((uint32)0U << 18U)
                  | (uint32)((uint32)0U << 17U)
                  | (uint32)((uint32)0U << 16U)
                  | (uint32)((uint32)0U << 15U)
                  | (uint32)((uint32)0U << 14U)
                  | (uint32)((uint32)0U << 13U)
                  | (uint32)((uint32)0U << 12U)
                  | (uint32)((uint32)0U << 11U)
                  | (uint32)((uint32)0U << 10U)
                  | (uint32)((uint32)0U <<  9U)
                  | (uint32)((uint32)0U <<  8U)
                  | (uint32)((uint32)0U <<  7U)
                  | (uint32)((uint32)0U <<  6U)
                  | (uint32)((uint32)0U <<  5U)
                  | (uint32)((uint32)0U <<  4U)
                  | (uint32)((uint32)0U <<  3U)
                  | (uint32)((uint32)0U <<  2U)
                  | (uint32)((uint32)0U <<  1U)
                  | (uint32)((uint32)0U <<  0U);

    /** - Enable error pin channels */
    esmREG->EEPAPR1 = (uint32)((uint32)0U << 31U)
                    | (uint32)((uint32)0U << 30U)
                    | (uint32)((uint32)0U << 29U)
                    | (uint32)((uint32)0U << 28U)
                    | (uint32)((uint32)0U << 27U)
                    | (uint32)((uint32)0U << 26U)
                    | (uint32)((uint32)0U << 25U)
                    | (uint32)((uint32)0U << 24U)
                    | (uint32)((uint32)0U << 23U)
                    | (uint32)((uint32)0U << 22U)
                    | (uint32)((uint32)0U << 21U)
                    | (uint32)((uint32)0U << 20U)
                    | (uint32)((uint32)0U << 19U)
                    | (uint32)((uint32)0U << 18U)
                    | (uint32)((uint32)0U << 17U)
                    | (uint32)((uint32)0U << 16U)
                    | (uint32)((uint32)0U << 15U)
                    | (uint32)((uint32)0U << 14U)
                    | (uint32)((uint32)0U << 13U)
                    | (uint32)((uint32)0U << 12U)
                    | (uint32)((uint32)0U << 11U)
                    | (uint32)((uint32)0U << 10U)
                    | (uint32)((uint32)0U <<  9U)
                    | (uint32)((uint32)0U <<  8U)
                    | (uint32)((uint32)0U <<  7U)
                    | (uint32)((uint32)0U <<  6U)
                    | (uint32)((uint32)0U <<  5U)
                    | (uint32)((uint32)0U <<  4U)
                    | (uint32)((uint32)0U <<  3U)
                    | (uint32)((uint32)0U <<  2U)
                    | (uint32)((uint32)0U <<  1U)
                    | (uint32)((uint32)0U <<  0U);

    esmREG->IEPSR4 = (uint32)((uint32)0U << 31U)
                   | (uint32)((uint32)0U << 30U)
                   | (uint32)((uint32)0U << 29U)
                   | (uint32)((uint32)0U << 28U)
                   | (uint32)((uint32)0U << 27U)
                   | (uint32)((uint32)0U << 26U)
                   | (uint32)((uint32)0U << 25U)
                   | (uint32)((uint32)0U << 24U)
                   | (uint32)((uint32)0U << 23U)
                   | (uint32)((uint32)0U << 22U)
                   | (uint32)((uint32)0U << 21U)
                   | (uint32)((uint32)0U << 20U)
                   | (uint32)((uint32)0U << 19U)
                   | (uint32)((uint32)0U << 18U)
                   | (uint32)((uint32)0U << 17U)
                   | (uint32)((uint32)0U << 16U)
                   | (uint32)((uint32)0U << 15U)
                   | (uint32)((uint32)0U << 14U)
                   | (uint32)((uint32)0U << 13U)
                   | (uint32)((uint32)0U << 12U)
                   | (uint32)((uint32)0U << 11U)
                   | (uint32)((uint32)0U << 10U)
                   | (uint32)((uint32)0U <<  9U)
                   | (uint32)((uint32)0U <<  8U)
                   | (uint32)((uint32)0U <<  7U)
                   | (uint32)((uint32)0U <<  6U)
                   | (uint32)((uint32)0U <<  5U)
                   | (uint32)((uint32)0U <<  4U)
                   | (uint32)((uint32)0U <<  3U)
                   | (uint32)((uint32)0U <<  2U)
                   | (uint32)((uint32)0U <<  1U)
                   | (uint32)((uint32)0U <<  0U);

    esmREG->IEPSR7 = (uint32)((uint32)0U << 31U)
                   | (uint32)((uint32)0U << 30U)
                   | (uint32)((uint32)0U << 29U)
                   | (uint32)((uint32)0U << 28U)
                   | (uint32)((uint32)0U << 27U)
                   | (uint32)((uint32)0U << 26U)
                   | (uint32)((uint32)0U << 25U)
                   | (uint32)((uint32)0U << 24U)
                   | (uint32)((uint32)0U << 23U)
                   | (uint32)((uint32)0U << 22U)
                   | (uint32)((uint32)0U << 21U)
                   | (uint32)((uint32)0U << 20U)
                   | (uint32)((uint32)0U << 19U)
                   | (uint32)((uint32)0U << 18U)
                   | (uint32)((uint32)0U << 17U)
                   | (uint32)((uint32)0U << 16U)
                   | (uint32)((uint32)0U << 15U)
                   | (uint32)((uint32)0U << 14U)
                   | (uint32)((uint32)0U << 13U)
                   | (uint32)((uint32)0U << 12U)
                   | (uint32)((uint32)0U << 11U)
                   | (uint32)((uint32)0U << 10U)
                   | (uint32)((uint32)0U <<  9U)
                   | (uint32)((uint32)0U <<  8U)
                   | (uint32)((uint32)0U <<  7U)
                   | (uint32)((uint32)0U <<  6U)
                   | (uint32)((uint32)0U <<  5U)
                   | (uint32)((uint32)0U <<  4U)
                   | (uint32)((uint32)0U <<  3U)
                   | (uint32)((uint32)0U <<  2U)
                   | (uint32)((uint32)0U <<  1U)
                   | (uint32)((uint32)0U <<  0U);

    /** - Enable interrupts */
    esmREG->IESR1 = (uint32)((uint32)0U << 31U)
                  | (uint32)((uint32)0U << 30U)
                  | (uint32)((uint32)0U << 29U)
                  | (uint32)((uint32)0U << 28U)
                  | (uint32)((uint32)0U << 27U)
                  | (uint32)((uint32)0U << 26U)
                  | (uint32)((uint32)0U << 25U)
                  | (uint32)((uint32)0U << 24U)
                  | (uint32)((uint32)0U << 23U)
                  | (uint32)((uint32)0U << 22U)
                  | (uint32)((uint32)0U << 21U)
                  | (uint32)((uint32)0U << 20U)
                  | (uint32)((uint32)0U << 19U)
                  | (uint32)((uint32)0U << 18U)
                  | (uint32)((uint32)0U << 17U)
                  | (uint32)((uint32)0U << 16U)
                  | (uint32)((uint32)0U << 15U)
                  | (uint32)((uint32)0U << 14U)
                  | (uint32)((uint32)0U << 13U)
                  | (uint32)((uint32)0U << 12U)
                  | (uint32)((uint32)0U << 11U)
                  | (uint32)((uint32)0U << 10U)
                  | (uint32)((uint32)0U <<  9U)
                  | (uint32)((uint32)0U <<  8U)
                  | (uint32)((uint32)0U <<  7U)
                  | (uint32)((uint32)0U <<  6U)
                  | (uint32)((uint32)0U <<  5U)
                  | (uint32)((uint32)0U <<  4U)
                  | (uint32)((uint32)0U <<  3U)
                  | (uint32)((uint32)0U <<  2U)
                  | (uint32)((uint32)0U <<  1U)
                  | (uint32)((uint32)0U <<  0U);

    esmREG->IESR4 = (uint32)((uint32)0U << 31U)
                  | (uint32)((uint32)0U << 30U)
                  | (uint32)((uint32)0U << 29U)
                  | (uint32)((uint32)0U << 28U)
                  | (uint32)((uint32)0U << 27U)
                  | (uint32)((uint32)0U << 26U)
                  | (uint32)((uint32)0U << 25U)
                  | (uint32)((uint32)0U << 24U)
                  | (uint32)((uint32)0U << 23U)
                  | (uint32)((uint32)0U << 22U)
                  | (uint32)((uint32)0U << 21U)
                  | (uint32)((uint32)0U << 20U)
                  | (uint32)((uint32)0U << 19U)
                  | (uint32)((uint32)0U << 18U)
                  | (uint32)((uint32)0U << 17U)
                  | (uint32)((uint32)0U << 16U)
                  | (uint32)((uint32)0U << 15U)
                  | (uint32)((uint32)0U << 14U)
                  | (uint32)((uint32)0U << 13U)
                  | (uint32)((uint32)0U << 12U)
                  | (uint32)((uint32)0U << 11U)
                  | (uint32)((uint32)0U << 10U)
                  | (uint32)((uint32)0U <<  9U)
                  | (uint32)((uint32)0U <<  8U)
                  | (uint32)((uint32)0U <<  7U)
                  | (uint32)((uint32)0U <<  6U)
                  | (uint32)((uint32)0U <<  5U)
                  | (uint32)((uint32)0U <<  4U)
                  | (uint32)((uint32)0U <<  3U)
                  | (uint32)((uint32)0U <<  2U)
                  | (uint32)((uint32)0U <<  1U)
                  | (uint32)((uint32)0U <<  0U);

    esmREG->IESR7 = (uint32)((uint32)0U << 31U)
                  | (uint32)((uint32)0U << 30U)
                  | (uint32)((uint32)0U << 29U)
                  | (uint32)((uint32)0U << 28U)
                  | (uint32)((uint32)0U << 27U)
                  | (uint32)((uint32)0U << 26U)
                  | (uint32)((uint32)0U << 25U)
                  | (uint32)((uint32)0U << 24U)
                  | (uint32)((uint32)0U << 23U)
                  | (uint32)((uint32)0U << 22U)
                  | (uint32)((uint32)0U << 21U)
                  | (uint32)((uint32)0U << 20U)
                  | (uint32)((uint32)0U << 19U)
                  | (uint32)((uint32)0U << 18U)
                  | (uint32)((uint32)0U << 17U)
                  | (uint32)((uint32)0U << 16U)
                  | (uint32)((uint32)0U << 15U)
                  | (uint32)((uint32)0U << 14U)
                  | (uint32)((uint32)0U << 13U)
                  | (uint32)((uint32)0U << 12U)
                  | (uint32)((uint32)0U << 11U)
                  | (uint32)((uint32)0U << 10U)
                  | (uint32)((uint32)0U <<  9U)
                  | (uint32)((uint32)0U <<  8U)
                  | (uint32)((uint32)0U <<  7U)
                  | (uint32)((uint32)0U <<  6U)
                  | (uint32)((uint32)0U <<  5U)
                  | (uint32)((uint32)0U <<  4U)
                  | (uint32)((uint32)0U <<  3U)
                  | (uint32)((uint32)0U <<  2U)
                  | (uint32)((uint32)0U <<  1U)
                  | (uint32)((uint32)0U <<  0U);

/* USER CODE BEGIN (4) */
/* USER CODE END */
}

/** @fn uint32 esmError(void)
*   @brief Return Error status
*
*   @return The error status
*
*   Returns the error status.
*/
uint32 esmError(void)
{
    uint32 status;

/* USER CODE BEGIN (5) */
/* USER CODE END */

    status = esmREG->EPSR;

/* USER CODE BEGIN (6) */
/* USER CODE END */

    return status;
}


/** @fn void esmEnableError(uint64 channels)
*   @brief Enable Group 1 Channels Error Signals propagation for channels 0-63
*
*   @param[in] channels - Channel mask
*
*   Enable Group 1 Channels Error Signals propagation to the error pin.
*/
void esmEnableError(uint64 channels)
{
/* USER CODE BEGIN (7) */
/* USER CODE END */

    esmREG->IEPSR4 = (uint32)((channels >> 32U) & 0xFFFFFFFFU);
    esmREG->EEPAPR1 = (uint32)(channels & 0xFFFFFFFFU);

/* USER CODE BEGIN (8) */
/* USER CODE END */
}

/** @fn void esmEnableError(uint64 channels)
*   @brief Enable Group 1 Channels Error Signals propagation for channels 64-95
*
*   @param[in] channels - Channel mask
*
*   Enable Group 1 Channels Error Signals propagation to the error pin.
*/
void esmEnableErrorUpper(uint64 channels)
{
/* USER CODE BEGIN (9) */
/* USER CODE END */

    esmREG->IEPSR7  = (uint32)(channels & 0xFFFFFFFFU);

/* USER CODE BEGIN (10) */
/* USER CODE END */
}
/** @fn void esmDisableError(uint64 channels)
*   @brief Disable Group 1 Channels Error Signals propagation
*
*   @param[in] channels - Channel mask
*
*   Disable Group 1 Channels Error Signals propagation to the error pin.
*/
void esmDisableError(uint64 channels)
{
/* USER CODE BEGIN (11) */
/* USER CODE END */

    esmREG->IEPCR4 = (uint32)((channels >> 32U) & 0xFFFFFFFFU);
    esmREG->DEPAPR1 = (uint32)(channels & 0xFFFFFFFFU);

/* USER CODE BEGIN (12) */
/* USER CODE END */
}

/** @fn void esmDisableError(uint64 channels)
*   @brief Disable Group 1 Channels Error Signals propagation for channels 0-63
*
*   @param[in] channels - Channel mask
*
*   Disable Group 1 Channels Error Signals propagation to the error pin.
*/
void esmDisableErrorUpper(uint64 channels)
{
/* USER CODE BEGIN (13) */
/* USER CODE END */

    esmREG->IEPCR7 = (uint32)(channels & 0xFFFFFFFFU);

/* USER CODE BEGIN (14) */
/* USER CODE END */
}
/** @fn void esmTriggerErrorPinReset(void)
*   @brief Trigger error pin reset and switch back to normal operation
*
*   Trigger error pin reset and switch back to normal operation.
*/
void esmTriggerErrorPinReset(void)
{
/* USER CODE BEGIN (15) */
/* USER CODE END */

    esmREG->EKR = 5U;

/* USER CODE BEGIN (16) */
/* USER CODE END */
}


/** @fn void esmActivateNormalOperation(void)
*   @brief Activate normal operation
*
*   Activates normal operation mode.
*/
void esmActivateNormalOperation(void)
{
/* USER CODE BEGIN (17) */
/* USER CODE END */

    esmREG->EKR = 0U;

/* USER CODE BEGIN (18) */
/* USER CODE END */
}


/** @fn void esmEnableInterrupt(uint64 channels)
*   @brief Enable Group 1 Channels Interrupts for channels 0-63
*
*   @param[in] channels - Channel mask
*
*   Enable Group 1 Channels Interrupts.
*/
void esmEnableInterrupt(uint64 channels)
{
/* USER CODE BEGIN (19) */
/* USER CODE END */

    esmREG->IESR4 = (uint32)((channels >> 32U) & 0xFFFFFFFFU);
    esmREG->IESR1 = (uint32)(channels & 0xFFFFFFFFU);

/* USER CODE BEGIN (20) */
/* USER CODE END */
}

/** @fn void esmEnableInterrupt(uint64 channels)
*   @brief Enable Group 1 Channels Interrupts for channels 64-95
*
*   @param[in] channels - Channel mask
*
*   Enable Group 1 Channels Interrupts.
*/
void esmEnableInterruptUpper(uint64 channels)
{
/* USER CODE BEGIN (21) */
/* USER CODE END */

    esmREG->IESR7 = (uint32)(channels & 0xFFFFFFFFU);

/* USER CODE BEGIN (22) */
/* USER CODE END */
}
/** @fn void esmDisableInterrupt(uint32 channels)
*   @brief Disable Group 1 Channels Interrupts for channels 0-63
*
*   @param[in] channels - Channel mask
*
*   Disable Group 1 Channels Interrupts.
*/
void esmDisableInterrupt(uint64 channels)
{
/* USER CODE BEGIN (23) */
/* USER CODE END */

    esmREG->IECR4 = (uint32)((channels >> 32U) & 0xFFFFFFFFU);
    esmREG->IECR1 = (uint32)(channels & 0xFFFFFFFFU);

/* USER CODE BEGIN (24) */
/* USER CODE END */
}

/** @fn void esmDisableInterrupt(uint64 channels)
*   @brief Disable Group 1 Channels Interrupts for channels 64-95
*
*   @param[in] channels - Channel mask
*
*   Disable Group 1 Channels Interrupts.
*/
void esmDisableInterruptUpper(uint64 channels)
{
/* USER CODE BEGIN (25) */
/* USER CODE END */

    esmREG->IECR7 = (uint32)(channels & 0xFFFFFFFFU);

/* USER CODE BEGIN (26) */
/* USER CODE END */
}
/** @fn void esmSetInterruptLevel(uint64 channels, uint64 flags)
*   @brief Set Group 1 Channels Interrupt Levels for channels 0-63
*
*   @param[in] channels - Channel mask
*   @param[in] flags - Level mask: - 0: Low priority interrupt
*                                  - 1: High priority interrupt
*
*   Set Group 1 Channels Interrupts levels.
*/
void esmSetInterruptLevel(uint64 channels, uint64 flags)
{
/* USER CODE BEGIN (27) */
/* USER CODE END */

    esmREG->ILCR4 = (uint32)(((channels & (~flags)) >> 32U) & 0xFFFFFFFFU);
    esmREG->ILSR4 = (uint32)(((channels & flags) >> 32U) & 0xFFFFFFFFU);
    esmREG->ILCR1 = (uint32)((channels & (~flags)) & 0xFFFFFFFFU);
    esmREG->ILSR1 = (uint32)((channels & flags) & 0xFFFFFFFFU);

/* USER CODE BEGIN (28) */
/* USER CODE END */
}

/** @fn void esmSetInterruptLevel(uint64 channels, uint64 flags)
*   @brief Set Group 1 Channels Interrupt Levels for channels 64-95
*
*   @param[in] channels - Channel mask
*   @param[in] flags - Level mask: - 0: Low priority interrupt
*                                  - 1: High priority interrupt
*
*   Set Group 1 Channels Interrupts levels.
*/
void esmSetInterruptLevelUpper(uint64 channels, uint64 flags)
{
/* USER CODE BEGIN (29) */
/* USER CODE END */

    esmREG->ILCR7 = (uint32)((channels & (~flags)) & 0xFFFFFFFFU);
    esmREG->ILSR7 = (uint32)((channels & flags) & 0xFFFFFFFFU);

/* USER CODE BEGIN (30) */
/* USER CODE END */
}


/** @fn void esmClearStatus(uint32 group, uint32 channels)
*   @brief Clear Group error status
*
*   @param[in] group    - Error group
*   @param[in] channels - Channel mask
*
*   Clear Group error status.
*/
void esmClearStatus(uint32 group, uint64 channels)
{
/* USER CODE BEGIN (31) */
/* USER CODE END */

    esmREG->SR1[group] = (uint32)(channels & 0xFFFFFFFFU);
	if(group == 0U)
	{
	    esmREG->SR4[group] = (uint32)((channels >> 32U) & 0xFFFFFFFFU);
	}

/* USER CODE BEGIN (32) */
/* USER CODE END */
}

/** @fn void esmClearStatusUpper(uint32 group, uint64 channels)
*   @brief Clear Group error status for channels 64-95
*
*   @param[in] group    - Error group
*   @param[in] channels - Channel mask
*
*   Clear Group error status.
*/
void esmClearStatusUpper(uint32 group, uint64 channels)
{
/* USER CODE BEGIN (33) */
/* USER CODE END */

    esmREG->SR7[group] = (uint32)(channels & 0xFFFFFFFFU);

/* USER CODE BEGIN (34) */
/* USER CODE END */
}
/** @fn void esmClearStatusBuffer(uint32 channels)
*   @brief Clear Group 2 error status buffer
*
*   @param[in] channels - Channel mask
*
*   Clear Group 2 error status buffer.
*/
void esmClearStatusBuffer(uint32 channels)
{
/* USER CODE BEGIN (35) */
/* USER CODE END */

    esmREG->SSR2 = channels;

/* USER CODE BEGIN (36) */
/* USER CODE END */
}


/** @fn void esmSetCounterPreloadValue(uint32 value)
*   @brief Set counter preload value
*
*   @param[in] value - Counter preload value
*
*   Set counter preload value.
*/
void esmSetCounterPreloadValue(uint32 value)
{
/* USER CODE BEGIN (37) */
/* USER CODE END */

    esmREG->LTCPR = value & 0xC000U;

/* USER CODE BEGIN (38) */
/* USER CODE END */
}


/** @fn uint64 esmGetStatus(uint32 group, uint64 channels)
*   @brief Return Error status
*
*   @param[in] group   - Error group
*   @param[in] channels - Error Channels
*
*   @return The channels status of selected group (Channels from 0-63)
*
*   Returns the channels status of selected group.
*/
uint64 esmGetStatus(uint32 group, uint64 channels)
{
    uint64 status;
	uint32 ESM_ESTATUS4, ESM_ESTATUS1;
	if(group == 0U)
	{
		ESM_ESTATUS4 = esmREG->SR4[group];
	}
	else
	{
		ESM_ESTATUS4 = 0U;
	}
	ESM_ESTATUS1 = esmREG->SR1[group];


/* USER CODE BEGIN (39) */
/* USER CODE END */
    /*SAFETYMCUSW 51 S MR:12.3 <APPROVED> "Needs shifting for 64-bit value" */
     status = ((((uint64)ESM_ESTATUS4) << 32U) | (uint64)ESM_ESTATUS1) & channels;

/* USER CODE BEGIN (40) */
/* USER CODE END */

    return status;
}

/** @fn uint64 esmGetStatusUpper(uint32 group, uint64 channels)
*   @brief Return Error status
*
*   @param[in] group   - Error group
*   @param[in] channels - Error Channels
*
*   @return The channels status of selected group (Channels from 64-95)
*
*   Returns the channels status of selected group.
*/
uint64 esmGetStatusUpper(uint32 group, uint64 channels)
{
    uint64 status;
    uint32 ESM_ESTATUS7 = esmREG->SR7[group];


/* USER CODE BEGIN (41) */
/* USER CODE END */
    /*SAFETYMCUSW 51 S MR:12.3 <APPROVED> "Needs shifting for 64-bit value" */
     status = ((uint64)ESM_ESTATUS7) & channels;

/* USER CODE BEGIN (42) */
/* USER CODE END */

    return status;
}

/** @fn uint64 esmGetStatusBuffer(uint64 channels)
*   @brief Return Group 2 channel x Error status buffer
*
*   @param[in] channels - Error Channels
*
*   @return The channels status
*
*   Returns the group 2 buffered status of selected channels.
*/
uint32 esmGetStatusBuffer(uint32 channels)
{
    uint32 status;

/* USER CODE BEGIN (43) */
/* USER CODE END */
    status = esmREG->SSR2 & channels;

/* USER CODE BEGIN (44) */
/* USER CODE END */

    return status;
}

/** @fn esmSelfTestFlag_t esmEnterSelfTest(void)
*   @brief Return ESM Self test status
*
*   @return ESM Self test status
*
*   Returns the ESM Self test status.
*/
esmSelfTestFlag_t esmEnterSelfTest(void)
{
    esmSelfTestFlag_t status;

/* USER CODE BEGIN (45) */
/* USER CODE END */

    uint32 errPinStat = esmREG->EPSR & 0x1U;
    uint32 esmKeyReg  = esmREG->EKR;
    if((errPinStat == 0x0U) && (esmKeyReg == 0x0U))
    {
      status = esmSelfTest_NotStarted;
    }
    else
    {
      esmREG->EKR = 0xAU;
      status = esmSelfTest_Active;
      if((esmREG->EPSR & 0x1U) != 0x0U)
      {
        status = esmSelfTest_Failed;
      }
      esmREG->EKR = 0x5U;
    }

/* USER CODE BEGIN (46) */
/* USER CODE END */

    return status;
}

/** @fn esmSelfTestFlag_t esmSelfTestStatus(void)
*   @brief Return ESM Self test status
*
*   Returns the ESM Self test status.
*/
esmSelfTestFlag_t esmSelfTestStatus(void)
{
    esmSelfTestFlag_t status;

/* USER CODE BEGIN (47) */
/* USER CODE END */

    if((esmREG->EPSR & 0x1U) == 0x0U)
    {
      if(esmREG->EKR == 0x5U)
      {
        status = esmSelfTest_Active;
      }
      else
      {
        status = esmSelfTest_Failed;
      }
    }
    else
    {
        status = esmSelfTest_Passed;
    }

/* USER CODE BEGIN (48) */
/* USER CODE END */

    return status;
}

/** @fn void esmGetConfigValue(esm_config_reg_t *config_reg, config_value_type_t type)
*   @brief Get the initial or current values of the configuration registers
*
*   @param[in] *config_reg: pointer to the struct to which the initial or current
*                           value of the configuration registers need to be stored
*   @param[in] type:    whether initial or current value of the configuration registers need to be stored
*                       - InitialValue: initial value of the configuration registers will be stored
*                                       in the struct pointed by config_reg
*                       - CurrentValue: initial value of the configuration registers will be stored
*                                       in the struct pointed by config_reg
*
*   This function will copy the initial or current value (depending on the parameter 'type')
*   of the configuration registers to the struct pointed by config_reg
*
*/

void esmGetConfigValue(esm_config_reg_t *config_reg, config_value_type_t type)
{
    if (type == InitialValue)
    {
        config_reg->CONFIG_EEPAPR1 = ESM_EEPAPR1_CONFIGVALUE;
        config_reg->CONFIG_IESR1 = ESM_IESR1_CONFIGVALUE;
        config_reg->CONFIG_ILSR1 = ESM_ILSR1_CONFIGVALUE;
        config_reg->CONFIG_LTCPR = ESM_LTCPR_CONFIGVALUE;
        config_reg->CONFIG_EKR = ESM_EKR_CONFIGVALUE;
        config_reg->CONFIG_IEPSR4 = ESM_IEPSR4_CONFIGVALUE;
        config_reg->CONFIG_IESR4 = ESM_IESR4_CONFIGVALUE;
        config_reg->CONFIG_ILSR4 = ESM_ILSR4_CONFIGVALUE;
        config_reg->CONFIG_IEPSR7 = ESM_IEPSR4_CONFIGVALUE;
        config_reg->CONFIG_IESR7 = ESM_IESR4_CONFIGVALUE;
        config_reg->CONFIG_ILSR7 = ESM_ILSR4_CONFIGVALUE;
    }
    else
    {
    /*SAFETYMCUSW 134 S MR:12.2 <APPROVED> "Register read back support" */
        config_reg->CONFIG_EEPAPR1 = esmREG->EEPAPR1;
        config_reg->CONFIG_IESR1 = esmREG->IESR1;
        config_reg->CONFIG_ILSR1 = esmREG->ILSR1;
        config_reg->CONFIG_LTCPR = esmREG->LTCPR;
        config_reg->CONFIG_EKR = esmREG->EKR;
        config_reg->CONFIG_IEPSR4 = esmREG->IEPSR4;
        config_reg->CONFIG_IESR4 = esmREG->IESR4;
        config_reg->CONFIG_ILSR4 = esmREG->ILSR4;
        config_reg->CONFIG_IEPSR7 = esmREG->IEPSR7;
        config_reg->CONFIG_IESR7 = esmREG->IESR7;
        config_reg->CONFIG_ILSR7 = esmREG->ILSR7;
    }
}

/* USER CODE BEGIN (49) */
/* USER CODE END */

/** @fn void esmHighInterrupt(void)
*   @brief High Level Interrupt for ESM
*/
#pragma CODE_STATE(esmHighInterrupt, 32)
#pragma INTERRUPT(esmHighInterrupt, FIQ)

void esmHighInterrupt(void)
{
    /* Note : Group 1 Error           */
    /*   1 to  32 -> channel 0  to 31 */
    /*  65 to  96 -> channel 32 to 63 */
    /* 129 to 160 -> channel 64 to 95 */
    /* Note : Group 2 Error           */
    /*  33 to  64 -> channel 0  to 31 */

    uint32 vec = esmREG->IOFFHR - 1U;

/* USER CODE BEGIN (50) */
/* USER CODE END */

    if (vec < 32U)
    {
        esmREG->SR1[0U] = (uint32)1U << vec;
        esmGroup1Notification(esmREG,(vec));
    }
    else if (vec < 64U)
    {
        esmREG->SR1[1U] = (uint32)1U << (vec-32U);
        esmGroup2Notification(esmREG,(vec-32U));
    }
    else if (vec < 96U)
    {
        esmREG->SR4[0U] = (uint32)1U << (vec-64U);
        esmGroup1Notification(esmREG,(vec-32U));
    }
    else if ((vec >= 128U) && (vec < 160U))
    {
        esmREG->SR7[0U] = (uint32)1U << (vec-128U);
        esmGroup1Notification(esmREG,(vec-96U));
    }
    else
    {
        esmREG->SR7[0U] = 0xFFFFFFFFU;
        esmREG->SR4[0U] = 0xFFFFFFFFU;
        esmREG->SR1[1U] = 0xFFFFFFFFU;
        esmREG->SR1[0U] = 0xFFFFFFFFU;
    }

/* USER CODE BEGIN (51) */
/* USER CODE END */
}


/* USER CODE BEGIN (55) */
/* USER CODE END */
