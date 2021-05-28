#ifndef ENSPARTAN_MOTOR_H
#define ENSPARTAN_MOTOR_H

//---------------- VARIABLE TIMER ---------------//

//------------------------ ini yang dipake ----------//
#define prescaleTIM_APB1	11	//TIM3 , TIM4 , TIM12
#define prescaleTIM_APB2	11	//TIM1 , TIM8 , TIM10 , TIM11
#define periodTIM4	6999
#define periodTIM11	13999
#define periodTIM10	13999
//#define periodTIM11	6999	//gripper kiri
//#define periodTIM10	6999	//gripper kanan
#define periodTIM1	13999

#define periodTIM12	6999
#define periodTIM3	6999
#define periodTIM8	13999
//---------------------------------------------------//

//328125
//#define prescaleTIM	256
//#define prescaleTIM_APB1	42	//TIM3 , TIM4 , TIM12
//#define prescaleTIM_APB2	256	//TIM1 , TIM8 , TIM10 , TIM11
//
//#define periodTIM3	249	//mt1
//#define periodTIM1	999	//mt2
//#define periodTIM4	249 //mt3
//
//#define periodTIM11	999
//#define periodTIM10	999
//
//#define periodTIM12	999
//#define periodTIM8	999

//#define prescaleTIM_APB1	255	//TIM3 , TIM4 , TIM12
//#define prescaleTIM_APB2	255	//TIM1 , TIM8 , TIM10 , TIM11
//
//#define periodTIM3	249	//mt1
//#define periodTIM1	999	//mt2
//#define periodTIM4	249 //mt3
//
//#define periodTIM11	999
//#define periodTIM10	999
//
//#define periodTIM12	999
//#define periodTIM8	999
////////////////////

//#define prescaleTIM_APB1	83	//TIM3 , TIM4 , TIM12
//#define prescaleTIM_APB2	255	//TIM1 , TIM8 , TIM10 , TIM11
//#define  periodTIM4			249 //MOTOR1
//#define  periodTIM11		449 //MOTOR2
//#define  periodTIM10		449 //MOTOR3
//#define  periodTIM12		499 //Griper1
//#define  periodTIM3			499 //Griper2
//#define  periodTIM8			499 //TUAS
//#define periodTIM1			499	//mt2

//------------------------------------------------------------------//
void TIM5_Init(void);
void TIM5_IRQHandler(void);

void konfigurasitimer2();
void konfigurasitimer1(void);
void konfigurasitimer3(void);
void konfigurasitimer4(void);
void konfigurasitimer8(void);
void konfigurasitimer10(void);
void konfigurasitimer11(void);
void konfigurasitimer12(void);
uint32_t PrescalerValue;

void Dir_Motor_Init();
//------------------------------------------------------------------//

//----------------------------EXTI----------------------------------//
void external_interrupt(void);
void EXTI4_IRQHandler(void);
void EXTI0_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI15_10_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
//--------------------------- MOTOR --------------------------------//
void MOTOR1CW(int speedm1);
void MOTOR1CCW(int speedm1);
void MOTOR2CW(int speedm2);
void MOTOR2CCW(int speedm2);
void MOTOR3CW(int speedm3);
void MOTOR3CCW(int speedm3);
void MOTOR_griper1(int speed_g1);
void MOTOR_griper2(int speed_g2);
void MOTOR_Tuas(int speed_kick);

void PID_MOTOR1CW(int speedm1, int spd1_real);
void PID_MOTOR1CCW(int speedm1, int spd1_real);
void PID_MOTOR2CW(int speedm2, int spd2_real);
void PID_MOTOR2CCW(int speedm2, int spd2_real);
void PID_MOTOR3CW(int speedm3, int spd3_real);
void PID_MOTOR3CCW(int speedm3, int spd3_real);

#endif
