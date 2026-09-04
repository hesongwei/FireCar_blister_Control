#include "Motor.h"
#include "main.h"
#include "bsp_mylib.h"


SysSta   g_SysSta;

SysSta *x_sys=&g_SysSta; 

void Motr_Limit_Signal_Check(void)
{
		
	if(HAL_GPIO_ReadPin(Limit_Signal1_GPIO_Port,Limit_Signal1_Pin) == GPIO_PIN_RESET)   //检测到限位1有信号输入
	{
		g_SysSta.Limit1 = 0; //限位1信号置0
	}
	else
	{
		g_SysSta.Limit1 = 1; 
	}
	
	if(HAL_GPIO_ReadPin(Limit_Signal2_GPIO_Port,Limit_Signal2_Pin) == GPIO_PIN_RESET)   //检测到限位2有信号输入
	{
		g_SysSta.Limit2 = 0; //限位2信号置0
	}
	else
	{
		g_SysSta.Limit2 = 1; 
	}	
	
	if(HAL_GPIO_ReadPin(Limit_Signal3_GPIO_Port,Limit_Signal3_Pin) == GPIO_PIN_RESET)   //检测到限位3有信号输入
	{
		g_SysSta.Limit3 = 0; //限位3信号置0
	}
	else
	{
		g_SysSta.Limit3 = 1; 
	}

	if(HAL_GPIO_ReadPin(Limit_Signal4_GPIO_Port,Limit_Signal4_Pin) == GPIO_PIN_RESET)   //检测到限位4有信号输入
	{
		g_SysSta.Limit4 = 0; //限位4信号置0
	}
	else
	{
		g_SysSta.Limit4 = 1; 
	}

	if(HAL_GPIO_ReadPin(Limit_Signal5_GPIO_Port,Limit_Signal5_Pin) == GPIO_PIN_RESET)   //检测到限位5有信号输入
	{
		g_SysSta.Limit5 = 0; //限位5信号置0
	}
	else
	{
		g_SysSta.Limit5 = 1; 
	}

	if(HAL_GPIO_ReadPin(Limit_Signal6_GPIO_Port,Limit_Signal6_Pin) == GPIO_PIN_RESET)   //检测到限位6有信号输入
	{
		g_SysSta.Limit6 = 0; //限位6信号置0
	}	
	else
	{
		g_SysSta.Limit6 = 1; 
	}
	
	
}

void MotorControl(void)
{

	if((g_SysSta.sta&0x80)) //急停未打开
	{
		/* 俯仰电机 */
		if(x_sys->pitch_motor==MOTOR_CW && g_SysSta.Limit1 == 0)                     /*向上*/
		{		
			PITCH_MOTOR_CW; 	          
		}
		else if(x_sys->pitch_motor==MOTOR_CCW && g_SysSta.Limit2 == 0)              /*向下*/
		{			
			PITCH_MOTOR_CCW; 		
		}
		else                                                                                                    /*停止*/
		{		
			PITCH_MOTOR_STOP;
		}   
	
	
		/* 摇摆电机 */
		if(x_sys->auto_swing==AUTO_NULL/* && x_sys->auto_swing_remote==AUTO_NULL*/)
		{
			if(x_sys->swing_motor==MOTOR_CW && g_SysSta.Limit3 == 0)   /*向左*/
			{
				SWING_MOTOR_CCW;	
			}
			else if(x_sys->swing_motor==MOTOR_CCW && g_SysSta.Limit4 == 0) /*向右*/
			{
				SWING_MOTOR_CW;		
			}
			else
			{
				SWING_MOTOR_STOP;
			}
		}
		else if((x_sys->auto_swing == AUTO_SWING_30 || x_sys->auto_swing == AUTO_SWING_60 || x_sys->auto_swing == AUTO_SWING_90 || x_sys->auto_swing == AUTO_SWING_120) && x_sys->auto_swing_center_flag == 0) //进入自摆模式，还没回正
		{
			
			if(g_SysSta.Limit3 == 0 && x_sys->auto_swing_timer_count == 0)
			{
				SWING_MOTOR_CCW;
			}
			else if(g_SysSta.Limit3 == 1)
			{
				SWING_MOTOR_CW;	
				x_sys->auto_swing_timer_count = 2500; /* 到达一个限位后，往回走大概2.5S到居中位置 */
			}

			
//			if(x_sys->auto_swing_dir==MOTOR_CW && g_SysSta.Limit3 == 0)         /*向左*/
//			{    			
//				SWING_MOTOR_CCW; 			                  
//			}
//			else if(x_sys->auto_swing_dir==MOTOR_CCW && g_SysSta.Limit4 == 0)    /*向右*/
//			{				
//				SWING_MOTOR_CW;			
//			}
//			else                                                                                        /*停止*/
//			{
//				if(x_sys->auto_swing_dir==MOTOR_CW)        x_sys->auto_swing_dir=MOTOR_CCW;             /*向左*/
//				else if(x_sys->auto_swing_dir==MOTOR_CCW)   x_sys->auto_swing_dir=MOTOR_CW;             /*向右*/
//				else x_sys->auto_swing_dir=MOTOR_CW;                                                    /*向右*/												
//			}	
		}
		else if(x_sys->auto_swing == AUTO_SWING_30 && x_sys->auto_swing_center_flag == 1)
		{
			
			if(x_sys->auto_swing_timer_count == 0)
			{
				SWING_MOTOR_STOP;
				x_sys->auto_swing_timer_count = 4000;  //30°自摆行程
			}
			
			if(x_sys->auto_swing_timer_count >= 3000 && g_SysSta.Limit3 == 0)  //往左走一秒
			{
				SWING_MOTOR_CCW; 	
			}
			else if(x_sys->auto_swing_timer_count >= 1000 && g_SysSta.Limit4 == 0)  //往右走两秒
			{
				SWING_MOTOR_CW;	
			}
			else if(x_sys->auto_swing_timer_count > 0 && g_SysSta.Limit3 == 0)  //再往左走到中心位置
			{
				SWING_MOTOR_CCW; 
			}
			else SWING_MOTOR_STOP;
				
		}
		else if(x_sys->auto_swing == AUTO_SWING_60 && x_sys->auto_swing_center_flag == 1)
		{
			
			if(x_sys->auto_swing_timer_count == 0)
			{
				SWING_MOTOR_STOP;
				x_sys->auto_swing_timer_count = 6000;  //60°自摆行程
			}
			
			if(x_sys->auto_swing_timer_count >= 4500 && g_SysSta.Limit3 == 0)  //往左走1.5秒
			{
				SWING_MOTOR_CCW; 	
			}
			else if(x_sys->auto_swing_timer_count >= 1500 && g_SysSta.Limit4 == 0)  //往右走3秒
			{
				SWING_MOTOR_CW;	
			}
			else if(x_sys->auto_swing_timer_count > 0 && g_SysSta.Limit3 == 0)  //再往左走到中心位置
			{
				SWING_MOTOR_CCW; 
			}
			else SWING_MOTOR_STOP;
				
		}
		else if(x_sys->auto_swing == AUTO_SWING_90 && x_sys->auto_swing_center_flag == 1)
		{
			
			if(x_sys->auto_swing_timer_count == 0)
			{
				SWING_MOTOR_STOP;
				x_sys->auto_swing_timer_count = 8000;  //60°自摆行程
			}
			
			if(x_sys->auto_swing_timer_count >= 6000 && g_SysSta.Limit3 == 0)  //往左走2秒
			{
				SWING_MOTOR_CCW; 	
			}
			else if(x_sys->auto_swing_timer_count >= 2000 && g_SysSta.Limit4 == 0)  //往右走4秒
			{
				SWING_MOTOR_CW;	
			}
			else if(x_sys->auto_swing_timer_count > 0 && g_SysSta.Limit3 == 0)  //再往左走到中心位置
			{
				SWING_MOTOR_CCW; 
			}
			else SWING_MOTOR_STOP;
				
		}	
		else if(x_sys->auto_swing == AUTO_SWING_120 && x_sys->auto_swing_center_flag == 1)
		{
			
			if(x_sys->auto_swing_timer_count == 0)
			{
				SWING_MOTOR_STOP;
				x_sys->auto_swing_timer_count = 10000;  //60°自摆行程
			}
			
			if(x_sys->auto_swing_timer_count >= 7500 && g_SysSta.Limit3 == 0)  //往左走2.5秒
			{
				SWING_MOTOR_CCW; 	
			}
			else if(x_sys->auto_swing_timer_count >= 2500 && g_SysSta.Limit4 == 0)  //往右走5秒
			{
				SWING_MOTOR_CW;	
			}
			else if(x_sys->auto_swing_timer_count > 0 && g_SysSta.Limit3 == 0)  //再往左走到中心位置
			{
				SWING_MOTOR_CCW; 
			}
			else SWING_MOTOR_STOP;
				
		}		
		
		
		if(x_sys->shower_motor==MOTOR_CW)        /*直流*/
		{     			
			SHOWER_MOTOR_CW;			
		}
		else if(x_sys->shower_motor==MOTOR_CCW)   /*喷雾*/
		{
			SHOWER_MOTOR_CCW;		
		}
		else                                /*停止*/
		{
			SHOWER_MOTOR_STOP;
		} 
	}
	else  //急停打开
	{
		PITCH_MOTOR_STOP;
		SWING_MOTOR_STOP;
		SHOWER_MOTOR_STOP;
	}
		

}

