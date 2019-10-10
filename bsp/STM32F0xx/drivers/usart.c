/**
  ********************************  STM32F0xx  *********************************
  * @�ļ���     �� usart.c
  * @����       �� sun
  * @��汾     �� V1.5.0
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2016��05��28��
  * @ժҪ       �� USARTԴ�ļ�
  ******************************************************************************/
/*----------------------------------------------------------------------------
  ������־:
  2016-05-28 V1.0.0:��ʼ�汾
  ----------------------------------------------------------------------------*/
/* ������ͷ�ļ� --------------------------------------------------------------*/

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
�������� �� USART_GPIO_Configuration
��    �� �� USART��ʹ�ùܽ�������붨��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� sun
*************************************************/
static void uart1_gpio_configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);

    /* ����USART TX_RX ����Ϊ������� */
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9 | GPIO_Pin_10;            //����
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;                       //����ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;                  //����
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                     //�������
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;                       //����
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/************************************************
�������� �� USART_Configuration
��    �� �� ����USART
��    �� �� ��
�� �� ֵ �� ��
��    �� �� sun
*************************************************/
static void uart1_configuration(uint32_t bund)
{
    USART_InitTypeDef USART_InitStructure;

    /* ʹ��APB2ʱ�� */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 
    /******************************************************************
    USART������ʼ��:  ������     ����λ��   ֹͣλ��  У��λ��
            115200         8         1        0(NO)
    *******************************************************************/
    USART_InitStructure.USART_BaudRate = bund;                       //�趨��������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;        //�趨��������λ��
    USART_InitStructure.USART_StopBits = USART_StopBits_1;             //�趨ֹͣλ����
    USART_InitStructure.USART_Parity = USART_Parity_No ;               //����У��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;    //ʹ�ý��պͷ��͹���
    USART_Init(USART1, &USART_InitStructure);                          //��ʼ��USART1

   // USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                     //ʹ��USART1�����ж�

    USART_Cmd(USART1, ENABLE);                                         //ʹ��USART1
}


/************************************************
�������� �� USART1_SendChar
��    �� �� ����1����һ���ַ�
��    �� �� Data --- ����
�� �� ֵ �� ��
��    �� �� sun
*************************************************/
static void uart1_sendbyte(uint8_t Data)
{
    USART1->TDR = (Data & (uint16_t)0x01FF);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);//�ȴ��������
}

/************************************************
�������� �� USART1_SendNByte
��    �� �� ����1����N���ַ�
��    �� �� pData ----- �ַ���
            Length --- ����
�� �� ֵ �� ��
��    �� �� sun
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







