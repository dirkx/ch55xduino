//This file is generated by a script. 
/*
 * Copyright (c) 2020 by Deqing Sun <ds@thinkcreate.us> (c version for CH552 port)
 * WS2812 library for arduino CH552.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */


#include "WS2812.h"

void neopixel_show_long_P1_4(uint32_t dataAndLen) {
  //'dpl' (LSB),'dph','b' & 'acc'
  //DPTR is the array address, B is the low byte of length
#if F_CPU == 24000000
  __asm__ ("    mov r3, b                           \n"

           ";save EA to R6                          \n"
           "    mov c,_EA                           \n"
           "    clr a                               \n"
           "    rlc a                               \n"
           "    mov r6, a                           \n"
           ";disable interrupt                      \n"
           "    clr _EA                             \n"

           //.even may skip a byte, leaving it 0xFF
           //CH55x can save 1 cycle (or more) of jump/branch instructions going from/to an even addr
           ".even                                   \n" // [bytes, cycles]
           "startNewByte$:                          \n"
           "    movx  a,@dptr                       \n" // [1,1]
           "    inc dptr                            \n" // [1,1]
           "    mov r2,#8                           \n" // [2,2]
           "loopbit$:                               \n"
           "    setb _P1_4                          \n" // [2,2]
           "    rlc a                               \n" // [1,1]
           "    nop                                 \n" // [1,1] //make it even
           "    jnc bit7skipHighNop$                \n" // [2,2/4|5]
           "    nop                                 \n" // [1,1]
           "    nop                                 \n" // [1,1]
           "    nop                                 \n" // [1,1]
           "    nop                                 \n" // [1,1]
           "    nop                                 \n" // [1,1]
           "    nop                                 \n" // [1,1]
           "    nop                                 \n" // [1,1]
           "    nop                                 \n" // [1,1]
           "    nop                                 \n" // [1,1]
           "    nop                                 \n" // [1,1]
           "bit7skipHighNop$:                       \n"
           "    clr _P1_4                           \n" // [2,2]
           "    jc bit7skipLowNop$                  \n" // [2,2/4|5]
           "    nop                                 \n" // [1,1]
           "    nop                                 \n" // [1,1]
           "    nop                                 \n" // [1,1]
           "    nop                                 \n" // [1,1]
           "    nop                                 \n" // [1,1]
           "    nop                                 \n" // [1,1]
           "    nop                                 \n" // [1,1]
           "    nop                                 \n" // [1,1]
           "    nop                                 \n" // [1,1]
           "    nop                                 \n" // [1,1]
           "bit7skipLowNop$:                        \n"
           "    djnz r2,loopbit$                    \n" // [2,2/4|5|6]
           "    djnz r3,startNewByte$               \n" // [2,2/4|5|6]

           ";restore EA from R6                     \n"
           "    mov a,r6                            \n"
           "    jz  skipRestoreEA_NP$               \n"
           "    setb  _EA                           \n"
           "skipRestoreEA_NP$:                      \n"

          );
          
          (void)dataAndLen;
#else
#error Only support 24M clock for neopixel now
#endif
}