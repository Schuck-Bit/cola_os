/**
  *********************************  STM32F0xx  ********************************
  * @�ļ���     �� bsp.h
  * @����       �� sun
  * @��汾     �� V1.5.0
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2016��05��28��
  * @ժҪ       �� BSP�弶֧�ְ�ͷ�ļ�
  ******************************************************************************/

/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef _BSP_H
#define _BSP_H

/* ������ͷ�ļ� --------------------------------------------------------------*/

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





///* �궨�� --------------------------------------------------------------------*/


///* �������� ------------------------------------------------------------------*/

void bsp_init(void);
void delay_ms(uint32_t cnt);

#endif /* _BSP_H */

/**** Copyright (C)2016 sun. All Rights Reserved **** END OF FILE ****/
