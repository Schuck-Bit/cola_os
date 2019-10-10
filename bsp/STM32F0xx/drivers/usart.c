/**
  ********************************  STM32F0xx  *********************************
  * @文件名     ： usart.c
  * @作者       ： sun
  * @库版本     ： V1.5.0
  * @文件版本   ： V1.0.0
  * @日期       ： 2016年05月28日
  * @摘要       ： USART源文件
  ******************************************************************************/
/*----------------------------------------------------------------------------
  更新日志:
  2016-05-28 V1.0.0:初始版本
  ----------------------------------------------------------------------------*/
/* 包含的头文件 --------------------------------------------------------------*/

#include "stm32f0xx.h"
#include "usart.h"
#include "config.h"


#ifdef  USING_DEBUG
int fputc(int ch, FILE *f)
{      
	while((USART1->ISR & USART_FLAG_TXE) == RESET);
    USART1->TDR = ((ch) & (uint16_t)0x01FF);
	return ch;
}
#endif


/************************************************
函数名称 ： USART_GPIO_Configuration
功    能 ： USART所使用管脚输出输入定义
参    数 ： 无
返 回 值 ： 无
作    者 ： sun
*************************************************/
static void uart1_gpio_configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);

    /* 定义USART TX_RX 引脚为复用输出 */
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9 | GPIO_Pin_10;            //引脚
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;                       //复用模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;                  //高速
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                     //推完输出
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;                       //上拉
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/************************************************
函数名称 ： USART_Configuration
功    能 ： 配置USART
参    数 ： 无
返 回 值 ： 无
作    者 ： sun
*************************************************/
static void uart1_configuration(uint32_t bund)
{
    USART_InitTypeDef USART_InitStructure;

    /* 使能APB2时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 
    /******************************************************************
    USART参数初始化:  波特率     传输位数   停止位数  校验位数
            115200         8         1        0(NO)
    *******************************************************************/
    USART_InitStructure.USART_BaudRate = bund;                       //设定传输速率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;        //设定传输数据位数
    USART_InitStructure.USART_StopBits = USART_StopBits_1;             //设定停止位个数
    USART_InitStructure.USART_Parity = USART_Parity_No ;               //不用校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//不用流量控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;    //使用接收和发送功能
    USART_Init(USART1, &USART_InitStructure);                          //初始化USART1

   // USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                     //使能USART1接收中断

    USART_Cmd(USART1, ENABLE);                                         //使能USART1
}


/************************************************
函数名称 ： USART1_SendChar
功    能 ： 串口1发送一个字符
参    数 ： Data --- 数据
返 回 值 ： 无
作    者 ： sun
*************************************************/
static void uart1_sendbyte(uint8_t Data)
{
    USART1->TDR = (Data & (uint16_t)0x01FF);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);//等待发送完成
}

/************************************************
函数名称 ： USART1_SendNByte
功    能 ： 串口1发送N个字符
参    数 ： pData ----- 字符串
            Length --- 长度
返 回 值 ： 无
作    者 ： sun
*************************************************/
static void uart1_sendnbyte(uint8_t *pData, uint16_t Length)
{
  while(Length--)
  {
    uart1_sendbyte(*pData);
    pData++;
  }
}

static void usart_init(void)
{
    uart1_gpio_configuration();
    uart1_configuration(115200);  
    
}

fs_initcall(usart_init);







