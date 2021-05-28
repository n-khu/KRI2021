#ifndef ENSPARTAN_INISIALISASI_H
#define ENSPARTAN_INISIALISASI_H

#define P_0  	GPIO_Pin_0
#define P_1  	GPIO_Pin_1
#define P_2  	GPIO_Pin_2
#define P_3  	GPIO_Pin_3
#define P_4  	GPIO_Pin_4
#define P_5  	GPIO_Pin_5
#define P_6  	GPIO_Pin_6
#define P_7  	GPIO_Pin_7
#define P_8  	GPIO_Pin_8
#define P_9  	GPIO_Pin_9
#define P_10  	GPIO_Pin_10
#define P_11  	GPIO_Pin_11
#define P_12  	GPIO_Pin_12
#define P_13  	GPIO_Pin_13
#define P_14  	GPIO_Pin_14
#define P_15  	GPIO_Pin_15
#define On 	0x01
#define Off 0x02
#define TO 	0x04
#define SYSTICK_RELOAD_VAL 0xA80000
#define SYSTICK_DIV(x) ((x*0x0186)>>16)
GPIO_TypeDef* 		GPIO;
GPIO_InitTypeDef   	GPIO_InitStructure;
static __IO uint32_t 		TimmingDelay;
unsigned int 		Tick;
uint32_t 			mlls;
uint32_t 			mcrs;
uint32_t 			Count;

void init_IO(uint32_t RCC_AHB1Periph_GPIO, uint16_t Pin, GPIOMode_TypeDef GPIO_Mode,GPIOOType_TypeDef GPIO_OType, GPIOPuPd_TypeDef GPIO_PuPd );
void Pin(GPIO_TypeDef* GPIO,uint8_t Stat, uint16_t Pin);
uint8_t Pin_In(GPIO_TypeDef* GPIO, uint16_t Pin);
uint8_t Pin_Out(GPIO_TypeDef* GPIO, uint16_t Pin);

//------------------------------------------------------------------//
void TIM5_Init(void);
void Init_ADC1();
int READ_ADC1(int Channel);
void Check_Rotary_Switch_MODE(void);
void inisialisasi_button();
void LED_Init(void);
void Selektor_Program_Robot(void);
void Prox_init();
void catu_solenoid();
void State_Awal_Sol();
void Solenoid_Pin_Init();
void inisialisasi_universal();
void kalibrasi_lapangan();
void setting_robot();
void SetMode();

#endif
