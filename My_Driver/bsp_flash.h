/**
  ********************************  STM32G0xx  *********************************
  * @文件名     ： flash.h
  * @作者       ： 之风
  * @日期       ： 2020年06月06日
  * @摘要       ： 内核Flash编程头文件
  ******************************************************************************/

/* 定义防止递归包含 ----------------------------------------------------------*/
#ifndef _FLASH_H
#define _FLASH_H

/* 包含的头文件 --------------------------------------------------------------*/
#include "bsp_mylib.h"

#define FLASH_UESR_PAGE_START      13
#define FLASH_UESR_PAGE      1

#define FLASH_INIT      0
#define FLASH_SAVE  1
#define FLASH_ERASE     2
/*************************外部接口************************************/
#define FRAME_START	0XAFFFFFFA      /*新的一帧数据开始*/
#define FRAME_END	0XBFFFFFFB      /*新的一帧数据结束*/
#define FRAME_EMPTY	0XFFFFFFFF      /*空白帧*/

#define FLASH_INFO			g_FlashInfo			/*数据句柄*/
#define FLASH_INDEX_SIZE	sizeof(g_FlashInfo )	/*数据大小*/
#define FLASH_WRITE_NUM	    (sizeof(g_FlashInfo )/8)	/*数据大小*/

// 保存的数据格式
typedef struct
{
    uint32_t    flag_start;         /*起始存储标志*/
    uint8_t     channel;    /*信道*/
    uint8_t     e_addr;     /*设备地址*/
    uint16_t    w_addr;     /*无线地址*/
    uint32_t    mode;       /*0连续上传模式 1 睡眠上传模式*/
	uint32_t    time;       /*上传时间间隔 单位s*/
}MY_FLASH_FLAG;


typedef struct
{
    uint32_t flash_start_addr;          /*存储起始地址*/
    uint32_t flash_end_addr;            /*存储结束地址*/
}MY_FLASH;

extern MY_FLASH_FLAG g_FlashInfo;
void Veribe_Init(void);
void My_FLASH_Index_Iint(void);
void Flash_Init(void);
void Flash_GetData(void);
void MY_FLASH_SaveTest(void);
void Flash_SaveOrErase(uint8_t init,uint16_t write_num);
void Open_Num_Fun(void);


#endif /* _FLASH_H */

/**** Copyright (C)2016 之风. All Rights Reserved **** END OF FILE ****/
