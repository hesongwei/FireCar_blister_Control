#ifndef __SYS_H
#define __SYS_H
#include "stm32g0xx_hal.h"
#include "stm32g0xx_it.h"
#include <stdarg.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "iwdg.h"
#include "main.h"
#include "usart.h"
#include "bsp_mydelay.h"
#include "bsp_sendfun.h"
#include "bsp_myserialbuf.h"
//#include "bsp_communication.h"
//#include "bsp_key.h" 
//#include "bsp_mymain.h"
//#include "bsp_iwdg.h" 
//#include "bsp_min_lcd.h"
//#include "bsp_motor.h" 
#define digitalHi(p, i) (p->BSRR = i)				  //输出为高电平
#define digitalLo(p, i) (p->BSRR = (uint32_t)i << 16) //输出低电平
#define digitalToggle(p, i) (p->ODR ^= i)			  //输出反转状态

/*###########################自己写的函数库##########################################*/
void MCU_GetID(uint8_t *id); //获取芯片ID
void ResetSystem(void);
uint8_t XOR_Verify(uint8_t *pdata, uint8_t len);
uint8_t SunVerify_Fun(uint8_t *pdata, uint8_t len);
uint8_t C_SunVerify_Fun(uint8_t *pdata, uint8_t len);
uint8_t FindStr(char *a, char *buff);
uint8_t BCDToInt(uint8_t *bcd, uint8_t len); //BCD转十进制
void DectoBCD(uint16_t Dec, uint8_t *Bcd, int8_t length);
uint8_t Get_Bit_1_Num(uint32_t data);
void Get_FunRunTimeStart(void);
void Get_FunRunTimeEnd(void);
/*###########################移植安富莱的函数库##########################################*/
int str_len(char *_str);
void str_cpy(char *_tar, char *_src);
int str_cmp(char *s1, char *s2);
void mem_set(char *_tar, char _data, int _len);

void int_to_str(int _iNumber, char *_pBuf, unsigned char _len);
int str_to_int(char *_pStr);

uint16_t BEBufToUint16(uint8_t *_pBuf);
uint16_t LEBufToUint16(uint8_t *_pBuf);

uint32_t BEBufToUint32(uint8_t *_pBuf);
uint32_t LEBufToUint32(uint8_t *_pBuf);

uint16_t CRC16_Modbus(uint8_t *_pBuf, uint16_t _usLen);
int32_t CaculTwoPoint(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x);
float CaculTwoPointFloat(float x1, float y1, float x2, float y2, float x);

char BcdToChar(uint8_t _bcd);
void HexToAscll(uint8_t *_pHex, char *_pAscii, uint16_t _BinBytes);
uint16_t AsciiToHex(char *_pAscii, uint8_t *_pHex, uint16_t _MaxLen);

uint32_t AsciiToUint32(char *pAscii);

uint8_t CharToInt(char _ch);
uint8_t TwoCharToInt(char *_ch);

int str_to_int2(char *_pStr);
int str_to_int3(char *_pStr);
uint8_t ip_str_decode(char *_ipstr, uint8_t *_out);

uint16_t GetHigh16OfFloat(float _ff);
uint16_t GetLow16OfFloat(float _ff);
uint32_t Get32BitOfFloat(float _ff);
uint8_t float_isnan(float _ff);

float BEBufToFloat(uint8_t *_pBuf);

char *strlwr(char *str);
char *strupr(char *str);
char *StrUTF8ToGBK(char *utf8, char *gbk, uint16_t gbk_size);

uint8_t CheckBlankBuf(const char *_buf, uint32_t _len, uint8_t _EmptyValue);

#endif
