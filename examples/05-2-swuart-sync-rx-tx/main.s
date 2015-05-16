	.file	"main.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.stabs	"/home/indy/dev/hwa-dev/examples/05-2-swuart-sync-rx-tx/",100,0,2,.Ltext0
	.stabs	"main.c",100,0,2,.Ltext0
	.text
.Ltext0:
	.stabs	"gcc2_compiled.",60,0,0,0
	.stabs	"int:t(0,1)=r(0,1);-32768;32767;",128,0,0,0
	.stabs	"char:t(0,2)=r(0,2);0;127;",128,0,0,0
	.stabs	"long int:t(0,3)=@s32;r(0,3);020000000000;017777777777;",128,0,0,0
	.stabs	"unsigned int:t(0,4)=r(0,4);0;0177777;",128,0,0,0
	.stabs	"long unsigned int:t(0,5)=@s32;r(0,5);0;037777777777;",128,0,0,0
	.stabs	"long long int:t(0,6)=@s64;r(0,6);01000000000000000000000;0777777777777777777777;",128,0,0,0
	.stabs	"long long unsigned int:t(0,7)=@s64;r(0,7);0;01777777777777777777777;",128,0,0,0
	.stabs	"short int:t(0,8)=r(0,8);-32768;32767;",128,0,0,0
	.stabs	"short unsigned int:t(0,9)=r(0,9);0;0177777;",128,0,0,0
	.stabs	"signed char:t(0,10)=@s8;r(0,10);-128;127;",128,0,0,0
	.stabs	"unsigned char:t(0,11)=@s8;r(0,11);0;255;",128,0,0,0
	.stabs	"float:t(0,12)=r(0,1);4;0;",128,0,0,0
	.stabs	"double:t(0,13)=r(0,1);4;0;",128,0,0,0
	.stabs	"long double:t(0,14)=r(0,1);4;0;",128,0,0,0
	.stabs	"short _Fract:t(0,15)=r(0,1);1;0;",128,0,0,0
	.stabs	"long _Fract:t(0,16)=r(0,1);4;0;",128,0,0,0
	.stabs	"long long _Fract:t(0,17)=r(0,1);8;0;",128,0,0,0
	.stabs	"unsigned short _Fract:t(0,18)=r(0,1);1;0;",128,0,0,0
	.stabs	"unsigned _Fract:t(0,19)=r(0,1);2;0;",128,0,0,0
	.stabs	"unsigned long _Fract:t(0,20)=r(0,1);4;0;",128,0,0,0
	.stabs	"unsigned long long _Fract:t(0,21)=r(0,1);8;0;",128,0,0,0
	.stabs	"_Sat short _Fract:t(0,22)=r(0,1);1;0;",128,0,0,0
	.stabs	"_Sat _Fract:t(0,23)=r(0,1);2;0;",128,0,0,0
	.stabs	"_Sat long _Fract:t(0,24)=r(0,1);4;0;",128,0,0,0
	.stabs	"_Sat long long _Fract:t(0,25)=r(0,1);8;0;",128,0,0,0
	.stabs	"_Sat unsigned short _Fract:t(0,26)=r(0,1);1;0;",128,0,0,0
	.stabs	"_Sat unsigned _Fract:t(0,27)=r(0,1);2;0;",128,0,0,0
	.stabs	"_Sat unsigned long _Fract:t(0,28)=r(0,1);4;0;",128,0,0,0
	.stabs	"_Sat unsigned long long _Fract:t(0,29)=r(0,1);8;0;",128,0,0,0
	.stabs	"short _Accum:t(0,30)=r(0,1);2;0;",128,0,0,0
	.stabs	"long _Accum:t(0,31)=r(0,1);8;0;",128,0,0,0
	.stabs	"long long _Accum:t(0,32)=r(0,1);8;0;",128,0,0,0
	.stabs	"unsigned short _Accum:t(0,33)=r(0,1);2;0;",128,0,0,0
	.stabs	"unsigned _Accum:t(0,34)=r(0,1);4;0;",128,0,0,0
	.stabs	"unsigned long _Accum:t(0,35)=r(0,1);8;0;",128,0,0,0
	.stabs	"unsigned long long _Accum:t(0,36)=r(0,1);8;0;",128,0,0,0
	.stabs	"_Sat short _Accum:t(0,37)=r(0,1);2;0;",128,0,0,0
	.stabs	"_Sat _Accum:t(0,38)=r(0,1);4;0;",128,0,0,0
	.stabs	"_Sat long _Accum:t(0,39)=r(0,1);8;0;",128,0,0,0
	.stabs	"_Sat long long _Accum:t(0,40)=r(0,1);8;0;",128,0,0,0
	.stabs	"_Sat unsigned short _Accum:t(0,41)=r(0,1);2;0;",128,0,0,0
	.stabs	"_Sat unsigned _Accum:t(0,42)=r(0,1);4;0;",128,0,0,0
	.stabs	"_Sat unsigned long _Accum:t(0,43)=r(0,1);8;0;",128,0,0,0
	.stabs	"_Sat unsigned long long _Accum:t(0,44)=r(0,1);8;0;",128,0,0,0
	.stabs	"void:t(0,45)=(0,45)",128,0,0,0
	.stabs	"/home/indy/dev/hwa-dev/hwa.h",130,0,0,0
	.stabs	"/usr/lib/gcc/avr/4.8.2/include/stdint.h",130,0,0,0
	.stabs	"/usr/lib/avr/include/stdint.h",130,0,0,0
	.stabs	"int8_t:t(3,1)=(0,10)",128,0,121,0
	.stabs	"uint8_t:t(3,2)=(0,11)",128,0,122,0
	.stabs	"int16_t:t(3,3)=(0,1)",128,0,123,0
	.stabs	"uint16_t:t(3,4)=(0,4)",128,0,124,0
	.stabs	"int32_t:t(3,5)=(0,3)",128,0,125,0
	.stabs	"uint32_t:t(3,6)=(0,5)",128,0,126,0
	.stabs	"int64_t:t(3,7)=(0,6)",128,0,128,0
	.stabs	"uint64_t:t(3,8)=(0,7)",128,0,129,0
	.stabs	"intptr_t:t(3,9)=(3,3)",128,0,142,0
	.stabs	"uintptr_t:t(3,10)=(3,4)",128,0,147,0
	.stabs	"int_least8_t:t(3,11)=(3,1)",128,0,159,0
	.stabs	"uint_least8_t:t(3,12)=(3,2)",128,0,164,0
	.stabs	"int_least16_t:t(3,13)=(3,3)",128,0,169,0
	.stabs	"uint_least16_t:t(3,14)=(3,4)",128,0,174,0
	.stabs	"int_least32_t:t(3,15)=(3,5)",128,0,179,0
	.stabs	"uint_least32_t:t(3,16)=(3,6)",128,0,184,0
	.stabs	"int_least64_t:t(3,17)=(3,7)",128,0,192,0
	.stabs	"uint_least64_t:t(3,18)=(3,8)",128,0,199,0
	.stabs	"int_fast8_t:t(3,19)=(3,1)",128,0,213,0
	.stabs	"uint_fast8_t:t(3,20)=(3,2)",128,0,218,0
	.stabs	"int_fast16_t:t(3,21)=(3,3)",128,0,223,0
	.stabs	"uint_fast16_t:t(3,22)=(3,4)",128,0,228,0
	.stabs	"int_fast32_t:t(3,23)=(3,5)",128,0,233,0
	.stabs	"uint_fast32_t:t(3,24)=(3,6)",128,0,238,0
	.stabs	"int_fast64_t:t(3,25)=(3,7)",128,0,246,0
	.stabs	"uint_fast64_t:t(3,26)=(3,8)",128,0,253,0
	.stabs	"intmax_t:t(3,27)=(3,7)",128,0,273,0
	.stabs	"uintmax_t:t(3,28)=(3,8)",128,0,278,0
	.stabn	162,0,0,0
	.stabn	162,0,0,0
	.stabs	"hwa_r8_t:T(1,1)=s6a:(3,9),0,16;mmask:(3,2),16,8;mvalue:(3,2),24,8;omask:(3,2),32,8;ovalue:(3,2),40,8;;",128,0,0,0
	.stabs	"hwa_r8_t:t(1,2)=(1,1)",128,0,100,0
	.stabs	"hwa_r16_t:T(1,3)=s10a:(3,9),0,16;mmask:(3,4),16,16;mvalue:(3,4),32,16;omask:(3,4),48,16;ovalue:(3,4),64,16;;",128,0,0,0
	.stabs	"hwa_r16_t:t(1,4)=(1,3)",128,0,109,0
	.stabs	"rem_hwa_r32_t:T(1,5)=s18a:(3,9),0,16;mmask:(3,6),16,32;mvalue:(3,6),48,32;omask:(3,6),80,32;ovalue:(3,6),112,32;;",128,0,0,0
	.stabs	"hwa_r32_t:t(1,6)=(1,5)",128,0,118,0
	.stabs	"/home/indy/dev/hwa-dev/hwa_attiny84_1.h",130,0,0,0
	.stabs	"/home/indy/dev/hwa-dev/hwa_attinyx4_1.h",130,0,0,0
	.stabs	"/home/indy/dev/hwa-dev/hwa_atmelavr__corea_1.h",130,0,0,0
	.stabs	"hwa_corea_t:t(6,1)=(6,2)=s60sreg:(1,2),0,48;gimsk:(1,2),48,48;gifr:(1,2),96,48;mcucr:(1,2),144,48;mcusr:(1,2),192,48;osccal:(1,2),240,48;gpior2:(1,2),288,48;gpior1:(1,2),336,48;gpior0:(1,2),384,48;prr:(1,2),432,48;;",128,0,65,0
	.stabn	162,0,0,0
	.stabs	"/home/indy/dev/hwa-dev/hwa_atmelavr__io_1.h",130,0,0,0
	.stabs	"hwa_io8a_t:t(7,1)=(7,2)=s12port:(1,2),0,48;ddr:(1,2),48,48;;",128,0,26,0
	.stabn	162,0,0,0
	.stabs	"/home/indy/dev/hwa-dev/hwa_atmelavr__pcica_1.h",130,0,0,0
	.stabs	"hwa_pcica_t:t(8,1)=(8,2)=s12msk0:(1,2),0,48;msk1:(1,2),48,48;;",128,0,23,0
	.stabn	162,0,0,0
	.stabs	"/home/indy/dev/hwa-dev/hwa_atmelavr__wdoga_1.h",130,0,0,0
	.stabs	"/home/indy/dev/hwa-dev/hwa_atmelavr__wdog_1.h",130,0,0,0
	.stabs	"hwa_wdog_t:t(10,1)=(10,2)=s10address:(3,9),0,16;action:(3,2),16,8;timeout:(3,2),24,8;csr:(1,2),32,48;;",128,0,14,0
	.stabn	162,0,0,0
	.stabn	162,0,0,0
	.stabs	"/home/indy/dev/hwa-dev/hwa_atmelavr__c8a_1.h",130,0,0,0
	.stabs	"hwa_c8a_t:t(11,1)=(11,2)=s50ccra:(1,2),0,48;ccrb:(1,2),48,48;count:(1,2),96,48;:(11,3)=u6ocra:(1,2),0,48;compare0:(1,2),0,48;;,144,48;:(11,4)=u6ocrb:(1,2),0,48;compare1:(1,2),0,48;;,192,48;imsk:(1,2),240,48;ifr:(1,2),288,48;clock:(3,2),336,8;countmode:(3,2),344,8;top:(3,2),352,8;overflow:(3,2),360,8;compare0_update:(3,2),368,8;compare0_output:(3,2),376,8;compare1_update:(3,2),384,8;compare1_output:(3,2),392,8;;",128,0,65,0
	.stabn	162,0,0,0
	.stabs	"/home/indy/dev/hwa-dev/hwa_atmelavr__c16a_1.h",130,0,0,0
	.stabs	"hwa_c16a_t:t(12,1)=(12,2)=s81ccra:(1,2),0,48;ccrb:(1,2),48,48;ccrc:(1,2),96,48;count:(1,4),144,80;:(12,3)=u10ocra:(1,4),0,80;compare0:(1,4),0,80;;,224,80;:(12,4)=u10ocrb:(1,4),0,80;compare1:(1,4),0,80;;,304,80;:(12,5)=u10icr:(1,4),0,80;capture0:(1,4),0,80;;,384,80;imsk:(1,2),464,48;ifr:(1,2),512,48;clock:(3,2),560,8;countmode:(3,2),568,8;top:(3,2),576,8;overflow:(3,2),584,8;compare0_update:(3,2),592,8;compare0_output:(3,2),600,8;compare1_update:(3,2),608,8;compare1_output:(3,2),616,8;icr_input:(3,2),624,8;icr_edge:(3,2),632,8;icr_filter:(3,2),640,8;;",128,0,84,0
	.stabn	162,0,0,0
	.stabs	"/home/indy/dev/hwa-dev/hwa_atmelavr__ocua_1.h",130,0,0,0
	.stabs	"hwa_ocua_t:t(13,1)=(13,2)=s2update:(3,2),0,8;output:(3,2),8,8;;",128,0,21,0
	.stabn	162,0,0,0
	.stabs	"/home/indy/dev/hwa-dev/hwa_atmelavr__acmpa_1.h",130,0,0,0
	.stabs	"hwa_acmpa_t:t(14,1)=(14,2)=s6csr:(1,2),0,48;;",128,0,29,0
	.stabn	162,0,0,0
	.stabs	"/home/indy/dev/hwa-dev/hwa_atmelavr__ad10a_1.h",130,0,0,0
	.stabs	"hwa_ad10a_t:t(15,1)=(15,2)=s24admux:(1,2),0,48;sra:(1,2),48,48;srb:(1,2),96,48;did:(1,2),144,48;;",128,0,31,0
	.stabn	162,0,0,0
	.stabn	162,0,0,0
	.stabn	162,0,0,0
	.stabs	"hwa_t:t(1,7)=(1,8)=s268commit:(3,2),0,8;hw_core0:(6,1),8,480;hw_porta:(7,1),488,96;hw_portb:(7,1),584,96;hw_pcic0:(8,1),680,96;hw_watchdog0:(10,1),776,80;hw_counter0:(11,1),856,400;hw_counter1:(12,1),1256,648;hw_acmp0:(14,1),1904,48;hw_adc0:(15,1),1952,192;;",128,0,147,0
	.stabs	"/home/indy/dev/hwa-dev/hwa__2.h",130,0,0,0
	.stabs	"/home/indy/dev/hwa-dev/hwa_attiny84_2.h",130,0,0,0
	.stabs	"/home/indy/dev/hwa-dev/hwa_attinyx4_2.h",130,0,0,0
	.stabs	"/home/indy/dev/hwa-dev/hwa_atmelavr__corea_2.h",130,0,0,0
	.stabs	"/home/indy/dev/hwa-dev/hwa_atmelavr__core_2.h",130,0,0,0
	.stabs	"_hw_core_stat_t:t(20,1)=(20,2)=u1byte:(3,2),0,8;:(20,3)=s1porf:(0,4),0,1;extrf:(0,4),1,1;borf:(0,4),2,1;wdrf:(0,4),3,1;__4to7:(0,4),4,4;;,0,8;:(20,4)=s1reset_by_power_on:(0,4),0,1;reset_by_reset_pin:(0,4),1,1;reset_by_brown_out:(0,4),2,1;reset_by_watchdog:(0,4),3,1;__4to7_2:(0,4),4,4;;,0,8;;",128,0,118,0
	.stabn	162,0,0,0
	.stabn	162,0,0,0
	.stabs	"/home/indy/dev/hwa-dev/hwa_atmelavr__wdoga_2.h",130,0,0,0
	.stabs	"/home/indy/dev/hwa-dev/hwa_atmelavr__wdog_2.h",130,0,0,0
	.stabs	"_hw_wdog_stat_t:t(22,1)=(22,2)=u1byte:(3,2),0,8;:(22,3)=s1__0to6a:(0,4),0,7;irq:(0,4),7,1;;,0,8;;",128,0,160,0
	.stabn	162,0,0,0
	.stabn	162,0,0,0
	.stabs	"/home/indy/dev/hwa-dev/hwa_atmelavr__c8a_2.h",130,0,0,0
	.stabs	"_hw_c8a_stat_t:t(23,1)=(23,2)=u1byte:(3,2),0,8;:(23,3)=s1overflow:(0,4),0,1;compare0:(0,4),1,1;compare1:(0,4),2,1;__3to7:(0,4),3,5;;,0,8;;",128,0,520,0
	.stabn	162,0,0,0
	.stabs	"/home/indy/dev/hwa-dev/hwa_atmelavr__c16a_2.h",130,0,0,0
	.stabs	"_hw_c16a_stat_t:t(24,1)=(24,2)=u1byte:(3,2),0,8;:(24,3)=s1overflow:(0,4),0,1;compare0:(0,4),1,1;compare1:(0,4),2,1;_34:(0,4),3,2;capture0:(0,4),5,1;_76:(0,4),6,2;;,0,8;;",128,0,520,0
	.stabn	162,0,0,0
	.stabs	"/home/indy/dev/hwa-dev/hwa_atmelavr__ad10a_2.h",130,0,0,0
	.stabs	"_hw_ad10a_status_t:t(25,1)=(25,2)=u1byte:(3,2),0,8;:(25,3)=s1__0to3:(0,4),0,4;interrupt:(0,4),4,1;__5:(0,4),5,1;busy:(0,4),6,1;__7:(0,4),7,1;;,0,8;;",128,0,368,0
	.stabn	162,0,0,0
	.stabs	"/home/indy/dev/hwa-dev/hwa_atmelavr__swuarta_2.h",130,0,0,0
	.stabs	"swuart_status_t:t(26,1)=(26,2)=s1stop:(0,4),0,1;idle:(0,4),1,1;rxc:(0,4),2,1;txc:(0,4),3,1;rxtx:(0,4),4,1;wbtx:(0,4),5,1;synced:(0,4),6,1;__7:(0,4),7,1;;",128,0,253,0
	.stabn	162,0,0,0
	.stabn	162,0,0,0
	.stabn	162,0,0,0
	.stabn	162,0,0,0
	.stabn	162,0,0,0
	.section	.text.startup.main,"ax",@progbits
	.stabs	"main:F(0,1)",36,0,23,main
.global	main
	.type	main, @function
main:
	.stabd	46,0,0
	.stabn	68,0,24,.LM0-.LFBB1
.LM0:
.LFBB1:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
.LBB2009:
.LBB2010:
.LBB2011:
.LBB2012:
.LBB2013:
.LBB2014:
	.stabs	"/home/indy/dev/hwa-dev/hwa_atmelavr_2.h",132,0,0,.Ltext1
.Ltext1:
	.stabn	68,0,262,.LM1-.LFBB1
.LM1:
	ldi r24,lo8(32)
	out 0x3b,r24
.LBE2014:
.LBE2013:
.LBE2012:
.LBB2015:
.LBB2016:
.LBB2017:
	out 0x3a,r24
.LBE2017:
.LBE2016:
.LBE2015:
.LBB2018:
.LBB2019:
.LBB2020:
	out 0x35,r24
.LBE2020:
.LBE2019:
.LBE2018:
.LBE2011:
.LBB2021:
.LBB2022:
.LBB2023:
.LBB2024:
	ldi r24,lo8(-64)
	out 0x1a,r24
.LBE2024:
.LBE2023:
.LBE2022:
.LBE2021:
.LBB2025:
.LBB2026:
.LBB2027:
.LBB2028:
	ldi r24,lo8(1)
	out 0x20,r24
.LBE2028:
.LBE2027:
.LBE2026:
.LBE2025:
.LBB2029:
.LBB2030:
.LBB2031:
.LBB2032:
	out 0x2e,r24
.LBE2032:
.LBE2031:
.LBE2030:
.LBE2029:
.LBE2010:
.LBE2009:
	.stabs	"main.c",132,0,0,.Ltext2
.Ltext2:
	.stabn	68,0,47,.LM2-.LFBB1
.LM2:
/* #APP */
 ;  47 "main.c" 1
	sei
 ;  0 "" 2
/* #NOAPP */
.L7:
.LBB2033:
.LBB2034:
	.stabs	"/home/indy/dev/hwa-dev/hwa_atmelavr_2.h",132,0,0,.Ltext3
.Ltext3:
	.stabn	68,0,88,.LM3-.LFBB1
.LM3:
	sbi 0x1b,6
.LBE2034:
.LBE2033:
	.stabs	"main.c",132,0,0,.Ltext4
.Ltext4:
	.stabn	68,0,59,.LM4-.LFBB1
.LM4:
	rcall _hw_swuart0_reset
.L2:
	.stabn	68,0,60,.LM5-.LFBB1
.LM5:
	sbic 0x13,6
	rjmp .L10
	.stabn	68,0,61,.LM6-.LFBB1
.LM6:
/* #APP */
 ;  61 "main.c" 1
	sleep
 ;  0 "" 2
/* #NOAPP */
	rjmp .L2
.L10:
.LBB2035:
.LBB2036:
	.stabs	"/home/indy/dev/hwa-dev/hwa_atmelavr_2.h",132,0,0,.Ltext5
.Ltext5:
	.stabn	68,0,92,.LM7-.LFBB1
.LM7:
	cbi 0x1b,6
.LBE2036:
.LBE2035:
	.stabs	"main.c",132,0,0,.Ltext6
.Ltext6:
	.stabn	68,0,66,.LM8-.LFBB1
.LM8:
	ldi r24,lo8(36)
	rcall _hw_swuart0_putbyte
.L4:
.LBB2037:
	.stabn	68,0,72,.LM9-.LFBB1
.LM9:
	sbic 0x13,2
	rjmp .L11
	.stabn	68,0,73,.LM10-.LFBB1
.LM10:
/* #APP */
 ;  73 "main.c" 1
	sleep
 ;  0 "" 2
/* #NOAPP */
	rjmp .L4
.L11:
	.stabn	68,0,74,.LM11-.LFBB1
.LM11:
	rcall _hw_swuart0_getbyte
	.stabn	68,0,76,.LM12-.LFBB1
.LM12:
	cpi r24,lo8(65)
	brne .L7
.LBB2038:
.LBB2039:
.LBB2040:
	.stabs	"/home/indy/dev/hwa-dev/hwa_atmelavr_2.h",132,0,0,.Ltext7
.Ltext7:
	.stabn	68,0,88,.LM13-.LFBB1
.LM13:
	sbi 0x1b,6
.LBE2040:
.LBE2039:
.LBB2041:
.LBB2042:
	.stabn	68,0,323,.LM14-.LFBB1
.LM14:
	lds r28,_hw_swuart0_dtn
	lds r29,_hw_swuart0_dtn+1
.LBE2042:
.LBE2041:
	.stabs	"main.c",132,0,0,.Ltext8
.Ltext8:
	.stabn	68,0,84,.LM15-.LFBB1
.LM15:
	mov r24,r28
	rcall _hw_swuart0_putbyte
	.stabn	68,0,85,.LM16-.LFBB1
.LM16:
	mov r24,r29
	rcall _hw_swuart0_putbyte
.LBB2043:
.LBB2044:
	.stabs	"/home/indy/dev/hwa-dev/hwa_atmelavr_2.h",132,0,0,.Ltext9
.Ltext9:
	.stabn	68,0,323,.LM17-.LFBB1
.LM17:
	lds r28,_hw_swuart0_dt0
	lds r29,_hw_swuart0_dt0+1
.LBE2044:
.LBE2043:
	.stabs	"main.c",132,0,0,.Ltext10
.Ltext10:
	.stabn	68,0,88,.LM18-.LFBB1
.LM18:
	mov r24,r28
	rcall _hw_swuart0_putbyte
	.stabn	68,0,89,.LM19-.LFBB1
.LM19:
	mov r24,r29
	rcall _hw_swuart0_putbyte
	.stabn	68,0,91,.LM20-.LFBB1
.LM20:
	ldi r24,lo8(36)
	rcall _hw_swuart0_putbyte
.LBB2045:
.LBB2046:
	.stabs	"/home/indy/dev/hwa-dev/hwa_atmelavr_2.h",132,0,0,.Ltext11
.Ltext11:
	.stabn	68,0,92,.LM21-.LFBB1
.LM21:
	cbi 0x1b,6
	rjmp .L4
.LBE2046:
.LBE2045:
.LBE2038:
.LBE2037:
	.size	main, .-main
.Lscope1:
	.stabs	"",36,0,0,.Lscope1-.LFBB1
	.stabd	78,0,0
	.text
	.stabs	"",100,0,0,.Letext0
.Letext0:
	.ident	"GCC: (GNU) 4.8.2"
