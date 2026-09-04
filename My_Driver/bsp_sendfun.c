/**
  ******************************************************************************
  * @file    bsp_sendfun.c
  * @author  之风
  * @version V1.0
  * @date    2019-6-12 晚
  * @brief   串口0-8接收发送总处理
  ******************************************************************************
  * @attention
  *
  * 实验平台:无
  * 论坛    :无
  * 淘宝    :无
  *
  ******************************************************************************
  */
#include "bsp_sendfun.h"



/*****************  发送字符串 **********************/
void Uartx_SendString( UART_HandleTypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
	do 
	{
	  HAL_UART_Transmit( pUSARTx,(uint8_t *)(str + k) ,1,1000);
	  k++;
	} while(*(str + k)!='\0');

}

///重定向c库函数printf到串口DEBUG_USART，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
	/* 发送一个字节数据到串口DEBUG_USART */
	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 1000);	
	
	return (ch);
}

///重定向c库函数scanf到串口DEBUG_USART，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		
	int ch;
	HAL_UART_Receive(&huart1, (uint8_t *)&ch, 1, 1000);	
	return (ch);
}


