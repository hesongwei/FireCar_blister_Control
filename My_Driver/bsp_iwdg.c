 
#include "bsp_iwdg.h"   



// 喂狗
void IWDG_Feed(void)
{
	// 把重装载寄存器的值放到计数器中，喂狗，防止IWDG复位
	// 当计数器的值减到0的时候会产生系统复位
    HAL_IWDG_Refresh(&hiwdg);        
}


/*********************************************END OF FILE**********************/
