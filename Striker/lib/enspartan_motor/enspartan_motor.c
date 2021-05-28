#include "include_lib.h"
#include "enspartan_motor.h"

void konfigurasitimer1(void)
{
    //clock enable
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

    //GPIO__TIM_init
    GPIO_InitStructure.GPIO_Pin   = P_9;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_TIM1);

    //GPIO__TIM_init
    GPIO_InitStructure.GPIO_Pin   = P_14;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_TIM1);

    //timer_init
    TIM_TimeBaseStructure.TIM_Period = periodTIM1;
    TIM_TimeBaseStructure.TIM_Prescaler = prescaleTIM_APB2;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV2;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);


    //Channel 1,2,3, and 4//
    TIM_OCInitStructure.TIM_OCMode              = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState         = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState        = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse               = 0;
    TIM_OCInitStructure.TIM_OCPolarity          = TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_OCNPolarity         = TIM_OCNPolarity_Low;
    TIM_OCInitStructure.TIM_OCIdleState         = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState        = TIM_OCIdleState_Reset;


    TIM_OCInitStructure.TIM_OutputState         = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse               = 0;
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);							//ACTIVE

    TIM_OCInitStructure.TIM_OutputState         = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse               = 0;
    TIM_OC4Init(TIM1, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);							//ACTIVE

    //timer enable
    TIM_Cmd(TIM1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

void konfigurasitimer2()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    PrescalerValue = (uint32_t) ((SystemCoreClock / 2) / 1000000) - 1;
    TIM_TimeBaseStructure.TIM_Period = 1000000 ;
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV2;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_PrescalerConfig(TIM2, PrescalerValue, TIM_PSCReloadMode_Immediate);

    TIM_Cmd(TIM2, ENABLE);
}

void konfigurasitimer3(void)
{
    //clock enable
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC, ENABLE);


    //GPIO__TIM_init
    GPIO_InitStructure.GPIO_Pin   = P_4;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_TIM3);

    //GPIO__TIM_init
    GPIO_InitStructure.GPIO_Pin   = P_8;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM3);

    TIM_TimeBaseStructure.TIM_Period = periodTIM3; //PWM 8kHz
    TIM_TimeBaseStructure.TIM_Prescaler = prescaleTIM_APB1;//PrescalerValue;//0;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);


    //Channel 1,2,3, and 4//
    TIM_OCInitStructure.TIM_OCMode              = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState         = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState        = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse               = 0;
    TIM_OCInitStructure.TIM_OCPolarity          = TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_OCNPolarity         = TIM_OCNPolarity_Low;
    TIM_OCInitStructure.TIM_OCIdleState         = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState        = TIM_OCIdleState_Reset;

    TIM_OCInitStructure.TIM_OutputState         = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse               = 0;
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);							//INACTIVE

    TIM_OCInitStructure.TIM_OutputState         = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse               = 0;
    TIM_OC3Init(TIM3, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);							//ACTIVE

    //timer enable
    TIM_Cmd(TIM3, ENABLE);
    TIM_CtrlPWMOutputs(TIM3, ENABLE);
}

void konfigurasitimer4(void)
{
    //clock enable
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    //GPIO__TIM_init
    GPIO_InitStructure.GPIO_Pin   = P_7 | P_6;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);


    //frekuensi 500 HZ
    TIM_TimeBaseStructure.TIM_Period = periodTIM4;//867; Frekuensi 5kHz
    TIM_TimeBaseStructure.TIM_Prescaler = prescaleTIM_APB1;//173;//PrescalerValue;//0;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

    //Channel 1,2,3, and 4//
    TIM_OCInitStructure.TIM_OCMode              = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState         = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState        = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse               = 0;
    TIM_OCInitStructure.TIM_OCPolarity          = TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_OCNPolarity         = TIM_OCNPolarity_Low;
    TIM_OCInitStructure.TIM_OCIdleState         = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState        = TIM_OCIdleState_Reset;

    TIM_OCInitStructure.TIM_OutputState         = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse               = 0;
    TIM_OC1Init(TIM4, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);							//ACTIVE

    TIM_OCInitStructure.TIM_OutputState         = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse               = 0;
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);							//ACTIVE

    //timer enable
    TIM_Cmd(TIM4, ENABLE);
    TIM_CtrlPWMOutputs(TIM4, ENABLE);
}

void konfigurasitimer8(void)
{
    //clock enable
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    //GPIO__TIM_init
    GPIO_InitStructure.GPIO_Pin   = P_9;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_TIM8);

    TIM_TimeBaseStructure.TIM_Period = periodTIM8;//867; Frekuensi 5kHz
    TIM_TimeBaseStructure.TIM_Prescaler = prescaleTIM_APB2;//173;//PrescalerValue;//0;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV2;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

    //Channel 1,2,3, and 4//
    TIM_OCInitStructure.TIM_OCMode              = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState         = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState        = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse               = 0;
    TIM_OCInitStructure.TIM_OCPolarity          = TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_OCNPolarity         = TIM_OCNPolarity_Low;
    TIM_OCInitStructure.TIM_OCIdleState         = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState        = TIM_OCIdleState_Reset;

    TIM_OCInitStructure.TIM_OutputState         = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse               = 0;
    TIM_OC4Init(TIM8, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);							//ACTIVE


    //timer enable
    TIM_Cmd(TIM8, ENABLE);
    TIM_CtrlPWMOutputs(TIM8, ENABLE);
}

void konfigurasitimer10(void)
{
    //clock enable
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    //GPIO__TIM_init
    GPIO_InitStructure.GPIO_Pin   = P_8;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_TIM10);


    TIM_TimeBaseStructure.TIM_Period = periodTIM10;
    TIM_TimeBaseStructure.TIM_Prescaler = prescaleTIM_APB2;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV2;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM10, &TIM_TimeBaseStructure);


    //Channel 1,2,3, and 4//
    TIM_OCInitStructure.TIM_OCMode              = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState         = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState        = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse               = 0;
    TIM_OCInitStructure.TIM_OCPolarity          = TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_OCNPolarity         = TIM_OCNPolarity_Low;
    TIM_OCInitStructure.TIM_OCIdleState         = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState        = TIM_OCIdleState_Reset;


    TIM_OCInitStructure.TIM_OutputState         = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse               = 0;
    TIM_OC1Init(TIM10, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM10, TIM_OCPreload_Enable);							//ACTIVE

    //timer enable
    TIM_Cmd(TIM10, ENABLE);
    TIM_CtrlPWMOutputs(TIM10, ENABLE);
}

void konfigurasitimer11(void)
{
    //clock enable
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    //GPIO__TIM_init
    GPIO_InitStructure.GPIO_Pin   = P_9;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_TIM11);


    TIM_TimeBaseInit(TIM11, &TIM_TimeBaseStructure);
    //timer_init
    TIM_TimeBaseStructure.TIM_Period = periodTIM11;
    TIM_TimeBaseStructure.TIM_Prescaler = prescaleTIM_APB2;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV2;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM11, &TIM_TimeBaseStructure);


    //Channel 1,2,3, and 4//
    TIM_OCInitStructure.TIM_OCMode              = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState         = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState        = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse               = 0;
    TIM_OCInitStructure.TIM_OCPolarity          = TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_OCNPolarity         = TIM_OCNPolarity_Low;
    TIM_OCInitStructure.TIM_OCIdleState         = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState        = TIM_OCIdleState_Reset;


    TIM_OCInitStructure.TIM_OutputState         = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse               = 0;
    TIM_OC1Init(TIM11, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM11, TIM_OCPreload_Enable);							//ACTIVE

    //timer enable
    TIM_Cmd(TIM11, ENABLE);
    TIM_CtrlPWMOutputs(TIM11, ENABLE);
}

void konfigurasitimer12(void)
{
    //clock enable
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    //GPIO__TIM_init
    GPIO_InitStructure.GPIO_Pin   = P_14;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_TIM12);


    //timer_init
    TIM_TimeBaseStructure.TIM_Period = periodTIM12;
    TIM_TimeBaseStructure.TIM_Prescaler = prescaleTIM_APB1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM12, &TIM_TimeBaseStructure);


    //Channel 1,2,3, and 4//
    TIM_OCInitStructure.TIM_OCMode              = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState         = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState        = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse               = 0;
    TIM_OCInitStructure.TIM_OCPolarity          = TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_OCNPolarity         = TIM_OCNPolarity_Low;
    TIM_OCInitStructure.TIM_OCIdleState         = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState        = TIM_OCIdleState_Reset;


    TIM_OCInitStructure.TIM_OutputState         = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse               = 0;
    TIM_OC1Init(TIM12, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM12, TIM_OCPreload_Enable);							//ACTIVE

    //timer enable
    TIM_Cmd(TIM12, ENABLE);
    TIM_CtrlPWMOutputs(TIM12, ENABLE);
}

void TIM5_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

	TIM_TimeBaseInitTypeDef timerInitStructure;
	timerInitStructure.TIM_Prescaler = 3359;  //f per count= 84000000/(3359+1)=25000Hz = 0.00004s
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = 2500; //0.00004*2500=0.1s atau 100ms
//	timerInitStructure.TIM_Period = 1250; //0.00004*1250=0.05s atau 50ms
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM5, &timerInitStructure);
	TIM_Cmd(TIM5, ENABLE); //default di off dulu
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
    NVIC_InitTypeDef nvicStructure;
    nvicStructure.NVIC_IRQChannel = TIM5_IRQn;
    nvicStructure.NVIC_IRQChannelPreemptionPriority = 4;
    nvicStructure.NVIC_IRQChannelSubPriority = 1;
    nvicStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvicStructure);
}

void TIM5_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
	{
		if (Flag_tahan == 1)
		{
			Count_tahan++;
			if (Count_tahan >= 10) { Flag_tahan = 0; Count_tahan = 0; Flag_Posisi++;}
		}
		if (f_stop == 1) c_stop++;
		else if (f_stop == 0) c_stop= 0;
		if (c_g == 1) c_p++;
		else if (c_g == 0) c_p = 0;
		if (F_cnt_rotary == 1){ cnt_rotary++; if (cnt_rotary >= 51) cnt_rotary = 0;}
		else if (F_cnt_rotary == 0)cnt_rotary = 0;
		count_wifi++;
		Counter_LED++;
		kecepatan_robot();
		Counter_Start_Wifi();
		Odometry_Ball_Selection();
		Gripper_Lepas();
//********************* untuk proximity ********************************//
		ProxMode();
//********************** untuk solenoid ********************************//
		catu_solenoid();

		Waktu_Solenoid();
//************************** untuk tuas ********************************//
		Feedback_Tuas();
//*********************** untuk gripper ********************************//
		state_grip();
		waktu_cek_gripper();
//********************************************************************//
		convert_encoder();
	    Odometry_Rotary();
	    Counter_LCD_Clear();

	    TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	}
}

void external_interrupt(void)
{
///////////////////////////////Inisialisasi Interupt Rotary///////////////////////////////////

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	//    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	//    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_3;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	//    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2| GPIO_Pin_7;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	//    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	//    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOE, &GPIO_InitStruct);
///////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////Inisialisasi Data Rotary//////////////////////////////////////

//	DATA pin D
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN;
	//    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_3 | GPIO_Pin_1;
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

//	DATA pin C
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN;
	//    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_1| GPIO_Pin_0;
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

// DATA pin E
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN;
	//    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_12| GPIO_Pin_13;
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOE, &GPIO_InitStruct);

// DATA pin B
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN;
	//    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

//////////////////////////////////////////////////////////////////////////////////////////

	EXTI_InitStruct.EXTI_Line = EXTI_Line0|EXTI_Line1|EXTI_Line2|EXTI_Line3|EXTI_Line4|EXTI_Line7|EXTI_Line10;//|EXTI_Line11;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource4); // Encoder motor 1
	NVIC_InitStruct.NVIC_IRQChannel = EXTI4_IRQn ;//| EXTI1_IRQn | EXTI2_IRQn | EXTI3_IRQn | EXTI4_IRQn | EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource0); //Encoder motor 2
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;//| EXTI1_IRQn | EXTI2_IRQn | EXTI3_IRQn | EXTI4_IRQn | EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource3); // Encoder motor 3
	NVIC_InitStruct.NVIC_IRQChannel = EXTI3_IRQn ;//| EXTI1_IRQn | EXTI2_IRQn | EXTI3_IRQn | EXTI4_IRQn | EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource1); // Encoder motor 4
	NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn ;//| EXTI1_IRQn | EXTI2_IRQn | EXTI3_IRQn | EXTI4_IRQn | EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 4;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource2); // Encoder exteral 1
	NVIC_InitStruct.NVIC_IRQChannel = EXTI2_IRQn ;//| EXTI1_IRQn | EXTI2_IRQn | EXTI3_IRQn | EXTI4_IRQn | EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource10); // Encoder external 2
	NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn  ;//| EXTI1_IRQn | EXTI2_IRQn | EXTI3_IRQn | EXTI4_IRQn | EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource7); // cadangan
	NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn ;//| EXTI1_IRQn | EXTI2_IRQn | EXTI3_IRQn | EXTI4_IRQn | EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

}

void EXTI4_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line4) != RESET)
	{
		if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1) == 0)
		{
			if(Program_Untuk == CERBERUS)
			{
				rt0_m1.encoder--;
				rt0_m1.encoder2--;
				rt0_m1.arah = CLOCKWISE;
			}
			if (Program_Untuk == HYDRA)
			{
				rt_3.encoder--;
				rt_3.encoder2--;
//				rt_5.arah = CLOCKWISE;
			}
			else if (Program_Untuk == ORION)
			{
				rt_8.encoder--;
				rt_8.encoder2--;
				rt_8.arah = CLOCKWISE;
			}
		}
		else{

			if(Program_Untuk == CERBERUS)
			{
				rt0_m1.encoder++;
				rt0_m1.encoder2++;
				rt0_m1.arah = COUNTER_CLOCKWISE;
			}
			if (Program_Untuk == HYDRA)
			{
				rt_3.encoder++;
				rt_3.encoder2++;
//				rt_5.arah = COUNTER_CLOCKWISE;
			}
			else if (Program_Untuk == ORION)
			{
				rt_8.encoder++;
				rt_8.encoder2++;
				rt_8.arah = COUNTER_CLOCKWISE;
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}

void EXTI0_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
		if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3) == 0)
		{
			if(Program_Untuk == CERBERUS)
			{
				rt0_m2.encoder--;
				rt0_m2.encoder2--;
				rt0_m2.arah = CLOCKWISE;
			}
			else if (Program_Untuk == HYDRA)
			{
				rt_4.encoder--;
				rt_4.encoder2--;
//				rt_3.arah = CLOCKWISE;
			}
			else if (Program_Untuk == ORION)
			{
				rt_6.encoder--;
				rt_6.encoder2--;
				rt_6.arah = CLOCKWISE;
			}
		}
		else
		{
			if(Program_Untuk == CERBERUS)
			{
				rt0_m2.encoder++;
				rt0_m2.encoder2++;
				rt0_m2.arah = COUNTER_CLOCKWISE;
			}
			else if (Program_Untuk == HYDRA)
			{
				rt_4.encoder++;
				rt_4.encoder2++;
//				rt_3.arah = COUNTER_CLOCKWISE;
			}
			else if (Program_Untuk == ORION)
			{
				rt_6.encoder++;
				rt_6.encoder2++;
				rt_6.arah = COUNTER_CLOCKWISE;
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void EXTI3_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line3) != RESET)
	{
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0) == 0)
		{
			if(Program_Untuk == CERBERUS)
			{
				rt0_m3.encoder--;
				rt0_m3.encoder2--;
				rt0_m3.arah = CLOCKWISE;
			}
			else if (Program_Untuk == HYDRA)
			{
				rt_5.encoder--;
				rt_5.encoder2--;
//				rt_4.arah = CLOCKWISE;
			}
			else if (Program_Untuk == ORION)
			{
				rt_7.encoder--;
				rt_7.encoder2--;
				rt_7.arah = CLOCKWISE;
			}
		}
		else{
			if(Program_Untuk == CERBERUS)
			{
				rt0_m3.encoder++;
				rt0_m3.encoder2++;
				rt0_m3.arah = COUNTER_CLOCKWISE;
			}
			else if (Program_Untuk == HYDRA)
			{
				rt_5.encoder++;
				rt_5.encoder2++;
//				rt_4.arah = COUNTER_CLOCKWISE;
			}
			else if (Program_Untuk == ORION)
			{
				rt_7.encoder++;
				rt_7.encoder2++;
				rt_7.arah = COUNTER_CLOCKWISE;
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line3);
	}
}

void EXTI1_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line1)!= RESET)
	{
		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12) == 0)
		{
			if(Program_Untuk == CERBERUS)
			{
				rt0_m4.encoder--;
				rt0_m4.encoder2--;
				rt0_m4.arah = CLOCKWISE;
			}
			else if (Program_Untuk == HYDRA)
			{
								rt0_m1.encoder--;//				Belum fix
								rt0_m1.encoder2--;
				//				rt_4.arah = CLOCKWISE;
			}
			else if (Program_Untuk == ORION)
			{
				rt0_m1.encoder--;
				rt0_m1.encoder2--;
				rt0_m1.arah = CLOCKWISE;
				//				rt_7.encoder--;				Belum fix
				//				rt_7.encoder2--;
				//				rt_7.arah = CLOCKWISE;
			}
		}
		else
		{
			if(Program_Untuk == CERBERUS)
			{
				rt0_m4.encoder++;
				rt0_m4.encoder2++;
				rt0_m4.arah = COUNTER_CLOCKWISE;
			}
			else if (Program_Untuk == HYDRA)
			{
				rt0_m1.encoder++;//				Belum fix
				rt0_m1.encoder2++;
				//				rt_4.arah = COUNTER_CLOCKWISE;
			}
			else if (Program_Untuk == ORION)
			{
				rt0_m1.encoder++;
				rt0_m1.encoder2++;
//				rt0_m1.arah = CLOCKWISE;
				//				rt_7.encoder++;				Belum fix
				//				rt_7.encoder2++;
				//				rt_7.arah = COUNTER_CLOCKWISE;
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

void EXTI2_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line2) != RESET)
	{
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1) == 0)
		{
			if(Program_Untuk == CERBERUS)
			{
				rt0_1.encoder--;
				rt0_1.encoder2--;
				rt0_1.arah = CLOCKWISE;
			}
			else if (Program_Untuk == HYDRA)
			{
				rt0_m2.encoder--;//				Belum fix
				rt0_m2.encoder2--;
				//				rt_4.arah = CLOCKWISE;
			}
			else if (Program_Untuk == ORION)
			{
				rt0_m2.encoder--;//				Belum fix
				rt0_m2.encoder2--;
				//				rt_7.encoder--;				Belum fix
				//				rt_7.encoder2--;
				//				rt_7.arah = CLOCKWISE;
			}
		}
		else
		{
			if(Program_Untuk == CERBERUS)
			{
				rt0_1.encoder++;
				rt0_1.encoder2++;
				rt0_1.arah = COUNTER_CLOCKWISE;
			}
			else if (Program_Untuk == HYDRA)
			{
				rt0_m2.encoder++;//				Belum fix
				rt0_m2.encoder2++;	//				rt_4.arah = COUNTER_CLOCKWISE;
			}
			else if (Program_Untuk == ORION)
			{
				rt0_m2.encoder++;//				Belum fix
				rt0_m2.encoder2++;
				//				rt_7.encoder++;				Belum fix
				//				rt_7.encoder2++;
				//				rt_7.arah = COUNTER_CLOCKWISE;
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}

void EXTI15_10_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line10) == 1)
	{
		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13) == 0)
		{
			if(Program_Untuk == CERBERUS)
			{
				rt0_2.encoder--;
				rt0_2.encoder2--;
				rt0_2.arah = CLOCKWISE;
			}
			else if (Program_Untuk == HYDRA)
			{
				rt0_m3.encoder--;//				Belum fix
				rt0_m3.encoder2--;	//				rt_4.arah = CLOCKWISE;
			}
			else if (Program_Untuk == ORION)
			{
				rt0_m3.encoder--;//				Belum fix
				rt0_m3.encoder2--;
				//				rt_7.encoder--;				Belum fix
				//				rt_7.encoder2--;
				//				rt_7.arah = CLOCKWISE;
			}
		}
		else
		{
			if(Program_Untuk == CERBERUS)
			{
				rt0_2.encoder++;
				rt0_2.encoder2++;
				rt0_2.arah = COUNTER_CLOCKWISE;
			}
			else if (Program_Untuk == HYDRA)
			{
				rt0_m3.encoder++;//				Belum fix
				rt0_m3.encoder2++;	//				rt_4.arah = COUNTER_CLOCKWISE;
			}
			else if (Program_Untuk == ORION)
			{
				rt0_m3.encoder++;//				Belum fix
				rt0_m3.encoder2++;
				//				rt_7.encoder++;				Belum fix
				//				rt_7.encoder2++;
				//				rt_7.arah = COUNTER_CLOCKWISE;
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line10);
	}
}

void EXTI9_5_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line7) != RESET)
	{
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) == 1)
		{
			if(Program_Untuk == CERBERUS)
			{
				//				rt0_2.encoder--;		cadangan
				//				rt0_2.encoder2--;
				//				rt0_2.arah = CLOCKWISE;
			}
			else if (Program_Untuk == HYDRA)
			{
				//				rt_4.encoder--;				Belum fix
				//				rt_4.encoder2--;
				//				rt_4.arah = CLOCKWISE;
			}
			else if (Program_Untuk == ORION)
			{
				//				rt_7.encoder--;				Belum fix
				//				rt_7.encoder2--;
				//				rt_7.arah = CLOCKWISE;
			}
		}
		else
		{
			if(Program_Untuk == CERBERUS)
			{
				//				rt0_2.encoder++;		cadangan
				//				rt0_2.encoder2++;
				//				rt0_2.arah = COUNTER_CLOCKWISE;
			}
			else if (Program_Untuk == HYDRA)
			{
				//				rt_4.encoder++;				Belum fix
				//				rt_4.encoder2++;
				//				rt_4.arah = COUNTER_CLOCKWISE;
			}
			else if (Program_Untuk == ORION)
			{
				//				rt_7.encoder++;				Belum fix
				//				rt_7.encoder2++;
				//				rt_7.arah = COUNTER_CLOCKWISE;
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line7);
	}
}

//------------------------------------------------------------------//
void Dir_Motor_Init()
{
//-------------------------ORION---------------------------//
	//------------------- motor 1 --------------------//
	// PB4(TIM3_CH1) & PC8(TIM3_CH3)	= PWM
	// PB5							= EN PIN
	//------------------- motor 2 --------------------//
	// PE9(TIM1_CH1) & PE14(TIM1_CH4)	= PWM
	// PA8								= EN PIN
	//------------------- motor 3 --------------------//
	// PB6(TIM4_CH1) & PB7(TIM4_CH2)	= PWM
	// PB15								= EN PIN
	//----------------- GRIPPER 1 --------------------//
	// PB9(TIM11_CH1)					= PWM
	// PE15 & PB14						= DIR PIN
	//----------------- GRIPPER 2 --------------------//
	// PB8(TIM10_CH1)					= PWM
	// PE10 & PE11						= DIR PIN
	//-------------------- TUAS ----------------------//
	// PC9(TIM8_CH4)					= PWM
	// PC15 & PC6						= DIR PIN
	//------------------------------------------------//
//--------------------------HYDRA---------------------------//
	//------------------- motor 1 --------------------//
	// PB6(TIM4_CH1) & PB7(TIM4_CH2)	= PWM
	// PB5							= EN PIN
	//------------------- motor 2 --------------------//
	// PE9(TIM1_CH1) & PE14(TIM1_CH4)	= PWM
	// PA8								= EN PIN
	//------------------- motor 3 --------------------//
	// PB4(TIM3_CH1) & PC8(TIM3_CH3)	= PWM
	// PB15								= EN PIN
	//----------------- GRIPPER 1 --------------------//
	// PB9(TIM11_CH1)					= PWM
	// PE15 & PB14						= DIR PIN
	//----------------- GRIPPER 2 --------------------//
	// PB8(TIM10_CH1)					= PWM
	// PE10 & PE11						= DIR PIN
	//-------------------- TUAS ----------------------//
	// PC9(TIM8_CH4)					= PWM
	// PC15 & PC6						= DIR PIN
	//------------------------------------------------//

	//inisialisasi pin EN Motor1
	init_IO(RCC_AHB1Periph_GPIOB, GPIO_Pin_5,GPIO_Mode_OUT, GPIO_OType_OD, GPIO_PuPd_NOPULL );
	//inisialisasi pin EN Motor2
	init_IO(RCC_AHB1Periph_GPIOA, GPIO_Pin_8, GPIO_Mode_OUT, GPIO_OType_OD, GPIO_PuPd_NOPULL );
	//inisialisasi pin EN Motor3
	init_IO(RCC_AHB1Periph_GPIOB, GPIO_Pin_15,GPIO_Mode_OUT, GPIO_OType_OD, GPIO_PuPd_NOPULL );

	//inisialisasi pin direction Gripper1 (GRIPPER KIRI)
//	init_IO(RCC_AHB1Periph_GPIOE, GPIO_Pin_14, GPIO_Mode_OUT, GPIO_OType_OD, GPIO_PuPd_NOPULL );	//PIN LAMA
	init_IO(RCC_AHB1Periph_GPIOE, GPIO_Pin_15, GPIO_Mode_OUT, GPIO_OType_OD, GPIO_PuPd_NOPULL );
	init_IO(RCC_AHB1Periph_GPIOB, GPIO_Pin_14, GPIO_Mode_OUT, GPIO_OType_OD, GPIO_PuPd_NOPULL );	// PIN BARU


	//inisialisasi pin direction Gripper2 (GRIPPER KANAN)
	init_IO(RCC_AHB1Periph_GPIOE, GPIO_Pin_10,GPIO_Mode_OUT, GPIO_OType_OD, GPIO_PuPd_NOPULL );
	init_IO(RCC_AHB1Periph_GPIOE, GPIO_Pin_11,GPIO_Mode_OUT, GPIO_OType_OD, GPIO_PuPd_NOPULL );

	//inisialisasi pin direction TUAS
	init_IO(RCC_AHB1Periph_GPIOC, GPIO_Pin_15,GPIO_Mode_OUT, GPIO_OType_OD, GPIO_PuPd_NOPULL );
	init_IO(RCC_AHB1Periph_GPIOC, GPIO_Pin_6, GPIO_Mode_OUT, GPIO_OType_OD, GPIO_PuPd_NOPULL );

	//inisialisasi pin CADANGAN
	init_IO(RCC_AHB1Periph_GPIOA, GPIO_Pin_7, GPIO_Mode_OUT, GPIO_OType_OD, GPIO_PuPd_NOPULL );
	init_IO(RCC_AHB1Periph_GPIOD, GPIO_Pin_14, GPIO_Mode_OUT, GPIO_OType_OD, GPIO_PuPd_NOPULL );
	init_IO(RCC_AHB1Periph_GPIOD, GPIO_Pin_12, GPIO_Mode_OUT, GPIO_OType_OD, GPIO_PuPd_NOPULL );


	//Inisialisasi timer
	konfigurasitimer1();
	konfigurasitimer3();
	konfigurasitimer4();
	konfigurasitimer8();
	konfigurasitimer10();
	konfigurasitimer11();
//	konfigurasitimer12();

//    konfigurasitimer2();

	TIM5_Init();

	//Inisialisasi EXTI
	external_interrupt();
}

void MOTOR1CCW(int speedm1)
{ 									//Motor1
	if (Program_Untuk == ORION)
	{
		int Spd_motor1 	= (uint16_t) (( speedm1 * (periodTIM3 - 1)) / 100);
		TIM3->CCR3 = Spd_motor1;
	}
	if (Program_Untuk == HYDRA)
	{
		int Spd_motor1 	= (uint16_t) (( speedm1 * (periodTIM4 - 1)) / 100);
		TIM4->CCR2 = Spd_motor1;
	}
}
void MOTOR1CW(int speedm1)
{ 									//Motor1
    if (Program_Untuk == ORION)
    {
    	int Spd_motor1 	= (uint16_t) (( speedm1 * (periodTIM3 - 1)) / 100);
    	TIM3->CCR1 = Spd_motor1;
    }
    if (Program_Untuk == HYDRA)
    {
    	int Spd_motor1 	= (uint16_t) (( speedm1 * (periodTIM4 - 1)) / 100);
    	TIM4->CCR1 = Spd_motor1;
    }
}

void MOTOR2CCW(int speedm2)
{ 									//Motor2
    int Spd_motor2 	= (uint16_t) (( speedm2 * (periodTIM1 - 1)) / 100);
    TIM1->CCR4 = Spd_motor2;
}
void MOTOR2CW(int speedm2)
{ 									//Motor2
    int Spd_motor2 	= (uint16_t) (( speedm2 * (periodTIM1 - 1)) / 100);
    TIM1->CCR1 = Spd_motor2;
}
void MOTOR3CCW(int speedm3)
{ 									//Motor3
    if (Program_Untuk == ORION)
    {
    	int Spd_motor3 	= (uint16_t) (( speedm3 * (periodTIM4 - 1))/ 100);
    	TIM4->CCR2 = Spd_motor3;
    }
    if (Program_Untuk == HYDRA)
    {
    	int Spd_motor3 	= (uint16_t) (( speedm3 * (periodTIM3 - 1))/ 100);
    	TIM3->CCR3 = Spd_motor3;
    }
}
void MOTOR3CW(int speedm3)
{ 									//Motor3
    if (Program_Untuk == ORION)
    {
    	int Spd_motor3 	= (uint16_t) (( speedm3 * (periodTIM4 - 1))/ 100);
    	TIM4->CCR1 = Spd_motor3;
    }
    if (Program_Untuk == HYDRA)
    {
    	int Spd_motor3 	= (uint16_t) (( speedm3 * (periodTIM3 - 1))/ 100);
    	TIM3->CCR1 = Spd_motor3;
    }
}
void MOTOR_griper1(int speed_g1)
{ 									//Griper Kiri
//    int Spd_griper1 	= (uint16_t) (( speed_g1 * (periodTIM12 - 1)) / 100);	// PIN LAMA
//    TIM12->CCR1 = Spd_griper1;
	int Spd_griper1 	= (uint16_t) (( speed_g1 * (periodTIM11 - 1)) / 100);	// PIN BARU
    TIM11->CCR1 = Spd_griper1;

}
void MOTOR_griper2(int speed_g2)
{ 									//Griper Kanan
    int Spd_griper2 = (uint16_t) (( speed_g2 * (periodTIM10 - 1)) / 100);
    TIM10->CCR1 = Spd_griper2;
}
void MOTOR_Tuas(int speed_kick)
{ 									//TUAS
    int Spd_kick 	= (uint16_t) (( speed_kick * (periodTIM8 - 1)) / 100);
    TIM8->CCR4 = Spd_kick;
}

void PID_MOTOR1CW(int speedm1, int spd1_real)
{
	if (Program_Untuk == ORION)
	{
		if (speedm1 <= 6) TIM3->CCR1 = 0;
		else
		{
			speed_motor1 = PID_motor_1(speedm1, abs(spd1_real), 0.6, 0);
			int CCR_mt1 = speed_motor1 + abs(spd1_real);
//			lcd_gotoxy(17,3);  sprintf(lcd, "%d",(int) CCR_mt1);  lcd_putstr(lcd);
//			int CCR_mt1 = speedm1;
			CCR_mt1 = (uint16_t) ((CCR_mt1 * (periodTIM3 - 1) / 100));
			if (CCR_mt1 >= periodTIM3) CCR_mt1 = periodTIM3 - 1;
			TIM3->CCR1 = CCR_mt1;
		}
	}
	if (Program_Untuk == HYDRA)
	{
		if (speedm1 <= 6) TIM4->CCR1 = 0;
		else
		{
			speed_motor1 = PID_motor_1(speedm1, abs(spd1_real), 0.6, 0);
			int CCR_mt1 = speed_motor1 + abs(spd1_real);
//			lcd_gotoxy(17,3);  sprintf(lcd, "%d",(int) CCR_mt1);  lcd_putstr(lcd);
//			int CCR_mt1 = speedm1;
			CCR_mt1 = (uint16_t) ((CCR_mt1 * (periodTIM4 - 1) / 100));
			if (CCR_mt1 >= periodTIM4) CCR_mt1 = periodTIM4 - 1;
			TIM4->CCR1 = CCR_mt1;
		}
	}
}
void PID_MOTOR1CCW(int speedm1, int spd1_real)
{
	if (Program_Untuk == ORION)
	{
		if (speedm1 <= 6) TIM3->CCR3 = 0;
		else
		{
			speed_motor1 = PID_motor_1(speedm1, abs(spd1_real), 0.6, 0);
			int CCR_mt1 = speed_motor1 + abs(spd1_real);
//			lcd_gotoxy(17,3);  sprintf(lcd, "%d",(int) CCR_mt1);  lcd_putstr(lcd);
//			int CCR_mt1 = speedm1;
			CCR_mt1 = (uint16_t) ((CCR_mt1 * (periodTIM3 - 1) / 100));
			if (CCR_mt1 >= periodTIM3) CCR_mt1 = periodTIM3 - 1;
			TIM3->CCR3 = CCR_mt1;
		}
	}
	if (Program_Untuk == HYDRA)
	{
		if (speedm1 <= 6) TIM4->CCR2 = 0;
		else
		{
			speed_motor1 = PID_motor_1(speedm1, abs(spd1_real), 0.6, 0);
			int CCR_mt1 = speed_motor1 + abs(spd1_real);
//			lcd_gotoxy(17,3);  sprintf(lcd, "%d",(int) CCR_mt1);  lcd_putstr(lcd);
//			int CCR_mt1 = speedm1;
			CCR_mt1 = (uint16_t) ((CCR_mt1 * (periodTIM4 - 1) / 100));
			if (CCR_mt1 >= periodTIM4) CCR_mt1 = periodTIM4 - 1;
			TIM4->CCR2 = CCR_mt1;
		}
	}
}

void PID_MOTOR2CW(int speedm2, int spd2_real)
{
	if (speedm2 <= 6) TIM1->CCR1 = 0;
	else
	{
		if (Program_Untuk == ORION)	{ speed_motor2 = PID_motor_2(speedm2, abs(spd2_real), 0.6, 0); }
		if (Program_Untuk == HYDRA)	{ speed_motor2 = PID_motor_2(speedm2, abs(spd2_real), 0.6, 0); }
		int CCR_mt2 = speed_motor2 + abs(spd2_real);
//		lcd_gotoxy(17,2);  sprintf(lcd, "%d",(int) CCR_mt2);  lcd_putstr(lcd);
//		int CCR_mt2 = speedm2;
		CCR_mt2 = (uint16_t) ((CCR_mt2 * (periodTIM1 - 1) / 100));
		if (CCR_mt2 >= periodTIM1) CCR_mt2 = periodTIM1 - 1;
		TIM1->CCR1 = CCR_mt2;
	}
}
void PID_MOTOR2CCW(int speedm2, int spd2_real)
{
	if (speedm2 <= 6) TIM1->CCR4 = 0;
	else
	{
		if (Program_Untuk == ORION)	{ speed_motor2 = PID_motor_2(speedm2, abs(spd2_real), 0.6, 0); }
		if (Program_Untuk == HYDRA)	{ speed_motor2 = PID_motor_2(speedm2, abs(spd2_real), 0.6, 0); }
		int CCR_mt2 = speed_motor2 + abs(spd2_real);
//		lcd_gotoxy(17,2);  sprintf(lcd, "%d",(int) CCR_mt2);  lcd_putstr(lcd);
//		int CCR_mt2 = speedm2;
		CCR_mt2 = (uint16_t) ((CCR_mt2 * (periodTIM1 - 1) / 100));
		if (CCR_mt2 >= periodTIM1) CCR_mt2 = periodTIM1 - 1;
		TIM1->CCR4 = CCR_mt2;
	}
}

void PID_MOTOR3CW(int speedm3, int spd3_real)
{
	if (Program_Untuk == ORION)
	{
		if (speedm3 <= 6) TIM4->CCR1 = 0;
		else
		{
			speed_motor3 = PID_motor_3(speedm3, abs(spd3_real), 0.6, 0);
			int CCR_mt3 = speed_motor3 + abs(spd3_real);
//			lcd_gotoxy(17,2);  sprintf(lcd, "%d",(int) CCR_mt3);  lcd_putstr(lcd);
//			int CCR_mt3 = speedm3;
			CCR_mt3 = (uint16_t) ((CCR_mt3 * (periodTIM4 - 1) / 100));
			if (CCR_mt3 >= periodTIM4) CCR_mt3 = periodTIM4 - 1;
			TIM4->CCR1 = CCR_mt3;
		}
	}
	if (Program_Untuk == HYDRA)
	{
		if (speedm3 <= 6) TIM3->CCR1 = 0;
		else
		{
			speed_motor3 = PID_motor_3(speedm3, abs(spd3_real), 0.6, 0);
			int CCR_mt3 = speed_motor3 + abs(spd3_real);
//			lcd_gotoxy(17,3);  sprintf(lcd, "%d",(int) CCR_mt3);  lcd_putstr(lcd);
//			int CCR_mt3 = speedm3;
			CCR_mt3 = (uint16_t) ((CCR_mt3 * (periodTIM3 - 1) / 100));
			if (CCR_mt3 >= periodTIM3) CCR_mt3 = periodTIM3 - 1;
			TIM3->CCR1 = CCR_mt3;
		}
	}
}
void PID_MOTOR3CCW(int speedm3, int spd3_real)
{

	if (Program_Untuk == ORION)
	{
		if (speedm3 <= 6) TIM4->CCR2 = 0;
		else
		{
			speed_motor3 = PID_motor_3(speedm3, abs(spd3_real), 0.56, 0);
			int CCR_mt3 = speed_motor3 + abs(spd3_real);
//			lcd_gotoxy(17,2);  sprintf(lcd, "%d",(int) CCR_mt3);  lcd_putstr(lcd);
//			int CCR_mt3 = speedm3;
			CCR_mt3 = (uint16_t) ((CCR_mt3 * (periodTIM4 - 1) / 100));
			if (CCR_mt3 >= periodTIM4) CCR_mt3 = periodTIM4 - 1;
			TIM4->CCR2 = CCR_mt3;
		}

	}
	if (Program_Untuk == HYDRA)
	{
		if (speedm3 <= 6) TIM3->CCR3 = 0;
		else
		{
			speed_motor3 = PID_motor_3(speedm3, abs(spd3_real), 0.5, 0);
			int CCR_mt3 = speed_motor3 + abs(spd3_real);
//			lcd_gotoxy(17,3);  sprintf(lcd, "%d",(int) CCR_mt3);  lcd_putstr(lcd);
//			int CCR_mt3 = speedm3;
			CCR_mt3 = (uint16_t) ((CCR_mt3 * (periodTIM3 - 1) / 100));
			if (CCR_mt3 >= periodTIM3) CCR_mt3 = periodTIM3 - 1;
			TIM3->CCR3 = CCR_mt3;
		}

	}

}
