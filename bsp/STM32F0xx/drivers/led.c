
#include "stm32f0xx.h"
#include "led.h"
#include "cola_device.h"


#define PORT_GREEN_LED                 GPIOC                   
#define PIN_GREENLED                   GPIO_Pin_13              

/* LEDÁÁ¡¢Ãð¡¢±ä»¯ */
#define LED_GREEN_OFF                  (PORT_GREEN_LED->BSRR = PIN_GREENLED)
#define LED_GREEN_ON                   (PORT_GREEN_LED->BRR  = PIN_GREENLED)
#define LED_GREEN_TOGGLE               (PORT_GREEN_LED->ODR ^= PIN_GREENLED)


static cola_device_t led_dev;

static void led_gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = PIN_GREENLED;                            
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;                     
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                  
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                     
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;                  
    GPIO_Init(PORT_GREEN_LED, &GPIO_InitStructure);
    LED_GREEN_OFF;
}

static int led_ctrl(cola_device_t *dev, int cmd, void *args)
{
    if(LED_TOGGLE == cmd)
    {
        LED_GREEN_TOGGLE;
    }
    else 
    {
        
    }
    return 1;
}


static struct cola_device_ops ops =
{
    .control = led_ctrl,
};

static void led_register(void)
{
    led_gpio_init();
    led_dev.dops = &ops;
    led_dev.name = "led";
    cola_device_register(&led_dev);
}

device_initcall(led_register);
