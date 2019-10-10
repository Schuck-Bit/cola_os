/**
  *********************************  STM32F0xx  ********************************
  * @文件名     ： bsp.h
  * @作者       ： sun
  * @库版本     ： V1.5.0
  * @文件版本   ： V1.0.0
  * @日期       ： 2016年05月28日
  * @摘要       ： BSP板级支持包头文件
  ******************************************************************************/

/* 定义防止递归包含 ----------------------------------------------------------*/
#ifndef _BSP_H
#define _BSP_H

/* 包含的头文件 --------------------------------------------------------------*/

#include <stdint.h>


void enable_irq(void);

void disable_irq(void);
	
uint32_t get_pri(void );

void set_pri(uint32_t x);
uint8_t get_run_mode(void);

#define OS_CPU_SR   uint32_t
#define enter_critical()        \
    do { cpu_sr = get_pri(); disable_irq();} while (0)
#define exit_critical()         \
    do { set_pri(cpu_sr);} while (0)





///* 宏定义 --------------------------------------------------------------------*/


///* 函数申明 ------------------------------------------------------------------*/

void bsp_init(void);
void delay_ms(uint32_t cnt);

#endif /* _BSP_H */

/**** Copyright (C)2016 sun. All Rights Reserved **** END OF FILE ****/
