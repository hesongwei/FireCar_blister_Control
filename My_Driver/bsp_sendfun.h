#ifndef __SENDFUN_H
#define	__SENDFUN_H

#include "bsp_mylib.h"

#define MY485_1						2				/*485接口1 串口2 数传使用*/
#define MY485_2						3				/*485接口2 串口3 云台驱动使用*/
#define MY485_3						4				/*485接口3 串口4 气体采集使用*/
#define MY485_4						5				/*485接口4 串口5 蓄电池使用*/

	/// 不精确的延时
static void RS485_delay(__IO uint32_t nCount)
{
	for(; nCount != 0; nCount--);
} 

/*485 1 控制收发引脚*/
//进入接收模式,必须要有延时等待485处理完数据
#define MY485_1_RX_EN			 digitalLo(MAX485_1_GPIO_Port,MAX485_1_Pin)
//进入发送模式,必须要有延时等待485处理完数据
#define MY485_1_TX_EN			 digitalHi(MAX485_1_GPIO_Port,MAX485_1_Pin)

/*485 2 控制收发引脚*/
//进入接收模式,必须要有延时等待485处理完数据
#define MY485_2_RX_EN			 digitalLo(MAX485_2_GPIO_Port,MAX485_2_Pin)
//进入发送模式,必须要有延时等待485处理完数据
#define MY485_2_TX_EN			 digitalHi(MAX485_2_GPIO_Port,MAX485_2_Pin)

/*485 3 控制收发引脚*/
//进入接收模式,必须要有延时等待485处理完数据
#define MY485_3_RX_EN			 digitalLo(MAX485_3_GPIO_Port,MAX485_3_Pin)
//进入发送模式,必须要有延时等待485处理完数据
#define MY485_3_TX_EN			 digitalHi(MAX485_3_GPIO_Port,MAX485_3_Pin)

/*485 4 控制收发引脚*/
//进入接收模式,必须要有延时等待485处理完数据
#define MY485_4_RX_EN			 digitalLo(MAX485_4_GPIO_Port,MAX485_4_Pin)
//进入发送模式,必须要有延时等待485处理完数据
#define MY485_4_TX_EN			 digitalHi(MAX485_4_GPIO_Port,MAX485_4_Pin)

#define __SYS_DEBUG
               
#ifdef  __SYS_DEBUG
    #define SYS_DEBUG_ON         1
    #define NRF24l01_DEBUG_ON    1
    #define SYS_DEBUG_ARRAY_ON   0
    #define SYS_DEBUG_FUNC_ON    0
#else
    #define SYS_DEBUG_ON         0
    #define NRF24l01_DEBUG_ON    0
    #define SYS_DEBUG_ARRAY_ON   0
    #define SYS_DEBUG_FUNC_ON    0
#endif
   
// Log define
#define SYS_INFO(fmt,arg...)           printf("<<-SYS-INFO->> "fmt"\n",##arg)
#define SYS_ERROR(fmt,arg...)          printf("<<-SYS-ERROR->> "fmt"\n",##arg)

#define SYS_DEBUG(fmt,arg...)          do{\
                                         if(SYS_DEBUG_ON)\
                                         printf(""fmt"", ##arg);\
                                       }while(0)

#define NRF24L01_DEBUG(fmt,arg...)    do{\
                                         if(NRF24l01_DEBUG_ON)\
                                         printf(""fmt"", ##arg);\
                                       }while(0)

                                       
#define SYS_DEBUG_ARRAY(array, num)    do{\
                                         int32_t i;\
                                         uint8_t* a = array;\
                                         if(SYS_DEBUG_ARRAY_ON)\
                                         {\
                                            printf("<<-SYS-DEBUG-ARRAY->>\n");\
                                            for (i = 0; i < (num); i++)\
                                            {\
                                                printf("%02x   ", (a)[i]);\
                                                if ((i + 1 ) %10 == 0)\
                                                {\
                                                    printf("\n");\
                                                }\
                                            }\
                                            printf("\n");\
                                        }\
                                       }while(0)

#define SYS_DEBUG_FUNC()               do{\
                                         if(SYS_DEBUG_FUNC_ON)\
                                         printf("<<-SYS-FUNC->> Func:%s@Line:%d\n",__func__,__LINE__);\
                                       }while(0)


void MY_485_EN_Config(void);
void Uartx_SendString( UART_HandleTypeDef * pUSARTx, char *str);
#endif /* __SENDFUN_H */
