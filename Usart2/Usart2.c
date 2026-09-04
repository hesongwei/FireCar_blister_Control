#include "Usart2.h"
#include "bsp_myserialbuf.h"
#include "Motor.h"


void Get_Seria_X_buff(void)	
{	
  if(seri_buf[2].r_finish==1)
	{	
		if(seri_buf[2].r_buf[0]==FRAME_HEAD)
		{  
				if(seri_buf[2].r_buf[seri_buf[2].len-1]==SunVerify_Fun(seri_buf[2].r_buf,seri_buf[2].len-1))/*校验正确*/
				{
						if(seri_buf[2].len == 6)
						{
							Data_Anasy(&seri_buf[2].r_buf[2]);  
							HAL_UART_Transmit(&huart2, (uint8_t *)seri_buf[2].r_buf, seri_buf[2].len, 1000);	
						}
				}
		}

		seri_buf[2].len = 0;
		seri_buf[2].r_finish=0;
	}
}


/********************************************************************************
* @fun	 Data_Anasy
* @brief 串口数据解析
* @param data 输入数据 
* @retval 
* @author 渣渣威
* @data   2026.7.14 
********************************************************************************/
void Data_Anasy(__IO uint8_t *data)
{
	uint8_t num = 0;
	uint8_t MototStatus_bit = *data;
	
	g_SysSta.auto_swing_angle = data[1]; //按键5自摆角度选择   数值3:30°自摆  2:60°自摆   1:90°自摆   0:120°自摆    其他数值：按下无效
	
	g_SysSta.sta = data[2]; //获取急停状态
	
	switch(g_SysSta.auto_swing_angle)
	{
//		case 0:  //180°自摆
//			    g_SysSta.auto_swing = AUTO_SWING_180;
//					break;

//		case 1:  //150°自摆
//			    g_SysSta.auto_swing = AUTO_SWING_150;
//					break;

		case 0:  //120°自摆
			    g_SysSta.auto_swing = AUTO_SWING_120;
					break;

		case 1:  //90°自摆
			    g_SysSta.auto_swing = AUTO_SWING_90;
					break;

		case 2:  //60°自摆
			    g_SysSta.auto_swing = AUTO_SWING_60;
					break;		
		
		case 3:  //30°自摆
			    g_SysSta.auto_swing = AUTO_SWING_30;
					break;	

		default :  //无自摆操作
					g_SysSta.auto_swing = AUTO_NULL;
					break;
		
	}
	
	for(num=0;num<8;num++)/*寻找一个bit为1*/
	{
			if(MototStatus_bit&0X80)
				break;
			else
				MototStatus_bit <<= 1;	/* 左移一个bit */			
	}
	
        switch(num)
        {
            case 2:/*向上*/
            if(g_SysSta.Limit1 == 0)/*y轴原点上方*/
            {
							g_SysSta.pitch_motor = MOTOR_CW;
            }
            else
            {
							g_SysSta.pitch_motor = MOTOR_DIS;
            }
//						g_SysSta.auto_swing_remote = AUTO_NULL;
						g_SysSta.auto_swing = AUTO_NULL;
						g_SysSta.auto_swing_timer_count = 0;
						g_SysSta.auto_swing_center_flag = 0;
            break;

            case 3:/*向下*/
            if(g_SysSta.Limit2 == 0)/*y轴原点下方*/      
            {
							g_SysSta.pitch_motor = MOTOR_CCW;
            }
            else
            {
							g_SysSta.pitch_motor = MOTOR_DIS;
            }
//						g_SysSta.auto_swing_remote = AUTO_NULL;
						g_SysSta.auto_swing = AUTO_NULL;
						g_SysSta.auto_swing_timer_count = 0;
						g_SysSta.auto_swing_center_flag = 0;
            break;

            case 0:/*向左*/
            if(g_SysSta.Limit3 == 0)/*x轴原点左方*/
            {
							g_SysSta.swing_motor = MOTOR_CW;
            }
            else
            {
							g_SysSta.swing_motor = MOTOR_DIS;
            }
//						g_SysSta.auto_swing_remote = AUTO_NULL;
						g_SysSta.auto_swing = AUTO_NULL;
						g_SysSta.auto_swing_timer_count = 0;
						g_SysSta.auto_swing_center_flag = 0;
            break;	

            case 1:/*向右*/
            if(g_SysSta.Limit4 == 0)/*x轴原点右方*/
            {
							g_SysSta.swing_motor = MOTOR_CCW;
            }
            else
            {
							g_SysSta.swing_motor = MOTOR_DIS;
            }
//						g_SysSta.auto_swing_remote = AUTO_NULL;
						g_SysSta.auto_swing = AUTO_NULL;
						g_SysSta.auto_swing_timer_count = 0;
						g_SysSta.auto_swing_center_flag = 0;
            break;	

            case 4:/*直流*/
								g_SysSta.shower_motor = MOTOR_CW;// dir=5;
//								g_SysSta.auto_swing_remote = AUTO_NULL;
								g_SysSta.auto_swing = AUTO_NULL;
								g_SysSta.auto_swing_timer_count = 0;
								g_SysSta.auto_swing_center_flag = 0;
            break;	

            case 5:/*喷雾*/
                g_SysSta.shower_motor = MOTOR_CCW;//dir=6;
//								g_SysSta.auto_swing_remote = AUTO_NULL;
								g_SysSta.auto_swing = AUTO_NULL;
								g_SysSta.auto_swing_timer_count = 0;
								g_SysSta.auto_swing_center_flag = 0;
            break;	

            case 6:/*自摆设置*/
//								g_SysSta.auto_swing = AUTO_SWING_180;
//								g_SysSta.auto_swing_remote = AUTO_SWING_180;
            break;	

            case 7:/*无摇杆操作*/
//								g_SysSta.auto_swing_remote = AUTO_NULL;
//                g_SysSta.auto_swing = AUTO_NULL;//dir=8;
//						    g_SysSta.auto_swing_dir = MOTOR_DIS;
								g_SysSta.pitch_motor = MOTOR_DIS;
						    g_SysSta.swing_motor = MOTOR_DIS;
						    g_SysSta.shower_motor = MOTOR_DIS;
            break;		

            default :
//											g_SysSta.auto_swing_remote = AUTO_NULL;
//											g_SysSta.auto_swing = AUTO_NULL;
//											g_SysSta.auto_swing_dir = MOTOR_DIS;
											g_SysSta.pitch_motor = MOTOR_DIS;
											g_SysSta.swing_motor = MOTOR_DIS;
											g_SysSta.shower_motor = MOTOR_DIS;
            break;
        }

	
}


