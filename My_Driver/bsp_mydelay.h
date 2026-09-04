#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "bsp_mylib.h"
#define TIM_TASK_NUM    3
/* 获取内核时钟频率 */
#define GET_CPU_ClkFreq()       HAL_RCC_GetSysClockFreq()



/*******************************************************************************
 * 函数声明
 ******************************************************************************/
HAL_StatusTypeDef HAL_Core_InitTick(void);/*初始化时间戳*/
uint32_t CPU_TS_TmrRd(void);	/*读取当前时间戳*/

//最大延时值为8秒
uint8_t  Core_Delay_Us( uint32_t us);
void  Core_Delay_Ms(  uint32_t ms);
#define  Core_Delay_S(s)    Core_Delay_Ms(s*1000)

extern __IO uint32_t TaskTick_S[];
extern __IO	uint32_t TaskTick_Ms[]; 

#endif /* __SYSTICK_H */

