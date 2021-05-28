#include "include_lib.h"
#include "enspartan_inisialisasi.h"

void init_IO(uint32_t RCC_AHB1Periph_GPIO, uint16_t Pin, GPIOMode_TypeDef GPIO_Mode,GPIOOType_TypeDef GPIO_OType, GPIOPuPd_TypeDef GPIO_PuPd )
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIO, ENABLE);
    switch(RCC_AHB1Periph_GPIO){
        case ((uint32_t)0x00000001) : GPIO = GPIOA; break;
        case ((uint32_t)0x00000002) : GPIO = GPIOB;	break;
        case ((uint32_t)0x00000004) : GPIO = GPIOC; break;
        case ((uint32_t)0x00000008) : GPIO = GPIOD;	break;
        case ((uint32_t)0x00000010) : GPIO = GPIOE; break;
        case ((uint32_t)0x00000020) : GPIO = GPIOF;	break;
    }

    GPIO_InitStructure.GPIO_Pin = Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode;
    GPIO_InitStructure.GPIO_OType = GPIO_OType;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd;
    GPIO_Init(GPIO, &GPIO_InitStructure);
}
void Pin(GPIO_TypeDef* GPIO,uint8_t Stat, uint16_t Pin){
    switch(Stat){
        case 0x01 : GPIO->BSRRL = Pin; break;
        case 0x02 : GPIO->BSRRH = Pin; break;
        case 0x04 : GPIO->ODR  ^= Pin; break;
    }
}
uint8_t Pin_In(GPIO_TypeDef* GPIO, uint16_t Pin){
    uint8_t bit = 0;
    if((GPIO->IDR & Pin) != 0) bit = 1;	else bit = 0;
    return bit;
}
uint8_t Pin_Out(GPIO_TypeDef* GPIO, uint16_t Pin){
    uint8_t bit = 0;
    if((GPIO->ODR & Pin) != 0) bit = 1;	else bit = 0;
    return bit;
}

void Init_ADC1() // ADC Pin_C4 => ADC1 or ADC2 , Channel 14
{
    ADC_InitTypeDef ADC_init_structure; //Structure for adc confguration
    GPIO_InitTypeDef GPIO_initStructre; //Structure for analog input pin
    //Clock configuration
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//The ADC1 is connected the APB2 peripheral bus thus we will use its clock source
    RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOAEN,ENABLE);//Clock for the ADC port!! Do not forget about this one ;)
	RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOCEN,ENABLE);

    //Analog pin configuration
    GPIO_initStructre.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_0;//The channel 14 is connected to PC4
    GPIO_initStructre.GPIO_Mode = GPIO_Mode_AN; //The PC4 pin is configured in analog mode
    GPIO_initStructre.GPIO_PuPd = GPIO_PuPd_NOPULL; //We don't need any pull up or pull down
    GPIO_Init(GPIOA,&GPIO_initStructre);//Affecting the port with the initialization structure configuration

    GPIO_initStructre.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 |GPIO_Pin_5;//The channel 14 is connected to PC4
    GPIO_initStructre.GPIO_Mode = GPIO_Mode_AN; //The PC4 pin is configured in analog mode
    GPIO_initStructre.GPIO_PuPd = GPIO_PuPd_NOPULL; //We don't need any pull up or pull down
    GPIO_Init(GPIOC,&GPIO_initStructre);//Affecting the port with the initialization structure configuration

	ADC_DeInit();
    ADC_init_structure.ADC_DataAlign = ADC_DataAlign_Right;//data converted will be shifted to right
    ADC_init_structure.ADC_Resolution = ADC_Resolution_6b;//Input voltage is converted into a 8bit number giving a maximum value of 255
    ADC_init_structure.ADC_ContinuousConvMode = DISABLE; //the conversion is continuous, the input data is converted more than once
    ADC_init_structure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;// conversion is synchronous with TIM1 and CC1 (actually I'm not sure about this one :/)
    ADC_init_structure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//no trigger for conversion
    ADC_init_structure.ADC_NbrOfConversion = 5;//I think this one is clear :p
    ADC_init_structure.ADC_ScanConvMode = ENABLE;//The scan is configured in one channel
    ADC_Init(ADC1,&ADC_init_structure);//Initialize ADC with the previous configuration
    //Enable ADC conversion
    ADC_Cmd(ADC1,ENABLE);
   }

int READ_ADC1(int Channel)
{
	ADC_RegularChannelConfig(ADC1,Channel,5,ADC_SampleTime_144Cycles);
    ADC_SoftwareStartConv(ADC1);//Start the conversion
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));//Processing the conversion
    return ADC_GetConversionValue(ADC1); //Return the converted data
}

void Check_Rotary_Switch_MODE(void)
{
    ConvertedValue = READ_ADC1(ADC_Channel_2);//Read the ADC converted value

    //5<< | 14-19-24 | 33-38-43 | 54-57-60 | 61>> | 45-50-53
    // 0	, 21		, 42|43z		, 63		, 63		, 45
    if ( ConvertedValue <= 5)
    {
        //USART6_sendString("MODE = 1 \n", 0); //Rotary_Switch_MODE
        Rotary_Switch_MODE = 1 ;
    }
    else if ( ConvertedValue >= 10 && ConvertedValue <= 19 )
    {
        //USART6_sendString("MODE = 2 \n", 0);
        Rotary_Switch_MODE = 2 ;
    }
    else if ( ConvertedValue >= 20 && ConvertedValue <= 30 )
    {
        //USART6_sendString("MODE = 3 \n", 0);
        Rotary_Switch_MODE = 3 ;
    }
    else if ( ConvertedValue >= 31 && ConvertedValue <= 44 )
    {
        //	USART6_sendString("MODE = 4 \n", 0);
        Rotary_Switch_MODE = 4 ;
    }
    else if ( ConvertedValue >= 45 && ConvertedValue <= 59 )
    {
        //	USART6_sendString("MODE = 5 \n", 0);
        Rotary_Switch_MODE = 5 ;
    }
    else if ( ConvertedValue >= 60  )
    {
        //	USART6_sendString("MODE = 6 \n", 0);
        Rotary_Switch_MODE = 6 ;
    }
}

void inisialisasi_button()
{
    init_IO(RCC_AHB1Periph_GPIOE, GPIO_Pin_0,GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL );
    init_IO(RCC_AHB1Periph_GPIOA, GPIO_Pin_15,GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL );
    init_IO(RCC_AHB1Periph_GPIOE, GPIO_Pin_2,GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL );
    init_IO(RCC_AHB1Periph_GPIOE, GPIO_Pin_3,GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL );
    init_IO(RCC_AHB1Periph_GPIOE, GPIO_Pin_4,GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL );
    init_IO(RCC_AHB1Periph_GPIOE, GPIO_Pin_5,GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL );

}

void LED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
}

/// <summary>
///	   MSB	   LSB
///	   PD7	   PB12
///  	0		1 		=		KEEPER              (   CERBERUS    )
///		1		0		=		STRIKER UTAMA       (   ORION       )
///		1		1		= 		STRIKER ASISTEN     (   HYDRA       )
/// </summary>
void Selektor_Program_Robot(void)
{

	init_IO(RCC_AHB1Periph_GPIOB, GPIO_Pin_12,GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP );
	init_IO(RCC_AHB1Periph_GPIOD, GPIO_Pin_7,GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP );

    int X_LSB = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12);
    int X_MSB = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7);
//	lcd_gotoxy(1,0);  sprintf(lcd, "%d|%d",X_LSB,X_MSB);  lcd_putstr(lcd);

    if ( X_MSB == 0 && X_LSB == 1)
    {
        Program_Untuk = CERBERUS ;
    }
    else if ( X_MSB == 1 && X_LSB == 0)
    {
        Program_Untuk = HYDRA ;
    }
    else if ( X_MSB == 1 && X_LSB == 1)
    {
        Program_Untuk = ORION ;
    }
    else {
        Program_Untuk = 0 ;
    }
}

void Prox_init()
{
	init_IO(RCC_AHB1Periph_GPIOD, GPIO_Pin_13,GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL );	// PROXIM1
//	init_IO(RCC_AHB1Periph_GPIOE, GPIO_Pin_8,GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL );	// jadi pin catu relay solenoid
	init_IO(RCC_AHB1Periph_GPIOC, GPIO_Pin_13,GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL );	// PROXIM2
	init_IO(RCC_AHB1Periph_GPIOB, GPIO_Pin_13,GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL );
}



void Solenoid_Pin_Init()
{
	init_IO(RCC_AHB1Periph_GPIOA, GPIO_Pin_1,GPIO_Mode_OUT, GPIO_OType_OD, GPIO_PuPd_NOPULL );
	init_IO(RCC_AHB1Periph_GPIOA, GPIO_Pin_3,GPIO_Mode_OUT, GPIO_OType_OD, GPIO_PuPd_NOPULL );
	init_IO(RCC_AHB1Periph_GPIOA, GPIO_Pin_5,GPIO_Mode_OUT, GPIO_OType_OD, GPIO_PuPd_NOPULL );
	init_IO(RCC_AHB1Periph_GPIOA, GPIO_Pin_6,GPIO_Mode_OUT, GPIO_OType_OD, GPIO_PuPd_NOPULL );
	init_IO(RCC_AHB1Periph_GPIOB, GPIO_Pin_1,GPIO_Mode_OUT, GPIO_OType_OD, GPIO_PuPd_NOPULL );
}

void State_Awal_Sol()
{
	//------------------ KONDISI AWAL SOLENOID ------------------//
	    solenoid1_state = CHARGING;
	    solenoid2_state = CHARGING;
	    solenoid3_state = CHARGING;
	    solenoid4_state = CHARGING;

	//    solenoid5_state = CHARGING;

	//    Solenoid_Manual_2021(solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state, solenoid5_state);
	    Solenoid_Manual_4Cell_2021(solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state);
}
void catu_solenoid()
{
	if (flag_catu_solenoid == 0)
	{
		count_catu_solenoid++;
//		if (count_catu_solenoid == 5 ) {Solenoid_Pin_Init(); State_Awal_Sol();	}
		if (count_catu_solenoid >= 20) flag_catu_solenoid = 1;
	}
	else if (flag_catu_solenoid == 1)
	{
	    //****************** catu untuk driver solenoid  ****************//
		init_IO(RCC_AHB1Periph_GPIOE, GPIO_Pin_8,GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL );
		Pin(GPIOE,On,P_8); flag_catu_solenoid = 2;
	}
	else if (flag_catu_solenoid == 2) Pin(GPIOE,On,P_8);
}

void inisialisasi_universal()
{
	//Inisialisasi untuk delay
    SystemInit();
    SysTick_Init();

	//****************** DIP SWITCH ****************//
	Selektor_Program_Robot();

    ENSPARTAN_LCD_Init();
    ENSPARTAN_LCD_CLEAR();
    lcd_gotoxy(19,0);	sprintf(lcd,"G");	lcd_putstr(lcd);

//    USArt1_1_Init();
    USArt1_2_Init();
    lcd_gotoxy(0,0);	sprintf(lcd,"2");	lcd_putstr(lcd);
    USArt1_3_Init();
	lcd_gotoxy(2,0);	sprintf(lcd,"3");	lcd_putstr(lcd);
    UART_4_Init();
	lcd_gotoxy(4,0);	sprintf(lcd,"4");	lcd_putstr(lcd);
    UART_5_Init();
	lcd_gotoxy(6,0);	sprintf(lcd,"5");	lcd_putstr(lcd);
//    USART_6_Init();
//    lcd_gotoxy(8,0);	sprintf(lcd,"6");	lcd_putstr(lcd);

	//****************** PUSH BUTTON ****************//
    inisialisasi_button();
    lcd_gotoxy(0,2);	sprintf(lcd,"Button");	lcd_putstr(lcd);
    //****************** LED STRIP ****************//
    LED_Init();
    lcd_gotoxy(8,3);	sprintf(lcd,"LED");	lcd_putstr(lcd);
    //****************** DIR MOTOR ****************//
    Dir_Motor_Init();
    lcd_gotoxy(0,1);	sprintf(lcd,"DIR");	lcd_putstr(lcd);

    if (Program_Untuk == HYDRA)
    {
		Prox_init();
		Solenoid_Pin_Init();
		Init_ADC1();
		Check_Rotary_Switch_MODE();
    }
    else if (Program_Untuk == ORION){
    	Prox_init();
    	Solenoid_Pin_Init();
    	Init_ADC1();
        Check_Rotary_Switch_MODE();
    }

}

void kalibrasi_lapangan(void)
{
//    TUAS_KICKER = 4;
//    FlagADCRotarySwitch = 0;
//
// 	FlagBallFinder = 0;
// 	FlagGeser = 0;
//	FlagStrikerDribble = 0;
//	FlagCorner = 0;
//	FlagPosCorner[0] = 0;
//	FlagGoalKick = 0;
//	FlagKickOff = 0;
//	FlagFreeKick = 0;
//    FlagSolenoid1 = 0;
//    FlagSolenoid2 = 0;
//    FlagSolenoid3 = 0;
//    FlagSolenoid4 = 0;
//    FlagSolenoid5 = 0;
//    SolenoidCounter1 = 0;
//    SolenoidCounter2 = 0;
//    flagMove = 0;
//    gerak_miring = 0;
//    flagTambah = 0;
//    CounterStop = 0;
//    CounterTendang = 0;
//    mode = 0;
//    calibrating2 = NO;
//    calibrating_magneto = NO;
//
//    x_od_pengali = 6.0/x_od_sekarang;
//    y_od_pengali = 9.0/y_od_sekarang;

	//-----------------UKURAN LAPANGAN----------------//
	diameter_bola = 20;
	diameter_gripper =  6;
    X_Lapangan = 600.0;
    Y_Lapangan = 450.0;
    X_Gawang_cm = (int)(X_Lapangan/2.0);
    Y_Gawang_cm = (int)(Y_Lapangan+30.0);

//    X_Real_min = -80.0;
//    X_Real_max = X_Lapangan + 80.0;
//    Y_Real_min = -80.0;
//    Y_Real_max = Y_Lapangan + 80.0;

    X_Real_min = -5*X_Lapangan;
    X_Real_max = 5*X_Lapangan;
    Y_Real_min = -5*Y_Lapangan;
    Y_Real_max = 5*Y_Lapangan;

    X_Basestation_min = 0.0;
    X_Basestation_max = 663.0;//690.0;
    Y_Basestation_min = 0.0;
    Y_Basestation_max = 483.0;

    X_Asli_min[0] = X_Real_min;
    X_Asli_max[0] = 0.0;
    X_Bs_min[0] = 0.0;
    X_Bs_max[0] = 47.0;//36.0;

    Y_Asli_min[0] = Y_Real_min;
    Y_Asli_max[0] = 0.0;
    Y_Bs_min[0] = 0.0;
    Y_Bs_max[0] = 52.0;//36.0;

    X_Asli_min[1] = X_Asli_max[0];
    X_Asli_max[1] = X_Lapangan;
    X_Bs_min[1] = X_Bs_max[0];
    X_Bs_max[1] = 616.0;//654.0;

    Y_Asli_min[1] = Y_Asli_max[0];
    Y_Asli_max[1] = Y_Lapangan;
    Y_Bs_min[1] = Y_Bs_max[0];
    Y_Bs_max[1] = 431;//447.0;

    X_Asli_min[2] = X_Asli_max[1];
    X_Asli_max[2] = X_Real_max;
    X_Bs_min[2] = X_Bs_max[1];
    X_Bs_max[2] = X_Basestation_max;

    Y_Asli_min[2] = Y_Asli_max[1];
    Y_Asli_max[2] = Y_Real_max;
    Y_Bs_min[2] = Y_Bs_max[1];
    Y_Bs_max[2] = Y_Basestation_max;

    if (Program_Untuk == HYDRA){
		lcd_gotoxy(0,0);  sprintf(lcd, "HYDRA");  lcd_putstr(lcd);
    	Jarak_Bola_Dekat = 70;
    	Jarak_Bola_Dekat_Asisten = 65;
    	Jarak_Obs_Dekat = 85;
//		X_Oddo_cm[5] = 25.0;
//		Y_Oddo_cm[5] = -25.0;
		PWM_MAKSIMAL = 70;
    }
    else if (Program_Untuk == ORION){
    	Jarak_Bola_Dekat = 65;
    	Jarak_Bola_Dekat_Utama = 70;
    	Jarak_Obs_Dekat = 80;
		lcd_gotoxy(0,0);  sprintf(lcd, "ORION");  lcd_putstr(lcd);
//		X_Oddo_cm[5] = (X_Lapangan - 25.0);
//		Y_Oddo_cm[5] = -25.0;
		PWM_MAKSIMAL = 80;
    }
	ENSPARTAN_LCD_CLEAR();
	Hitung_Pengali_Terpisah();
	Hitung_Pengali();
}

void setting_robot()
{
//	dummy1 = 1;

	//---------------- reset encoder -------------//
//	rt_3.encoder = 0;
//	rt_3.encoder2 = 0;
//	rt_4.encoder = 0;
//	rt_4.encoder2 = 0;
//	rt_5.encoder = 0;
//	rt_5.encoder2 = 0;

	//---------------- state awal gripper -------------//
	Flag_reset_grip = 1;
	F_Gmundur = 1; F_Gkanan = 1; F_Gmaju = 1; F_Gkiri = 1;
	//------------------ LIMIT SPEED ------------------//
    speed_min  = -10;
    speed_minn =  10;
    speed_max  = -60;
    speed_maxx =  60;

    //------------------ POSISI START ROBOT ------------------//
    if (Program_Untuk == HYDRA)
    {
//    	X_Oddo_cm[5] = 570;
//    	Y_Oddo_cm[5] = 200;
//    	start_hadap = 90;
    	X_Oddo_cm[5] = 30;
    	Y_Oddo_cm[5] = 200;
    	start_hadap =  -90;
        SP_Kamera = 48;
        T_HYDRA.Keadaan_Robot = 8;
    }
    if (Program_Untuk == ORION)
    {
    	//-----ONLINE-----//
    	X_Oddo_cm[5] = 30;
    	Y_Oddo_cm[5] = 200;
//    	X_Oddo_cm[5] = 300;
//    	Y_Oddo_cm[5] = 200;
    	//----OFFLINE-----//
//    	X_Oddo_cm[5] = 30;
//    	Y_Oddo_cm[5] = 400;
    	//----------------//
    	start_hadap =  -90;
    	SP_Kamera = 23;
    	T_ORION.Keadaan_Robot = 9;
    }

	//------------------ KONDISI AWAL SOLENOID ------------------//
	    solenoid1_state = CHARGING;
	    solenoid2_state = CHARGING;
	    solenoid3_state = CHARGING;
	    solenoid4_state = CHARGING;
	    Pin(GPIOB,Off,P_1);
	//    solenoid5_state = CHARGING;

	//    Solenoid_Manual_2021(solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state, solenoid5_state);
	    Solenoid_Manual_4Cell_2021(solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state);
}

void SetMode()
{
//	lcd_gotoxy(19,0); sprintf(lcd, "%d",(int)mode); lcd_putstr(lcd);
	if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0) == 1)
	{
		mode = 1;
	}
	else if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15) == 1)
	{
		mode = 2;
	}
	else if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) == 1)
	{
		mode = 3;
	}
	else if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == 1)
	{
		mode = 4;
	}
	else if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == 1)
	{
		mode = 5;
	}
	else if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5) == 1)
	{
		mode = 6;
	}
}
