/**
  ********************************  STM32F0xx  *********************************
  * @�ļ���     �� bsp.c
  * @����       �� sun
  * @��汾     �� V1.5.0
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2016��05��28��
  * @ժҪ       �� BSP�弶֧�ְ�Դ�ļ�
  ******************************************************************************/
/*----------------------------------------------------------------------------
  ������־:
  2016-05-28 V1.0.0:��ʼ�汾
  ----------------------------------------------------------------------------*/
/* ������ͷ�ļ� --------------------------------------------------------------*/
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

