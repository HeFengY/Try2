#include "KEY.h"
#include "TIM.h"
u32 i = 0;
u8 readkey;


 
void Key_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
//	EXTI_InitTypeDef EXTI_InitStructure;

	/*��������GPIO�ڵ�ʱ��*/
	RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK,ENABLE);
//												
//	/* ���� NVIC �ж�*/
//	NVIC_Configuration();
//	
/*--------------------------KEY1����-----------------------------*/
	/* ѡ�񰴼��õ���GPIO */	
  GPIO_InitStructure.GPIO_Pin = KEY1_INT_GPIO_PIN;
	//��������
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStructure);
	//readkey = KEY2_INT_GPIO_PORT->IDR & KEY2_INT_GPIO_PIN;
	


  /*--------------------------KEY2����-----------------------------*/
	/* ѡ�񰴼��õ���GPIO */	
  GPIO_InitStructure.GPIO_Pin = KEY2_INT_GPIO_PIN;
  /* ����Ϊ�������� */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(KEY2_INT_GPIO_PORT, &GPIO_InitStructure);
	//GPIO_Init(KEY2_INT_GPIO_PORT, &GPIO_InitStructure);
	RCC_APB2PeriphClockCmd(KEY2_INT_GPIO_CLK,ENABLE);
//												
}

u8 key_scan( u8 mode )
{
	static u8 key_up = 1;
	if( mode ) key_up = 1;
	if( key_up && ((KEY1_INT_GPIO_PORT->IDR& KEY1_INT_GPIO_PIN) == 0) && ((KEY2_INT_GPIO_PORT->IDR & KEY2_INT_GPIO_PIN)== 0))	
	{
		Delay(10);//����
		key_up = 0;
		if((KEY1_INT_GPIO_PORT->IDR & KEY1_INT_GPIO_PIN)== 0)
		{
			do
			{
				i++;
			}
			while( i < 25000000);
			return 1;
		}
			else if(( KEY2_INT_GPIO_PORT->IDR & KEY2_INT_GPIO_PIN)== 0 ) 
			{	
			//	while((KEY2_INT_GPIO_PORT->IDR & KEY1_INT_GPIO_PIN)== 0)(i++);
				do
			{
				//readkey = KEY2_INT_GPIO_PORT->IDR & KEY2_INT_GPIO_PIN;
				i++;
			}
			while( i<25000000 );
				return 2;
			}
	}
	else if((KEY1_INT_GPIO_PORT->IDR & KEY1_INT_GPIO_PIN) == 1 &&  (KEY2_INT_GPIO_PORT->IDR & KEY2_INT_GPIO_PIN)== 0)key_up = 1;
	return 0;
}

//void KEY_Init(void)
//{
//	
//	GPIO_InitTypeDef GPIO_InitStructure;

// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);//ʹ��PORTA,PORTCʱ��

//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�jtag��ʹ��SWD��������SWDģʽ����
//	
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;//PA15
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA15
//	
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;//PC5
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
// 	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC5
// 
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//PA0
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0���ó����룬Ĭ������	  
//	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.0
//	
//} 
////����������
////���ذ���ֵ
////mode:0,��֧��������;1,֧��������;
////����ֵ��
////0��û���κΰ�������
////KEY0_PRES��KEY0����
////KEY1_PRES��KEY1����
////WKUP_PRES��WK_UP���� 
////ע��˺�������Ӧ���ȼ�,KEY0>KEY1>WK_UP!!
//u8 KEY_Scan(u8 mode)
//{	 
//	static u8 key_up=1;//�������ɿ���־
//	if(mode)key_up=1;  //֧������		  
//	if(key_up&&(KEY0==0||KEY1==0||WK_UP==1))
//	{
//		delay_ms(10);//ȥ���� 
//		key_up=0;
//		if(KEY0==0)return KEY0_PRES;
//		else if(KEY1==0)return KEY1_PRES;
//		else if(WK_UP==1)return WKUP_PRES; 
//	}else if(KEY0==1&&KEY1==1&&WK_UP==0)key_up=1; 	     
//	return 0;// �ް�������
//}

///*********************************************END OF FILE**********************/
