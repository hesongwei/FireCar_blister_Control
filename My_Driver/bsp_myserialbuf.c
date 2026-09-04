/**
  ******************************************************************************
  * @file    bsp_myserialbuf.c
  * @author  之风 
  * @version V1.0
  * @date    2019-6-12 晚
  * @brief   定义一些串口函数
  ******************************************************************************
  * @attention
  *
  * 实验平台:无
  * 论坛    :无
  * 淘宝    :无
  *
  ******************************************************************************/
#include "bsp_myserialbuf.h"

SERIAL_BUF seri_buf[SERIAL_TASK_NUM]; /*串口1-9数据*/

// uint8_t g_RxBuflp[UARTX_MAX_LEN1]; /* 接收缓冲区 */
 uint8_t g_RxBuf1[UARTX_MAX_LEN1];  /* 接收缓冲区 */
 uint8_t g_RxBuf2[UARTX_MAX_LEN1];  /* 接收缓冲区 */
// uint8_t g_RxBuf3[UARTX_MAX_LEN1];  /* 接收缓冲区 */
// uint8_t g_RxBuf4[UARTX_MAX_LEN1];  /* 接收缓冲区 */
// uint8_t g_RxBuf5[UARTX_MAX_LEN1];  /* 接收缓冲区 */
// uint8_t g_RxBuf6[UARTX_MAX_LEN1];  /* 接收缓冲区 */
// uint8_t g_RxBuf7[UARTX_MAX_LEN1];  /* 接收缓冲区 */
// uint8_t g_RxBuf8[UARTX_MAX_LEN1];  /* 接收缓冲区 */



/********************************************************************************
*	@fun    UartVarInit
*   @brief  串口相关变量初始化
*   @param 
*   @retval 
*	@author 之风
*   @data   2019.6.12 晚
********************************************************************************/
void UartVarInit(void)
{
//    seri_buf[0].uart = LPUART1;             /* STM32 串口设备 */
//    seri_buf[0].r_buf = g_RxBuflp;          /* 接收缓冲区指针 */
//    seri_buf[0].buf_size = UARTX_MAX_LEN1; /* 接收缓冲区大小 */
//    seri_buf[0].ms = 2;                    /* 等待空闲中断时间*/
//    
    seri_buf[1].uart = USART1;             /* STM32 串口设备 */
    seri_buf[1].r_buf = g_RxBuf1;          /* 接收缓冲区指针 */
    seri_buf[1].buf_size = UARTX_MAX_LEN1; /* 接收缓冲区大小 */
    seri_buf[1].ms = 2;                    /* 等待空闲中断时间*/
    
    seri_buf[2].uart = USART2;             /* STM32 串口设备 */
    seri_buf[2].r_buf = g_RxBuf2;          /* 接收缓冲区指针 */
    seri_buf[2].buf_size = UARTX_MAX_LEN1; /* 接收缓冲区大小 */
    seri_buf[2].ms = 3;                    /* 等待空闲中断时间*/
    
//    seri_buf[3].uart = USART3;             /* STM32 串口设备 */
//    seri_buf[3].r_buf = g_RxBuf3;          /* 接收缓冲区指针 */
//    seri_buf[3].buf_size = UARTX_MAX_LEN1; /* 接收缓冲区大小 */
//    seri_buf[3].ms = 2;                    /* 等待空闲中断时间*/
//    
//    seri_buf[4].uart = UART4;             /* STM32 串口设备 */
//    seri_buf[4].r_buf = g_RxBuf4;          /* 接收缓冲区指针 */
//    seri_buf[4].buf_size = UARTX_MAX_LEN1; /* 接收缓冲区大小 */
//    seri_buf[4].ms = 2;                    /* 等待空闲中断时间*/
//    
//    seri_buf[5].uart = UART5;             /* STM32 串口设备 */
//    seri_buf[5].r_buf = g_RxBuf5;          /* 接收缓冲区指针 */
//    seri_buf[5].buf_size = UARTX_MAX_LEN1; /* 接收缓冲区大小 */
//    seri_buf[5].ms = 2;                    /* 等待空闲中断时间*/
//    
//    seri_buf[6].uart = USART6;             /* STM32 串口设备 */
//    seri_buf[6].r_buf = g_RxBuf6;          /* 接收缓冲区指针 */
//    seri_buf[6].buf_size = UARTX_MAX_LEN1; /* 接收缓冲区大小 */
//    seri_buf[6].ms = 2;                    /* 等待空闲中断时间*/
//    
//    seri_buf[7].uart = UART7;             /* STM32 串口设备 */
//    seri_buf[7].r_buf = g_RxBuf7;          /* 接收缓冲区指针 */
//    seri_buf[7].buf_size = UARTX_MAX_LEN1; /* 接收缓冲区大小 */
//    seri_buf[7].ms = 2;                    /* 等待空闲中断时间*/
//    
//    seri_buf[8].uart = UART8;             /* STM32 串口设备 */
//    seri_buf[8].r_buf = g_RxBuf8;          /* 接收缓冲区指针 */
//    seri_buf[8].buf_size = UARTX_MAX_LEN1; /* 接收缓冲区大小 */
//    seri_buf[8].ms = 2;                    /* 等待空闲中断时间*/
    
}

/********************************************************************************
* @fun	  Enable_IT_Uart_Fun
* @brief  开启串口接收中断
* @param  无
* @retval 无
* @author 之风
* @data   2019.11.4 晚
  ********************************************************************************/
void Enable_IT_Uart_Fun(void)
{  
    UartVarInit();
//    HAL_HalfDuplex_EnableTransmitter(&huart1);
    __HAL_UART_ENABLE_IT(&huart2,UART_IT_RXNE);   //开启串口2接收中断
}
/********************************************************************************
*	@fun    My_UartIRQ
*   @brief  串口中断数据接处理
*   @param 
*   @retval 
*	@author 之风
*   @data   2019.6.12 晚
********************************************************************************/
void My_UartIRQ(SERIAL_BUF *ux)
{
    ux->r_buf[ux->len] = (ux->uart->RDR);
    ux->r_start = 1;   /*接收状态开始*/
    ux->r_ms = ux->ms; /*接收结束标志位置1*/

    if (++ux->len >= ux->buf_size)
    {
        ux->len = 0;
    }
}
