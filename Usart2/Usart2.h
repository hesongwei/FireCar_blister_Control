#ifndef _Usart_H_
#define _Usart_H_

#include "stm32g0xx_hal.h"

#define  UART_NUM 2               //串口数量
#define  UARTX_MAX_LEN1 128       //串口最大接收字节数
typedef struct 
{
	uint8_t start[UART_NUM];					/*串口x接收开始标志*/
	uint8_t finish[UART_NUM];					/*串口x接收结束标志*/
	uint8_t ms[UART_NUM];							/*串口接收倒计时*/

}UAX_STATU;

typedef struct 
{
	uint8_t buf1[UARTX_MAX_LEN1];	/*串口1接收数据缓存*/
	uint8_t buf2[UARTX_MAX_LEN1];	/*串口2接收数据缓存*/
	uint8_t buf3[UARTX_MAX_LEN1];	/*串口3接收数据缓存*/
	uint8_t buf4[UARTX_MAX_LEN1];	/*串口4接收数据缓存*/
	uint8_t buf5[UARTX_MAX_LEN1];	/*串口5接收数据缓存*/
	
	uint16_t len1;									/*串口1接收数据长度*/
	uint16_t len2;									/*串口2接收数据长度*/
	uint16_t len3;									/*串口3接收数据长度*/
	uint16_t len4;									/*串口4接收数据长度*/
	uint16_t len5;									/*串口5接收数据长度*/
	
	
}UAX_BUF;



void Get_Seria_X_buff(void);
void Data_Anasy(__IO uint8_t *data);


#endif


