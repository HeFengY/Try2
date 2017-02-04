#include "KEY.h"
#include "TIM.h"
u32 i = 0;
u8 readkey;


 
void Key_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
//	EXTI_InitTypeDef EXTI_InitStructure;

	/*开启按键GPIO口的时钟*/
	RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK,ENABLE);
//												
//	/* 配置 NVIC 中断*/
//	NVIC_Configuration();
//	
/*--------------------------KEY1配置-----------------------------*/
	/* 选择按键用到的GPIO */	
  GPIO_InitStructure.GPIO_Pin = KEY1_INT_GPIO_PIN;
	//上拉输入
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStructure);
	//readkey = KEY2_INT_GPIO_PORT->IDR & KEY2_INT_GPIO_PIN;
	


  /*--------------------------KEY2配置-----------------------------*/
	/* 选择按键用到的GPIO */	
  GPIO_InitStructure.GPIO_Pin = KEY2_INT_GPIO_PIN;
  /* 配置为浮空输入 */	
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
		Delay(10);//消抖
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

// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);//使能PORTA,PORTC时钟

//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试
//	
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;//PA15
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA15
//	
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;//PC5
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
// 	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC5
// 
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//PA0
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0设置成输入，默认下拉	  
//	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.0
//	
//} 
////按键处理函数
////返回按键值
////mode:0,不支持连续按;1,支持连续按;
////返回值：
////0，没有任何按键按下
////KEY0_PRES，KEY0按下
////KEY1_PRES，KEY1按下
////WKUP_PRES，WK_UP按下 
////注意此函数有响应优先级,KEY0>KEY1>WK_UP!!
//u8 KEY_Scan(u8 mode)
//{	 
//	static u8 key_up=1;//按键按松开标志
//	if(mode)key_up=1;  //支持连按		  
//	if(key_up&&(KEY0==0||KEY1==0||WK_UP==1))
//	{
//		delay_ms(10);//去抖动 
//		key_up=0;
//		if(KEY0==0)return KEY0_PRES;
//		else if(KEY1==0)return KEY1_PRES;
//		else if(WK_UP==1)return WKUP_PRES; 
//	}else if(KEY0==1&&KEY1==1&&WK_UP==0)key_up=1; 	     
//	return 0;// 无按键按下
//}

///*********************************************END OF FILE**********************/
