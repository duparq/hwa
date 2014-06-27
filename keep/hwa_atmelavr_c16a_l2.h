
/* This file is part of the HWA project.
 * Copyright (c) 2012 Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/** \file
 *  \brief	HWA layer 2, 16-bits version 'a' Atmel AVR timer-counters
 *
 *	Used in: ATtinyX4 Timer 1
 */


/*	Initialize a tc16a instance
 */
#define hwa_begin_c16a(iname)			\
  HWA_INIT(iname, ccra);			\
  HWA_INIT(iname, ccrb);			\
  HWA_INIT(iname, ccrc);			\
  HWA_INIT(iname, count);			\
  HWA_INIT(iname, icr);				\
  HWA_INIT(iname, ocra);			\
  HWA_INIT(iname, ocrb);			\
  HWA_INIT(iname, imsk);			\
  HWA_INIT(iname, ifr)


//  ATtinyX4 timer1: 16-bit timer counter
//  
//   Mode   Operation                     TOP     Update     DIR     TOV  OCF  ICF
//      WGM                                       of OCR             
//  							           
//   0 0000 Normal                        0xFFFF  Immediate  UP      0
//   1 0001 PWM, Phase Correct, 8-bit     0x00FF  TOP        UPDOWN  0
//   2 0010 PWM, Phase Correct, 9-bit     0x01FF  TOP        UPDOWN  0
//   3 0011 PWM, Phase Correct, 10-bit    0x03FF  TOP        UPDOWN  0
//   4 0100 CTC (Clear Timer on Match)    OCR1A   Immediate  UP      0    TOP
//   5 0101 Fast PWM, 8-bit               0x00FF  TOP        UP      TOP
//   6 0110 Fast PWM, 9-bit               0x01FF  TOP        UP      TOP
//   7 0111 Fast PWM, 10-bit              0x03FF  TOP        UP      TOP
//   8 1000 PWM, Phase & Freq. Correct    ICR1    0          UPDOWN  0         TOP
//   9 1001 PWM, Phase & Freq. Correct    OCR1A   0          UPDOWN  0    TOP
//  10 1010 PWM, Phase Correct            ICR1    TOP        UPDOWN  0         TOP
//  11 1011 PWM, Phase Correct            OCR1A   TOP        UPDOWN  0    TOP
//  12 1100 CTC (Clear Timer on Match)    ICR1    Immediate  UP      0         TOP
//  13 1101 *Reserved*					           
//  14 1110 Fast PWM                      ICR1    TOP        UP      TOP       TOP
//  15 1111 Fast PWM                      OCR1A   TOP        UP      TOP  TOP

//   Mode   Operation                     COUNTMODE    TOPTYPE  TOPVALUE  UPDATE OCR
//  							           
//   0 0000 Normal                        LOOP_UP      FIXED    0xFFFF    Immediate
//   1 0001 PWM, Phase Correct, 8-bit     LOOP_UPDOWN  FIXED    0x00FF    TOP
//   2 0010 PWM, Phase Correct, 9-bit     LOOP_UPDOWN  FIXED    0x01FF    TOP
//   3 0011 PWM, Phase Correct, 10-bit    LOOP_UPDOWN  FIXED    0x03FF    TOP
//   4 0100 CTC (Clear Timer on Match)    LOOP_UP      CPRA               Immediate
//   5 0101 Fast PWM, 8-bit               LOOP_UP      FIXED    0x00FF    TOP
//   6 0110 Fast PWM, 9-bit               LOOP_UP      FIXED    0x01FF    TOP
//   7 0111 Fast PWM, 10-bit              LOOP_UP      FIXED    0x03FF    TOP
//   8 1000 PWM, Phase & Freq. Correct    LOOP_UPDOWN  ICPT               0
//   9 1001 PWM, Phase & Freq. Correct    LOOP_UPDOWN  CPRA               0
//  10 1010 PWM, Phase Correct            LOOP_UPDOWN  ICPT               TOP
//  11 1011 PWM, Phase Correct            LOOP_UPDOWN  CPRA               TOP
//  12 1100 CTC (Clear Timer on Match)    LOOP_UP      ICPT               Immediate
//  13 1101 *Reserved*					           
//  14 1110 Fast PWM                      LOOP_UP      ICPT               TOP
//  15 1111 Fast PWM                      LOOP_UP      CPRA               TOP


HW_INLINE void hwa_commit_c16a ( hwa_t *hwa, hwa_c16a_t *timer )
{
  hwa_commit_8(  hwa->commit, &timer->ccra,  -1 );
  hwa_commit_8(  hwa->commit, &timer->ccrb,  -1 );
  hwa_commit_8(  hwa->commit, &timer->ccrc,  -1 );
  hwa_commit_16( hwa->commit, &timer->count, -1 );
  hwa_commit_16( hwa->commit, &timer->icr,   -1 );
  hwa_commit_16( hwa->commit, &timer->ocra,  -1 );
  hwa_commit_16( hwa->commit, &timer->ocrb,  -1 );
  hwa_commit_8(  hwa->commit, &timer->imsk,  -1 );
  hwa_commit_8(  hwa->commit, &timer->ifr,   -1 );
}
