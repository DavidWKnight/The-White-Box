/****************************************************************************/
/*  C5535.cmd                                                               */
/*  Copyright (c) 2012  Texas Instruments Incorporated                      */
/*  Author: Rafael de Souza                                                 */
/*                                                                          */
/*    Description: This file is a sample linker command file that can be    */
/*                 used for linking programs built with the C compiler and  */
/*                 running the resulting .out file on a C5535.              */
/*                 Use it as a guideline.  You will want to                 */
/*                 change the memory layout to match your specific          */
/*                 target system.  You may want to change the allocation    */
/*                 scheme according to the size of your program.            */
/*                                                                          */
/****************************************************************************/

MEMORY
{
    MMR:     o = 0x000000  l = 0x0000c0  /* 192B Memory Mapped Registers */
    DARAM0:  o = 0x0000C0  l = 0x001F40  /* 8kB Dual Access RAM 0 */
    DARAM1:  o = 0x002000  l = 0x002000  /* 8kB Dual Access RAM 1 */
    DARAM2:  o = 0x004000  l = 0x003000  /* 8kB Dual Access RAM 2 */
    DARAM3:  o = 0x007000  l = 0x002000  /* 8kB Dual Access RAM 3 */
    DARAM4:  o = 0x009000  l = 0x002000  /* 8kB Dual Access RAM 4 */
    DARAM5:  o = 0x00B000  l = 0x002000  /* 8kB Dual Access RAM 5 */
    DARAM6:  o = 0x00D000  l = 0x002000  /* 8kB Dual Access RAM 6 */
    DARAM7:  o = 0x00F000  l = 0x001000  /* 8kB Dual Access RAM 7 */
  
  	SARAM:   o = 0x010000  l = 0x040000
                    
    ROM:     o = 0xFE0000  l = 0x01FF00  /* 128kB ROM (MPNMC=0) or CS5 (MPNMC=1) */
    VECS:    o = 0xFFFF00  l = 0x000100  /* reset vector */
}                   
                    
SECTIONS            
{                   
    vectors (NOLOAD) >  VECS  /* If MPNMC = 1, remove the NOLOAD directive */
    .cinit         >  DARAM0
    .text          >  DARAM2
    .stack         >  DARAM0
    .sysstack      >  DARAM0
    .sysmem        >  DARAM1
    .data          >  DARAM1
    .cio           >  DARAM0
    .bss           >  SARAM
    .const         >  DARAM0
}
