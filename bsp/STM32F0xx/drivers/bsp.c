/**
  ********************************  STM32F0xx  *********************************
  * @文件名     ： bsp.c
  * @作者       ： sun
  * @库版本     ： V1.5.0
  * @文件版本   ： V1.0.0
  * @日期       ： 2016年05月28日
  * @摘要       ： BSP板级支持包源文件
  ******************************************************************************/
/*----------------------------------------------------------------------------
  更新日志:
  2016-05-28 V1.0.0:初始版本
  ----------------------------------------------------------------------------*/
/* 包含的头文件 --------------------------------------------------------------*/
#include "bsp.h"
#include "stm32f0xx.h"
#include "usart.h"
#include "systick.h"
#include "led.h"
#include "cola_init.h"

void bsp_rcc(void)
{
    
}
pure_initcall(bsp_rcc);

void bsp_init(void)
{
    do_init_call();
}

void enable_irq(void)
{
    __enable_irq();
}

void disable_irq(void)
{
    __disable_irq();
}
	
uint32_t get_pri(void )
{
    return __get_PRIMASK();
}

void set_pri(uint32_t x)
{
    __set_PRIMASK(x);
}

