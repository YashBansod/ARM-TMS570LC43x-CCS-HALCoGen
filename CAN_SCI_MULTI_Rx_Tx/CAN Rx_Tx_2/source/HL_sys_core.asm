;-------------------------------------------------------------------------------
; HL_sys_core.asm
;
; Copyright (C) 2009-2016 Texas Instruments Incorporated - www.ti.com
;
;
;  Redistribution and use in source and binary forms, with or without
;  modification, are permitted provided that the following conditions
;  are met:
;
;    Redistributions of source code must retain the above copyright
;    notice, this list of conditions and the following disclaimer.
;
;    Redistributions in binary form must reproduce the above copyright
;    notice, this list of conditions and the following disclaimer in the
;    documentation and/or other materials provided with the
;    distribution.
;
;    Neither the name of Texas Instruments Incorporated nor the names of
;    its contributors may be used to endorse or promote products derived
;    from this software without specific prior written permission.
;
;  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
;  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
;  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
;  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
;  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
;  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
;  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
;  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
;  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
;  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
;  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;
;
;

    .text
    .arm

;-------------------------------------------------------------------------------
; Initialize CPU Registers

    .def     _coreInitRegisters_
    .asmfunc


_coreInitRegisters_

    ; After reset, the CPU is in the Supervisor mode (M = 10011)
        mov r0, lr
        mov r1, #0x0000
        mov r2, #0x0000
        mov r3, #0x0000
        mov r4, #0x0000
        mov r5, #0x0000
        mov r6, #0x0000
        mov r7, #0x0000
        mov r8, #0x0000
        mov r9, #0x0000
        mov r10, #0x0000
        mov r11, #0x0000
        mov r12, #0x0000
        mov r13, #0x0000
        mrs r1, cpsr
        msr spsr_cxsf, r1
        ; Switch to FIQ mode (M = 10001)
        cps #17
        mov lr, r0
        mov r8, #0x0000
        mov r9, #0x0000
        mov r10, #0x0000
        mov r11, #0x0000
        mov r12, #0x0000
        mrs r1, cpsr
        msr spsr_cxsf, r1
        ; Switch to IRQ mode (M = 10010)
        cps #18
        mov lr, r0
        mrs r1,cpsr
        msr spsr_cxsf, r1
        ; Switch to Abort mode (M = 10111)
        cps #23
        mov lr, r0
        mrs r1,cpsr
        msr spsr_cxsf, r1
        ; Switch to Undefined Instruction Mode (M = 11011)
        cps #27
        mov lr, r0
        mrs r1,cpsr
        msr spsr_cxsf, r1
        ; Switch to System Mode ( Shares User Mode registers ) (M = 11111)
        cps #31
        mov lr, r0
        mrs r1,cpsr
        msr spsr_cxsf, r1


        mrc   p15,     #0x00,      r2,       c1, c0, #0x02
        orr   r2,      r2,         #0xF00000
        mcr   p15,     #0x00,      r2,       c1, c0, #0x02
        mov   r2,      #0x40000000
        fmxr  fpexc,   r2

        fmdrr d0,         r1,     r1
        fmdrr d1,         r1,     r1
        fmdrr d2,         r1,     r1
        fmdrr d3,         r1,     r1
        fmdrr d4,         r1,     r1
        fmdrr d5,         r1,     r1
        fmdrr d6,         r1,     r1
        fmdrr d7,         r1,     r1
        fmdrr d8,         r1,     r1
        fmdrr d9,         r1,     r1
        fmdrr d10,        r1,     r1
        fmdrr d11,        r1,     r1
        fmdrr d12,        r1,     r1
        fmdrr d13,        r1,     r1
        fmdrr d14,        r1,     r1
        fmdrr d15,        r1,     r1
        bl    next1
next1
        bl    next2
next2
        bl    next3
next3
        bl    next4
next4
        bx    r0

    .endasmfunc


;-------------------------------------------------------------------------------
; Initialize Stack Pointers

    .def     _coreInitStackPointer_
    .asmfunc

_coreInitStackPointer_

        cps   #17
        ldr   sp,       fiqSp
        cps   #18
        ldr   sp,       irqSp
        cps   #19
        ldr   sp,       svcSp
        cps   #23
        ldr   sp,       abortSp
        cps   #27
        ldr   sp,       undefSp
        cps   #31
        ldr   sp,       userSp
        bx    lr

userSp  .word 0x08000000+0x00001000
svcSp   .word 0x08000000+0x00001000+0x00000100
fiqSp   .word 0x08000000+0x00001000+0x00000100+0x00000100
irqSp   .word 0x08000000+0x00001000+0x00000100+0x00000100+0x00000100
abortSp .word 0x08000000+0x00001000+0x00000100+0x00000100+0x00000100+0x00000100
undefSp .word 0x08000000+0x00001000+0x00000100+0x00000100+0x00000100+0x00000100+0x00000100

    .endasmfunc

;-------------------------------------------------------------------------------
; Get CPSR Value

    .def     _getCPSRValue_
    .asmfunc

_getCPSRValue_

        mrs   r0, CPSR
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Take CPU to IDLE state

    .def     _gotoCPUIdle_
    .asmfunc

_gotoCPUIdle_

        WFI
        nop
        nop
        nop
        nop
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Enable VFP Unit

    .def     _coreEnableVfp_
    .asmfunc

_coreEnableVfp_

        mrc   p15,     #0x00,      r0,       c1, c0, #0x02
        orr   r0,      r0,         #0xF00000
        mcr   p15,     #0x00,      r0,       c1, c0, #0x02
        mov   r0,      #0x40000000
        fmxr  fpexc,   r0
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Enable Event Bus Export

    .def     _coreEnableEventBusExport_
    .asmfunc

_coreEnableEventBusExport_

        mrc   p15, #0x00, r0,         c9, c12, #0x00
        orr   r0,  r0,    #0x10
        mcr   p15, #0x00, r0,         c9, c12, #0x00
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Disable Event Bus Export

    .def     _coreDisableEventBusExport_
    .asmfunc

_coreDisableEventBusExport_

        mrc   p15, #0x00, r0,         c9, c12, #0x00
        bic   r0,  r0,    #0x10
        mcr   p15, #0x00, r0,         c9, c12, #0x00
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Enable Offset via Vic controller

    .def     _coreEnableIrqVicOffset_
    .asmfunc

_coreEnableIrqVicOffset_

        mrc   p15, #0, r0,         c1, c0,  #0
        orr   r0,  r0,    #0x01000000
        mcr   p15, #0, r0,         c1, c0,  #0
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Get data fault status register

    .def     _coreGetDataFault_
    .asmfunc

_coreGetDataFault_

        mrc   p15, #0, r0, c5, c0,  #0
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Clear data fault status register

    .def     _coreClearDataFault_
    .asmfunc

_coreClearDataFault_

        mov   r0,  #0
        mcr   p15, #0, r0, c5, c0,  #0
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Get instruction fault status register

    .def     _coreGetInstructionFault_
    .asmfunc

_coreGetInstructionFault_

        mrc   p15, #0, r0, c5, c0, #1
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Clear instruction fault status register

    .def     _coreClearInstructionFault_
    .asmfunc

_coreClearInstructionFault_

        mov   r0,  #0
        mcr   p15, #0, r0, c5, c0, #1
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Get data fault address register

    .def     _coreGetDataFaultAddress_
    .asmfunc

_coreGetDataFaultAddress_

        mrc   p15, #0, r0, c6, c0,  #0
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Clear data fault address register

    .def     _coreClearDataFaultAddress_
    .asmfunc

_coreClearDataFaultAddress_

        mov   r0,  #0
        mcr   p15, #0, r0, c6, c0,  #0
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Get instruction fault address register

    .def     _coreGetInstructionFaultAddress_
    .asmfunc

_coreGetInstructionFaultAddress_

        mrc   p15, #0, r0, c6, c0, #2
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Clear instruction fault address register

    .def     _coreClearInstructionFaultAddress_
    .asmfunc

_coreClearInstructionFaultAddress_

        mov   r0,  #0
        mcr   p15, #0, r0, c6, c0, #2
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Get auxiliary data fault status register

    .def     _coreGetAuxiliaryDataFault_
    .asmfunc

_coreGetAuxiliaryDataFault_

        mrc   p15, #0, r0, c5, c1, #0
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Clear auxiliary data fault status register

    .def     _coreClearAuxiliaryDataFault_
    .asmfunc

_coreClearAuxiliaryDataFault_

        mov   r0,  #0
        mcr   p15, #0, r0, c5, c1, #0
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Get auxiliary instruction fault status register

    .def     _coreGetAuxiliaryInstructionFault_
    .asmfunc

_coreGetAuxiliaryInstructionFault_

        mrc   p15, #0, r0, c5, c1, #1
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Clear auxiliary instruction fault status register

    .def     _coreClearAuxiliaryInstructionFault_
    .asmfunc

_coreClearAuxiliaryInstructionFault_

        mov   r0,  #0
        mrc   p15, #0, r0, c5, c1, #1
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Disable IRQ interrupt

        .def _disable_IRQ_interrupt_
        .asmfunc

_disable_IRQ_interrupt_

        cpsid i
        bx    lr

        .endasmfunc

;-------------------------------------------------------------------------------
; Enable interrupts - CPU IRQ

       .def _enable_IRQ_interrupt_
       .asmfunc

_enable_IRQ_interrupt_

        cpsie i
        bx    lr

        .endasmfunc
;-------------------------------------------------------------------------------
; Enable interrupts - CPU IRQ & FIQ

       .def _enable_interrupt_
       .asmfunc

_enable_interrupt_

        cpsie if
        bx    lr

        .endasmfunc

;-------------------------------------------------------------------------------
; Clear ESM CCM errorss

       .def _esmCcmErrorsClear_
       .asmfunc

_esmCcmErrorsClear_

        stmfd sp!, {r0-r2}
        ldr   r0, ESMSR1_REG    ; load the ESMSR1 status register address
        ldr   r2, ESMSR1_ERR_CLR
        str   r2, [r0]         ; clear the ESMSR1 register

        ldr   r0, ESMSR2_REG    ; load the ESMSR2 status register address
        ldr   r2, ESMSR2_ERR_CLR
        str   r2, [r0]         ; clear the ESMSR2 register

        ldr   r0, ESMSSR2_REG    ; load the ESMSSR2 status register address
        ldr   r2, ESMSSR2_ERR_CLR
        str   r2, [r0]             ; clear the ESMSSR2 register

        ldr   r0, ESMKEY_REG    ; load the ESMKEY register address
        mov   r2, #0x5             ; load R2 with 0x5
        str   r2, [r0]             ; clear the ESMKEY register

        ldr   r0, VIM_INTREQ    ; load the INTREQ register address
        ldr   r2, VIM_INT_CLR
        str   r2, [r0]         ; clear the INTREQ register
        ldr   r0, CCMR4_STAT_REG    ; load the CCMR4 status register address
        ldr   r2, CCMR4_ERR_CLR
        str   r2, [r0]         ; clear the CCMR4 status register
        ldmfd sp!, {r0-r2}
        bx    lr

ESMSR1_REG        .word 0xFFFFF518
ESMSR2_REG        .word 0xFFFFF51C
ESMSR3_REG        .word 0xFFFFF520
ESMKEY_REG        .word 0xFFFFF538
ESMSSR2_REG       .word 0xFFFFF53C
CCMR4_STAT_REG    .word 0xFFFFF600
ERR_CLR_WRD       .word 0xFFFFFFFF
CCMR4_ERR_CLR     .word 0x00010000
ESMSR1_ERR_CLR    .word 0x80000000
ESMSR2_ERR_CLR    .word 0x00000004
ESMSSR2_ERR_CLR   .word 0x00000004
VIM_INT_CLR       .word 0x00000001
VIM_INTREQ        .word 0xFFFFFE20

        .endasmfunc

;-------------------------------------------------------------------------------
;Initialize RAM memory

       .def _memInit_
       .asmfunc

_memInit_
        ldr   r12, MINITGCR     ;Load MINITGCR register address
        mov   r4, #0xA
        str   r4, [r12]         ;Enable global memory hardware initialization

        ldr   r11,  MSIENA      ;Load MSIENA register address
        mov   r4, #0x1          ;Bit position 0 of MSIENA corresponds to SRAM
        str   r4, [r11]         ;Enable auto hardware initalisation for SRAM
mloop                           ;Loop till memory hardware initialization comletes
        ldr   r5, MSTCGSTAT
        ldr   r4, [r5]
        tst   r4, #0x100
        beq   mloop

        mov   r4, #5
        str   r4, [r12]         ;Disable global memory hardware initialization
        bx lr
        .endasmfunc

;-------------------------------------------------------------------------------
; Check Initialize RAM memory

       .def _checkMemInitOn_
       .asmfunc

_checkMemInitOn_
        ldr   r12, MINITGCR     ;Load MINITGCR register address
mloop5  ldr   r4, [r12]
        teq   r4, #0xA
        beq   mloop5
        bx lr
        .endasmfunc

MINITGCR    .word 0xFFFFFF5C
MSIENA      .word 0xFFFFFF60
MSTCGSTAT   .word 0xFFFFFF68

;-------------------------------------------------------------------------------
; Enable caches

        .def  _cacheEnable_
        .asmfunc

_cacheEnable_

        stmfd sp!, {r0-r1}
        mov r0,#0

        MRC   p15, #0, R1, c1, c0, #0   ; Read System Control Register configuration data
        ORR   R1, R1, #0x1 <<12         ; instruction cache enable
        ORR   R1, R1, #0x1 <<2          ; data cache enable
        DSB
        MCR   p15, #0, r0, c15, c5, #0  ; Invalidate entire data cache
        DSB                             ; delay is required, manually added
        MCR   p15, #0, r0, c7, c5, #0   ; Invalidate entire instruction cache
        DSB                             ; delay is required, manually added
        MCR   p15, #0, R1, c1, c0, #0   ; enabled cache RAMs
        ISB

        ldmfd sp!, {r0-r1}

        bx    lr
        .endasmfunc

;-------------------------------------------------------------------------------
; Disable caches

        .def  _cacheDisable_
        .asmfunc

_cacheDisable_

        stmfd sp!, {r1}

        MRC   p15, #0, R1, c1, c0, #0   ; Read System Control Register configuration data
        BIC   R1, R1, #0x1 <<12         ; instruction cache disable
        BIC   R1, R1, #0x1 <<2          ; data cache disable
        DSB
        MCR   p15, #0, R1, c1, c0, #0   ; disabled cache RAMs
        ISB

        ldmfd sp!, {r1}

        bx    lr
        .endasmfunc

;-------------------------------------------------------------------------------
; Invalidate Data Cache

        .def  _dCacheInvalidate_
        .asmfunc

_dCacheInvalidate_
        MOV   R0,#0
        DSB
        MCR   P15, #0, R0, C15, C5, #0
        DSB
        bx    lr
        .endasmfunc

;-------------------------------------------------------------------------------
; Invalidate Instruction Cache

        .def  _iCacheInvalidate_
        .asmfunc

_iCacheInvalidate_
        MOV   R0,#0
        DSB
        MCR   p15, #0, r0, c7, c5, #0
        DSB
        bx    lr
        .endasmfunc



;-------------------------------------------------------------------------------
; C++ construct table pointers

    .def    __TI_PINIT_Base, __TI_PINIT_Limit
    .weak   SHT$$INIT_ARRAY$$Base, SHT$$INIT_ARRAY$$Limit

__TI_PINIT_Base  .long SHT$$INIT_ARRAY$$Base
__TI_PINIT_Limit .long SHT$$INIT_ARRAY$$Limit


    
;-------------------------------------------------------------------------------

