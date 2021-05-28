#include "include_lib.h"
#include "enspartan_variabel.h"


//--------------- VARIABLE KALIBRASI LAPANGAN ------------------//
int X_Gawang_cm, Y_Gawang_cm, X_Obs, Y_Obs, Jarak_Obs;
float X_Lapangan, Y_Lapangan;
float X_Basestation_min, X_Basestation_max, X_Real_min, X_Real_max, Y_Basestation_min, Y_Basestation_max, Y_Real_min, Y_Real_max;
float X_Bs_max[4], X_Bs_min[4], Y_Bs_max[4], Y_Bs_min[4], X_Asli_max[4],X_Asli_min[4], Y_Asli_max[4], Y_Asli_min[4];
int Jarak_Bola_Dekat, Jarak_Bola_Dekat_Utama, Jarak_Bola_Dekat_Asisten, Jarak_Obs_Dekat;
float Pengali_A, Pengali_B, Penambah_C, Penambah_D;
float PengaliA[3], PengaliB[3], PenambahC[3], PenambahD[3];



//------------- DIP SWITCH -------------//
int Program_Untuk = 0;

//-------------- SENSORS --------------//
int Proxim1,Proxim2,Proxim3,Proxim4,Prox;
int kalibrasi_imu,imu_asli,imu_filter,imu_filter_awal, imu_real, reset_imu;
int Flag_Switch_Angle;

//---------------------- INPUT -----------------------//
int ConvertedValue = 0; //Converted value readed from ADC
int Rotary_Switch_MODE = 0 ;
int mode;
int Tuas_Switch1, Tuas_Switch2, Tuas_Pot, Griper_Pot1, Griper_Pot2;
int Flag_Tuas;
float Tuas_P, Tuas_I, Tuas_D , Tuas_I_ERROR;
//---------------- VARIABLE PARSING -----------------//
int Data_Wifi;
int wifi2020, count_wifi;
int Striker_Main_Assist, reserved1, reserved2, reserved3, reserved4;
int dummy1,dummy2,dummy3,dummy4;
int posisi_robot;
int Range_Ball, Angle_Ball, Range_Obs, Angle_Obs;
int T_WarnaTIM,T_ModeMain,T_KickOff,T_Mode_Drible;
int CounterStartWifi, StartWifi_Detik, FlagPosCorner[10], ModePositioning, ModeMain;

//---------------- VARIABLE SOLENOID -----------------//
int Flag_cas, Counter_cas,Counter_dcas, Siap_tendang,Flag_Loop;
int solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state, solenoid5_state;
int count_catu_solenoid = 0;
int flag_catu_solenoid = 0;

//---------------- VARIABLE GRIPPER -----------------//
int GRIPPER,Counter_Gripper;
int X_awal, Y_awal,C_Giring,C_lepas,Flag_Giring,Perpindahan_Robot;
int Counter_Tendang,Flagg_Tendang;
float F_Grip_Error1,F_Grip_Error2,Grip_Error1,Grip_P,Grip_I, Grip_I_ERROR ,Grip_PI;
int value_grip_kanan, value_grip_kiri;
int Flag_Gripper1, Flag_Gripper2, Flag_steady_grip, count_steady_grip, Flag_reset_grip, count_gripper;
int F_Gmaju, F_Gmundur, F_Gkanan, F_Gkiri;
int Flag_cek_count_gripper, cek_count_gripper;

//--- variable fuzzy gripper ---//
int Left_Gripper_Input;
int Right_Gripper_Input;
int Left_Gripper_Output;
int Right_Gripper_Output;

float vektor_bola, sudut_bola;
float diameter_bola;
float diameter_gripper;
float spd_grip_kiri, spd_grip_kanan;
//--------------- VARIABLE UMUM ---------------------//
int start_hadap, c_stop, f_stop, f_berhenti;
float pitch=0, roll=0, MinYaw = 360, ZeroYaw, RealYaw,RealRawYaw,DRealYaw, lastRealYaw, ErrorYaw, YawZeroSUCyan,YawZeroSACyan,YawZeroKCyan,YawZeroSUMagenta,YawZeroSAMagenta,YawZeroKMagenta,FlagMC, prevYaw, yaw2,yaw0, angleToGawangSendiri,angleToGawang, angleToTitik,calibrating,FlagRotate;
int calibrating2, catch_error_yaw = 0, calibrating_magneto, PinKalibrasi, yawbase;
float yaw, yaw_1, yaw_2, yaw_4, yaw_5, yaw_12, yaw_13;
int PWM_MAKSIMAL;
int SP_Kamera,nilai_random,Flag_random,nilai_rand,coba_tendang, sudut_tembak,error_tendang;
int speed_min,speed_minn,speed_max,speed_maxx;
int simpan_posisi_x[2],simpan_posisi_y[2],jarak_perpindahan, kecepatan_perpindahan;
int FlagUtama = 0, FlagAsisten = 0;

int spd,num,CounterGrip,LastAngle,LastRBall,LastRBall2,LastAngle2,CounterAngle,CounterCorner,CounterLS,CounterStartUtama,CounterManual,CounterRBall,CounterLawan,CounterTendang,CounterStop,CounterOper,CounterDribble,
	cnt[20],FlagPagar,max_cnt,COLOR,x_red,RLap,AreaLap,XLap,YLap,AngleLap,R_Ball,R_Ball_Pos,R_Ball2,R_BallFront,x_green, cnt2, lastNum, y_green, y_red, area, AreaOmni, XOmni, YOmni, angle, angle_2,AngleRot,LastAngleRot,x_area[10],sdt,x_red1[20];

int Counter_LED;

//--------------- VARIABLE ODOMETRY dan MOTOR ---------------------//
double X_Oddo_mm[14],Y_Oddo_mm[14], Oddo_mm[14], Oddo_cm[14], X_Oddo_Ball[5], Y_Oddo_Ball[5];
float X_Oddo_cm[17],Y_Oddo_cm[17], X_Oddo_Enc[14],Y_Oddo_Enc[14];
float w[5];

int pwm_1, pwm_2, pwm_3, pwm_4;
float pwm1, pwm2, pwm3;
int range_error,sudut_error;
float Hadap_error, Hadap_P, Hadap_I, Hadap_PI, Hadap_tot,error_posisi;
float F_Pwm1,F_Pwm2,F_Pwm3,F_Error_Hadap,F_Error_Jarak,F_Error_Sudut, F_Nilai_P, F_Nilai_I, F_Nilai_PI;
int manipul_sud;
int PWM_Rotate;

int Counter_Tendang,Flagg_Tendang,FlagSiapTendang;
int c_g, c_p;
int sedang_rotate;
int f_oper = 0;

int cnt_rotary;
int F_cnt_rotary, variabel_rotary, variabel_rotary1, variabel_rotary2, variabel_rotary3;

//----------------------- variable receive ball ------------------------//
int eyaw[15],Pwm_er[15],Oddo_er_X[15],Oddo_er_Y[15];
int posisi, sp_receive, Flag_Switch_Angle, Flag_er_oddo;
//----------------------- variable PID motor ------------------------//

float PID_P, PID_I, PID_D , PID_I_ERROR;
float MT1_P, MT1_I, MT1_D , MT1_I_ERROR;
float MT2_P, MT2_I, MT2_D, MT2_I_ERROR;
float MT3_P, MT3_I, MT3_D, MT3_I_ERROR;
int pwm_real_1, pwm_real_2, pwm_real_3;
float speed_motor1, speed_motor2, speed_motor3, speed_motor4;

//-------------------------------------------------------------------//

//----------------------- variable strategi ONLINE ------------------------//
int Flag_Posisi = 0;
int Flag_tahan = 0;
int Count_tahan = 0;
int Flag_Gerak, hindar_dummy;
int Tujuan_KoorY, Tujuan_KoorX, arahX, arahY;
int Flag_timer, Flag_posisi_receive, Flag_reset, reset_posisi, Flag_reset_game, R_DATA;
int kickoff_awal, Flag_untuk_reset;

int Flag_pos, Current_X, Current_Y, State_Position;
//-------------------------------------------------------------------------//

//----------------------- variable strategi OFFLINE ------------------------//
int Warna_Team = 0;
int Mode_Main_Robot = 0;
int Shoot_Down, Shoot_Up, Solenoid_set;
//-------------------------------------------------------------------------//

//-------------------------------------------STRUCTURE-------------------------------------------------------//

//*************************STRUCT ROTARY*********************//
//    		  1 2 3 4 5 6 7 8 9   a b c d e f g h
Rotary rt1_3={0,0,0,0,0,0,0,0,115.0,0,0,0,0,0,0,0,0,0,0,0,0};
Rotary rt1_2={0,0,0,0,0,0,0,0,115.0,0,0,0,0,0,0,0,0,0,0,0,0};//PENENDANG
//=========== MOTOR GERAK STRIKER UTAMA ==========//
Rotary rt_3={0,0,0,0,0,0,0,0,2000.0,0,0,0,0,0,0,0,0,0,0,0,0}; //360 (derajat) = 110 robot 1 , 115 robot 2 //PPR MOTOR 1 136
Rotary rt_4={0,0,0,0,0,0,0,0,2000.0,0,0,0,0,0,0,0,0,0,0,0,0}; //PPR MOTOR 2 96
Rotary rt_5={0,0,0,0,0,0,0,0,2000.0,0,0,0,0,0,0,0,0,0,0,0,0}; //PPR MOTOR 3 136
//=========== MOTOR GERAK STRIKER ASISTEN ==========//
Rotary rt_6={0,0,0,0,0,0,0,0,200.0,0,0,0,0,0,0,0,0,0,0,0,0}; //PPR MOTOR 1
Rotary rt_7={0,0,0,0,0,0,0,0,200.0,0,0,0,0,0,0,0,0,0,0,0,0}; //PPR MOTOR 2
Rotary rt_8={0,0,0,0,0,0,0,0,200.0,0,0,0,0,0,0,0,0,0,0,0,0}; //PPR MOTOR 3
//=========== MOTOR GERAK KEEPER 4 RODA ==========//
Rotary rt0_m1={0,0,0,0,0,0,0,0,2000.0,0,0,0,0,0,0,0,0,0,0,0,0}; //motor1
Rotary rt0_m2={0,0,0,0,0,0,0,0,2000.0,0,0,0,0,0,0,0,0,0,0,0,0}; //motor2
Rotary rt0_m3={0,0,0,0,0,0,0,0,2000.0,0,0,0,0,0,0,0,0,0,0,0,0}; //motor3
Rotary rt0_m4={0,0,0,0,0,0,0,0,2000.0,0,0,0,0,0,0,0,0,0,0,0,0}; //motor4
Rotary rt0_1={0,0,0,0,0,0,0,0,2000.0,0,0,0,0,0,0,0,0,0,0,0,0}; //rotary1
Rotary rt0_2={0,0,0,0,0,0,0,0,2000.0,0,0,0,0,0,0,0,0,0,0,0,0}; //rotary2

//***********************************************************//

//********************STRUCT DATA PARSING********************//
//  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19
ROBOT T_APOLLO  	= { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
ROBOT T_HYDRA    	= { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
ROBOT T_ORION		= { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//***********************************************************//

//********************STRUCT ROBOT STRIKER********************//
striker ball_follow = {0.85,0.29,0.03,0,0,0,0,0,0,0,0,1};
striker pos_follow = {1,0,0,0,0,0,0,0,0,0,0,1};
striker koor = {4.6,0,0,0,0,0,0,0,0,0,0,1}; //Kasih nilai Ki dan Kd
striker Koor_cm = {0.53,0,0,0,0,0,0,0,0,0,0,1};
striker rotate = {2.2,0,0,0,0,0,0,0,0,0,0,1};
striker Rotate_sdt = {0.5,0,0,0,0,0,0,0,0,0,0,1};
striker Rotate_cm = {2.2,0,0,0,0,0,0,0,0,0,0,1};
striker M1 = {2.0,0,0,0,0,0,0,0,0,0,0,1};
striker M2 = {2.0,0,0,0,0,0,0,0,0,0,0,1};
striker M3 = {2.0,0,0,0,0,0,0,0,0,0,0,1};
striker Penendang = {1.0,0,0,0,0,0,0,0,0,0,0,1};
//***********************************************************//
