;******************************************************************************
;* FILENAME                                                                   *
;*   FIR_filters_asm.asm                                                      *
;*                                                                            *
;* DESCRIPTION                                                                *
;*   Finite Impulse Response Filters using the TMS320C5505 USB Stick.         *
;*   Implemented in assembly language for when C code versions are too slow.  *
;*                                                                            *
;*  Revision: 1.00                                                            *
;*  Author: Richard Sikora                                                    *
;*                                                                            *
;*----------------------------------------------------------------------------*
;*  HISTORY                                                                   *
;*  Revision: 1.00                                                            *
;*  1st January 2010. Created by Richard Sikora from FIR_filters.c            *
;*                                                                            *
;*----------------------------------------------------------------------------*
;*                                                                            *
;*  The number of FIR filter elements is controlled by N                      *
;*                                                                            * 
;******************************************************************************
;*
;* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/ 
;* 
;* 
;*  Redistribution and use in source and binary forms, with or without 
;*  modification, are permitted provided that the following conditions 
;*  are met:
;*
;*    Redistributions of source code must retain the above copyright 
;*    notice, this list of conditions and the following disclaimer.
;*
;*    Redistributions in binary form must reproduce the above copyright
;*    notice, this list of conditions and the following disclaimer in the 
;*    documentation and/or other materials provided with the   
;*    distribution.
;*
;*    Neither the name of Texas Instruments Incorporated nor the names of
;*    its contributors may be used to endorse or promote products derived
;*    from this software without specific prior written permission.
;*
;*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
;*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
;*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
;*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
;*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
;*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
;*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
;*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
;*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
;*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
;*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;*
;*

	.mmregs
FP	.set	AR7
N   .set    51              

	.sect	".text"

; First buffer of N = 51 elements, aligned on 64-bit boundary.  

	.bss	_buffer1,N,0,64  

; Second buffer of N = 51 elements  

    .bss    _buffer2,N,0,0
 

; Give functions global scope to make them available to other functions

	.sect	".text"
	
	.global _FIR_filters_asm_init

	.global	_FIR_filter_asm
	.global _FIR_filter_asm_2

    
;******************************************************************************
;* FUNCTION DEF: _FIR_asm_initialize                                          *
;******************************************************************************
;*                                                                            *
;* Fill four buffers used for FIR filters with zeroes to prevent noise and    *
;* clicks.                                                                    *
;*                                                                            *
;******************************************************************************

_FIR_filters_asm_init:
 
       PSHBOTH       XAR3              ; Temporary save AR3
       
       AMOV       #_buffer1, XAR3   ; AR3 points to buffer1[0]

       RPT        #(N-1)           ; N - 1 repeats
       MOV        #0, *AR3+        ; Fill each element with zero

       AMOV       #_buffer2, AR3   ; AR3 points to buffer2[0]

       RPT        #(N-1)           ; N - 1 repeats
       MOV        #0, *AR3+        ; Fill each element with zero

       
       POPBOTH    XAR3              ; Restore AR3
       
       RET                        ; Return 


;******************************************************************************
;* FUNCTION DEF: _FIR_filter_asm                                              *
;******************************************************************************
;*                                                                            *
;* FIR filter for first channel. Can be used for high pass, low pass          *
;* or other FIR filters.  Input in T0, Coefficients pointer XAR0              *
;*                                                                            *
;******************************************************************************

; Note: We are using huge memory model, so pointers need to be 23 bits e.g. XAR3, not AR3

_FIR_filter_asm:

	PSH       mmap (@ST0)           ; Keep original values of flags
	PSH       mmap (@ST1)
        PSHBOTH   XAR4                  ; Keep original values of register
        
        BSET      ST1_SATD              ; Prevent overflow 
        BSET      ST1_FRCT              ; Extra shift for multiplications
        BSET      ST1_SXMD              ; Turn on sign-extension mode
        
        AMOV      #_buffer1+N-1, XAR4   ; XAR4 points to last element in buffer
					; Do not use AR4 here - high bits are indeterminate.      
     
        AMOV 	  XAR0, XCDP		; Copy XAR0 to coefficient data pointer XCDP
       	MOV 	  #0, AC0               ; Clear AC0
        
        MACM      *AR4-, *CDP+, AC0     ; Multiply and accumulate. No delay at end of buffer
        
        RPT 	  #(N-3)                ; Will be N-1 repeats, less two other instructions
        MACMZ     *AR4-, *CDP+, AC0     ; Multiply and accumulate with delay    
           
        MACMRZ    *AR4, *CDP, AC0       ; Final value with delay and rounding 
               
        MOV       T0, *(_buffer1)       ; Latest input value into beginning of buffer
            
        SFTSC     AC0, #-16, AC0        ; Remove fractional part by shift right 16 
        
        MOV       AC0, T0               ; Return with result in T0 to calling function     
        
        POPBOTH   XAR4                  ; Restore register
        POP       mmap(@ST1)            ; Restore flags
        POP       mmap(@ST0)                    

        RET                             ; Return with result in T0 


;******************************************************************************
;* FUNCTION DEF: _FIR_filter_asm_2                                            *
;******************************************************************************
;*                                                                            *
;* FIR filter for second channel. Can be used for high pass, low pass         *
;* or other FIR filters.                                                      *
;*                                                                            *
;******************************************************************************

_FIR_filter_asm_2:

	PSH       mmap (@ST0)           ; Keep original values of flags
	PSH       mmap (@ST1)
        PSHBOTH   XAR4                  ; Keep original values of register
        
        BSET      ST1_SATD              ; Prevent overflow 
        BSET      ST1_FRCT              ; Extra shift for multiplications
        BSET      ST1_SXMD              ; Turn on sign-extension mode
        
        AMOV      #_buffer2+N-1, XAR4   ; XAR4 points to last element in buffer
                                        ; Do not use AR4 here - high bits are indeterminate.      
     
        AMOV 	  XAR0, XCDP		    ; Copy XAR0 to coefficient data pointer XCDP
       	MOV 	  #0, AC0               ; Clear AC0
        
        MACM      *AR4-, *CDP+, AC0     ; Multiply and accumulate. No delay at end of buffer
        
        RPT 	  #(N-3)                ; Will be N-1 repeats, less two other instructions
        MACMZ     *AR4-, *CDP+, AC0     ; Multiply and accumulate with delay    
           
        MACMRZ    *AR4, *CDP, AC0       ; Final value with delay and rounding 
               
        MOV       T0, *(_buffer2)       ; Latest input value into beginning of buffer
            
        SFTSC     AC0, #-16, AC0        ; Remove fractional part by shift right 16 
        
        MOV       AC0, T0               ; Return with result in T0 to calling function     
        
        POPBOTH   XAR4                  ; Restore register
        POP       mmap(@ST1)            ; Restore flags
        POP       mmap(@ST0)                    

        RET                             ; Return with result in T0 
                           




;******************************************************************************
;* End of FIR_filters_asm.asm                                                 *
;******************************************************************************
