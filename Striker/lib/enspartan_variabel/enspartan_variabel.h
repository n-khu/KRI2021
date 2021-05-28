#ifndef ENSPARTAN_VARIABEL_H
#define ENSPARTAN_VARIABEL_H


//------------------ OBJECT STRUCT -----------------//
EXTI_InitTypeDef 			EXTI_InitStruct;
GPIO_InitTypeDef 			GPIO_InitStruct;
NVIC_InitTypeDef 			NVIC_InitStruct;
GPIO_InitTypeDef  			GPIO_InitStructure;
TIM_ICInitTypeDef  			TIM_ICInitStructure;
TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure;
TIM_OCInitTypeDef			TIM_OCInitStructure;
NVIC_InitTypeDef			NVIC_InitStructure;


//******************* Pilih Sesuai Kebutuhan *********************//
//#define UPCLICK GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) == 1		//C
//#define DOWNCLICK GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0) == 1		//A
//#define OKCLICK GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15) == 1		//B
//#define R_UPCLICK GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == 1		//D
//#define BACKCLICK GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == 1		//E
//#define R_DOWNCLICK GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5) == 1	//F
//************************** atau ********************************//
#define UPCLICK GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == 1		//D
#define DOWNCLICK GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) == 1		//C
#define OKCLICK GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == 1		//E
#define R_UPCLICK GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5) == 1		//A
#define BACKCLICK GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15) == 1	//B
#define R_DOWNCLICK GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0) == 1	//F
//***************************************************************//

//--------------- VARIABLE KALIBRASI LAPANGAN ------------------//
extern int X_Gawang_cm, Y_Gawang_cm, X_Obs, Y_Obs, Jarak_Obs;
extern float X_Lapangan, Y_Lapangan;
extern float X_Basestation_min, X_Basestation_max, X_Real_min, X_Real_max, Y_Basestation_min, Y_Basestation_max, Y_Real_min, Y_Real_max;
extern float X_Bs_max[4], X_Bs_min[4], Y_Bs_max[4], Y_Bs_min[4], X_Asli_max[4],X_Asli_min[4], Y_Asli_max[4], Y_Asli_min[4];
extern int Jarak_Bola_Dekat, Jarak_Bola_Dekat_Utama, Jarak_Bola_Dekat_Asisten, Jarak_Obs_Dekat;
extern float Pengali_A, Pengali_B, Penambah_C, Penambah_D;
extern float PengaliA[3], PengaliB[3], PenambahC[3], PenambahD[3];
//-------------- VARIABLE DIP SWITCH --------------//
extern int Program_Untuk;
#define CERBERUS	1
#define HYDRA	2
#define ORION	3

// #define CERBERUS 1		
// #define HYDRA 2
// #define ORION 3

//-------------- SENSORS --------------//
extern int Proxim1,Proxim2,Proxim3,Proxim4,Prox;
extern int kalibrasi_imu,imu_asli,imu_filter,imu_filter_awal, imu_real, reset_imu;
extern int Flag_Switch_Angle;

//--------------------- INPUT -----------------------//
extern int ConvertedValue;
extern int Rotary_Switch_MODE;
extern int mode;
extern int Tuas_Switch1, Tuas_Switch2, Tuas_Pot, Griper_Pot1, Griper_Pot2;
extern int Flag_Tuas;
extern float Tuas_P, Tuas_I, Tuas_D , Tuas_I_ERROR;
//------------------ VARIABLE ROTARY ----------------//
#define CLOCKWISE 1
#define COUNTER_CLOCKWISE -1
#define DIAM 0

//------------------ VARIABLE STATE ----------------//
#define NOPE	0
#define YES		1
#define NO		2
#define OPER	3
#define SHOOT	4
#define NO2		6
#define DRIBEL	7

#define NO_BALL 0
#define ADA_BALL 1
#define OFF 0
#define ON 1
#define BALIK 2
#define NATURAL 3
#define BLINK 8
#define BLINK_FAST 9

#define pi              3.141592653589//7932384626433832795


//---------------- VARIABLE PARSING -----------------//
extern int Data_Wifi;
extern int wifi2020, count_wifi;
extern int Striker_Main_Assist, reserved1, reserved2, reserved3, reserved4;
extern int dummy1,dummy2,dummy3,dummy4;
extern int posisi_robot;
extern int Range_Ball, Angle_Ball, Range_Obs, Angle_Obs;
extern int T_WarnaTIM,T_ModeMain,T_KickOff,T_Mode_Drible;
extern int CounterStartWifi, StartWifi_Detik, FlagPosCorner[10], ModePositioning, ModeMain;

#define WELCOME_Wifi       4
#define START_Wifi         1
#define STOP_Wifi  		   2
#define RESET_Wifi  	   3
#define POSITIONING_Wifi  -1

//---------------- VARIABLE SOLENOID -----------------//
extern int Flag_cas, Counter_cas,Counter_dcas, Siap_tendang,Flag_Loop;
extern int solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state, solenoid5_state;
extern int count_catu_solenoid;
extern int flag_catu_solenoid;

#define CHARGE 			10
#define DISCHARGE 		11
#define CHARGING		0
#define DISCHARGING		1
#define SHOOTING_MODE	3
#define PASSING_MODE	4
#define ALL_MODE		5

//---------------- VARIABLE GRIPPER -----------------//
extern int GRIPPER,Counter_Gripper;
extern int X_awal, Y_awal,C_Giring,C_lepas,Flag_Giring,Perpindahan_Robot;
extern int Counter_Tendang,Flagg_Tendang;
extern float F_Grip_Error1,F_Grip_Error2,Grip_Error1,Grip_P,Grip_I, Grip_I_ERROR,Grip_PI;
extern int value_grip_kanan, value_grip_kiri;
extern int Flag_Gripper1, Flag_Gripper2, Flag_steady_grip, count_steady_grip, Flag_reset_grip, count_gripper;
extern int F_Gmaju, F_Gmundur, F_Gkanan, F_Gkiri;
extern int Flag_cek_count_gripper, cek_count_gripper;

extern float vektor_bola, sudut_bola;
extern float diameter_bola;
extern float diameter_gripper;
extern float spd_grip_kiri, spd_grip_kanan;

#define DRIBBLE_OFF		0
#define DRIBBLE_MAJU	1
#define DRIBBLE_MUNDUR	2
#define DRIBBLE_KANAN	3
#define DRIBBLE_KIRI	4

//--- variable fuzzy gripper ---//
#define ZR	1	//zero
#define PST	2	//positive
#define NS	3	//negative small
#define NM	4	//negative medium
#define NB	5	//negative big
extern int Left_Gripper_Input;
extern int Right_Gripper_Input;

#define FR		6	//Fast reverse
#define MR		7	//medium reverse
#define SR		8	//small reverse
#define FWD		9	//forward
#define STOP	10	//stop
extern int Left_Gripper_Output;
extern int Right_Gripper_Output;

//--------------- VARIABLE UMUM
extern int start_hadap, c_stop, f_stop, f_berhenti;
extern float pitch, roll, MinYaw, ZeroYaw, RealYaw,RealRawYaw,DRealYaw, lastRealYaw, ErrorYaw, YawZeroSUCyan,YawZeroSACyan,YawZeroKCyan,YawZeroSUMagenta,YawZeroSAMagenta,YawZeroKMagenta,FlagMC, prevYaw, yaw2,yaw0, angleToGawangSendiri,angleToGawang, angleToTitik,calibrating,FlagRotate;
extern int calibrating2, catch_error_yaw, calibrating_magneto, PinKalibrasi, yawbase;
extern float yaw, yaw_1, yaw_2, yaw_4, yaw_5, yaw_12, yaw_13;
extern int PWM_MAKSIMAL;
extern int speed_min,speed_minn,speed_max,speed_maxx;
extern int SP_Kamera,nilai_random,Flag_random,nilai_rand,coba_tendang, sudut_tembak,error_tendang;
extern int simpan_posisi_x[2],simpan_posisi_y[2],jarak_perpindahan, kecepatan_perpindahan;
extern int FlagUtama, FlagAsisten;

extern int spd,num,CounterGrip,LastAngle,LastRBall,LastRBall2,LastAngle2,CounterAngle,CounterCorner,CounterLS,CounterStartUtama,CounterManual,CounterRBall,CounterLawan,CounterTendang,CounterStop,CounterOper,CounterDribble,
	cnt[20],FlagPagar,max_cnt,COLOR,x_red,RLap,AreaLap,XLap,YLap,AngleLap,R_Ball,R_Ball_Pos,R_Ball2,R_BallFront,x_green, cnt2, lastNum, y_green, y_red, area, AreaOmni, XOmni, YOmni, angle, angle_2,AngleRot,LastAngleRot,x_area[10],sdt,x_red1[20];

extern int Counter_LED;

//--------------- VARIABLE ODOMETRY dan motor ---------------------//

extern double X_Oddo_mm[14],Y_Oddo_mm[14], Oddo_mm[14], Oddo_cm[14], X_Oddo_Ball[5], Y_Oddo_Ball[5];
extern float X_Oddo_cm[17],Y_Oddo_cm[17], X_Oddo_Enc[14],Y_Oddo_Enc[14];
extern float w[5];

extern int pwm_1, pwm_2, pwm_3, pwm_4;
extern float pwm1, pwm2, pwm3;
extern int range_error,sudut_error;
extern float Hadap_error, Hadap_P, Hadap_I, Hadap_PI, Hadap_tot,error_posisi;
extern float F_Pwm1,F_Pwm2,F_Pwm3,F_Error_Hadap,F_Error_Jarak,F_Error_Sudut, F_Nilai_P, F_Nilai_I, F_Nilai_PI;
extern int manipul_sud;
extern int PWM_Rotate;

extern int Counter_Tendang,Flagg_Tendang,FlagSiapTendang;
extern int c_g, c_p;
extern int sedang_rotate;
extern int f_oper;


extern int cnt_rotary;
extern int F_cnt_rotary, variabel_rotary, variabel_rotary1, variabel_rotary2, variabel_rotary3;


//----------------------- variable PID motor ------------------------//
#define hdp_gawang 1
#define kanan_lapangan 2
#define jauh_gawang 3
#define kiri_lapangan 4
#define diagonal_lapangan 5
#define diagonal_lapangan2 6

extern int eyaw[15],Pwm_er[15],Oddo_er_X[15],Oddo_er_Y[15];
extern int posisi, sp_receive, Flag_Switch_Angle, Flag_er_oddo;

//----------------------- variable PID motor ------------------------//
extern float PID_P, PID_I, PID_D , PID_I_ERROR;
extern float MT1_P, MT1_I, MT1_D , MT1_I_ERROR;
extern float MT2_P, MT2_I, MT2_D, MT2_I_ERROR;
extern float MT3_P, MT3_I, MT3_D, MT3_I_ERROR;
extern int pwm_real_1, pwm_real_2, pwm_real_3;
extern float speed_motor1, speed_motor2, speed_motor3, speed_motor4;

//-------------------------------------------------------------------//

//----------------------- variable strategi ------------------------//
extern int Flag_Posisi;
extern int Flag_tahan;
extern int Count_tahan;
extern int Flag_Gerak, hindar_dummy;
extern int Tujuan_KoorY, Tujuan_KoorX, arahX, arahY;
extern int Flag_timer, Flag_posisi_receive, Flag_reset, reset_posisi, Flag_reset_game, R_DATA;
extern int kickoff_awal, Flag_untuk_reset;

extern int Flag_pos, Current_X, Current_Y, State_Position;
//-------------------------------------------------------------------//

//----------------------- variable strategi OFFLINE ------------------------//
extern int Warna_Team;
#define CYAN	1
#define MAGENTA	2

extern int Mode_Main_Robot;
#define SATU_ROBOT	1
#define DUA_ROBOT	2

extern int Shoot_Down, Shoot_Up, Solenoid_set;
//-------------------------------------------------------------------------//

//-------------------------------------- STRUCTURE ----------------------------------------------------//

//*************************STRUCT ROTARY*********************//
typedef struct{
    uint32_t EXTI_ReadValue1;	//1 --> Baca data pertama
    uint32_t EXTI_ReadValue2;	//2 --> Baca data kedua
    uint8_t CaptureNumber;		//3 --> Penanda
    uint32_t Capture;			//4 --> Data hasil kalkulasi
    float Freq;					//5 --> Frekuensi putaran
    int Rpm;					//6 --> Kecepatan putaran
    float encoder;				//7 --> Data encoder
    int sudut;					//8 --> Data sudut
    float ppr;					//9 --> Data pulse per rotation encoder
    int arah;					//a
    float encoder2;				//b
    float Rpm2;					//c
    float sudut2;				//d
    float yaw_encoder;			//e
    float yaw_encoder2;			//f
    float encoder_yaw;			//g
    float encoder3;				//h
    float time;
    int error;
    int pwm_set;
    float pwm_going;
    int value;

}
Rotary;
//    		  1 2 3 4 5 6 7 8 9   a b c d e f g h
Rotary rt1_3;
Rotary rt1_2;//PENENDANG
//=========== MOTOR GERAK STRIKER UTAMA ==========//
Rotary rt_3; //360 (derajat) = 110 robot 1 , 115 robot 2 //PPR MOTOR 1 136
Rotary rt_4; //PPR MOTOR 2 96
Rotary rt_5; //PPR MOTOR 3 136
//=========== MOTOR GERAK STRIKER ASISTEN ==========//
Rotary rt_6; //PPR MOTOR 1
Rotary rt_7; //PPR MOTOR 2
Rotary rt_8; //PPR MOTOR 3
//=========== MOTOR GERAK KEEPER 4 RODA ==========//
Rotary rt0_m1; //motor1
Rotary rt0_m2; //motor2
Rotary rt0_m3; //motor3
Rotary rt0_m4; //motor4
Rotary rt0_1; //rotary1
Rotary rt0_2; //rotary2
//***********************************************************//

//********************STRUCT DATA PARSING********************//
typedef struct{
	int YAW;				//0
	int Jarak_Bola;			//1
	int Sudut_Bola;			//2
	int Jarak_Obs;			//3
	int Sudut_Obs;			//4
	int Koor_X;				//5
	int Koor_Y;				//6
	int Keadaan_Robot;		//7
	int Robot_aktif;		//8
	int Attack;				//9
	int Deffend;			//10
	int DeathBall_Musuh;	//11
	int DeathBall_Kita;		//12
	int R_Tuas;				//13
	int R_Yaw;				//14
	int R_Oddo_X;			//15
	int R_Oddo_Y;			//16
	int Arah_Tendang;		//17
	int Goto_X;				//18
	int Goto_Y;				//19
}ROBOT;

//  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19
ROBOT T_APOLLO;
ROBOT T_HYDRA;
ROBOT T_ORION;
//***********************************************************//

//********************STRUCT ROBOT STRIKER********************//
typedef struct{
	float 	 Kp;  //set konstanta Kp
	float 	 Kd;  //set konstanta Kd
	float 	 Ki;  //set konstanta Ki
	float    P;
	float 	 I;
	float 	 D;
	float 	 error;
	float 	 last_error;
	float 	 nil_pid;
	float 	 pwm1;
	float 	 pwm2;
	float 	 Ts;
}striker;

striker ball_follow;
striker pos_follow;
striker koor; //Kasih nilai Ki dan Kd
striker Koor_cm;
striker rotate;
striker Rotate_sdt;
striker Rotate_cm;
striker M1;
striker M2;
striker M3;
striker Penendang;
//***********************************************************//

#endif
