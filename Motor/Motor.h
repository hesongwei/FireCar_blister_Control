#ifndef _Motor_H_
#define _Motor_H_

#include "stm32g0xx_hal.h"


#define MOTOR_CW      1
#define MOTOR_CCW     2
#define MOTOR_DIS     0


#define AUTO_SWING_30   1
#define AUTO_SWING_60   2 
#define AUTO_SWING_90   3
#define AUTO_SWING_120  4
#define AUTO_SWING_150  5
#define AUTO_SWING_180  6
#define AUTO_NULL       0

#define REMAP_PITCH   1
#define REMAP_SWING   2
#define REMAP_SHOWER   3

/* 左右摆动电机控制部分 */
#define SWING_MOTOR_IN_A_H		 	    digitalHi(MCU_RELAY_1_GPIO_Port,MCU_RELAY_1_Pin)
#define SWING_MOTOR_IN_A_L		   		digitalLo(MCU_RELAY_1_GPIO_Port,MCU_RELAY_1_Pin)
#define SWING_MOTOR_IN_B_H		 	    digitalHi(MCU_RELAY_2_GPIO_Port,MCU_RELAY_2_Pin)
#define SWING_MOTOR_IN_B_L		   		digitalLo(MCU_RELAY_2_GPIO_Port,MCU_RELAY_2_Pin)

#define SWING_MOTOR_CW			        SWING_MOTOR_IN_A_H;SWING_MOTOR_IN_B_L     /*电机顺时针*/
#define SWING_MOTOR_CCW			        SWING_MOTOR_IN_A_L;SWING_MOTOR_IN_B_H     /*电机逆时针*/
#define SWING_MOTOR_STOP			      SWING_MOTOR_IN_A_L;SWING_MOTOR_IN_B_L     /*电机停止*/


/* 俯仰摆动电机控制部分 */
#define PITCH_MOTOR_IN_A_H		 	    digitalHi(MCU_RELAY_3_GPIO_Port,MCU_RELAY_3_Pin)
#define PITCH_MOTOR_IN_A_L		   		digitalLo(MCU_RELAY_3_GPIO_Port,MCU_RELAY_3_Pin)
#define PITCH_MOTOR_IN_B_H		 	    digitalHi(MCU_RELAY_4_GPIO_Port,MCU_RELAY_4_Pin)
#define PITCH_MOTOR_IN_B_L		   		digitalLo(MCU_RELAY_4_GPIO_Port,MCU_RELAY_4_Pin)

#define PITCH_MOTOR_CW              PITCH_MOTOR_IN_A_H;PITCH_MOTOR_IN_B_L     /*电机顺时针*/
#define PITCH_MOTOR_CCW			        PITCH_MOTOR_IN_A_L;PITCH_MOTOR_IN_B_H     /*电机逆时针*/
#define PITCH_MOTOR_STOP			      PITCH_MOTOR_IN_A_L;PITCH_MOTOR_IN_B_L     /*电机停止*/


/* 花洒摆动电机控制部分 */
#define SHOWER_MOTOR_IN_A_H		 	    digitalHi(MCU_RELAY_5_GPIO_Port,MCU_RELAY_5_Pin)
#define SHOWER_MOTOR_IN_A_L		   		digitalLo(MCU_RELAY_5_GPIO_Port,MCU_RELAY_5_Pin)
#define SHOWER_MOTOR_IN_B_H		 	    digitalHi(MCU_RELAY_6_GPIO_Port,MCU_RELAY_6_Pin)
#define SHOWER_MOTOR_IN_B_L		   		digitalLo(MCU_RELAY_6_GPIO_Port,MCU_RELAY_6_Pin)

#define SHOWER_MOTOR_CW			        SHOWER_MOTOR_IN_A_H;SHOWER_MOTOR_IN_B_L     /*电机顺时针*/
#define SHOWER_MOTOR_CCW            SHOWER_MOTOR_IN_A_L;SHOWER_MOTOR_IN_B_H     /*电机逆时针*/
#define SHOWER_MOTOR_STOP			   	  /*SHOWER_MOTOR_PWM_L;*/SHOWER_MOTOR_IN_A_L;SHOWER_MOTOR_IN_B_L     /*电机停止*/

typedef struct 
{
	  uint8_t Limit1;    /* 限位信号1 */
	  uint8_t Limit2;    /* 限位信号2 */
	  uint8_t Limit3;    /* 限位信号3 */
	  uint8_t Limit4;    /* 限位信号4 */
	  uint8_t Limit5;    /* 限位信号5 */
	  uint8_t Limit6;	   /* 限位信号6 */
	
    uint8_t swing_motor;	    /*摆动电机*/
    uint8_t pitch_motor;	    /*俯仰电机*/
    uint8_t shower_motor;	    /*花洒电机*/
    uint8_t reserved_motor_remap;	    /*预留电机接口映射*/

		uint8_t sta;	/*运行状态相关 bit7 急停 bit6 视频分割 bit5 避障接触 bit4 刹车 bit3 图传重启 bit2 云台/水泡切换*/
	
    uint16_t power_voltege;             /*电源电压 单位mV*/
    
    uint16_t swing_motor_current;       /*左右摆动电机电流 单位mA*/
    uint16_t pitch_motor_current;       /*俯仰摆动电机电流 单位mA*/
    uint16_t shower_motor_current;      /*直流喷雾电机电流 单位mA*/
    
    uint8_t motor_current_p;            /*bit7左右摆动电机电流保护标志 bit6俯仰摆动电机电流保护标志 bit5直流喷雾电机电流保护标志*/
        
    int8_t auto_swing;                  /*自摆设置*/
    int8_t auto_swing_remote;  /*自摆设置 Remote*/
    int8_t auto_swing_dir;                  /*自摆方向*/

		uint8_t auto_swing_angle;
		uint8_t auto_swing_center_flag;  /* 自摆回到居中位置标志位 */
		uint16_t auto_swing_timer_count;  /* 自摆运行计时变量，用于回到中间位置 */

    uint32_t temp;
	
} SysSta;/*状态的一些flag*/

extern SysSta  g_SysSta;



typedef struct
{	
	/*触发后稳定状态*/
	uint8_t key1;
	uint8_t key2;
	uint8_t key3;
	uint8_t key4;
	uint8_t key5;
	uint8_t key6;
	uint8_t key7;
	uint8_t key8;
    uint8_t key9;
    uint8_t key10;
    uint8_t key11;
    uint8_t key12;
    uint8_t key_sta;
    
    uint8_t aux1;
    uint8_t aux2;
    uint8_t auxx;

    
    /*1 左 2右 */
    uint8_t swing30_1;
    uint8_t swing30_2;
    uint8_t swing60_1;
    uint8_t swing60_2;
    uint8_t swing90_1;
    uint8_t swing90_2;
    uint8_t swing180_1;
    uint8_t swing180_2;
    

    uint8_t pitch_up; 
    uint8_t pitch_down;
    
//    uint8_t x_pitch_up; 
//    uint8_t x_pitch_down;

	uint8_t mode;
	
}KEY_STA;

void Motr_Limit_Signal_Check(void); //限位信号检测函数
void MotorControl(void); //电机控制函数



#endif


