/**
  ******************************************************************************
  * @file    bsp_adc.c
  * @author  之风  
  * @version V1.0
  * @date    2019-6-12 晚
  * @brief   低功耗
  ******************************************************************************
  * @attention
  *
  * 实验平台:路线灯PCB板
  * 论坛    :无
  * 淘宝    :无
  *
  ******************************************************************************
  */
#include "bsp_low_power.h"

extern void SystemClock_Config(void);

/**
  * @brief  停机唤醒后配置系统时钟: 使能 HSE, PLL
  *         并且选择PLL作为系统时钟.
  * @param  None
  * @retval None
  */
static void SYSCLKConfig_STOP(void)
{
    SYS_DEBUG("sysclockfreq=%d\n",HAL_RCC_GetSysClockFreq());
}




/********************************************************************************
* @fun	  Standby_Mode_Fun
* @brief  待机模式
* @param  无
* @retval 无
* @author 之风
* @data   2019.6.12 晚
********************************************************************************/
void Standby_Mode_Fun(void)
{	
	
	/*清除WU状态位*/
    __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WUF1);
	
	/* 使能WKUP引脚的唤醒功能 ，使能PA0*/
	HAL_PWR_EnableWakeUpPin (PWR_WAKEUP_PIN1_HIGH);
    /* 进入待机模式 */
    HAL_PWR_EnterSTANDBYMode();
	
}

/********************************************************************************
* @fun	  Stop_Mode_Fun
* @brief  停止模式
* @param  无
* @retval 无
* @author 之风
* @data   2019.6.12 晚
********************************************************************************/
void Stop_Mode_Fun(void)
{	
    LED_OFF;
    LCD_POWER_L;
    WIRELESS_SLEEP;

    g_SysSta.set=0;

    TaskTick_Ms[0]=0;
    TaskTick_Ms[1]=0;
    MY_FEEL_DOG=0;
    TaskTick_Ms[3]=0;
    MY_LCD_SHOW=0;


	/* 进入停止模式，设置电压调节器为低功耗模式，等待中断唤醒 */
    HAL_PWR_EnterSTOPMode(PWR_MAINREGULATOR_ON,PWR_STOPENTRY_WFI);
    SystemClock_Config();      
}                              

/********************************************************************************
* @fun	  Sleep_Mode_Fun
* @brief  睡眠模式
* @param  无
* @retval 无
* @author 之风
* @data   2019.6.12 晚
********************************************************************************/
void Sleep_Mode_Fun(void)
{	
    //进入睡眠模式
    __WFI();	//WFI指令进入睡眠
}
/*********************************************END OF FILE**********************/
