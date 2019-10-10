
#include "stm32f0xx.h"
#include "systick.h"
#include "cola_os.h"
#include "cola_device.h"

static void sys_tick_init(uint16_t ms, uint8_t priority)
{
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.SYSCLK_Frequency /(1000/ms));
  NVIC_SetPriority (SysTick_IRQn, priority);  
	
}

void SysTick_Handler(void)
{
    cola_timer_ticker();
}

static void tick_init(void)
{
    sys_tick_init(1,0); 
}
fs_initcall(tick_init);

