#ifndef __SERIAL_BUFF_H
#define __SERIAL_BUFF_H
#include "bsp_mylib.h"


#define UARTX_MAX_LEN1 128 /*串口接收最大长度*/
#define SERIAL_TASK_NUM 3		   /*使用的串口数量 对应串口1——5*/

#define DRIVER_ID               4
#define FRAME_HEAD             0XFA
#define MAST_FALG               128
#define SLAVE_FALG              0

typedef struct
{
	USART_TypeDef *uart;    /* STM32内部串口设备指针 */		
	uint8_t *r_buf;         /*串口接收数据缓存*/
	uint16_t buf_size;      /*串口接收数据最大长度*/
	uint16_t len;           /*串口接收未使用数据长度*/

	/*接收完成计算*/
	uint8_t r_start;	/*串口x接收开始标志*/
	uint8_t r_finish;	/*串口x接收完成标志*/
	uint8_t r_ms;		/*串口x接收延时 自减用*/
	uint8_t ms;			/*串口x接收延时*/

} SERIAL_BUF;
extern SERIAL_BUF seri_buf[SERIAL_TASK_NUM];

void UartVarInit(void);
void Enable_IT_Uart_Fun(void);
void My_UartIRQ(SERIAL_BUF *ux);

#endif
