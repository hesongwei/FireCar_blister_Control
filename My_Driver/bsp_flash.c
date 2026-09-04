/**
  ********************************  STM32F0xx  *********************************
  * @文件名     ： flash.c
  * @作者       ： 之风
  * @库版本     ： V1.5.0
  * @文件版本   ： V1.0.0
  * @日期       ： 2019年09月28日
  * @摘要       ： 内核Flash编程源文件
  ******************************************************************************/

/* 包含的头文件 --------------------------------------------------------------*/
#include "bsp_flash.h" 


#define FLASH_USER_START_ADDR   (FLASH_BASE + (FLASH_UESR_PAGE_START * FLASH_PAGE_SIZE))   /* Start @ of user Flash area */
#define FLASH_USER_END_ADDR     (FLASH_BASE + FLASH_SIZE - 1)   /* End @ of user Flash area */

#define DATA_64                 ((uint64_t)0x1234567812345678)
#define DATA_32                 ((uint32_t)0x12345678)

uint64_t *p_Write=0; 

static uint32_t flashAddrNow;
static uint32_t flashAddrNext;

FLASH_EraseInitTypeDef EraseInitStruct;
MY_FLASH_FLAG g_FlashInfo={FRAME_START,0X00};
MY_FLASH g_my_flash;

    
/********************************************************************************
* @fun	  GetPage
* @brief  获取当前地址所在的页面
* @dir    无
* @param  无
* @retval 无
* @author 之风
* @data   2019.9.28 晚
********************************************************************************/
static uint32_t GetPage(uint32_t Addr)
{
  return (Addr - FLASH_BASE) / FLASH_PAGE_SIZE;;
}

/********************************************************************************
* @fun	  My_FLASH_Index_Iint
* @brief  自用的内部flash存储空间初始化
* @dir    无
* @param  无
* @retval 无
* @author 之风
* @data   2019.9.28 晚
********************************************************************************/
void My_FLASH_Index_Iint(void)
{   

    EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;                                                /*擦除方式 整页擦除*/
    EraseInitStruct.Page        = GetPage(FLASH_USER_START_ADDR);                                       /*擦除起始page*/
    EraseInitStruct.NbPages     = GetPage(FLASH_USER_END_ADDR) - EraseInitStruct.Page+1;    /*擦除页数*/                          
    
    g_my_flash.flash_start_addr=FLASH_USER_START_ADDR;
    g_my_flash.flash_end_addr=FLASH_USER_END_ADDR;  /* 防止存储空间溢出*/
}

/********************************************************************************
* @fun	  Veribe_Init
* @brief  模式初始化
* @dir    无
* @param  无
* @retval 无
* @author 之风
* @data   2019.9.28 晚
********************************************************************************/
void Veribe_Init(void)
{
	g_FlashInfo.flag_start=FRAME_START;  
	g_FlashInfo.channel=0;
	g_FlashInfo.e_addr=1;
	g_FlashInfo.w_addr=0;
	g_FlashInfo.mode=0;
    g_FlashInfo.time=10;
    flashAddrNow = g_my_flash.flash_start_addr;
    flashAddrNext=flashAddrNow;    
}

/********************************************************************************
* @fun	  ClrFlashPage
* @brief  在制定的地址擦除指定页数的数据
* @dir    无
* @param  无
* @retval 无
* @author 之风
* @data   2019.9.28 晚
********************************************************************************/
static void ClrFlashPage(void)
{
    uint32_t PageError=0;
    if (HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) != HAL_OK)
    {
        /*
        Error occurred while page erase.
        User can add here some code to deal with this error.
        PageError will contain the faulty page and then to know the code error on this page,
        user can call function 'HAL_FLASH_GetError()'
        */
        /* Infinite loop */
        while (1)
        {
            LED_ON;
            HAL_Delay(1000);
            LED_OFF;
            HAL_Delay(1000);
        }
    }
//    HAL_Delay(2);
}
/********************************************************************************
* @fun	  Read_D_Word
* @brief  读两个字的数据
* @dir    无
* @param  无
* @retval 无
* @author 之风
* @data   2019.9.28 晚
********************************************************************************/
static uint64_t Read_D_Word(uint64_t addr)
{
	return *(__IO uint64_t*)addr;
}	
/********************************************************************************
* @fun	  ReadWord
* @brief  读一个字的数据
* @dir    无
* @param  无
* @retval 无
* @author 之风
* @data   2019.9.28 晚
********************************************************************************/
static uint32_t ReadWord(uint32_t addr)
{
	return *(__IO uint32_t*)addr;
}	

/********************************************************************************
* @fun	  ReadWord
* @brief  读半个字的数据
* @dir    无
* @param  无
* @retval 无
* @author 之风
* @data   2019.9.28 晚
********************************************************************************/
static uint16_t ReadHWord(uint32_t addr)
{
	return *(__IO uint16_t*)addr;
}

/********************************************************************************
* @fun	   H_flashReadIndex
* @brief  在制定的地址读指定长度的数据
* @dir    无
* @param  Address 读数据的地址 pData 存储数据的指针 len 读数据的长度
* @retval 无
* @author 之风
* @data   2019.9.28 晚
********************************************************************************/
static void H_flashReadIndex(uint32_t Address, uint16_t *pData,uint16_t len)
{
	uint8_t i;
	len >>= 1;
	for(i=0; i<len; i++)
	{
		*pData++ = ReadWord(Address);
		Address += 2;
	}
}
/********************************************************************************
* @fun	  Flash_SaveOrErase
* @brief  在索引的地址存储结构体的数据
* @dir    无
* @param  init 初始化选择
* @retval 无
* @author 之风
* @data   2019.9.28 晚
********************************************************************************/
void Flash_SaveOrErase(uint8_t init,uint16_t write_num)
{  
    HAL_StatusTypeDef sta=0;
    uint32_t end_addr;   
    uint8_t data_save=0;
    p_Write=(uint64_t *)&FLASH_INFO;   

    HAL_FLASH_Unlock();                                                   
      
    end_addr =flashAddrNext+write_num*FLASH_INDEX_SIZE;  
    
    if(end_addr > g_my_flash.flash_end_addr || init==FLASH_ERASE)/*如果如果地址大于存储的结束地址 则把当前页面的数据擦除*/
    {	
        flashAddrNow = g_my_flash.flash_start_addr;
        flashAddrNext = flashAddrNow;
        end_addr =flashAddrNext+write_num*FLASH_INDEX_SIZE;          
        ClrFlashPage();    //清除
    }
  
  while (flashAddrNext < end_addr)
  {
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, flashAddrNext, *p_Write) == HAL_OK)
    {
        p_Write+=1;
        flashAddrNext +=8;
        data_save=1;
    }
   else
    {
      /* Error occurred while writing data in Flash memory.
         User can add here some code to deal with this error */
      while (1)
      {        
            LED_ON;
            HAL_Delay(1000);
            LED_OFF;
            HAL_Delay(1000);
      }
    }
  }  
    if(data_save)
    {
        flashAddrNow=flashAddrNext-FLASH_INDEX_SIZE;

    }
    
    HAL_FLASH_Lock();    
    
}

/********************************************************************************
* @fun		GetIndexAddr
* @brief  获取索引递地址
* @dir    无
* @param  无
* @retval 无
* @author 之风
* @data   2019.9.28 晚
********************************************************************************/
static void GetIndexAddr(void)
{
	uint32_t addr = g_my_flash.flash_start_addr;
	uint32_t eAddr = g_my_flash.flash_end_addr;
    printf("   \n");
    printf("存储起始地址 %X\n",addr);
    printf("存储结束地址 %X\n",eAddr);
    printf("FLASH总大小 %d K\n",(*((uint32_t *)FLASH_SIZE_DATA_REGISTER)) & (0x00FFU));
    printf("FLASH页大小 %X\n",FLASH_PAGE_SIZE);
    printf("索引大小 %X\n",FLASH_INDEX_SIZE); 
    printf("写双字 %d\n",1);
    
    
	// 第一个位置的标记位检测
	if(ReadWord(addr) != FRAME_EMPTY && ReadWord(addr) != FRAME_START)
	{
        HAL_FLASH_Unlock();      
        ClrFlashPage();    //清除
        HAL_FLASH_Lock();

	}
	while(addr+FLASH_INDEX_SIZE <= eAddr) /*判断最后得空间够不够存储一个FLASH_INDEX_SIZE*/
	{
		if(ReadWord(addr) == FRAME_EMPTY)/*寻找到空白的地址*/
		{
            if(addr == g_my_flash.flash_start_addr)
            {    
                flashAddrNow=addr;
                flashAddrNext=flashAddrNow;
                Flash_SaveOrErase(FLASH_SAVE,1);  /*第一次写数据，先存储*/
                printf("\nflashAddrNow=%08X\n",flashAddrNow);
                printf("flashAddrNext=%08X\n",flashAddrNext);

            }
            else
            {
                flashAddrNow = addr - FLASH_INDEX_SIZE;
                flashAddrNext=addr;
                printf("\nflashAddrNow=%08X\n",flashAddrNow);
                printf("flashAddrNext=%08X\n",flashAddrNext);


            }
            return;
	
		}
		addr += FLASH_INDEX_SIZE;
	}
    
    /*数据满了*/
    printf("\nFLASH SAVE FULL\n");
    flashAddrNow=addr-FLASH_INDEX_SIZE;    /*后退一步*/ 
    flashAddrNext=flashAddrNow;    
}

/********************************************************************************
* @fun	   Flash_GetData
* @brief  从索引地址中获取数据
* @dir    无
* @param  无
* @retval 无
* @author 之风
* @data   2019.9.28 晚
********************************************************************************/
void Flash_GetData(void)
{       
    uint64_t date1=Read_D_Word(flashAddrNow);
    flashAddrNow+=8;
    uint64_t date2=Read_D_Word(flashAddrNow);
    flashAddrNow-=8;

    g_FlashInfo.flag_start=date1;   /*读数据*/
    g_FlashInfo.channel=date1>>32;      /*读数据*/
    g_FlashInfo.e_addr=date1>>40;       /*读数据*/
    g_FlashInfo.w_addr=date1>>48;       /*读数据*/
    g_FlashInfo.mode=date2;         /*读数据*/
    g_FlashInfo.time=date2>>32;         /*读数据*/

    if(g_FlashInfo.flag_start!=FRAME_START)  /*读出的数进行校验错误*/
    {
        Flash_SaveOrErase(FLASH_ERASE,1); //并保存一次
    }
    printf("now memory addr=%08X\n",flashAddrNow);
    printf("channel=%d\n",g_FlashInfo.channel);
    printf("e addr=%d\n",g_FlashInfo.e_addr);
    printf("w_addr=%d\n",g_FlashInfo.w_addr);
    printf("mode=%d\n",g_FlashInfo.mode);
    printf("time=%d\n",g_FlashInfo.time);


}

/********************************************************************************
* @fun	  MY_FLASH_SaveTest
* @brief  数据存储测试
* @dir    无
* @param  无
* @retval 无
* @author 之风
* @data   2019.9.28 晚
********************************************************************************/
void MY_FLASH_SaveTest(void)
{
    uint16_t count=0;
    HAL_StatusTypeDef sta=0;
    HAL_FLASH_Unlock();      
    ClrFlashPage();    //清除
    for(count=0;count<10000;count++)
    {
        printf("%08X ",flashAddrNow);
        if(flashAddrNow > g_my_flash.flash_end_addr)/*如果如果地址大于存储的结束地址 则把当前页面的数据擦除*/
        {	
            printf("\n\n空间存满\n");
            flashAddrNow = g_my_flash.flash_start_addr;                
            ClrFlashPage();    //清除
            break;
        }        
        sta=HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, flashAddrNow,DATA_64); /*在指定地址写入64Bit数据*/
        if(sta!=0)
        {
            printf("\n\nsave err=%d\n",sta);
        }
        flashAddrNow += 8;        
    } 
    HAL_Delay(10);
    HAL_FLASH_Lock(); 	  
}
                                             

 /********************************************************************************
* @fun	  Flash_Init
* @brief  FLASH初始化
* @dir    无
* @param  无
* @retval 无
* @author 之风
* @data   2019.9.28 晚
  ********************************************************************************/
void Flash_Init(void)
{
    My_FLASH_Index_Iint();
    Veribe_Init();
//    MY_FLASH_SaveTest();

//    Flash_SaveOrErase(FLASH_ERASE,1);

//	GetIndexAddr();        
//	Flash_GetData();
        
}


/**** Copyright (C)2016 之风. All Rights Reserved **** END OF FILE ****/
