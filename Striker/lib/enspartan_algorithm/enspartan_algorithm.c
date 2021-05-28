#include "include_lib.h"
#include "enspartan_algorithm.h"


void Parsing_Data(void){
	if (Header == 2){
		if 		( Data1 == 1)	Data_Wifi = WELCOME_Wifi ;
		else if ( Data1 == 2)  	Data_Wifi = START_Wifi;
		else if ( Data1 == 3)  	Data_Wifi = STOP_Wifi;
		else if ( Data1 == 4)  	Data_Wifi = RESET_Wifi;
		}
	if (Header == 13)
	{
		if (Program_Untuk == HYDRA){
			T_HYDRA.Goto_X = Data1;
			T_HYDRA.Goto_Y = Data2;
			T_ORION.Koor_X = Data3 ;
			T_ORION.Koor_Y = Data4;
			wifi2020 = Data5;
		}
		if (Program_Untuk == ORION){
			T_ORION.Goto_X = Data1;
			T_ORION.Goto_Y = Data2;
			T_HYDRA.Koor_X  = Data3;
			T_HYDRA.Koor_Y = Data4;
			wifi2020 = Data5;
		}
	}
	if (Header == 90)
	{
		dummy1 = Data1;
		dummy2 = Data2;
		dummy3 = Data3;
		dummy4 = Data4;
		if (Program_Untuk == ORION) T_HYDRA.Keadaan_Robot = Data5;
		else if (Program_Untuk == HYDRA) T_ORION.Keadaan_Robot = Data5;
	}
	if (Header == 91)
	{
		Striker_Main_Assist = Data1;
	}
//	if (Header == 222){
//		if 		( Data1 == 1)	Data_Wifi = T_HYDRA.Koor_X ;
//		else if ( Data1 == 2)  	Data_Wifi = T_HYDRA.Koor_Y;
//		else if ( Data1 == 3)  	Data_Wifi = T_HYDRA.Jarak_Bola;
//		else if ( Data1 == 4)  	Data_Wifi = T_HYDRA.Sudut_Bola;
//		else if ( Data1 == 5)  	Data_Wifi = T_HYDRA.YAW;
//	}
//	if (Header == 2){
//		Data_Wifi = POSITIONING_Wifi ;
//		if (Data1 == 1)//PARKING
//		{
//			Team_Yang_Menendang = Warna_Team_Kita;
//			if (Data2 == 1)	MODE_POSITIONING = DROPPED_BALL ;
//			else if (Data2 == 2)	MODE_POSITIONING = PARKING ;
//		}
//	if (Data1 == 2)//BOLA_TIM_CYAN
//		{
//			Team_Yang_Menendang = TEAM_CYAN;
//			if 		(Data2 == 1)	MODE_POSITIONING =  KICKOFF ;
//			else if (Data2 == 2)	MODE_POSITIONING =  FREEKICK ;
//			else if (Data2 == 3)    MODE_POSITIONING =  GOALKICK ;
//			else if (Data2 == 4)	MODE_POSITIONING =  THROWIN ;
//			else if (Data2 == 5)    MODE_POSITIONING =  CORNER ;
//			else if (Data2 == 6)    MODE_POSITIONING =  PENALTY ;
//		}
//		else if (Data1 == 3)//BOLA_TIM_MAGENTA
//		{
//			Team_Yang_Menendang = TEAM_MAGENTA;
//			if 		(Data2 == 1)	MODE_POSITIONING =  KICKOFF ;
//			else if (Data2 == 2)	MODE_POSITIONING =  FREEKICK ;
//			else if (Data2 == 3)    MODE_POSITIONING =  GOALKICK ;
//			else if (Data2 == 4)	MODE_POSITIONING =  THROWIN ;
//			else if (Data2 == 5)    MODE_POSITIONING =  CORNER ;
//			else if (Data2 == 6)    MODE_POSITIONING =  PENALTY ;
//		}
//	}
	if (Header == 3){

	}
	if (Header == 4){
		if (Data1 == 1){
			T_APOLLO.Jarak_Bola = Data2;
			T_APOLLO.Sudut_Bola = Data3;
			T_APOLLO.Jarak_Obs = Data4;
			T_APOLLO.Sudut_Obs = Data5;}
		else if (Data1 == 2){
			T_HYDRA.Jarak_Bola = Data2;
			T_HYDRA.Sudut_Bola = Data3;
			T_HYDRA.Jarak_Obs = Data4;
			T_HYDRA.Sudut_Obs = Data5;}
		else if (Data1 == 3){
			T_ORION.Jarak_Bola = Data2;
			T_ORION.Sudut_Bola = Data3;
			T_ORION.Jarak_Obs = Data4;
			T_ORION.Sudut_Obs = Data5;}
	}
	if (Header == 5){
		if (Data1 == 1){
			T_APOLLO.Koor_X = Data2;
			T_APOLLO.Koor_Y = Data3;
			T_APOLLO.Keadaan_Robot = Data4;
			T_APOLLO.Robot_aktif = Data5;}
		else if (Data1 == 2){
			T_HYDRA.Koor_X = Data2;
			T_HYDRA.Koor_Y = Data3;
			T_HYDRA.Keadaan_Robot = Data4;
			T_HYDRA.Robot_aktif = Data5;}
		else if (Data1 == 3){
			T_ORION.Koor_X = Data2;
			T_ORION.Koor_Y = Data3;
			T_ORION.Keadaan_Robot = Data4;
			T_ORION.Robot_aktif = Data5;}
	}
	if (Header == 7){
		Range_Ball = Data1;
		Angle_Ball = Data2;
		Range_Obs = Data3;
		Angle_Obs = Data4;
	}
	if (Header == 99){  				//HYDRA
		if (Data1 == 1){
			T_HYDRA.Attack = Data2;
			T_HYDRA.Deffend = Data3;
			T_HYDRA.DeathBall_Kita = Data4;
			T_HYDRA.DeathBall_Musuh = Data5;}
		else if (Data1 == 2){
			T_HYDRA.Arah_Tendang =Data2;
			T_HYDRA.R_Yaw = Data3;
			T_HYDRA.R_Oddo_X = Data4;
			T_HYDRA.R_Oddo_Y = Data5;}
		else if (Data1 == 3){
			T_HYDRA.R_Tuas = Data2;
			T_HYDRA.Goto_X = Data4;
			T_HYDRA.Goto_Y = Data5;}
	}
	if (Header == 66){  				//ORION
		if (Data1 == 1){
			T_ORION.Attack = Data2;
			T_ORION.Deffend = Data3;
			T_ORION.DeathBall_Kita = Data4;
			T_ORION.DeathBall_Musuh = Data5;}
		else if (Data1 == 2){
			T_ORION.Arah_Tendang =Data2;
			T_ORION.R_Yaw = Data3;
			T_ORION.R_Oddo_X = Data4;
			T_ORION.R_Oddo_Y = Data5;}
		else if (Data1 == 3){
			T_ORION.R_Tuas = Data2;
			T_ORION.Goto_X = Data4;
			T_ORION.Goto_Y = Data5;}
	}
	if (Header == 69){
		T_WarnaTIM = Data1;
		T_ModeMain = Data2;
		T_KickOff = Data3;
		T_ModeMain = Data4;
	}
}
void Parsing_Data_Online(void){
	if (Header == 2){
		if 		( Data1 == 1)	Data_Wifi = WELCOME_Wifi ;
		else if ( Data1 == 2)  	Data_Wifi = START_Wifi;
		else if ( Data1 == 3)  	Data_Wifi = STOP_Wifi;
		else if ( Data1 == 4)  	Data_Wifi = RESET_Wifi;
	}
	if (Header == 7){
		Range_Ball = Data1;
		Angle_Ball = Data2;
		Range_Obs = Data3;
		Angle_Obs = Data4;
	}
	if (Header == 13)
	{
		if (Program_Untuk == HYDRA){
			T_HYDRA.Goto_X = Data1;
			T_HYDRA.Goto_Y = Data2;
			T_ORION.Koor_X = Data3 ;
			T_ORION.Koor_Y = Data4;
			wifi2020 = Data5;
		}
		if (Program_Untuk == ORION){
			T_ORION.Goto_X = Data1;
			T_ORION.Goto_Y = Data2;
			T_HYDRA.Koor_X  = Data3;
			T_HYDRA.Koor_Y = Data4;
			wifi2020 = Data5;
		}
	}
	if (Header == 90)
	{
		dummy1 = Data1;
		dummy2 = Data2;
		dummy3 = Data3;
		dummy4 = Data4;
		if (Program_Untuk == ORION) T_HYDRA.Keadaan_Robot = Data5;
		else if (Program_Untuk == HYDRA) T_ORION.Keadaan_Robot = Data5;
	}
	if (Header == 91)
	{
		Striker_Main_Assist = Data1;
		reserved1 = Data2;
		reserved2 = Data3;
		reserved3 = Data4;
		reserved4 = Data5;
	}
}
void Parsing_Data_Offline(void){
	if (Header == 2){
		if 		( Data1 == 1)	Data_Wifi = WELCOME_Wifi ;
		else if ( Data1 == 2)  	Data_Wifi = START_Wifi;
		else if ( Data1 == 3)  	Data_Wifi = STOP_Wifi;
		else if ( Data1 == 4)  	Data_Wifi = RESET_Wifi;
		}
	if (Header == 3){}

	if (Header == 4){
		if (Data1 == 1){
			T_APOLLO.Jarak_Bola = Data2;
			T_APOLLO.Sudut_Bola = Data3;
			T_APOLLO.Jarak_Obs = Data4;
			T_APOLLO.Sudut_Obs = Data5;}
		else if (Data1 == 2){
			T_HYDRA.Jarak_Bola = Data2;
			T_HYDRA.Sudut_Bola = Data3;
			T_HYDRA.Jarak_Obs = Data4;
			T_HYDRA.Sudut_Obs = Data5;}
		else if (Data1 == 3){
			T_ORION.Jarak_Bola = Data2;
			T_ORION.Sudut_Bola = Data3;
			T_ORION.Jarak_Obs = Data4;
			T_ORION.Sudut_Obs = Data5;}
	}
	if (Header == 5){
		if (Data1 == 1){
			T_APOLLO.Koor_X = Data2;
			T_APOLLO.Koor_Y = Data3;
			T_APOLLO.Keadaan_Robot = Data4;
			T_APOLLO.Robot_aktif = Data5;}
		else if (Data1 == 2){
			T_HYDRA.Koor_X = Data2;
			T_HYDRA.Koor_Y = Data3;
			T_HYDRA.Keadaan_Robot = Data4;
			T_HYDRA.Robot_aktif = Data5;}
		else if (Data1 == 3){
			T_ORION.Koor_X = Data2;
			T_ORION.Koor_Y = Data3;
			T_ORION.Keadaan_Robot = Data4;
			T_ORION.Robot_aktif = Data5;}
	}
	if (Header == 7){
		Range_Ball = Data1;
		Angle_Ball = Data2;
		Range_Obs = Data3;
		Angle_Obs = Data4;
	}
	if (Header == 99){  				//HYDRA
		if (Data1 == 1){
			T_HYDRA.Attack = Data2;
			T_HYDRA.Deffend = Data3;
			T_HYDRA.DeathBall_Kita = Data4;
			T_HYDRA.DeathBall_Musuh = Data5;}
		else if (Data1 == 2){
			T_HYDRA.Arah_Tendang =Data2;
			T_HYDRA.R_Yaw = Data3;
			T_HYDRA.R_Oddo_X = Data4;
			T_HYDRA.R_Oddo_Y = Data5;}
		else if (Data1 == 3){
			T_HYDRA.R_Tuas = Data2;
			T_HYDRA.Goto_X = Data4;
			T_HYDRA.Goto_Y = Data5;}
	}
	if (Header == 66){  				//ORION
		if (Data1 == 1){
			T_ORION.Attack = Data2;
			T_ORION.Deffend = Data3;
			T_ORION.DeathBall_Kita = Data4;
			T_ORION.DeathBall_Musuh = Data5;}
		else if (Data1 == 2){
			T_ORION.Arah_Tendang =Data2;
			T_ORION.R_Yaw = Data3;
			T_ORION.R_Oddo_X = Data4;
			T_ORION.R_Oddo_Y = Data5;}
		else if (Data1 == 3){
			T_ORION.R_Tuas = Data2;
			T_ORION.Goto_X = Data4;
			T_ORION.Goto_Y = Data5;}
	}
	if (Header == 69){
		T_WarnaTIM = Data1;
		T_ModeMain = Data2;
		T_KickOff = Data3;
		T_ModeMain = Data4;
	}
}

void Hitung_Pengali_Terpisah()
{
	for(i=0 ; i< 3; i++){
		PengaliA[i] = (Y_Bs_max[i]-Y_Bs_min[i]) / (X_Asli_max[i]-X_Asli_min[i]);
		PengaliB[i] = (X_Bs_max[i]-X_Bs_min[i]) / (Y_Asli_max[i]-Y_Asli_min[i]);
		PenambahC[i] = (((Y_Bs_max[i]+Y_Bs_min[i]) - (PengaliA[i]*(X_Asli_max[i]+X_Asli_min[i]))) / 2.0);
		PenambahD[i] = (((X_Bs_max[i]+X_Bs_min[i]) - (PengaliB[i]*(Y_Asli_max[i]+Y_Asli_min[i]))) / 2.0);
	}
}

void Hitung_Pengali()
{
	Pengali_A = (X_Basestation_min - X_Basestation_max) / (Y_Real_min - Y_Real_max);
	Pengali_B = (Y_Basestation_min - Y_Basestation_max) / (X_Real_min - X_Real_max);

	Penambah_C = - (Pengali_A * X_Real_min);
	Penambah_D = - (Pengali_B * Y_Real_min);
}

void kecepatan_robot(){
		simpan_posisi_x[2] = X_Oddo_cm[5];
		simpan_posisi_y[2] = Y_Oddo_cm[5];
		int nilai_x = simpan_posisi_x[2] -simpan_posisi_x[1];
		int nilai_y = simpan_posisi_y[2] -simpan_posisi_y[1];
		jarak_perpindahan = sqrt((nilai_x*nilai_x)+(nilai_y*nilai_y));
		kecepatan_perpindahan = jarak_perpindahan/0.1;
		simpan_posisi_x[1] = simpan_posisi_x[2];
		simpan_posisi_y[1] = simpan_posisi_y[2];
}

void Counter_Start_Wifi(void)
{
	if (Data_Wifi == START_Wifi && (FlagUtama != 1 || FlagAsisten != 1)){
		if (CounterStartWifi < 150) CounterStartWifi++;
//		if (CounterStartWifi >= 50 && CounterStartWifi < 60) StartWifi_Detik = 5;
		if (CounterStartWifi >= 60 && CounterStartWifi < 100) StartWifi_Detik = 7;
		else if (CounterStartWifi >= 100) StartWifi_Detik = 10;
	}
	else if (Data_Wifi == STOP_Wifi) {
		CounterStartWifi = 0;
		StartWifi_Detik = 0;
	}
}

void Odometry_Ball_Selection(void){
	if (R_Ball == 0){
//		X_Oddo_Ball[1] = 0;
//		Y_Oddo_Ball[1] = 0;
		if (R_Ball2 != 0){
			X_Oddo_Ball[0] = X_Oddo_Ball[2];
			Y_Oddo_Ball[0] = Y_Oddo_Ball[2];
		}
		else {
			X_Oddo_Ball[0] = X_Oddo_Ball[1];
			Y_Oddo_Ball[0] = Y_Oddo_Ball[1];
		}
	}
	else {
		if (R_Ball2 < R_Ball && R_Ball2 != 0){
			X_Oddo_Ball[0] = X_Oddo_Ball[2];
			Y_Oddo_Ball[0] = Y_Oddo_Ball[2];
		}
		else {
			X_Oddo_Ball[0] = X_Oddo_Ball[1];
			Y_Oddo_Ball[0] = Y_Oddo_Ball[1];
		}
	}
}

void convert_encoder()
{
    if(Program_Untuk == CERBERUS)
	{
//        			(nilai encoder/banyak nilai 1 putaran)
//        	RPM=	-------------------------------------
//        					(sampling time / 60)
		rt0_m1.Rpm2=(rt0_m1.encoder2/3.37078652)*3.45;

		rt0_m2.Rpm2=(rt0_m2.encoder2/3.37078652)*3.45;

		rt0_m3.Rpm2=(rt0_m3.encoder2/3.37078652)*3.45;

		rt0_m4.Rpm2=(rt0_m4.encoder2/3.37078652)*3.45;

		rt0_1.Rpm2 =(rt0_1.encoder2/3.37078652)*3.45;

		rt0_2.Rpm2 =(rt0_2.encoder2/3.37078652)*3.45;

		rt0_m1.encoder2 =0;
		rt0_m2.encoder2 =0;
		rt0_m3.encoder2 =0;
		rt0_m4.encoder2 =0;
		rt0_1.encoder2 =0;
		rt0_2.encoder2 =0;
	}
    else if (Program_Untuk == HYDRA)
    {
    	//************************ ROTARY EXTERNAL **************************//
   			rt_3.Freq = -40;
   			rt_3.Rpm2 = (rt_3.encoder2*rt_3.Freq*60)/rt_3.ppr;

   			rt_4.Freq = -40;
   			rt_4.Rpm2 = (rt_4.encoder2*rt_4.Freq*60)/rt_4.ppr;

   			rt_5.Freq = -40;
   			rt_5.Rpm2 = (rt_5.encoder2*rt_5.Freq*60)/rt_5.ppr;

   			rt_3.encoder2 = 0;
   	        rt_4.encoder2 = 0;
   	        rt_5.encoder2 = 0;

   	    //*******************************************************************//
   	    //************************ ROTARY INTERNAL **************************//
			rt_3.Freq = -40;
			rt0_m1.Rpm2 = (rt0_m1.encoder2*rt_3.Freq*60)/200;

			rt_4.Freq = -40;
			rt0_m2.Rpm2 = (rt0_m2.encoder2*rt_4.Freq*60)/200;

			rt_5.Freq = -40;
			rt0_m3.Rpm2 = (rt0_m3.encoder2*rt_5.Freq*60)/200;

			rt0_m1.encoder2 = 0;
			rt0_m2.encoder2 = 0;
			rt0_m3.encoder2 = 0;
		//******************************************************************//
   	}
	else if (Program_Untuk == ORION){
		//************************ ROTARY EXTERNAL **************************//
		rt_6.Freq = -40;
		rt_6.Rpm2 = (rt_6.encoder2*rt_6.Freq*60)/rt_6.ppr;

		rt_7.Freq = -40;
		rt_7.Rpm2 = (rt_7.encoder2*rt_7.Freq*60)/rt_7.ppr;

		rt_8.Freq = -40;
		rt_8.Rpm2 = (rt_8.encoder2*rt_8.Freq*60)/rt_8.ppr;

		rt_6.encoder2 = 0;
		rt_7.encoder2 = 0;
		rt_8.encoder2 = 0;
		//*******************************************************************//
		//************************ ROTARY INTERNAL **************************//
		rt_6.Freq = -40;
		rt0_m1.Rpm2 = (rt0_m1.encoder2*rt_6.Freq*60)/200;

		rt_7.Freq = -40;
		rt0_m2.Rpm2 = (rt0_m2.encoder2*rt_7.Freq*60)/200;

		rt_8.Freq = -40;
		rt0_m3.Rpm2 = (rt0_m3.encoder2*rt_8.Freq*60)/200;

		rt0_m1.encoder2 = 0;
		rt0_m2.encoder2 = 0;
		rt0_m3.encoder2 = 0;
		//******************************************************************//
	}
}

void Waktu_Solenoid(){
if (Flag_cas != 0){						//biar tidak langsung Charge
	Counter_cas++;
	if(Counter_cas >= 30){
		Flag_cas = 0;
		Counter_cas = 0;}
}

else if(Flag_cas == 0 && Siap_tendang == 0){
	Counter_dcas++;
	if(Counter_dcas >= 30){
		Siap_tendang = 1;
		Counter_dcas = 0;}
	}
}

void Gripper_Lepas(){
	if(GRIPPER == 2 || GRIPPER == 1)Counter_Gripper++;
	if (Proxim1 == 0) {
		C_Giring++;
		if(C_Giring >= 3 && Flag_Giring == 0){
			X_awal = X_Oddo_cm[5];
			Y_awal = Y_Oddo_cm[5];
			Flag_Giring = 1;}
		else if(C_Giring >= 3 && Flag_Giring == 1){
			int nilai_XX = X_Oddo_cm[5] - X_awal;
			int nilai_YY = Y_Oddo_cm[5] - Y_awal;
			Perpindahan_Robot = sqrt((nilai_XX*nilai_XX)+(nilai_YY*nilai_YY));}
		else if(C_Giring >= 3 && Flag_Giring == 3)C_lepas++;
	}
	else if(Proxim1 == 1){
		Flag_Giring = 0;
		Perpindahan_Robot = 0;
		C_Giring = 0;
	}
}

void ProxMode(){
	if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_13) == 1) Proxim1 = 1;
	else if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_13) == 0) Proxim1 = 0;

	if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == 1) Proxim2 = 1;
	else if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == 0) Proxim2 = 0;

	//	if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8) == 1) Proxim3 = 1;
//	else if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8) == 0) Proxim3 = 0;


	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == 1) Proxim4 = 1;
	else if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == 0) Proxim4 = 0;

	if (Proxim1 == 0 && Proxim2 == 0) Prox = 0;
//	if (Proxim1 == 0 || Proxim2 == 0) Prox = 0;
	else if (Proxim1 == 1 && Proxim2 == 1) {
//		FlagTendangBayu = 0;
		Counter_Tendang = 0;
		Prox = 1;
	}
	else if (Proxim1 == 1 && Proxim2 == 0) Prox = 2;
	else if (Proxim1 == 0 && Proxim2 == 1) Prox = 3;
}

void LED (int state){
	if (state == ON) Pin(GPIOE,On,P_7);
	else if (state== OFF) Pin(GPIOE,Off,P_7);
	else if (state == BLINK){
		if (Counter_LED <= 5) Pin(GPIOE,On,P_7);
		else if (Counter_LED <=10 )Pin(GPIOE,Off,P_7);
		else Counter_LED = 0;
	}
	else if (state == BLINK_FAST){
		if (Counter_LED <= 2) Pin(GPIOE,On,P_7);
		else if (Counter_LED <=4 )Pin(GPIOE,Off,P_7);
		else Counter_LED = 0;
	}
}

void Odometry_Rotary(void)
{
	if (Program_Untuk == HYDRA){
		w[1] = rt_3.Rpm2;
		w[2] = rt_4.Rpm2;
		w[3] = rt_5.Rpm2;
	}
	else if (Program_Untuk == ORION){
		w[1] = rt_6.Rpm2;
		w[2] = rt_7.Rpm2;
		w[3] = rt_8.Rpm2;
	}

	double theta1 = imu_filter + 30.0;
	double theta2 = imu_filter + 270.0;
	double theta3 = imu_filter + 150.0;
//	double theta1 = imu_filter + 10.75	+ 70.75;
//	double theta2 = imu_filter + 250.75 + 70.75;
//	double theta3 = imu_filter + 130.75 + 70.75;

	X_Oddo_cm[1] = w[1]*sin((theta1*pi)/180.0);
	X_Oddo_cm[2] = w[2]*sin((theta2*pi)/180.0);
	X_Oddo_cm[3] = w[3]*sin((theta3*pi)/180.0);

	if (Program_Untuk == HYDRA){ ///0.015412 (5-6) 0.015351 (2)
//		X_Oddo_cm[5] = X_Oddo_cm[5] + ((X_Oddo_cm[1] + X_Oddo_cm[2] + X_Oddo_cm[3])*0.017351 /*0.0104106 0.0052053*/) ;

		X_Oddo_cm[5] = X_Oddo_cm[5] + ((X_Oddo_cm[1] + X_Oddo_cm[2] + X_Oddo_cm[3])*0.015301 * 1.19 * 0.906919108 * 1.2345679 ) ;
//		X_Oddo_cm[5] = X_Oddo_cm[5] + ((X_Oddo_cm[1] + X_Oddo_cm[2] + X_Oddo_cm[3])*0.015301*1.19 /*0.0104106 0.0052053*/) ;
	}
	else if (Program_Untuk == ORION){
//		X_Oddo_cm[5] = X_Oddo_cm[5] + ((X_Oddo_cm[1] + X_Oddo_cm[2] + X_Oddo_cm[3]) * 0.000189154 *0.934579439);
		X_Oddo_cm[5] = X_Oddo_cm[5] + ((X_Oddo_cm[1] + X_Oddo_cm[2] + X_Oddo_cm[3]) * 0.000189154 *0.934579439 * 1.04895105);
//		X_Oddo_cm[5] = X_Oddo_cm[5] + ((X_Oddo_cm[1] + X_Oddo_cm[2] + X_Oddo_cm[3]) * 1.096027933 * 0.00052053 * 0.281690141*1.1 * 1.07) ;//(0.006073));
//		X_Oddo_cm[5] = X_Oddo_cm[5] + ((X_Oddo_cm[1] + X_Oddo_cm[2] + X_Oddo_cm[3]) * 0.007705/*(0.007705) * (2.0/3.0)*/) ;//(0.006073));
	}

	X_Oddo_cm[1] = 0;
	X_Oddo_cm[2] = 0;
	X_Oddo_cm[3] = 0;

	if(X_Oddo_cm[5]>(X_Real_max)) X_Oddo_cm[5] = (X_Real_max);
	if(X_Oddo_cm[5]<(X_Real_min)) X_Oddo_cm[5] = (X_Real_min);

	Y_Oddo_cm[1] = w[1]*cos((theta1*pi)/180.0);
	Y_Oddo_cm[2] = w[2]*cos((theta2*pi)/180.0);
	Y_Oddo_cm[3] = w[3]*cos((theta3*pi)/180.0);

	if (Program_Untuk == HYDRA){
//		Y_Oddo_cm[5] = Y_Oddo_cm[5] + ((Y_Oddo_cm[1] + Y_Oddo_cm[2] + Y_Oddo_cm[3])*0.017351/*0.0104106 * 0.0052053*/);
		Y_Oddo_cm[5] = Y_Oddo_cm[5] + ((Y_Oddo_cm[1] + Y_Oddo_cm[2] + Y_Oddo_cm[3])*0.015301 * 1.19 * 0.918464364 * 1.07526882);
//		Y_Oddo_cm[5] = Y_Oddo_cm[5] + ((Y_Oddo_cm[1] + Y_Oddo_cm[2] + Y_Oddo_cm[3])*0.015301 * 1.19/*0.0104106 * 0.0052053*/);
	}
	else if (Program_Untuk == ORION){
		Y_Oddo_cm[5] = Y_Oddo_cm[5] + ((Y_Oddo_cm[1] + Y_Oddo_cm[2] + Y_Oddo_cm[3]) * 0.000188399 *0.84*1.1 * 1.14942529 * 0.9090/**0.934579439*/);
//		Y_Oddo_cm[5] = Y_Oddo_cm[5] + ((Y_Oddo_cm[1] + Y_Oddo_cm[2] + Y_Oddo_cm[3]) * 1.189877298 * 0.853625578 * 0.00052053 * 0.281690141* 1.1 * 1.15) ;
//		Y_Oddo_cm[5] = Y_Oddo_cm[5] + ((Y_Oddo_cm[1] + Y_Oddo_cm[2] + Y_Oddo_cm[3]) * 0.00/*(0.007705) * (2.0/3.0)*/) ;//0.00911062(0.006073));
	}

	Y_Oddo_cm[1] = 0;
	Y_Oddo_cm[2] = 0;
	Y_Oddo_cm[3] = 0;

	if(Y_Oddo_cm[5]>(Y_Real_max)) Y_Oddo_cm[5] = (Y_Real_max);
	if(Y_Oddo_cm[5]<(Y_Real_min)) Y_Oddo_cm[5] = (Y_Real_min);

}

//************************************************ FUNGSI SOLENOID ******************************************//
void Solenoid_Manual_2021(int S1, int S2, int S3, int S4, int S5)
{
//-------------------------------NOTE-------------------------------//
//						S1 - S4 = Solenoid kick						//
//						S5		= Solenoid passing					//
//------------------------------------------------------------------//

	if (S1 == 1)Pin(GPIOA,On,P_1);
	else if (S1 == 0)Pin(GPIOA,Off,P_1);
	if (S2 == 1)Pin(GPIOA,On,P_3);
	else if (S2 == 0)Pin(GPIOA,Off,P_3);
	if (S3 == 1)Pin(GPIOA,On,P_5);
	else if (S3 == 0)Pin(GPIOA,Off,P_5);
	if (S4 == 1)Pin(GPIOA,On,P_6);
	else if (S4 == 0)Pin(GPIOA,Off,P_6);
	if (S5 == 1)Pin(GPIOB,On,P_1);
	else if (S5 == 0)Pin(GPIOB,Off,P_1);

	solenoid1_state = S1;
	solenoid2_state = S2;
	solenoid3_state = S3;
	solenoid4_state = S4;
	solenoid5_state = S5;
}

void Solenoid_Manual_4Cell_2021(int S1, int S2, int S3, int S4)
{
//-------------------------------NOTE-------------------------------//
//						S1 - S3 = Solenoid kick						//
//						S4		= Solenoid passing					//
//------------------------------------------------------------------//

	if (S1 == 1)Pin(GPIOA,On,P_1);
	else if (S1 == 0)Pin(GPIOA,Off,P_1);
	if (S2 == 1)Pin(GPIOA,On,P_3);
	else if (S2 == 0)Pin(GPIOA,Off,P_3);
	if (S3 == 1)Pin(GPIOA,On,P_5);
	else if (S3 == 0)Pin(GPIOA,Off,P_5);
	if (S4 == 1)Pin(GPIOA,On,P_6);
	else if (S4 == 0)Pin(GPIOA,Off,P_6);

	solenoid1_state = S1;
	solenoid2_state = S2;
	solenoid3_state = S3;
	solenoid4_state = S4;
}

void SOLENOID_ALGORITHM(int kondisi, int jumlah, int mode)
{ //ALGORITMA SOLENOID

	if (mode == SHOOTING_MODE)
	{
		if (kondisi == CHARGE)
		{
			if (Flag_cas == 0)
			{
				if (jumlah == 1) {solenoid4_state = CHARGING;}
				if (jumlah == 2) {solenoid3_state = CHARGING; solenoid4_state = CHARGING;}
				if (jumlah == 3) {solenoid2_state = CHARGING; solenoid3_state = CHARGING; solenoid4_state = CHARGING;}
				if (jumlah == 4) {solenoid1_state = CHARGING; solenoid2_state = CHARGING; solenoid3_state = CHARGING; solenoid4_state = CHARGING;}
				Solenoid_Manual_2021(solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state, solenoid5_state);
			}
			else if (Flag_cas != 0)
			{
				Solenoid_Manual_2021(solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state, solenoid5_state);
			}
		}
		else if (kondisi == DISCHARGE)
		{
			if (Siap_tendang == 1)
			{
				if (jumlah == 1) {solenoid4_state = DISCHARGING;}
				if (jumlah == 2) {solenoid3_state = DISCHARGING; solenoid4_state = DISCHARGING;}
				if (jumlah == 3) {solenoid2_state = DISCHARGING; solenoid3_state = DISCHARGING; solenoid4_state = DISCHARGING;}
				if (jumlah == 4) {solenoid1_state = DISCHARGING; solenoid2_state = DISCHARGING; solenoid3_state = DISCHARGING; solenoid4_state = DISCHARGING;}
				Solenoid_Manual_2021(solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state, solenoid5_state);
				Flag_cas = 4; Siap_tendang = 0;
			}
			else if (Siap_tendang == 0)
			{
				Solenoid_Manual_2021(solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state, solenoid5_state);
			}
		}
	}
	else if (mode == PASSING_MODE)
	{
		if (kondisi == CHARGE)
		{
			if (Flag_cas == 0)
			{
				solenoid5_state = CHARGING;
				Solenoid_Manual_2021(solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state, solenoid5_state);
			}
			else if (Flag_cas != 0)
			{
				Solenoid_Manual_2021(solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state, solenoid5_state);
			}
		}
		else if (kondisi == DISCHARGE)
		{
			if (Siap_tendang == 1)
			{
				solenoid5_state = DISCHARGING;
				Solenoid_Manual_2021(solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state, solenoid5_state);
				Flag_cas = 5; Siap_tendang = 0;
			}
			else if (Siap_tendang == 0)
			{
				Solenoid_Manual_2021(solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state, solenoid5_state);
			}
//			if (solenoid5_state == 0){lcd_gotoxy(19,3);  sprintf(lcd, "a");  	   lcd_putstr(lcd);}
//			else if (solenoid5_state == 1){lcd_gotoxy(19,3);  sprintf(lcd, "b");  	   lcd_putstr(lcd);}
		}
	}
	else if (mode == ALL_MODE)
	{
		if (kondisi == CHARGE)
		{
			if (Flag_cas == 0)
			{
				solenoid1_state = CHARGING;
				solenoid2_state = CHARGING;
				solenoid3_state = CHARGING;
				solenoid4_state = CHARGING;
				solenoid5_state = CHARGING;
				Solenoid_Manual_2021(solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state, solenoid5_state);
			}
			else if (Flag_cas != 0)
			{
				Solenoid_Manual_2021(solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state, solenoid5_state);
			}
		}
		else if (kondisi == DISCHARGE)
		{
			if (Siap_tendang == 1)
			{
				solenoid1_state = DISCHARGING;
				solenoid2_state = DISCHARGING;
				solenoid3_state = DISCHARGING;
				solenoid4_state = DISCHARGING;
				solenoid5_state = DISCHARGING;
				Solenoid_Manual_2021(solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state, solenoid5_state);
				Flag_cas = 6; Siap_tendang = 0;
			}
			else if (Siap_tendang == 0)
			{
				Solenoid_Manual_2021(solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state, solenoid5_state);
			}
		}
	}

}

void SOLENOID_ALGORITHM_4Cell(int kondisi, int jumlah, int mode)
{ //ALGORITMA SOLENOID

	if (mode == SHOOTING_MODE)
	{
		if (kondisi == CHARGE)
		{
			if (Flag_cas == 0)
			{
				if (jumlah == 1) {solenoid3_state = CHARGING;}
				if (jumlah == 2) {solenoid2_state = CHARGING; solenoid3_state = CHARGING;}
				if (jumlah == 3) {solenoid1_state = CHARGING; solenoid2_state = CHARGING; solenoid3_state = CHARGING;}
				Solenoid_Manual_4Cell_2021(solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state);
			}
			else if (Flag_cas != 0)
			{
				Solenoid_Manual_4Cell_2021(solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state);
			}
		}
		else if (kondisi == DISCHARGE)
		{
			if (Siap_tendang == 1)
			{
				if (jumlah == 1) {solenoid3_state = DISCHARGING;}
				if (jumlah == 2) {solenoid2_state = DISCHARGING; solenoid3_state = DISCHARGING;}
				if (jumlah == 3) {solenoid1_state = DISCHARGING; solenoid2_state = DISCHARGING; solenoid3_state = DISCHARGING;}
				Solenoid_Manual_4Cell_2021(solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state);
				Flag_cas = 4; Siap_tendang = 0;
			}
			else if (Siap_tendang == 0)
			{
				Solenoid_Manual_4Cell_2021(solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state);
			}
		}
	}
	else if (mode == PASSING_MODE)
	{
		if (kondisi == CHARGE)
		{
			if (Flag_cas == 0)
			{
				solenoid4_state = CHARGING;
				Solenoid_Manual_4Cell_2021(solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state);
			}
			else if (Flag_cas != 0)
			{
				Solenoid_Manual_4Cell_2021(solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state);
			}
		}
		else if (kondisi == DISCHARGE)
		{
			if (Siap_tendang == 1)
			{
				solenoid4_state = DISCHARGING;
				Solenoid_Manual_4Cell_2021(solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state);
				Flag_cas = 5; Siap_tendang = 0;
			}
			else if (Siap_tendang == 0)
			{
				Solenoid_Manual_4Cell_2021(solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state);
			}
		}
	}
	else if (mode == ALL_MODE)
	{
		if (kondisi == CHARGE)
		{
			if (Flag_cas == 0)
			{
				solenoid1_state = CHARGING;
				solenoid2_state = CHARGING;
				solenoid3_state = CHARGING;
				solenoid4_state = CHARGING;
				Solenoid_Manual_4Cell_2021(solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state);
			}
			else if (Flag_cas != 0)
			{
				Solenoid_Manual_4Cell_2021(solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state);
			}
		}
		else if (kondisi == DISCHARGE)
		{
			if (Siap_tendang == 1)
			{
				solenoid1_state = DISCHARGING;
				solenoid2_state = DISCHARGING;
				solenoid3_state = DISCHARGING;
				solenoid4_state = DISCHARGING;
				Solenoid_Manual_4Cell_2021(solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state);
				Flag_cas = 6; Siap_tendang = 0;
			}
			else if (Siap_tendang == 0)
			{
				Solenoid_Manual_4Cell_2021(solenoid1_state, solenoid2_state, solenoid3_state, solenoid4_state);
			}
		}
	}

}
//***********************************************************************************************************//

//************************************************ FUNGSI GRIPPER *******************************************//
void Gripper1_IN(int PWM_Gripper_Kiri)
{
	if ((PWM_Gripper_Kiri <= 15 && PWM_Gripper_Kiri > 0) && Flag_Gripper1 == 0)
	{
		MOTOR_griper1(16);
		Pin(GPIOB,Off,P_14);
		Pin(GPIOE,On,P_15);
		Flag_Gripper1 = 1;
	}
	else
	{
		MOTOR_griper1(PWM_Gripper_Kiri);
		Pin(GPIOB,Off,P_14);
		Pin(GPIOE,On,P_15);
	}
}
void Gripper1_OUT(int PWM_Gripper_Kiri)
{
	if ((PWM_Gripper_Kiri <= 15 && PWM_Gripper_Kiri > 0) && Flag_Gripper1 == 0)
	{
		MOTOR_griper1(16);
		Pin(GPIOB,On,P_14);
		Pin(GPIOE,Off,P_15);
		Flag_Gripper1 = 1;
	}
	else
	{
		MOTOR_griper1(PWM_Gripper_Kiri);
		Pin(GPIOB,On,P_14);
		Pin(GPIOE,Off,P_15);
	}
}
void Gripper1_OFF()
{
	MOTOR_griper1(0);
	Pin(GPIOB,Off,P_14);
	Pin(GPIOE,Off,P_15);
}
void Gripper2_IN(int PWM_Gripper_Kanan)
{
	if ((PWM_Gripper_Kanan <= 15 && PWM_Gripper_Kanan > 0) && Flag_Gripper2 == 0)
	{
		MOTOR_griper2(16);
//		Pin(GPIOE,Off,P_11);
//		Pin(GPIOE,On,P_10);
		Pin(GPIOE,On,P_11);
		Pin(GPIOE,Off,P_10);
		Flag_Gripper2 = 1;
	}
	else
	{
		MOTOR_griper2(PWM_Gripper_Kanan);
//		Pin(GPIOE,Off,P_11);
//		Pin(GPIOE,On,P_10);
		Pin(GPIOE,On,P_11);
		Pin(GPIOE,Off,P_10);
	}
}
void Gripper2_OUT(int PWM_Gripper_Kanan)
{
	if ((PWM_Gripper_Kanan <= 15 && PWM_Gripper_Kanan > 0) && Flag_Gripper2 == 0)
	{
		MOTOR_griper2(16);
//		Pin(GPIOE,On,P_11);
//		Pin(GPIOE,Off,P_10);
		Pin(GPIOE,Off,P_11);
		Pin(GPIOE,On,P_10);
		Flag_Gripper2 = 1;
	}
	else
	{
		MOTOR_griper2(PWM_Gripper_Kanan);
//		Pin(GPIOE,On,P_11);
//		Pin(GPIOE,Off,P_10);
		Pin(GPIOE,Off,P_11);
		Pin(GPIOE,On,P_10);
	}
}
void Gripper2_OFF()
{
	MOTOR_griper2(0);
	Pin(GPIOE,Off,P_11);
	Pin(GPIOE,Off,P_10);
}
void Gripper_OFF()
{
	Gripper1_OFF();
	Gripper2_OFF();

	Flag_Gripper1 = 0;
	Flag_Gripper2 = 0;
}
void Gripper_IN(int PWM_Gripper)
{
	Gripper1_IN(PWM_Gripper);
	Gripper2_IN(PWM_Gripper);
}
void Gripper_OUT(int PWM_Gripper)
{
	Gripper1_OUT(PWM_Gripper);
	Gripper2_OUT(PWM_Gripper);
}
void Gripper_NATURAL(int PWM_Gripper)
{
	Gripper1_OUT(0.5*PWM_MAKSIMAL);
	Gripper2_IN(PWM_Gripper);
}
void Gripper_function(int mode_gripper, int spd_grip)
{
//	lcd_gotoxy(17,2); sprintf(lcd, "%d",(int)spd_grip);  lcd_putstr(lcd);
	if (mode_gripper == OFF) 			{Gripper_OFF();}
	else if (mode_gripper == ON) 		{Gripper_IN(spd_grip);}
	else if (mode_gripper == BALIK)		{Gripper_OUT(spd_grip);}
	else if (mode_gripper == NATURAL)	{Gripper_NATURAL(spd_grip);}
}
//----------------------------- bikinan evan KRSBI 18 ---------------------------------//
void Gripper_MAJU(int PWM_Gripper_kiri, int PWM_Gripper_kanan)
{
	// klo speed 30, pwm gripper = 8
	//maka x = 0.27
//	int spd_grip1 = 0.2 * PWM_Gripper_kiri;
//	int spd_grip2 = 0.24 * PWM_Gripper_kanan;
	int spd_grip1 = 0.3 * PWM_Gripper_kiri;
	int spd_grip2 = 0.26 * PWM_Gripper_kanan;
	if (spd_grip1 <= 7 && spd_grip1 < 0) spd_grip1 = 7;
	if (spd_grip2 <= 7 && spd_grip1 < 0) spd_grip2 = 7;
	if (spd_grip1 >= 11) spd_grip1 = 11;
	if (spd_grip2 >= 11) spd_grip2 = 11;

	Gripper1_OUT(spd_grip1);
	Gripper2_OUT(spd_grip2);

}
void Gripper_MUNDUR(int PWM_Gripper_kiri, int PWM_Gripper_kanan)
{
	int spd_grip1 = PWM_Gripper_kiri;
	int spd_grip2 = PWM_Gripper_kanan;
	if (spd_grip1 >= 35) spd_grip1 = 35;
	if (spd_grip2 >= 35) spd_grip2 = 35;
	if (spd_grip1 <= 25) spd_grip1 = 25;
	if (spd_grip2 <= 25) spd_grip2 = 25;

	Gripper1_IN(spd_grip1);
	Gripper2_IN(spd_grip2);
}
void Gripper_KANAN(int PWM_Gripper_kiri, int PWM_Gripper_kanan)
{
//	int spd_grip1 = 0.5 * PWM_Gripper_kiri;
//	int spd_grip2 = 0.32 * PWM_Gripper_kanan;
	int spd_grip1 = PWM_Gripper_kiri;
	int spd_grip2 = 0.66 * PWM_Gripper_kanan;
	if (spd_grip1 >= 35) spd_grip1 = 35;
	if (spd_grip2 >= 25) spd_grip2 = 25;

	Gripper1_IN(spd_grip1);
	Gripper2_OUT(spd_grip2);
}
void Gripper_KIRI(int PWM_Gripper_kiri, int PWM_Gripper_kanan)
{
//	int spd_grip1 = 0.32 * PWM_Gripper_kiri;
//	int spd_grip2 = 0.5 * PWM_Gripper_kanan;
	int spd_grip1 = 0.66 *PWM_Gripper_kiri;
	int spd_grip2 = PWM_Gripper_kanan;
	if (spd_grip1 >= 20) spd_grip1 = 20;
	if (spd_grip2 >= 35) spd_grip2 = 35;

	Gripper1_OUT(spd_grip1);
	Gripper2_IN(spd_grip2);
}
void Natural_gripper (int direction, int spd_grip_kiri, int spd_grip_kanan)
{
	if (direction == DRIBBLE_MAJU)			{Gripper_MAJU(spd_grip_kiri, spd_grip_kanan);}
	else if (direction == DRIBBLE_MUNDUR) 	{Gripper_MUNDUR(spd_grip_kiri, spd_grip_kanan);}
	else if (direction == DRIBBLE_KIRI) 	{Gripper_KIRI(spd_grip_kiri, spd_grip_kanan);}
	else if (direction == DRIBBLE_KANAN) 	{Gripper_KANAN(spd_grip_kiri, spd_grip_kanan);}
	else if (direction == DRIBBLE_OFF) 		{Gripper_OFF();}
}

float posisi_grip(float Setpoint, float feedback, float K_p, float K_i, float K_d )
{

	Grip_Error1 = Setpoint - feedback;
	Grip_P = K_p * Grip_Error1;
	Grip_I_ERROR = (Grip_I_ERROR + Grip_Error1);
	Grip_I = K_i *Grip_I_ERROR;
	float out = Grip_P + Grip_I;

	if(Grip_Error1 < 1 && Grip_Error1 >-1)
	{
		Grip_P = 0;
		Grip_I = 0;
		Grip_I_ERROR = 0;
	}
	return out;

//	float kp;
//kiri 99-75 atau 99-90
//kanan 98-69 atau 99-90

//	if (abs(Grip_Error1) <=100 && abs(Grip_Error1) >= 98)			kp = 0.052;
//	else if (abs(Grip_Error1) <98 && abs(Grip_Error1) >= 96 )		kp = 0.042;
//	else if (abs(Grip_Error1) <96 && abs(Grip_Error1) >= 94 )		kp = 0.034;
//	else if (abs(Grip_Error1) <94 && abs(Grip_Error1) >= 92 )		kp = 0.022;
//	else if (abs(Grip_Error1) <92 && abs(Grip_Error1) >= 88 )		kp = 0.013;

//	if (abs(Grip_Error1) <=99 && abs(Grip_Error1) >= 95)			kp = 0.053;
//	else if (abs(Grip_Error1) <95 && abs(Grip_Error1) >= 90 )		kp = 0.045;
//	else if (abs(Grip_Error1) <90 && abs(Grip_Error1) >= 85 )		kp = 0.036;
//	else if (abs(Grip_Error1) <85 && abs(Grip_Error1) >= 80 )		kp = 0.025;
//	else if (abs(Grip_Error1) <80 && abs(Grip_Error1) >= 70 )		kp = 0.014;

//	if (abs(Grip_Error1) >=9) 										kp = 0;
//	else if (abs(Grip_Error1) <9 && abs(Grip_Error1) >= 7)			kp = 0.3;
//	else if (abs(Grip_Error1) <7 && abs(Grip_Error1) >=5 )			kp = 0.8;
//	else if (abs(Grip_Error1) == 4)							 		kp = 1.5;
//	else if (abs(Grip_Error1) < 4 && abs(Grip_Error1 > 0))	 		kp = 8;
//	else if (abs(Grip_Error1) == 0){Grip_Error1 = 1;		 		kp = 10;}
//	Grip_P = Grip_Error1*kp;
//	Grip_PI = Grip_P + Grip_I;
//
//	if(Grip_PI >=10)Grip_PI = 10;
//	if(Grip_Error1 >= -1 && Grip_Error1 <= 1)Grip_I = 0;
//	return Grip_PI;
}

void state_grip()
{
	if (Flag_Gripper1 == 1 || Flag_Gripper2 == 1)
	{
		count_gripper++;
		if (count_gripper >= 10) {count_gripper = 0; Flag_Gripper1 = 0; Flag_Gripper2 = 0;}
	}
	if (Flag_steady_grip != 0)
	{
		count_steady_grip++;
		if (count_steady_grip == 2) {Flag_steady_grip = 2; /*count_steady_grip = 0; Flag_reset_grip = 0;*/}
		if (count_steady_grip == 6) {Flag_steady_grip = 3; /*count_steady_grip = 0; Flag_reset_grip = 0;*/}
		if (count_steady_grip == 10) {Flag_steady_grip = 4; count_steady_grip = 0; Flag_reset_grip = 0;}
	}
}
void steady_grip()
{
	if (Flag_steady_grip == 0)
	{
		Flag_steady_grip = 1;
		Natural_gripper(DRIBBLE_OFF, 0, 0);
	}
	// Flag_steady_grip 1 ada di TIM5 IRQ handler
	else if (Flag_steady_grip == 2)
	{
		Natural_gripper(DRIBBLE_MUNDUR, 40, 40);
	}
	else if (Flag_steady_grip == 3)
	{
		Natural_gripper(DRIBBLE_OFF, 0, 0);
	}
	//function steady grip done after flag steady grip = 4;
}

void Gripper_josh(int distance_ball, int set_distance_ball, int spd_grip)
{
	if (Prox == 1)	// not detect ball
	{
		if (distance_ball < set_distance_ball + 10 && distance_ball > 0)
		{
			if ((F_Gmaju != 0 && F_Gmundur != 0 && F_Gkanan != 0 && F_Gkiri) && Flag_steady_grip != 4 && Flag_reset_grip == 1)
			{
				steady_grip();
			}
			else if ( Flag_steady_grip == 4 && Flag_reset_grip == 0)
			{
				Natural_gripper(DRIBBLE_MUNDUR, spd_grip, spd_grip);
			}
		}
		else if (distance_ball >= set_distance_ball + 10)
		{
			Natural_gripper(DRIBBLE_OFF, 0, 0);
			F_Gmundur = 1; F_Gkanan = 1; F_Gmaju = 1; F_Gkiri = 1; Flag_steady_grip = 0; count_steady_grip = 0;
		}
	}
	if (Prox != 1)	// detect ball
	{
		int potensio_kiri	= Griper_Pot1;
		int potensio_kanan	= Griper_Pot2;
		int Dir_mt1			= pwm_1;
		int Dir_mt3			= pwm_3;

		if ( abs(Dir_mt1) <= 14 && abs(Dir_mt1) > 0) Dir_mt1 = 0;
		if ( abs(Dir_mt3) <= 14 && abs(Dir_mt1) > 0) Dir_mt3 = 0;

		F_Grip_Error1 = posisi_grip(30, potensio_kiri, 0.06, 0, 0);
		value_grip_kiri = abs(Dir_mt1) + F_Grip_Error1;
		F_Grip_Error2 = posisi_grip(30, potensio_kanan, 0.06, 0, 0);
		value_grip_kanan = abs(Dir_mt3) + F_Grip_Error2;

		if (Prox == 3) value_grip_kanan += 10;
		else if (Prox == 2) value_grip_kiri += 10;

		if (Dir_mt1 > 0 && Dir_mt3 < 0)
		{	// maju
			value_grip_kiri = 30 + F_Grip_Error1;
			value_grip_kanan = 30 + F_Grip_Error2;
			if (F_Gmaju == 0)	{ steady_grip(); if (Flag_steady_grip == 4) {F_Gmaju = 1;}		}
			else
			{
				Natural_gripper(DRIBBLE_MAJU, value_grip_kiri, value_grip_kanan);
				F_Gmundur = 0; F_Gkanan = 0; F_Gkiri = 0; Flag_steady_grip = 0; count_steady_grip = 0; Flag_reset_grip = 1;
			}
		}
		else if (Dir_mt1 < 0 && Dir_mt3 > 0)
		{	// mundur
			if (F_Gmundur == 0)	{ steady_grip(); if (Flag_steady_grip == 4) {F_Gmundur = 1;}	}
			else
			{
				Natural_gripper(DRIBBLE_MUNDUR, value_grip_kiri, value_grip_kanan);
				F_Gmaju = 0; F_Gkanan = 0; F_Gkiri = 0; Flag_steady_grip = 0; count_steady_grip = 0; Flag_reset_grip = 1;
			}
		}
		else if (Dir_mt1 > 0 && Dir_mt3 > 0)
		{	// kanan
			if (F_Gkanan == 0)	{ steady_grip(); if (Flag_steady_grip == 4) {F_Gkanan = 1;}	}
			else
			{
				Natural_gripper(DRIBBLE_KANAN, value_grip_kiri, value_grip_kanan);
				F_Gmundur = 0; F_Gmaju = 0; F_Gkiri = 0; Flag_steady_grip = 0; count_steady_grip = 0; Flag_reset_grip = 1;
			}
		}
		else if (Dir_mt1 < 0 && Dir_mt3 < 0)
		{	// kiri
			if (F_Gkiri == 0)	{ steady_grip(); if (Flag_steady_grip == 4) {F_Gkiri = 1;}		}
			else
			{
				Natural_gripper(DRIBBLE_KIRI, value_grip_kiri, value_grip_kanan);
				F_Gmundur = 0; F_Gkanan = 0; F_Gmaju = 0; Flag_steady_grip = 0; count_steady_grip = 0; Flag_reset_grip = 1;
			}
		}
		else
		{
			if( (F_Gmaju != 0 || F_Gmundur != 0 || F_Gkanan != 0 || F_Gkiri != 0) && Flag_steady_grip != 4 && Flag_reset_grip == 1)
			{
				steady_grip();
			}
			else if (Flag_steady_grip == 4 && Flag_reset_grip == 0)
			{
				Natural_gripper(DRIBBLE_OFF, 0, 0);
				F_Gmundur = 1; F_Gkanan = 1; F_Gmaju = 1; F_Gkiri = 1; Flag_steady_grip = 0; count_steady_grip = 0;
			}
		}
	}

}

void GRIPPER_BARU(int distance_ball, int set_distance_ball)
{
	if (Prox == 1)
	{
		if (distance_ball < set_distance_ball + 10 && distance_ball > 0) Natural_gripper(DRIBBLE_MUNDUR,30,30);
		else { Natural_gripper(DRIBBLE_OFF,0,0);}
	}
	else if (Prox != 1)
	{
//		int potensio_kiri	= Griper_Pot1;
//		int potensio_kanan	= Griper_Pot2;
		int Dir_mt1			= pwm_1;
		int Dir_mt3			= pwm_3;

//		F_Grip_Error1 = posisi_grip(30, potensio_kiri, 0.06, 0, 0);
//		value_grip_kiri = abs(Dir_mt1) + F_Grip_Error1;
//		F_Grip_Error2 = posisi_grip(30, potensio_kanan, 0.06, 0, 0);
//		value_grip_kanan = abs(Dir_mt3) + F_Grip_Error2;

		value_grip_kiri = abs(Dir_mt1);
		value_grip_kanan = abs(Dir_mt3);

		if ( abs(Dir_mt1) <= 14 && abs(Dir_mt1) > 0)	{ Dir_mt1 = 0;}
		if ( abs(Dir_mt3) <= 14 && abs(Dir_mt1) > 0) 	{ Dir_mt3 = 0;}

		if (Dir_mt1 == 0)		{	Gripper1_OFF();							}
		else if (Dir_mt1 > 0)	{	Gripper1_OUT(8);						}
		else if (Dir_mt1 < 0)	{	Gripper1_IN(8);							}

		if (Dir_mt3 == 0)		{	Gripper2_OFF();							}
		else if (Dir_mt3 > 0)	{	Gripper2_IN(8);							}
		else if (Dir_mt3 < 0)	{	Gripper2_OUT(8);						}


	}
}

void feedforward_gripper(double theta, int speed)
{
	float r_bola = 0.5 * diameter_bola;
	float r_gripper = 0.5 * diameter_gripper;
	float Mbw = r_bola + r_gripper;

	int X_bola = speed + (cos(theta) * diameter_bola * theta);
	int Y_bola = speed + (sin(theta) * diameter_bola * theta);

	vektor_bola = sqrt(pow(X_bola, 2) + pow(Y_bola, 2));
	sudut_bola = atan(X_bola / Y_bola);


	spd_grip_kiri = ( vektor_bola /(r_bola*r_gripper) ) * ( sqrt( pow(r_bola,2) - ( pow(Mbw,2) * pow(sin(0),2) ) )
			* ( cos( (pi/4) - sudut_bola) ) );

	spd_grip_kanan = ( vektor_bola /(r_bola*r_gripper) ) * ( sqrt( pow(r_bola,2) - ( pow(Mbw,2) * pow(cos(90),2) ) )
			* ( cos( (pi/4) + sudut_bola) ) );

}
void fuzzy_input(int L_grip, int R_grip)
{
	if (L_grip >= 0 && L_grip < 10)			{ Left_Gripper_Input =  NB;	}
	else if (L_grip >= 10 && L_grip < 20)	{ Left_Gripper_Input =  NM;	}
	else if (L_grip >= 20 && L_grip < 30)	{ Left_Gripper_Input =  NS;	}
	else if (L_grip >= 30 && L_grip < 40)	{ Left_Gripper_Input =  ZR;	}
	else if (L_grip >= 40)					{ Left_Gripper_Input =  PST;}

	if (R_grip >= 0 && R_grip < 10)			{ Right_Gripper_Input = NB;	}
	else if (R_grip >= 10 && R_grip < 20)	{ Right_Gripper_Input = NM;	}
	else if (R_grip >= 20 && R_grip < 30)	{ Right_Gripper_Input = NS;	}
	else if (R_grip >= 30 && R_grip < 40)	{ Right_Gripper_Input = ZR;	}
	else if (R_grip >= 40)					{ Right_Gripper_Input = PST;}
}
int fuzzy_output_left(int L_grip, int R_grip)
{
	int out_grip;

	if (L_grip == NB && R_grip == NB)			{ out_grip =  FR;	}
	else if (L_grip == NB && R_grip == NM)		{ out_grip =  MR;	}
	else if (L_grip == NB && R_grip == NS)		{ out_grip =  MR;	}
	else if (L_grip == NB && R_grip == ZR)		{ out_grip =  MR;	}
	else if (L_grip == NB && R_grip == PST)		{ out_grip =  MR;	}

	else if (L_grip == NM && R_grip == NB)		{ out_grip =  MR;	}
	else if (L_grip == NM && R_grip == NM)		{ out_grip =  MR;	}
	else if (L_grip == NM && R_grip == NS)		{ out_grip =  MR;	}
	else if (L_grip == NM && R_grip == ZR)		{ out_grip =  MR;	}
	else if (L_grip == NM && R_grip == PST)		{ out_grip =  MR;	}

	else if (L_grip == NS && R_grip == NB)		{ out_grip =  SR;	}
	else if (L_grip == NS && R_grip == NM)		{ out_grip =  SR;	}
	else if (L_grip == NS && R_grip == NS)		{ out_grip =  SR;	}
	else if (L_grip == NS && R_grip == ZR)		{ out_grip =  SR;	}
	else if (L_grip == NS && R_grip == PST)		{ out_grip =  SR;	}

	else if (L_grip == ZR && R_grip == NB)		{ out_grip =  MR;	}
	else if (L_grip == ZR && R_grip == NM)		{ out_grip =  STOP;	}
	else if (L_grip == ZR && R_grip == NS)		{ out_grip =  STOP;	}
	else if (L_grip == ZR && R_grip == ZR)		{ out_grip =  STOP;	}
	else if (L_grip == ZR && R_grip == PST)		{ out_grip =  STOP;	}

	else if (L_grip == PST && R_grip == NB)		{ out_grip =  FWD;	}
	else if (L_grip == PST && R_grip == NM)		{ out_grip =  FWD;	}
	else if (L_grip == PST && R_grip == NS)		{ out_grip =  FWD;	}
	else if (L_grip == PST && R_grip == ZR)		{ out_grip =  FWD;	}
	else if (L_grip == PST && R_grip == PST)	{ out_grip =  FWD;	}

	return out_grip;
}

int fuzzy_output_right(int L_grip, int R_grip)
{
	int out_grip;

	if (L_grip == NB && R_grip == NB)			{ out_grip =  FR;	}
	else if (L_grip == NB && R_grip == NM)		{ out_grip =  MR;	}
	else if (L_grip == NB && R_grip == NS)		{ out_grip =  SR;	}
	else if (L_grip == NB && R_grip == ZR)		{ out_grip =  MR;	}
	else if (L_grip == NB && R_grip == PST)		{ out_grip =  FWD;	}

	else if (L_grip == NM && R_grip == NB)		{ out_grip =  MR;	}
	else if (L_grip == NM && R_grip == NM)		{ out_grip =  MR;	}
	else if (L_grip == NM && R_grip == NS)		{ out_grip =  SR;	}
	else if (L_grip == NM && R_grip == ZR)		{ out_grip =  STOP;	}
	else if (L_grip == NM && R_grip == PST)		{ out_grip =  FWD;	}

	else if (L_grip == NS && R_grip == NB)		{ out_grip =  MR;	}
	else if (L_grip == NS && R_grip == NM)		{ out_grip =  MR;	}
	else if (L_grip == NS && R_grip == NS)		{ out_grip =  SR;	}
	else if (L_grip == NS && R_grip == ZR)		{ out_grip =  STOP;	}
	else if (L_grip == NS && R_grip == PST)		{ out_grip =  FWD;	}

	else if (L_grip == ZR && R_grip == NB)		{ out_grip =  MR;	}
	else if (L_grip == ZR && R_grip == NM)		{ out_grip =  MR;	}
	else if (L_grip == ZR && R_grip == NS)		{ out_grip =  SR;	}
	else if (L_grip == ZR && R_grip == ZR)		{ out_grip =  STOP;	}
	else if (L_grip == ZR && R_grip == PST)		{ out_grip =  FWD;	}

	else if (L_grip == PST && R_grip == NB)		{ out_grip =  MR;	}
	else if (L_grip == PST && R_grip == NM)		{ out_grip =  MR;	}
	else if (L_grip == PST && R_grip == NS)		{ out_grip =  SR;	}
	else if (L_grip == PST && R_grip == ZR)		{ out_grip =  STOP;	}
	else if (L_grip == PST && R_grip == PST)	{ out_grip =  FWD;	}

	return out_grip;
}

int fuzzy_pwm_gripper(int value_grip)
{
	int hasil_pwm;

	if (value_grip == FR)		{ hasil_pwm = 30;}
	else if (value_grip == MR)	{ hasil_pwm = 25;}
	else if (value_grip == SR)	{ hasil_pwm = 18;}
	else if (value_grip == STOP){ hasil_pwm = 0;}
	else if (value_grip == FWD)	{ hasil_pwm = 8;}

	return hasil_pwm;
}

void fuzzy_gripper()
{
	int potensio_kiri	= Griper_Pot1;
	int potensio_kanan	= Griper_Pot2;

	fuzzy_input(potensio_kiri, potensio_kanan);
	Left_Gripper_Output = fuzzy_output_left(Left_Gripper_Input, Right_Gripper_Input);
	Right_Gripper_Output = fuzzy_output_right(Left_Gripper_Input, Right_Gripper_Input);

	value_grip_kiri	= fuzzy_pwm_gripper(Left_Gripper_Output);
	value_grip_kanan = fuzzy_pwm_gripper(Right_Gripper_Output);

	if (Left_Gripper_Output == FR || Left_Gripper_Output == MR || Left_Gripper_Output == SR)
	{
		Gripper1_IN(value_grip_kiri);
	}
	else if ( Left_Gripper_Output == FWD) Gripper1_OUT(value_grip_kiri);
	else { Gripper1_OFF();	}

	if (Right_Gripper_Output == FR || Right_Gripper_Output == MR || Right_Gripper_Output == SR)
	{
		Gripper2_IN(value_grip_kanan);
	}
	else if ( Right_Gripper_Output == FWD) Gripper2_OUT(value_grip_kanan);
	else { Gripper2_OFF();	}

}
//***********************************************************************************************************//

//************************************************ FUNGSI TUAS **********************************************//


void Feedback_Tuas()
{
	if(Tuas_Switch1 == 1){Flag_Tuas = 1;}
	if(Tuas_Switch2 == 1){Flag_Tuas = 2;}
	if (Tuas_Switch1 == 0 && Tuas_Switch2 ==0){Flag_Tuas =0;}
}
void Tuas_Manual(int spd_tuas)
{
	if (Flag_Tuas == 1)
	{
		if(spd_tuas < 0){
			MOTOR_Tuas(abs(spd_tuas));
			Pin(GPIOC,On,P_15);
			Pin(GPIOC,Off,P_6);}
		else if(spd_tuas == 0 || spd_tuas > 0){
			MOTOR_Tuas(0);
			Pin(GPIOC,Off,P_15);
			Pin(GPIOC,Off,P_6);}
		else{
			MOTOR_Tuas(0);
			Pin(GPIOC,On,P_15);
			Pin(GPIOC,On,P_6);}
	}
	else if (Flag_Tuas == 2)
	{
		if(spd_tuas > 0){
			MOTOR_Tuas(spd_tuas);
			Pin(GPIOC,Off,P_15);
			Pin(GPIOC,On,P_6);}
		else if(spd_tuas == 0 || spd_tuas < 0){
			MOTOR_Tuas(0);
			Pin(GPIOC,Off,P_15);
			Pin(GPIOC,Off,P_6);}
		else{
			MOTOR_Tuas(0);
			Pin(GPIOC,On,P_15);
			Pin(GPIOC,On,P_6);}
	}
	else
	{
		if(spd_tuas > 0){
			MOTOR_Tuas(spd_tuas);
			Pin(GPIOC,Off,P_15);
			Pin(GPIOC,On,P_6);}
		else if(spd_tuas < 0){
			MOTOR_Tuas(abs(spd_tuas));
			Pin(GPIOC,On,P_15);
			Pin(GPIOC,Off,P_6);}
		else if(spd_tuas == 0){
			MOTOR_Tuas(0);
			Pin(GPIOC,Off,P_15);
			Pin(GPIOC,Off,P_6);}
		else{
			MOTOR_Tuas(0);
			Pin(GPIOC,On,P_15);
			Pin(GPIOC,On,P_6);}
	}
}
void Setting_Tuas(int Sp_Tuas)
{
//	BATAS ATAS 70 ORION
//	BATAS BAWAH 30 ORION
//	BATAS ATAS HYDRA 80
//	BATAS BAWAH HYDRA 30

	if (Tuas_Pot >= Sp_Tuas+2 && Flag_Tuas ==0) 		{Tuas_Manual(-25);}		//tuas turun
	else if (Tuas_Pot <= Sp_Tuas-2 && Flag_Tuas ==0) 	{Tuas_Manual(25);}		//tuas naik
	else if (Tuas_Pot >= Sp_Tuas+2 && Flag_Tuas ==1) 	{Tuas_Manual(-25);}		//nyentuh lim atas. harus turun
	else if (Tuas_Pot <= Sp_Tuas+2 && Flag_Tuas ==1) 	{Tuas_Manual(0);}		//nyentuh lim atas.motor mati
	else if (Tuas_Pot <= Sp_Tuas-2 && Flag_Tuas ==2) 	{Tuas_Manual(25);}		//nyentuh lim bawah.harus naik
	else if (Tuas_Pot >= Sp_Tuas-2 && Flag_Tuas ==2) 	{Tuas_Manual(0);}		//nyentuh lim bawah.motor mati
	else {Tuas_Manual(0);/*Flag_Tuas =0;*/}
}

float PID_Tuas(float setpoint, float feedback ,float K_p,float K_i)
{
	float error_pid = setpoint - feedback;

	Tuas_P = K_p*error_pid;
	Tuas_I_ERROR = (Tuas_I_ERROR + error_pid);
	Tuas_I = K_i*Tuas_I_ERROR;
	float out = Tuas_P + Tuas_I;
	if(error_pid < 1 && error_pid >-1)
	{
		Tuas_P = 0;
		Tuas_I = 0;
		Tuas_I_ERROR = 0;
	}
	return out;
}

void Tuas_Algorithm(int Sp_Tuas, int Feedback_Tuas)
{
	//	BATAS ATAS 73 ORION 	(nyentuh lim switch)
	//	BATAS BAWAH 30 ORION	(nyentuh lim switch)
	//	BATAS ATAS HYDRA 80
	//	BATAS BAWAH HYDRA 30

	float speed_tuas = PID_Tuas(Sp_Tuas, Feedback_Tuas, 1.6, 0.01);
	if (speed_tuas < 13 && speed_tuas > 0) speed_tuas = 13;
	else if (speed_tuas > -13 && speed_tuas < 0) speed_tuas = -13;
	else if (speed_tuas == 0) speed_tuas = 0;
	lcd_gotoxy(0,1); sprintf(lcd, "%d", (int) speed_tuas);  	    lcd_putstr(lcd);

	if (Sp_Tuas >= Feedback_Tuas && Flag_Tuas == 1)			{Tuas_Manual(0);}
	else if (Sp_Tuas <= Feedback_Tuas && Flag_Tuas == 2)	{Tuas_Manual(0);}
	else {Tuas_Manual(speed_tuas);}
}
//***********************************************************************************************************//

void fwd_pwm_3roda(int speed1,int speed2,int speed3)
{
int MinPwm = 0;
if(abs(speed1)<=MinPwm)MinPwm = abs(speed1);
if(abs(speed2)<=MinPwm)MinPwm = abs(speed2);
if(abs(speed3)<=MinPwm)MinPwm = abs(speed3);
if (MinPwm < speed_minn && MinPwm > 3){
	speed1 *= speed_minn;
	speed1 /= MinPwm;
	speed2 *= speed_minn;
	speed2 /= MinPwm;
	speed3 *= speed_minn;
	speed3 /= MinPwm;
}
if (MinPwm > speed_min && MinPwm < -3){
	speed1 *= speed_min;
	speed1 /= MinPwm;
	speed2 *= speed_min;
	speed2 /= MinPwm;
	speed3 *= speed_min;
	speed3 /= MinPwm;
}
int MaxPwm = abs(speed2);
if(abs(speed1)>=MaxPwm)MaxPwm = abs(speed1);
if(abs(speed3)>=MaxPwm)MaxPwm = abs(speed3);
if(MaxPwm>speed_maxx){
	speed1 *= speed_maxx;
	speed1 /= MaxPwm;
	speed2 *= speed_maxx;
	speed2 /= MaxPwm;
	speed3 *= speed_maxx;
	speed3 /= MaxPwm;
}
if(MaxPwm<speed_max){
	speed1 *= speed_max;
	speed1 /= MaxPwm;
	speed2 *= speed_max;
	speed2 /= MaxPwm;
	speed3 *= speed_max;
	speed3 /= MaxPwm;
}

	if (speed1 == 0)
	{
		MOTOR1CW(0);
		MOTOR1CCW(0);
//		Pin(GPIOB,Off,P_5);
	}
	else if (speed1>0)
	{
		MOTOR1CW(speed1);
		MOTOR1CCW(0);
//		Pin(GPIOB,On,P_5);
	}
	else if (speed1<0)
	{
		MOTOR1CW(0);
		MOTOR1CCW(abs(speed1));
//		Pin(GPIOB,On,P_5);
	}
	if(speed2 == 0)
	{
		MOTOR2CW(0);
		MOTOR2CCW(0);
//		Pin(GPIOA,Off,P_8);
	}
	else if (speed2 >0)
	{
		MOTOR2CW(speed2);
		MOTOR2CCW(0);
//		Pin(GPIOA,On,P_8);
	}
	else if (speed2<0)
	{
		MOTOR2CW(0);
		MOTOR2CCW(abs(speed2));
//		Pin(GPIOA,On,P_8);
	}
	if(speed3 == 0)
	{
		MOTOR3CW(0);
		MOTOR3CCW(0);
//		Pin(GPIOB,Off,P_15);
	}
	else if (speed3 >0)
	{
		MOTOR3CW(speed3);
		MOTOR3CCW(0);
//		Pin(GPIOB,On,P_15);
	}
	else if (speed3<0)
	{
		MOTOR3CW(0);
		MOTOR3CCW(abs(speed3));
//		Pin(GPIOB,On,P_15);
	}
/////////////////pwm yg diinginkan////////////////////
	pwm_1 = speed1;									//
	pwm_2 = speed2;									//
	pwm_3 = speed3;									//
//////////////////////////////////////////////////////

}

float PID_function(float erroorrr ,float K_p,float K_i)
{

	PID_P = K_p*erroorrr;
	PID_I_ERROR = (MT1_I_ERROR + erroorrr);
	PID_I = K_i*MT1_I_ERROR;
	float out = MT1_P + MT1_I;

	if(erroorrr < 1 && erroorrr)
	{
		PID_P = 0;
		PID_I = 0;
		PID_I_ERROR = 0;
	}
	return out;
}

float PID_motor_1(float setpoint, float feedback ,float K_p,float K_i)
// sp = 100		feedback = 61	kp = 0.6	Ki = 0.01
{
	float error_pid = setpoint - feedback;

	MT1_P = K_p*error_pid;
	MT1_I_ERROR = (MT1_I_ERROR + error_pid);
	MT1_I = K_i*MT1_I_ERROR;
	float out = MT1_P + MT1_I;

//	lcd_gotoxy(17,1);  sprintf(lcd, "%d",(int) MT1_I);  lcd_putstr(lcd);
	if(error_pid < 1 && error_pid >-1)
	{
		MT1_P = 0;
		MT1_I = 0;
		MT1_I_ERROR = 0;
	}
	return out;
}
float PID_motor_2(float setpoint, float feedback ,float K_p,float K_i)
{
	float error_pid = setpoint - feedback;

	MT2_P = K_p*error_pid;
	MT2_I_ERROR = (MT2_I_ERROR + error_pid);
	MT2_I = K_i*MT2_I_ERROR;
	float out = MT2_P + MT2_I;
//	lcd_gotoxy(17,2);  sprintf(lcd, "%d",(int) MT2_I);  lcd_putstr(lcd);
	if(error_pid < 1 && error_pid >-1)
	{
		MT2_P = 0;
		MT2_I = 0;
		MT2_I_ERROR = 0;
	}
	return out;
}
float PID_motor_3(float setpoint, float feedback ,float K_p,float K_i)
{
	float error_pid = setpoint - feedback;

	MT3_P = K_p*error_pid;
	MT3_I_ERROR = (MT3_I_ERROR + error_pid);
	MT3_I = K_i*MT3_I_ERROR;
	float out = MT3_P + MT3_I;
//	lcd_gotoxy(17,3);  sprintf(lcd, "%d",(int) MT3_I);  lcd_putstr(lcd);
	if(error_pid < 1 && error_pid >-1)
	{
		MT3_P = 0;
		MT3_I = 0;
		MT3_I_ERROR = 0;
	}
	return out;
}

void convert_Rpm_2_PWM(int speed1, int speed2, int speed3)
{
//** to calibrate the value, use file excel RPM_2_PWM **//

	if (Program_Untuk == ORION)
	{
		//******************* Grafik data exponensial ***************//
//		pwm_real_1 = exp((rt0_m1.Rpm2 + 1405.1) / 580.62) ;
//		pwm_real_2 = exp((rt0_m2.Rpm2 + 1423.3) / 573.1) ;
//		pwm_real_3 = exp((rt0_m3.Rpm2 + 1409.3) / 582.04) ;

		//******************* Grafik data Linier ********************//

		if (speed1 >= 0) { pwm_real_1 = (rt0_m1.Rpm2 + 0.8) / 14.698;}
		else if (speed1 < 0){ pwm_real_1 = (abs(rt0_m1.Rpm2) + 12.8) / 15.047;}

		if (speed2 >= 0) { pwm_real_2 = (rt0_m2.Rpm2 + 44) / 14.589; }
		else if (speed2 < 0) { pwm_real_2 = (abs(rt0_m2.Rpm2) - 0.8) / 12.64;}

		if (speed3 >= 0) { pwm_real_3 = (rt0_m3.Rpm2 + 4) / 14.8; }
		else if (speed3 < 0) { pwm_real_3 = (abs(rt0_m3.Rpm2) + 8) / 15.069;}

//		if (speed1 >= 0) { pwm_real_1 = (rt0_m1.Rpm2 + 8.8) / 14.822;}
//		else if (speed1 < 0){ pwm_real_1 = (abs(rt0_m1.Rpm2) + 12.8) / 15.047;}
//
//		if (speed2 >= 0) { pwm_real_2 = (rt0_m2.Rpm2 - 11.733) / 13.088; }
//		else if (speed2 < 0) { pwm_real_2 = (abs(rt0_m2.Rpm2) - 10.4) / 13.185;}
//
//		if (speed3 >= 0) { pwm_real_3 = (rt0_m3.Rpm2 + 8.8) / 15.084; }
//		else if (speed3 < 0) { pwm_real_3 = (abs(rt0_m3.Rpm2) + 8) / 15.069;}
	}
	if (Program_Untuk == HYDRA)
	{
		//******************* grafik data linier *****************//
//		if(speed1 >= 0){pwm_real_1 = (rt0_m1.Rpm2 + 11.2) / 16.284;}
//		else if(speed1 < 0){pwm_real_1 = abs(rt0_m1.Rpm2) / 16.058;}
//
//		if(speed2 >= 0){pwm_real_2 = (rt0_m2.Rpm2 + 29.6) / 14.371;}
//		else if(speed2 < 0){pwm_real_2 = (abs(rt0_m2.Rpm2) + 2.4 ) / 12.372;}
//
//		if(speed3 >= 0){pwm_real_3 = (rt0_m3.Rpm2 + 3.2) / 14.211;}
//		else if(speed3 < 0){pwm_real_3 = (abs(rt0_m3.Rpm2) + 12.8) / 14.829;}

		if(speed1 >= 0){pwm_real_1 = (rt0_m1.Rpm2 + 7.2) / 16.036;}
		else if(speed1 < 0){pwm_real_1 = abs(rt0_m1.Rpm2 +3.2) / 16.018;}

		if(speed2 >= 0){pwm_real_2 = (rt0_m2.Rpm2 + 3.2) / 15.745;}
		else if(speed2 < 0){pwm_real_2 = (abs(rt0_m2.Rpm2) + 4.8 ) / 15.425;}

		if(speed3 >= 0){pwm_real_3 = (rt0_m3.Rpm2 + 0.5333) / 13.762;}
		else if(speed3 < 0){pwm_real_3 = (abs(rt0_m3.Rpm2) + 20) / 14.48;}
	}

	if (pwm_real_1 <= 6 && pwm_real_1 >= -6) pwm_real_1 = 0;
	if (pwm_real_2 <= 6 && pwm_real_2 >= -6) pwm_real_2 = 0;
	if (pwm_real_3 <= 6 && pwm_real_3 >= -6) pwm_real_3 = 0;
}

void fwd_pwm_3roda_PID(int speed1,int speed2,int speed3)
{
//*****************ini rpm sama tp tanpa beban **********************//
//	if (Program_Untuk == ORION)
//	{
//		if (speed1 > 0) speed1 *= 0.96;
//		else if (speed1 < 0) speed1 *= 1;
//
//		if (speed2 > 0) speed2 *= 1;
//		else if (speed2 < 0) speed2 *= 1.12;
//
//		if (speed3 > 0) speed3 *= 0.96;
//		else if (speed3 < 0) speed3 *= 1;
//	}
//*******************************************************************//

//************************* LUMAYAN BAGUS ***************************//
	if (Program_Untuk == ORION)
	{
//		if (speed1 > 0) speed1 *= 1;
//		else if (speed1 < 0) speed1 *= 1;

		if (speed2 > 0) speed2 *= 0.98;
		else if (speed2 < 0) speed2 *= 0.98;

//		if (speed3 > 0) speed3 *= 1.11;
//		else if (speed3 < 0) speed3 *= 1.12;
	}
	if (Program_Untuk == HYDRA)
	{
		if (speed1 > 0) speed1 *= 0.98;
		else if (speed1 < 0) speed1 *= 0.96;
//
		if (speed2 > 0) speed2 *= 0.86;
		else if (speed2 < 0) speed2 *= 0.85;
//
//		if (speed3 > 0) speed3 *= 1;
//		if (speed3 < 0) speed3 *= 0.96;
	}
//*******************************************************************//
int MinPwm = 0;
if(abs(speed1)<=MinPwm)MinPwm = abs(speed1);
if(abs(speed2)<=MinPwm)MinPwm = abs(speed2);
if(abs(speed3)<=MinPwm)MinPwm = abs(speed3);
if (MinPwm < speed_minn && MinPwm > 3){
	speed1 *= speed_minn;
	speed1 /= MinPwm;
	speed2 *= speed_minn;
	speed2 /= MinPwm;
	speed3 *= speed_minn;
	speed3 /= MinPwm;
}
if (MinPwm > speed_min && MinPwm < -3){
	speed1 *= speed_min;
	speed1 /= MinPwm;
	speed2 *= speed_min;
	speed2 /= MinPwm;
	speed3 *= speed_min;
	speed3 /= MinPwm;
}
int MaxPwm = abs(speed2);
if(abs(speed1)>=MaxPwm)MaxPwm = abs(speed1);
if(abs(speed3)>=MaxPwm)MaxPwm = abs(speed3);
if(MaxPwm>speed_maxx){
	speed1 *= speed_maxx;
	speed1 /= MaxPwm;
	speed2 *= speed_maxx;
	speed2 /= MaxPwm;
	speed3 *= speed_maxx;
	speed3 /= MaxPwm;
}
if(MaxPwm<speed_max){
	speed1 *= speed_max;
	speed1 /= MaxPwm;
	speed2 *= speed_max;
	speed2 /= MaxPwm;
	speed3 *= speed_max;
	speed3 /= MaxPwm;
}

	convert_Rpm_2_PWM(speed1, speed2, speed3);

	if (speed1 == 0)
	{
		PID_MOTOR1CW(0, pwm_real_1);
		PID_MOTOR1CCW(0, pwm_real_1);
//		Pin(GPIOB,Off,P_5);
	}
	else if (speed1>0)
	{
		PID_MOTOR1CW(speed1, pwm_real_1);
		PID_MOTOR1CCW(0, pwm_real_1);
//		Pin(GPIOB,On,P_5);
	}
	else if (speed1<0)
	{
		PID_MOTOR1CW(0, pwm_real_1);
		PID_MOTOR1CCW(abs(speed1), pwm_real_1);
//		Pin(GPIOB,On,P_5);
	}
	if(speed2 == 0)
	{
		PID_MOTOR2CW(0, pwm_real_2);
		PID_MOTOR2CCW(0, pwm_real_2);
//		Pin(GPIOA,Off,P_8);
	}
	else if (speed2 >0)
	{
		PID_MOTOR2CW(speed2, pwm_real_2);
		PID_MOTOR2CCW(0, pwm_real_2);
//		Pin(GPIOA,On,P_8);
	}
	else if (speed2<0)
	{
		PID_MOTOR2CW(0, pwm_real_2);
		PID_MOTOR2CCW(abs(speed2), pwm_real_2);
//		Pin(GPIOA,On,P_8);
	}
	if(speed3 == 0)
	{
		PID_MOTOR3CW(0, pwm_real_3);
		PID_MOTOR3CCW(0, pwm_real_3);
//		Pin(GPIOB,Off,P_15);
	}
	else if (speed3 >0)
	{
		PID_MOTOR3CW(speed3, pwm_real_3);
		PID_MOTOR3CCW(0, pwm_real_3);
//		Pin(GPIOB,On,P_15);
	}
	else if (speed3<0)
	{
		PID_MOTOR3CW(0, pwm_real_3);
		PID_MOTOR3CCW(abs(speed3), pwm_real_3);
//		Pin(GPIOB,On,P_15);
	}
/////////////////pwm yg diinginkan////////////////////
	pwm_1 = speed1;									//
	pwm_2 = speed2;									//
	pwm_3 = speed3;									//
//////////////////////////////////////////////////////

}

void move_angle_3roda(double theta,int speed, int move)
{
	theta = theta+60;

	double theta1 = (theta*pi)/180;
	double theta2 = ((theta+120)*pi)/180;
	double theta3 = ((theta-120)*pi)/180;

	pwm1 = speed*sin(theta1);
	pwm2 = speed*sin(theta2);
	pwm3 = speed*sin(theta3);

	if(move == YES){
		int MaxPwm = abs(pwm2);
		if(abs(pwm1)>=MaxPwm)MaxPwm = abs(pwm1);
		if(abs(pwm3)>=MaxPwm)MaxPwm = abs(pwm3);
		pwm1 *= speed;
		pwm1 /= MaxPwm;
		pwm2 *= speed;
		pwm2 /= MaxPwm;
		pwm3 *= speed;
		pwm3 /= MaxPwm;
//		fwd_pwm_3roda(pwm1,pwm2,pwm3);
		fwd_pwm_3roda_PID(pwm1,pwm2,pwm3);
	}
}

int koordinat_to_sudut(int x0, int y0, int x1, int y1)
{
	float dx = x1-x0;
	float dy = y1-y0;
//	if(dx == 0)dx = 1;
//	if(dy == 0)dy = 1;
	float theta = atan2f(dy,dx);
	theta = (theta*180)/pi;
	return theta;
}

int Hadap(int Setpoint){
	Hadap_error = Setpoint/* - imu_filter*/;
	float kp;
if (Program_Untuk == ORION)
{
	if (abs(Hadap_error) <10) 										/*kp = 0.7;*/ kp = 0.7;
	else if (abs(Hadap_error) <19 && abs(Hadap_error) >=10 )		/*kp = 0.7; */kp = 0.65;
	else if (abs(Hadap_error) <25 && abs(Hadap_error) >=19 )		kp = 0.6;
	else if (abs(Hadap_error) <35 &&abs(Hadap_error) >=25 ) 		kp = 0.55;
	else if(abs(Hadap_error) >=35) 									kp = 0.35;
}
if (Program_Untuk == HYDRA)
{
	if (abs(Hadap_error) <10) 										/*kp = 0.7;*/ kp = 0.6;
	else if (abs(Hadap_error) <19 && abs(Hadap_error) >=10 )		/*kp = 0.7; */kp = 0.6;
	else if (abs(Hadap_error) <25 && abs(Hadap_error) >=19 )		kp = 0.6;
	else if (abs(Hadap_error) <35 &&abs(Hadap_error) >=25 ) 		kp = 0.55;
	else if(abs(Hadap_error) >=35) 									kp = 0.35;
}
	Hadap_P = Hadap_error*kp;
//	if (abs(Hadap_error) <15 ) 								Hadap_I += Hadap_error * 0.1;
//	if (abs(Hadap_error) <7 && abs(Hadap_error) >=5 ) 	Hadap_I += Hadap_error * 0.04;
//	else if (abs(Hadap_error) <12 && abs(Hadap_error) >=7 ) 	Hadap_I += Hadap_error * 0.02;
//	else if (abs(Hadap_error) <15 && abs(Hadap_error) >=12 ) Hadap_I += Hadap_error * 0.01;
	Hadap_PI = Hadap_P + Hadap_I;

	if(Hadap_PI >25)Hadap_PI = 25;
	if(Hadap_PI <-25)Hadap_PI = -25;
	if(Hadap_error >= -1 && Hadap_error <= 1)Hadap_I = 0;
	return Hadap_PI;
}

void Follow_Ball(int sud, int jar, int set){
	manipul_sud = sud;
	if(manipul_sud >180) manipul_sud -=360;
	F_Error_Hadap = Hadap(manipul_sud);
	if (jar == 0) jar = set;
	F_Error_Jarak = jar - set;
	if (Program_Untuk == ORION)
	{
//		if(abs(F_Error_Jarak) > 0 && abs(F_Error_Jarak)< 19)		 F_Nilai_P = 40; 	/*1.7*/
		if(abs(F_Error_Jarak) >= 0 && abs(F_Error_Jarak)< 19)		 F_Nilai_P = F_Error_Jarak * 1.95; 	/*1.7*/
		else if(abs(F_Error_Jarak) < 40 && abs(F_Error_Jarak) >= 19) F_Nilai_P = F_Error_Jarak * 1.6;
		else if(abs(F_Error_Jarak) < 65 && abs(F_Error_Jarak) >= 40) F_Nilai_P = F_Error_Jarak * 1;
		else if(abs(F_Error_Jarak) >= 65)							 F_Nilai_P = F_Error_Jarak * 0.8;
//		if (abs(F_Error_Jarak) < 5 && abs(sud <30))									 F_Nilai_I += F_Error_Jarak * 0.19;
//		else if(abs(F_Error_Jarak) < 7 && abs(F_Error_Jarak) >= 5 && abs(sud <30))	 F_Nilai_I += F_Error_Jarak * 0.13;
//		else if(abs(F_Error_Jarak) < 12 && abs(F_Error_Jarak) >= 7 && abs(sud <30))	 F_Nilai_I += F_Error_Jarak * 0.06;
		if(F_Nilai_I>30)F_Nilai_I=30;
		if(F_Nilai_I<-30)F_Nilai_I=-30;
		if(Prox != 1 || abs(sud >30))  F_Nilai_I =0;
	}
	else if (Program_Untuk == HYDRA)
	{
//		if(abs(F_Error_Jarak)< 10)					 				 F_Nilai_P = F_Error_Jarak * 1.9; 	/*1.7*/
		if(abs(F_Error_Jarak) < 19 && abs(F_Error_Jarak) > 0) 		 F_Nilai_P = 40;	/*1.5*/
		else if(abs(F_Error_Jarak) < 40 && abs(F_Error_Jarak) >= 19) F_Nilai_P = F_Error_Jarak * 1.3;
		else if(abs(F_Error_Jarak) < 65 && abs(F_Error_Jarak) >= 40) F_Nilai_P = F_Error_Jarak * 0.85;
		else if(abs(F_Error_Jarak) >= 65)							 F_Nilai_P = F_Error_Jarak * 0.75;
		if (abs(F_Error_Jarak) < 10 && abs(sud <30))									 F_Nilai_I += F_Error_Jarak * 0.15;
		else if(abs(F_Error_Jarak) < 15 && abs(F_Error_Jarak) >= 10 && abs(sud <30))	 F_Nilai_I += F_Error_Jarak * 0.09;
		else if(abs(F_Error_Jarak) < 20 && abs(F_Error_Jarak) >= 15 && abs(sud <30))	 F_Nilai_I += F_Error_Jarak * 0.06;
		if(F_Nilai_I>30)F_Nilai_I=30;
		if(F_Nilai_I<-30)F_Nilai_I=-30;
		if(Prox != 1 || abs(sud >30))  F_Nilai_I =0;
	}
	F_Nilai_PI = F_Nilai_P + F_Nilai_I ;
	move_angle_3roda(manipul_sud,F_Nilai_PI,NO);
	if (abs(F_Error_Jarak) >= 50  ){
		if (F_Error_Hadap >= 0.7*pwm1 || F_Error_Hadap >= 0.7*pwm2 || F_Error_Hadap >= 0.7*pwm3)
		{	if (Program_Untuk == HYDRA) F_Error_Hadap *= 0.40/*0.55*/;
			if (Program_Untuk == ORION) F_Error_Hadap *= 0.8;	}}
	F_Pwm1 = pwm1 + F_Error_Hadap;
	F_Pwm2 = pwm2 + F_Error_Hadap;
	F_Pwm3 = pwm3 + F_Error_Hadap;

	if (Program_Untuk == ORION) fwd_pwm_3roda_PID(F_Pwm1,F_Pwm2,F_Pwm3);
	else if (Program_Untuk == HYDRA) fwd_pwm_3roda_PID(F_Pwm1,F_Pwm2,F_Pwm3);
}
void Follow_Bola(int sud, int jar, int set)
{
	manipul_sud = sud;
	if (manipul_sud > 180) manipul_sud -= 360;
	F_Error_Hadap = Hadap(manipul_sud);
	F_Error_Jarak = jar - set;

	if (Program_Untuk == ORION)
	{
		if(abs(F_Error_Jarak) >= 0 && abs(F_Error_Jarak)< 19)		 F_Nilai_P = F_Error_Jarak * 1.8; 	/*1.7*/
		else if(abs(F_Error_Jarak) < 40 && abs(F_Error_Jarak) >= 19) F_Nilai_P = F_Error_Jarak * 1.6;
		else if(abs(F_Error_Jarak) < 65 && abs(F_Error_Jarak) >= 40) F_Nilai_P = F_Error_Jarak * 1;
		else if(abs(F_Error_Jarak) >= 65)							 F_Nilai_P = F_Error_Jarak * 0.8;
//		if(Prox == 0 || abs(sud >30))  F_Nilai_I =0;
	}
//	F_Nilai_PI = F_Nilai_P + F_Nilai_I ;
	F_Nilai_PI = F_Nilai_P;
	move_angle_3roda(manipul_sud,F_Nilai_PI,NO);

	F_Pwm1 = pwm1 + F_Error_Hadap;
	F_Pwm2 = pwm2 + F_Error_Hadap;
	F_Pwm3 = pwm3 + F_Error_Hadap;

	if (Program_Untuk == ORION) fwd_pwm_3roda_PID(F_Pwm1,F_Pwm2,F_Pwm3);

	lcd_gotoxy(0,3); sprintf(lcd, "%d",(int)F_Error_Hadap);						  lcd_putstr(lcd);
	lcd_gotoxy(7,3); sprintf(lcd, "%d",(int)F_Error_Jarak);						  lcd_putstr(lcd);
	lcd_gotoxy(14,3); sprintf(lcd, "%d",(int)F_Nilai_PI);						  lcd_putstr(lcd);
}

void Move_Koordinat_3roda(int x0, int y0, int x1, int y1, int x2, int y2){//x0 = Y odometry  y0= X odometry
	int sudut_imu = imu_filter;
	if (sudut_imu < 0 && Flag_Switch_Angle == 1) sudut_imu += 360;

	int range_x = abs(x1 - x0);
	int range_y = abs(y1 - y0);
	if(range_x == 0 ) range_x = 1;
	if(range_y == 0 ) range_y = 1;
	range_error = sqrt((range_x*range_x)+(range_y*range_y));
	sudut_error = koordinat_to_sudut(x0,y0,x1,y1)-sudut_imu;
	sudut_tembak = koordinat_to_sudut(x0,y0,x2,y2)-sudut_imu;
	F_Error_Hadap = Hadap(sudut_tembak);

//	if(abs(range_error)< 19)					 				 Koor_cm.P = range_error * 1.3;

	if(abs(range_error)< 19)					 				 Koor_cm.P = range_error * 1.4;
	else if(abs(range_error) < 40 && abs(range_error) >= 19) Koor_cm.P = range_error * 1.3;
	else if(abs(range_error) < 65 && abs(range_error) >= 40) Koor_cm.P = range_error * 1.2;
	else if(abs(range_error) >= 65)							 Koor_cm.P = range_error * 1.1;
	if (abs(range_error) < 5)									 Koor_cm.Ki += range_error * 0.07;

	if (abs(range_error) < 1) Koor_cm.Ki = 0;
//	if(abs(range_error)< 19)					 				 Koor_cm.P = range_error * 1.9;
//	else if(abs(range_error) < 40 && abs(range_error) >= 19) Koor_cm.P = range_error * 1.4;
//	else if(abs(range_error) < 65 && abs(range_error) >= 40) Koor_cm.P = range_error * 1.2;
//	else if(abs(range_error) >= 65)							 Koor_cm.P = range_error * 1.1;
//	if (abs(range_error) < 5)									 Koor_cm.Ki += range_error * 0.07;


	//else if(abs(range_error) < 7 && abs(range_error) >= 5)	 Koor_cm.Ki += range_error * 0.04;
	//else if(abs(range_error) < 12 && abs(range_error) >= 7)	 Koor_cm.Ki += range_error * 0.02;
	//else if(abs(range_error) < 15 && abs(range_error) >= 12) 	 Koor_cm.Ki += range_error * 0.04;
//	Koor_cm.nil_pid = Koor_cm.P + Koor_cm.Ki ;
	Koor_cm.nil_pid = Koor_cm.P ;

	move_angle_3roda(sudut_error,Koor_cm.nil_pid,NO);
	if (F_Error_Hadap >= 0.7*pwm1 || F_Error_Hadap >= 0.7*pwm2 || F_Error_Hadap >= 0.7*pwm3) F_Error_Hadap *= 0.5;
	F_Pwm1 = pwm1 + F_Error_Hadap;
	F_Pwm2 = pwm2 + F_Error_Hadap;
	F_Pwm3 = pwm3 + F_Error_Hadap;
//	fwd_pwm_3roda(F_Pwm1,F_Pwm2,F_Pwm3);
	fwd_pwm_3roda_PID(F_Pwm1,F_Pwm2,F_Pwm3);
}

//************************************************ FUNGSI ROTASI **********************************************//

void Rotate_To_Sudut(int sp_yaw)
{
	yaw2 = imu_filter;
	if(yaw2 >180)yaw2 -= 360;
	if (sp_yaw > 180)sp_yaw -= 360;
	Rotate_sdt.error = sp_yaw - (int)yaw2;
	Rotate_sdt.last_error = Rotate_sdt.error;
	Rotate_sdt.Kp= 0.7;
	Rotate_sdt.P = Rotate_sdt.Kp*Rotate_sdt.error;
//	Rotate_sdt.I = Rotate_sdt.Ki*(Rotate_sdt.error+Rotate_sdt.last_error)*Rotate_sdt.Ts;
//	Rotate_sdt.D = Rotate_sdt.Kd/Rotate_sdt.Ts*(Rotate_sdt.error-Rotate_sdt.last_error);
	if (abs(Rotate_sdt.error) <7 ) 	Rotate_sdt.I += Rotate_sdt.error * 0.02;
	Rotate_sdt.nil_pid =  (int)(Rotate_sdt.P + Rotate_sdt.I + Rotate_sdt.D);
	Rotate_sdt.pwm1 = Rotate_sdt.nil_pid;

	if(Rotate_sdt.pwm1 > 25)Rotate_sdt.pwm1 = 25;
	else if(Rotate_sdt.pwm1 < -25)Rotate_sdt.pwm1 = -25;
	else if(Rotate_sdt.pwm1 < 13 && Rotate_sdt.pwm1 >= 7)Rotate_sdt.pwm1 = 10;
	else if(Rotate_sdt.pwm1 > -13 && Rotate_sdt.pwm1 <= -7)Rotate_sdt.pwm1 = -10;
	else if(Rotate_sdt.pwm1 > -7 && Rotate_sdt.pwm1 < 7)Rotate_sdt.pwm1 = 0;

	PWM_Rotate = Rotate_sdt.pwm1;
if (PWM_Rotate >15 )PWM_Rotate=15;
if (PWM_Rotate <-15 )PWM_Rotate=-15;
//	fwd_pwm_3roda(PWM_Rotate,PWM_Rotate,PWM_Rotate);
//	fwd_pwm_3roda_PID(PWM_Rotate,PWM_Rotate,PWM_Rotate);
}

void Rotate_To_cm(int x, int y, int ball, int penendang_rotate)
{
	angleToTitik = koordinat_to_sudut((int)Y_Oddo_cm[5],(int)X_Oddo_cm[5],y,x);
	if(angleToTitik>180)angleToTitik -= 360;
	if(angleToTitik<-180)angleToTitik += 360;
	if(angleToTitik>180)angleToTitik -= 360;
	if(angleToTitik<-180)angleToTitik += 360;
	yaw2 = imu_filter;
	if(yaw2>180)yaw2 -= 360;
	if(yaw2<-180)yaw2 += 360;
	if(yaw2>180)yaw2 -= 360;
	if(yaw2<-180)yaw2 += 360;

	Rotate_cm.error = angleToTitik - yaw2;
//	lcd_gotoxy(17,3); sprintf(lcd, "%d", (int)Rotate_cm.error);  lcd_putstr(lcd);
	if (Prox == 1)
	{
		if (abs(Rotate_cm.error) < 20)
		{
			if(Program_Untuk == HYDRA) 		{Rotate_cm.Kp = 1.4;}
			else if(Program_Untuk == ORION) {Rotate_cm.Kp = 1.1;}
		}
		else
		{
			if(Program_Untuk == HYDRA)		{Rotate_cm.Kp = 1.4;}
			else if(Program_Untuk == ORION)	{Rotate_cm.Kp = 0.95;}
		}
	}

	else if (Prox != 1)
	{
		if (abs(Rotate_cm.error) < 20){
			if(Program_Untuk == HYDRA)
			{
				Rotate_cm.Kp = 1.5;
				if (abs(Rotate_cm.error) < 15)Rotate_cm.Kp = 1.8;
			}
			else if(Program_Untuk == ORION)	{Rotate_cm.Kp = 1.1;}
		}
		else
		{
			if(Program_Untuk == HYDRA)		{Rotate_cm.Kp = 1.5;}
			else if(Program_Untuk == ORION)	{Rotate_cm.Kp = 0.95;}
		}
	}

	Rotate_cm.P = Rotate_cm.Kp*Rotate_cm.error;
	Rotate_cm.I += Rotate_cm.Ki*Rotate_cm.error;
	Rotate_cm.D = Rotate_cm.Kd/Rotate_cm.Ts*(Rotate_cm.error-Rotate_cm.last_error);

	Rotate_cm.nil_pid =  (int)(Rotate_cm.P + Rotate_cm.I + Rotate_cm.D);
	Rotate_cm.pwm1 = Rotate_cm.nil_pid;
	if (Prox != 1){
		if (Program_Untuk == ORION) Gripper_function(ON,23);
		if (Program_Untuk == HYDRA) Gripper_function(ON,20);
		if (abs(Rotate_cm.error) < 30){
			if(Program_Untuk == HYDRA)
			{
				if(Rotate_cm.pwm1 > 18)Rotate_cm.pwm1 = 18;
				else if(Rotate_cm.pwm1 < -18)Rotate_cm.pwm1 = -18;
				else if(Rotate_cm.pwm1<=6  && Rotate_cm.pwm1>=-6)Rotate_cm.pwm1 = 0;
			}
			else if(Program_Untuk == ORION)
			{
				if(Rotate_cm.pwm1 > 18)Rotate_cm.pwm1 = 18;
				else if(Rotate_cm.pwm1 < -18)Rotate_cm.pwm1 = -18;
				else if(Rotate_cm.pwm1<= 6 && Rotate_cm.pwm1>=-6)Rotate_cm.pwm1 = 0;
			}
		}
		else {
			if(Program_Untuk == HYDRA){
				if(Rotate_cm.pwm1 > 24)Rotate_cm.pwm1 = 24;
				else if(Rotate_cm.pwm1 < -24)Rotate_cm.pwm1 = -24;
				else if(Rotate_cm.pwm1<=6  && Rotate_cm.pwm1>=-6)Rotate_cm.pwm1 = 0;
			}
			else if(Program_Untuk == ORION){
				if(Rotate_cm.pwm1 > 22)Rotate_cm.pwm1 = 22;
				else if(Rotate_cm.pwm1 < -22)Rotate_cm.pwm1 = -22;
				else if(Rotate_cm.pwm1<= 6 && Rotate_cm.pwm1>=-6)Rotate_cm.pwm1 = 0;
			}
		}
	}
	else
	{
//		Gripper_function(OFF,0);
		if (abs(Rotate_cm.error) < 20){
			if(Program_Untuk == HYDRA)
			{
				if(Rotate_cm.pwm1 > 18)Rotate_cm.pwm1 = 18;
				else if(Rotate_cm.pwm1 < -18)Rotate_cm.pwm1 = -18;
				else if(Rotate_cm.pwm1<=10 && Rotate_cm.pwm1>=-10)Rotate_cm.pwm1 = 0;
			}
			else if(Program_Untuk == ORION)
			{
				if(Rotate_cm.pwm1 > 12)Rotate_cm.pwm1 = 12;
				else if(Rotate_cm.pwm1 < -12)Rotate_cm.pwm1 = -12;
				else if(Rotate_cm.pwm1<=10 && Rotate_cm.pwm1>=-10)Rotate_cm.pwm1 = 0;
			}
		}
		else
		{
			if(Program_Untuk == HYDRA)
			{
				if(Rotate_cm.pwm1 > 25)Rotate_cm.pwm1 = 25;
				else if(Rotate_cm.pwm1 < -25)Rotate_cm.pwm1 = -25;
				else if(Rotate_cm.pwm1 < 10)Rotate_cm.pwm1 = 10;
				else if(Rotate_cm.pwm1 > -10)Rotate_cm.pwm1 = -10;
			}

			else if(Program_Untuk == ORION)
			{
				if(Rotate_cm.pwm1 > 22)Rotate_cm.pwm1 = 22;
				else if(Rotate_cm.pwm1 < -22)Rotate_cm.pwm1 = -22;
				else if(Rotate_cm.pwm1 < 10)Rotate_cm.pwm1 = 10;
				else if(Rotate_cm.pwm1 > -10)Rotate_cm.pwm1 = -10;
			}
		}
	}
	if(Rotate_cm.pwm1 == 0 &&  Prox != 1){
		Counter_Tendang++;
		Flagg_Tendang = 1;
		if (penendang_rotate == SHOOT && Counter_Tendang >= 3 )	FlagSiapTendang = 1;
		else if (Program_Untuk == HYDRA && Counter_Tendang >= 4 && T_ORION.Keadaan_Robot == 3)FlagSiapTendang = 1;
		else if (Program_Untuk == ORION && Counter_Tendang >= 3 && T_HYDRA.Keadaan_Robot == 3)FlagSiapTendang = 1;
	}
	else {Flagg_Tendang = 0; Counter_Tendang = 0;}

	if (abs(Rotate_cm.pwm1) < 6) /*STOP_tahan();*/ fwd_pwm_3roda_PID(0,0,0);
	else fwd_pwm_3roda_PID(Rotate_cm.pwm1,Rotate_cm.pwm1,Rotate_cm.pwm1);
//	fwd_pwm_3roda_PID(Rotate_cm.pwm1,Rotate_cm.pwm1,Rotate_cm.pwm1);
}

void Rotate_Kick(int x, int y, int kick)
{
	if (FlagSiapTendang == 0)
	{
		Rotate_To_cm(x,y,NO,kick);
		c_g = 0;
		c_p = 0;
		sedang_rotate = 1;
	}
	if (FlagSiapTendang == 1)
	{
		if (kick == SHOOT){
			LED(BLINK);
//			Solenoid_Manual_2021(1,1,1,1,solenoid5_state);
			Solenoid_Manual_4Cell_2021(1,1,1,solenoid4_state);
			Flagg_Tendang = 0;
			f_oper = 1;
			c_g = 1 ;
		}
		else if (kick == OPER){
//			lcd_gotoxy(10,3);  sprintf(lcd, "A");  lcd_putstr(lcd);
			LED(BLINK_FAST);
			Gripper_function(OFF,0);
//			Solenoid_Manual_2021(solenoid1_state,solenoid2_state,solenoid3_state,solenoid4_state,1);
			Solenoid_Manual_4Cell_2021(solenoid1_state,solenoid2_state,solenoid3_state,1);
			Flagg_Tendang = 0;
			c_g = 1 ;
			f_oper = 1;
		}
	}
	else LED(OFF);
}

void Rotate_To_Ball()
{
	angleToTitik = Angle_Ball;
	if(angleToTitik>180)angleToTitik -= 360;
	else if(angleToTitik<-180)angleToTitik += 360;
	yaw2 = imu_filter;
	if(yaw2>180)yaw2 -= 360;
	else if(yaw2<-180)yaw2 += 360;
//	Rotate_cm.error = angleToTitik - yaw2;
	Rotate_cm.error = angleToTitik;

	if(Program_Untuk == ORION)		{Rotate_cm.Kp = 1.5;}
	else if(Program_Untuk == HYDRA)	{Rotate_cm.Kp = 1.5;}

	Rotate_cm.P = Rotate_cm.Kp*Rotate_cm.error;
	Rotate_cm.I = Rotate_cm.Ki*(Rotate_cm.error+Rotate_cm.last_error)*Rotate_cm.Ts;
	Rotate_cm.D = Rotate_cm.Kd/Rotate_cm.Ts*(Rotate_cm.error-Rotate_cm.last_error);

	Rotate_cm.nil_pid =  (int)(Rotate_cm.P + Rotate_cm.I + Rotate_cm.D);
	Rotate_cm.pwm1 = Rotate_cm.nil_pid;
		if(Program_Untuk == HYDRA){
			if (abs(Rotate_cm.error) <= 30 && abs(Rotate_cm.error) > 0){//(Rotate_cm.error >= -25 && Rotate_cm.error <= 25){
				if(Rotate_cm.pwm1 > 13)Rotate_cm.pwm1 = 13;
				else if(Rotate_cm.pwm1 < -13)Rotate_cm.pwm1 = -13;
				else if(Rotate_cm.pwm1<=7 && Rotate_cm.pwm1>=-7)Rotate_cm.pwm1 = 0;
			}
			else if (abs(Rotate_cm.error) >= 60){
				if(Rotate_cm.pwm1 > 20)Rotate_cm.pwm1 = 20;
				else if(Rotate_cm.pwm1 < -20)Rotate_cm.pwm1 = -20;
			}
			else {
				if(Rotate_cm.pwm1 > 20)Rotate_cm.pwm1 = 20;
				else if(Rotate_cm.pwm1 < -20)Rotate_cm.pwm1 = -20;
			}
		}
		else if(Program_Untuk == ORION){

			if (abs(Rotate_cm.error) <= 30 && abs(Rotate_cm.error) > 0){//(Rotate_cm.error >= -25 && Rotate_cm.error <= 25){
				if(Rotate_cm.pwm1 > 13)Rotate_cm.pwm1 = 13;
				else if(Rotate_cm.pwm1 < -13)Rotate_cm.pwm1 = -13;
				else if(Rotate_cm.pwm1<=7 && Rotate_cm.pwm1>=-7)Rotate_cm.pwm1 = 0;
			}
			else if (abs(Rotate_cm.error) >= 80){
				if(Rotate_cm.pwm1 > 25)Rotate_cm.pwm1 = 25;
				else if(Rotate_cm.pwm1 < -25)Rotate_cm.pwm1 = -25;
			}
			else {
				if(Rotate_cm.pwm1 > 16)Rotate_cm.pwm1 = 16;
				else if(Rotate_cm.pwm1 < -16)Rotate_cm.pwm1 = -16;
			}
	}
//	if (abs(Rotate_cm.pwm1) < 7)	{STOP_tahan();}
//	/*else*/ fwd_pwm_3roda(Rotate_cm.pwm1,Rotate_cm.pwm1,Rotate_cm.pwm1);
	fwd_pwm_3roda_PID(Rotate_cm.pwm1,Rotate_cm.pwm1,Rotate_cm.pwm1);
}

void receive_ball(int Sud, int hadap)
{

	eyaw[0] = imu_filter;					//IMU
	if (eyaw[0] < 0)eyaw[0] += 360;
	eyaw[2]= Sud;					//Omni
	if (eyaw[2]>180)eyaw[2] -=360;

	if (hadap == jauh_gawang) Flag_Switch_Angle = 1;
	else if (hadap == diagonal_lapangan) Flag_Switch_Angle = 1;
	else { Flag_Switch_Angle =  0;}

	if (Flag_er_oddo == 0 && Prox == 1)
	{
		Oddo_er_X[0] = X_Oddo_cm[5];
		Oddo_er_Y[0] = Y_Oddo_cm[5];
		Flag_er_oddo = 1;
	}
	else if (Flag_er_oddo == 1 && Prox != 1) Flag_er_oddo = 0;

	if (hadap == hdp_gawang)
	{
		if (eyaw[0] > 180)eyaw[3] = eyaw[0] - 360;
		posisi = eyaw[3] + eyaw[2];
		Pwm_er[2] = PID_function(posisi,2,0.7);

		if ( X_Oddo_cm[5] <= Oddo_er_X[0]+20 && X_Oddo_cm[5] >= Oddo_er_X[0]-20)
		{ Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Oddo_er_Y[0],X_Oddo_cm[5] + Pwm_er[2],500,X_Oddo_cm[5]);}

		else if (X_Oddo_cm[5] > Oddo_er_X[0]+20)		//batas kanan
		{
			if (eyaw[2] >= 0) fwd_pwm_3roda_PID(0,0,0);
			else if (eyaw[2] < 0) Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Oddo_er_Y[0],X_Oddo_cm[5] + Pwm_er[2],500,X_Oddo_cm[5]);
		}

		else if (X_Oddo_cm[5] < Oddo_er_X[0]-20)		//batas kiri
		{
			if (eyaw[2] <= 0) fwd_pwm_3roda_PID(0,0,0);
			else if (eyaw[2] > 0) Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Oddo_er_Y[0],X_Oddo_cm[5] + Pwm_er[2],500,X_Oddo_cm[5]);
		}
	}

	else if (hadap == kanan_lapangan)		// robot hadap kanan lapangan
	{
		sp_receive = 90;
		posisi = eyaw[0] + eyaw[2];
		eyaw[3] = sp_receive - posisi;
		Pwm_er[2] = PID_function(eyaw[3],2,0.7);

		if ( Y_Oddo_cm[5] <= Oddo_er_Y[0]+20 && Y_Oddo_cm[5] >= Oddo_er_Y[0]-20)
		{ Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Y_Oddo_cm[5] + Pwm_er[2],Oddo_er_X[0],Y_Oddo_cm[5],600);}

		else if (Y_Oddo_cm[5] > Oddo_er_Y[0]+20)		//batas kiri
		{
			if (eyaw[2] <= 0) fwd_pwm_3roda_PID(0,0,0);
			else if (eyaw[2] > 0) Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Y_Oddo_cm[5] + Pwm_er[2],Oddo_er_X[0],Y_Oddo_cm[5],600);
		}

		else if (Y_Oddo_cm[5] < Oddo_er_Y[0]-20)		//batas kanan
		{
			if (eyaw[2] >= 0) fwd_pwm_3roda_PID(0,0,0);
			else if (eyaw[2] < 0) Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Y_Oddo_cm[5] + Pwm_er[2],Oddo_er_X[0],Y_Oddo_cm[5],600);
		}
	}

	else if (hadap == jauh_gawang)		// robot menjauhi gawang
	{
		sp_receive = 180;
		posisi = eyaw[0] + eyaw[2];
		eyaw[3] = sp_receive - posisi;
		Pwm_er[2] = PID_function(eyaw[3],3.55,0);

		if ( X_Oddo_cm[5] <= Oddo_er_X[0]+20 && X_Oddo_cm[5] >= Oddo_er_X[0]-20)
		{ Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Oddo_er_Y[0],X_Oddo_cm[5] + Pwm_er[2],-100,X_Oddo_cm[5]);}

		else if (X_Oddo_cm[5] > Oddo_er_X[0]+20)		//batas kiri
		{
			if (eyaw[2] <= 0) fwd_pwm_3roda_PID(0,0,0);
			else if (eyaw[2] > 0) Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Oddo_er_Y[0],X_Oddo_cm[5] + Pwm_er[2],-100,X_Oddo_cm[5]);
		}

		else if (X_Oddo_cm[5] < Oddo_er_X[0]-20)		//batas kanan
		{
			if (eyaw[2] >= 0) fwd_pwm_3roda_PID(0,0,0);
			else if (eyaw[2] < 0) Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Oddo_er_Y[0],X_Oddo_cm[5] + Pwm_er[2],-100,X_Oddo_cm[5]);
		}
	}

	else if (hadap == kiri_lapangan)		// robot hadap kiri lapangan
	{
		sp_receive = 270;
		posisi = eyaw[0] + eyaw[2];
		eyaw[3] = sp_receive - posisi;
		int kpppp = 1.4;
		if (R_Ball < 70) kpppp = 3;
		Pwm_er[2] = -1 * PID_function(eyaw[3],kpppp,0);

		if ( Y_Oddo_cm[5] <= Oddo_er_Y[0]+30 && Y_Oddo_cm[5] >= Oddo_er_Y[0]-20)
		{ Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Y_Oddo_cm[5] + Pwm_er[2],Oddo_er_X[0],Y_Oddo_cm[5],-100);}

		else if (Y_Oddo_cm[5] > Oddo_er_Y[0]+30)		//batas kanan
		{
			if (eyaw[2] >= 0) fwd_pwm_3roda_PID(0,0,0);
			else if (eyaw[2] < 0) Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Y_Oddo_cm[5] + Pwm_er[2],Oddo_er_X[0],Y_Oddo_cm[5],-100);
		}
		else if (Y_Oddo_cm[5] < Oddo_er_Y[0]-20)		//batas kiri
		{
			if (eyaw[2] <= 0) fwd_pwm_3roda_PID(0,0,0);
			else if (eyaw[2] > 0) Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Y_Oddo_cm[5] + Pwm_er[2],Oddo_er_X[0],Y_Oddo_cm[5],-100);
		}
	}

	else if (hadap == diagonal_lapangan)		// sudut 135
	{
		sp_receive = 125;
		posisi = eyaw[0] + eyaw[2];
		eyaw[3] = sp_receive - posisi;
		Pwm_er[2] = PID_function(eyaw[3],2.85,0.7);
		if ( X_Oddo_cm[5] <= Oddo_er_X[0]+20 && X_Oddo_cm[5] >= Oddo_er_X[0]-30)
		{ Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Y_Oddo_cm[5] + (1.43*Pwm_er[2]),X_Oddo_cm[5] + Pwm_er[2],Y_Oddo_cm[5]-100,X_Oddo_cm[5]+143);}

		else if (X_Oddo_cm[5] > Oddo_er_X[0]+20)		//batas kiri
		{
			if (eyaw[2] <= 0) fwd_pwm_3roda_PID(0,0,0);
			else if (eyaw[2] > 0) Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Y_Oddo_cm[5] + (1.43*Pwm_er[2]),X_Oddo_cm[5] + Pwm_er[2],Y_Oddo_cm[5]-100,X_Oddo_cm[5]+143);
		}

		else if (X_Oddo_cm[5] < Oddo_er_X[0]-30)		//batas kanan
		{
			if (eyaw[2] >= 0) fwd_pwm_3roda_PID(0,0,0);
			else if (eyaw[2] < 0) Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Y_Oddo_cm[5] + (1.43*Pwm_er[2]),X_Oddo_cm[5] + Pwm_er[2],Y_Oddo_cm[5]-100,X_Oddo_cm[5]+143);
		}
	}
	else if (hadap == diagonal_lapangan2)		// sudut 135
		{
			sp_receive = 220;
			posisi = eyaw[0] + eyaw[2];
			eyaw[3] = sp_receive - posisi;
			Pwm_er[2] = PID_function(eyaw[3],2.85,0.7);

			if ( X_Oddo_cm[5] <= Oddo_er_X[0]+20 && X_Oddo_cm[5] >= Oddo_er_X[0]-20)
			{ Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Y_Oddo_cm[5] - Pwm_er[2],X_Oddo_cm[5] + Pwm_er[2],Y_Oddo_cm[5]-100,X_Oddo_cm[5]-84);}

			else if (X_Oddo_cm[5] > Oddo_er_X[0]+20)		//batas kiri
			{
				if (eyaw[2] <= 0) fwd_pwm_3roda_PID(0,0,0);
				else if (eyaw[2] > 0) Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Y_Oddo_cm[5] - Pwm_er[2],X_Oddo_cm[5] + Pwm_er[2],Y_Oddo_cm[5]-100,X_Oddo_cm[5]-84);
			}

			else if (X_Oddo_cm[5] < Oddo_er_X[0]-20)		//batas kanan
			{
				if (eyaw[2] >= 0) fwd_pwm_3roda_PID(0,0,0);
				else if (eyaw[2] < 0) Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Y_Oddo_cm[5] - Pwm_er[2],X_Oddo_cm[5] + Pwm_er[2],Y_Oddo_cm[5]-100,X_Oddo_cm[5]-84);
			}
		}
}

//*************************************************************************************************************//

void cek_lapangan()
{
	if (Flag_Posisi == 0)
	{
//		Tujuan_KoorX = 0;		arahX = X_Oddo_cm[5];
//		Tujuan_KoorY = 200;		arahY = 500;
		Tujuan_KoorX = 200;		arahX = 0;
		Tujuan_KoorY = 200;		arahY = 500;

		if ((Y_Oddo_cm[5] > Tujuan_KoorY - 5 && Y_Oddo_cm[5] < Tujuan_KoorY + 5) &&
				(X_Oddo_cm[5] > Tujuan_KoorX -5 && X_Oddo_cm[5] < Tujuan_KoorX + 5)) Flag_tahan = 1;
	}
	else if (Flag_Posisi == 1)
	{
//		Tujuan_KoorX = 200;		arahX = X_Oddo_cm[5];
//		Tujuan_KoorY = 200;		arahY = 500;
		Tujuan_KoorX = 0;		arahX = 300;
		Tujuan_KoorY = 200;		arahY = 500;

		if ((Y_Oddo_cm[5] > Tujuan_KoorY - 5 && Y_Oddo_cm[5] < Tujuan_KoorY + 5) &&
				(X_Oddo_cm[5] > Tujuan_KoorX -5 && X_Oddo_cm[5] < Tujuan_KoorX + 5)) Flag_tahan = 1;
	}
	else if (Flag_Posisi == 2)
	{
//		Tujuan_KoorX = 200;		arahX = X_Oddo_cm[5];
//		Tujuan_KoorY = 0;		arahY = 500;
		Tujuan_KoorX = 0;		arahX = 500;
		Tujuan_KoorY = 0;		arahY = Y_Oddo_cm[5];

		if ((Y_Oddo_cm[5] > Tujuan_KoorY - 5 && Y_Oddo_cm[5] < Tujuan_KoorY + 5) &&
				(X_Oddo_cm[5] > Tujuan_KoorX -5 && X_Oddo_cm[5] < Tujuan_KoorX + 5)) Flag_tahan = 1;
	}
	else if (Flag_Posisi == 3)
	{
//		Tujuan_KoorX = 0;		arahX = X_Oddo_cm[5];
//		Tujuan_KoorY = 0;		arahY = 500;
		Tujuan_KoorX = 0;		arahX = X_Oddo_cm[5];
		Tujuan_KoorY = 200;		arahY = 500;

		if ((Y_Oddo_cm[5] > Tujuan_KoorY - 5 && Y_Oddo_cm[5] < Tujuan_KoorY + 5) &&
				(X_Oddo_cm[5] > Tujuan_KoorX -5 && X_Oddo_cm[5] < Tujuan_KoorX + 5)) Flag_tahan = 1;
	}
	else if (Flag_Posisi == 4)
	{
		Tujuan_KoorX = 200;		arahX = X_Oddo_cm[5];
		Tujuan_KoorY = 200;		arahY = 500;

		if ((Y_Oddo_cm[5] > Tujuan_KoorY - 5 && Y_Oddo_cm[5] < Tujuan_KoorY + 5) &&
				(X_Oddo_cm[5] > Tujuan_KoorX -5 && X_Oddo_cm[5] < Tujuan_KoorX + 5)) Flag_tahan = 1;
	}
	else if (Flag_Posisi == 5)
	{
//		Tujuan_KoorX = 0;		arahX = X_Oddo_cm[5];
//		Tujuan_KoorY = 200;		arahY = 500;
		Tujuan_KoorX = 100;		arahX = X_Oddo_cm[5];
		Tujuan_KoorY = 100;		arahY = 500;

		if ((Y_Oddo_cm[5] > Tujuan_KoorY - 5 && Y_Oddo_cm[5] < Tujuan_KoorY + 5) &&
				(X_Oddo_cm[5] > Tujuan_KoorX -5 && X_Oddo_cm[5] < Tujuan_KoorX + 5)) Flag_tahan = 1;
	}
	else if (Flag_Posisi == 6)
	{
//		Tujuan_KoorX = 200;		arahX = X_Oddo_cm[5];
//		Tujuan_KoorY = 0;		arahY = 500;
		Tujuan_KoorX = 0;		arahX = 300;
		Tujuan_KoorY = 200;		arahY = 500;

		if ((Y_Oddo_cm[5] > Tujuan_KoorY - 5 && Y_Oddo_cm[5] < Tujuan_KoorY + 5) &&
				(X_Oddo_cm[5] > Tujuan_KoorX -5 && X_Oddo_cm[5] < Tujuan_KoorX + 5)) Flag_tahan = 1;
	}
	else if (Flag_Posisi == 7)
	{
		Tujuan_KoorX = 0;		arahX = X_Oddo_cm[5];
		Tujuan_KoorY = 0;		arahY = 500;

		if ((Y_Oddo_cm[5] > Tujuan_KoorY - 5 && Y_Oddo_cm[5] < Tujuan_KoorY + 5) &&
				(X_Oddo_cm[5] > Tujuan_KoorX -5 && X_Oddo_cm[5] < Tujuan_KoorX + 5)) Flag_tahan = 1;
	}
	else if (Flag_Posisi == 8) Flag_Posisi = 0;

	if (Flag_Posisi != 9)
	{
		Move_Koordinat_3roda(Y_Oddo_cm[5], X_Oddo_cm[5], Tujuan_KoorY, Tujuan_KoorX, arahY, arahX);
	}
}

void waktu_cek_gripper()
{
//	if (execute == 0) Flag_cek_count_gripper = 0; cek_count_gripper = 0;
	if (Flag_cek_count_gripper == 1) cek_count_gripper++;
	if (cek_count_gripper > 200) cek_count_gripper = 0;
}
void cek_gripper()
{
	Flag_cek_count_gripper = 1;

	if (Flag_cek_count_gripper == 1)
	{
		if (cek_count_gripper <= 50) move_angle_3roda(0,40,YES);
		else if (cek_count_gripper > 50 && cek_count_gripper <= 100) move_angle_3roda(90,40,YES);
		else if (cek_count_gripper > 100 && cek_count_gripper <= 150) move_angle_3roda(180,40,YES);
		else if (cek_count_gripper > 150 && cek_count_gripper <= 200) move_angle_3roda(-90,40,YES);
	}
	else fwd_pwm_3roda_PID(0,0,0);
}
//******************************************** STRATEGI TAHUN 2021 ********************************************//

//----------------------------------------------- ONLINE ------------------------------------------------------//
void Strategi_HYDRA(int Sud_Bola, int Jar_Bola)
{
	Tuas_Algorithm(80, Tuas_Pot);
	if (Flag_Posisi == 0)
	{
		Flag_Gerak = 1; f_oper = 0;
		if (X_Oddo_cm[5] <= 450) hindar_dummy = 1;
		if (hindar_dummy == 0)
		{
			if (dummy3 == 4)
			{
				Tujuan_KoorY = 120;		Tujuan_KoorX = 435;
				arahY = Y_Oddo_cm[5]-100;	arahX = X_Oddo_cm[5]-84;
			}
			else if (dummy3 == 5)
			{
				Tujuan_KoorY = 160;		Tujuan_KoorX = 425;
				arahY = Y_Oddo_cm[5]-100;	arahX = X_Oddo_cm[5]-84;
			}
			else hindar_dummy = 1;
		}
		else if (hindar_dummy != 0)
		{
			Tujuan_KoorY = 120;		Tujuan_KoorX = 435;		arahY = Y_Oddo_cm[5]-100;	arahX = X_Oddo_cm[5]-84;
		}
		if ( (X_Oddo_cm[5] > (int)(Tujuan_KoorX-8)) && X_Oddo_cm[5] < (int)(Tujuan_KoorX+8) &&
				(Y_Oddo_cm[5] < (int)(Tujuan_KoorY+8) && Y_Oddo_cm[5] > (int)(Tujuan_KoorY-8)) && hindar_dummy == 1 )
			{ Flag_Posisi = 1; }
		if (hindar_dummy == 1 && T_ORION.Keadaan_Robot == 5) Flag_Posisi = 1;
	}
	else if (Flag_Posisi == 1)
	{
		Flag_Gerak = 0;
		if (Prox == 1)
		{
			c_g = 1;
			if (c_p <=2) fwd_pwm_3roda_PID(0,0,0);
			if (Jar_Bola > 50 && Flag_posisi_receive == 0 && c_p <= 8 && T_ORION.Keadaan_Robot == 1)receive_ball(Sud_Bola,diagonal_lapangan);
			if (Jar_Bola == 0 && Flag_posisi_receive == 0)
			{
				Rotate_To_Sudut(220);
				if (abs(Rotate_sdt.error) < 10 ) fwd_pwm_3roda_PID(0,0,0);
				else fwd_pwm_3roda_PID(PWM_Rotate,PWM_Rotate,PWM_Rotate);
			}
			if ( ( ( (Jar_Bola <= 50 && Jar_Bola > 0) || c_p > 8 ) && Flag_posisi_receive == 0 ) || T_ORION.Keadaan_Robot == 2)
			{
				Rotate_To_Ball();
				T_HYDRA.Keadaan_Robot = 3;
				if (Jar_Bola <= SP_Kamera) Flag_posisi_receive = 1;
			}
			if (Jar_Bola > 0 && Flag_posisi_receive == 1) Follow_Ball(Sud_Bola, Jar_Bola, SP_Kamera);
		}
		else if (Prox != 1) {	Flag_Posisi = 2; c_g = 0; c_p = 0;	}
	}
	else if (Flag_Posisi == 2)
	{
		if (Prox != 1 && f_oper == 0)
		{
			T_HYDRA.Keadaan_Robot = 1;
			Rotate_Kick(T_ORION.Koor_X, T_ORION.Koor_Y , OPER);
		}
		else if (Prox == 1 && f_oper == 0) Follow_Ball(Sud_Bola, Jar_Bola, SP_Kamera);
		else if (Prox == 1 && f_oper == 1 && c_p >=5)
		{
			FlagSiapTendang = 0;	c_g = 0;	c_p = 0;	sedang_rotate = 0;
			Flag_Posisi = 3;
		}
	}
	else if (Flag_Posisi == 3)
	{
		Flag_Gerak = 1;
		if (dummy3 ==  4 ) 	  {Tujuan_KoorY = 260;	Tujuan_KoorX = 440;	arahY = Y_Oddo_cm[5]; arahX = 0;
			if( Y_Oddo_cm[5] > (int)(150) && X_Oddo_cm[5] > (int) 400 )Flag_Posisi = 4;}
		else if (dummy3 == 5) {Tujuan_KoorY = 90;	Tujuan_KoorX = 440;	arahY = Y_Oddo_cm[5]; arahX = 0;
			if( Y_Oddo_cm[5] < (int)(185) && X_Oddo_cm[5] > (int) 400 ) Flag_Posisi = 4;}
		else 		 		  {Flag_Posisi = 4;}
	}
	else if (Flag_Posisi == 4)
	{
		Tujuan_KoorY = 190;	Tujuan_KoorX = 580;	arahY = Y_Oddo_cm[5]; arahX = 0;
		if( Y_Oddo_cm[5] > (int)(180) && X_Oddo_cm[5] > (int)(570) )Flag_Posisi = 5;
	}
	else if (Flag_Posisi == 5)
	{
		Flag_Gerak = 0;
		fwd_pwm_3roda_PID(0,0,0);
	}
	if(Flag_Gerak == 1) Move_Koordinat_3roda(Y_Oddo_cm[5], X_Oddo_cm[5], Tujuan_KoorY, Tujuan_KoorX, arahY, arahX);
}

void Strategi_ORION(int Sud_Bola, int Jar_Bola)
{
	if (Flag_Posisi == 0)
	{
		f_oper = 0; c_g = 0; c_p = 0; T_ORION.Keadaan_Robot = 1;
		Flag_Gerak = 1; kickoff_awal = 1;
		Tuas_Algorithm(70, Tuas_Pot);
		Tujuan_KoorY = 0;		Tujuan_KoorX = 100;		arahY = Y_Oddo_cm[5]+ 20; arahX = 600;
		if( Y_Oddo_cm[5] < 80 && Y_Oddo_cm[5] > -20) Flag_Posisi = 1;
		if (dummy1 != 1 ) Flag_Posisi = 1;
	}
	else if (Flag_Posisi == 1)
	{
		if (Prox == 1 && f_oper == 0)
		{
			Tuas_Algorithm(70, Tuas_Pot);
			if (Jar_Bola > SP_Kamera + 40 && kickoff_awal == 1)
			{
				Flag_Gerak = 1; c_g = 0; c_p = 0;
				if (dummy1 == 1 )
				{	Tujuan_KoorY = 5; Tujuan_KoorX = 230;	arahY = Y_Oddo_cm[5]+20; arahX = 600;	}
				else if (dummy1 != 1 )
				{	Tujuan_KoorY = 0; Tujuan_KoorX = 210;	arahY = Y_Oddo_cm[5]+20; arahX = 600;	}
			}
			if (Jar_Bola <= SP_Kamera + 40 && Jar_Bola > 0 && kickoff_awal == 1) kickoff_awal = 3;
			if ( (T_HYDRA.Keadaan_Robot == 3 && dummy1 != 1) && kickoff_awal == 1) kickoff_awal = 3;

			if (kickoff_awal == 3)
			{
				Flag_Gerak = 0;
				c_g = 1;
				if (c_p < 5)
				{
					if (c_p < 2) fwd_pwm_3roda_PID(0,0,0);
					else Rotate_To_Ball();
				}
				else Follow_Ball(Sud_Bola, Jar_Bola, SP_Kamera);
			}
		}
		else if (Prox == 1 && f_oper == 1 && c_p > 2)
		{
			FlagSiapTendang = 0;	Flag_Posisi = 2; c_g = 0; c_p = 0; f_oper = 0;
		}
		else
		{
			T_ORION.Keadaan_Robot = 5;
			Rotate_Kick(T_HYDRA.Koor_X, T_HYDRA.Koor_Y , OPER);
		}
	}
	else if (Flag_Posisi == 2)
	{
		Flag_Gerak = 1; kickoff_awal = 1;
		Tuas_Algorithm(30, Tuas_Pot);
		Tujuan_KoorY = 170;			Tujuan_KoorX = 205;		arahY = Y_Oddo_cm[5];		arahX = 600;
		if(	Y_Oddo_cm[5] < 130 && Y_Oddo_cm[5]>90 && dummy1 == 1)Flag_Posisi = 3;
		if(	Y_Oddo_cm[5] < 130 && Y_Oddo_cm[5]>100 && dummy1 != 1)Flag_Posisi = 3;
	}
	else if (Flag_Posisi == 3)
	{
		Flag_Gerak = 0; c_g = 1;
		if (Prox == 1)
		{
			Tuas_Algorithm(30, Tuas_Pot);
			if (Jar_Bola > 90 && Flag_posisi_receive == 0 && c_p <=15 )
			{
				if (c_p < 8 )fwd_pwm_3roda_PID(0,0,0);
				else receive_ball(Sud_Bola,kanan_lapangan);
			}
			else if (Jar_Bola == 0 && Flag_posisi_receive == 0) {
				Rotate_To_Sudut(90);
				if (abs(Rotate_sdt.error) < 10 ) fwd_pwm_3roda_PID(0,0,0);
				else fwd_pwm_3roda_PID(PWM_Rotate,PWM_Rotate,PWM_Rotate);
			}
			else if ( ((Jar_Bola <= 90 && Jar_Bola > 0) || c_p > 15) && Flag_posisi_receive == 0 )
			{
				Rotate_To_Ball();
				T_ORION.Keadaan_Robot = 3;
				if (Jar_Bola < (SP_Kamera + 15) )Flag_posisi_receive = 1;
			}
			else if (Jar_Bola > 0 && Flag_posisi_receive == 1){	Follow_Ball(Sud_Bola,Jar_Bola,SP_Kamera);	}
		}
		else if (Prox != 1) {	Flag_Posisi = 4;	c_g = 0;	c_p = 0;	}
	}
	else if (Flag_Posisi == 4)
	{
		Tuas_Algorithm(30, Tuas_Pot);
		if (Prox != 1)
		{
			if (X_Oddo_cm[5] > 200  && X_Oddo_cm[5] <= 250)	{	Flag_Gerak = 0; Rotate_Kick(245,600,SHOOT);	}
			else if (X_Oddo_cm[5] > 350  && X_Oddo_cm[5] <  400) {	Flag_Gerak = 0; Rotate_Kick(305,600,SHOOT);	}
			else { Flag_Gerak = 1;	Tujuan_KoorY = 150;	Tujuan_KoorX = 225;	arahY = Y_Oddo_cm[5];	arahX = 600; }
		}
		else if (Prox == 1 && c_p > 4 && f_oper == 1)
		{
			c_g = 0; c_p = 0; Flag_Posisi = 5; f_oper = 0;
		}
		else if (Prox == 1 && FlagSiapTendang == 0) { Flag_Gerak = 0; Follow_Ball(Sud_Bola, Jar_Bola, SP_Kamera); }
	}
	else if (Flag_Posisi == 5)
	{
		Flag_Gerak = 0;
		if (dummy1 == 1)
		{
			if (Flag_untuk_reset == 0){	Tujuan_KoorY = 270; Tujuan_KoorX = 140;	arahY = Y_Oddo_cm[5];arahX = 600;}
			if (Flag_untuk_reset == 1){	Tujuan_KoorY = 190; Tujuan_KoorX = 30;	arahY = Y_Oddo_cm[5];arahX = 600;}
			if (X_Oddo_cm[5] < 200 && Y_Oddo_cm[5] > 120 && Flag_untuk_reset == 0)Flag_untuk_reset = 1;

			if (X_Oddo_cm[5] < 55 && Y_Oddo_cm[5] > 190){	fwd_pwm_3roda_PID(0,0,0);	}
			else Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Tujuan_KoorY,Tujuan_KoorX,arahY,arahX);
		}
		else if (dummy1 == 2)
		{
			if (Flag_untuk_reset == 0){	Tujuan_KoorY = 100; Tujuan_KoorX = 80;	arahY = Y_Oddo_cm[5];arahX = 600;}
			if (Flag_untuk_reset == 1){	Tujuan_KoorY = 220; Tujuan_KoorX = 30;	arahY = Y_Oddo_cm[5];arahX = 600;}
			if (X_Oddo_cm[5] < 180 && Y_Oddo_cm[5] < 160 && Flag_untuk_reset == 0)Flag_untuk_reset = 1;

			if (X_Oddo_cm[5] < 40 && Y_Oddo_cm[5] > 190){	fwd_pwm_3roda_PID(0,0,0);	}
			else Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Tujuan_KoorY,Tujuan_KoorX,arahY,arahX);
		}
		else
		{
			if (X_Oddo_cm[5] < 40 && Y_Oddo_cm[5] > 190) {	fwd_pwm_3roda_PID(0,0,0);	}
			else Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],200,30,Y_Oddo_cm[5],600);
		}
	}
	if (Flag_Gerak == 1) Move_Koordinat_3roda(Y_Oddo_cm[5], X_Oddo_cm[5], Tujuan_KoorY, Tujuan_KoorX, arahY, arahX);
}

void strategi_1(int Sud_Bola, int Jar_Bola)
{
	if (Jar_Bola == 0)		LED(BLINK);
	else if (Jar_Bola > 0)	LED(ON);

	if (wifi2020 == 1)
	{
		f_stop = 0; f_berhenti = 0;
		if (R_DATA == 2)
		{
			FlagSiapTendang = 0;
//			Solenoid_Manual_2021(0,0,0,0,0);
			Solenoid_Manual_4Cell_2021(0,0,0,0);
			F_Nilai_I  = 0;		  Flag_Posisi = 0;
			c_g = 0; c_p = 0;
			Flag_posisi_receive = 0;
			Flag_reset_game = 0;	reset_imu = imu_real;	Flag_untuk_reset = 0;	hindar_dummy = 0;
			if (Program_Untuk == HYDRA){	X_Oddo_cm[5] = 570;	Y_Oddo_cm[5] = 200;	}
			if (Program_Untuk == ORION)	{X_Oddo_cm[5] = 30;	Y_Oddo_cm[5] = 200;	}
			R_DATA = 1;
		}
		else
		{
			if (Program_Untuk == ORION) Strategi_ORION(Sud_Bola, Jar_Bola);
			else if (Program_Untuk == HYDRA) Strategi_HYDRA(Sud_Bola,Jar_Bola);
		}
	}
	else if (wifi2020 == 2)
	{
		Natural_gripper(DRIBBLE_OFF, 0, 0);
//		Solenoid_Manual_2021(0,0,0,0,0);
		Solenoid_Manual_4Cell_2021(0,0,0,0);
		if (Program_Untuk == ORION) Tuas_Algorithm(45, Tuas_Pot);
		if (f_berhenti == 0){c_g = 0; c_p = 0; f_berhenti = 1;}
		R_DATA = 2;
		fwd_pwm_3roda_PID(0,0,0);
	}
	else if (wifi2020 == 3)
	{
		Natural_gripper(DRIBBLE_OFF, 0, 0);
//		Solenoid_Manual_2021(0,0,0,0,0);
		Solenoid_Manual_4Cell_2021(0,0,0,0);
		R_DATA  = 2;	f_stop = 1; f_berhenti = 0;
		if (Program_Untuk == ORION) Tuas_Algorithm(45, Tuas_Pot);

		if (c_stop < 2) fwd_pwm_3roda_PID(0,0,0);
		else {
			if (Program_Untuk == ORION)	{
				if (dummy1 == 1)
				{
					T_ORION.Keadaan_Robot = 1; kickoff_awal = 1;
					if (Flag_untuk_reset == 0)
					{
						c_g = 0; c_p = 0;
						Tujuan_KoorY = 250; Tujuan_KoorX = 120;	arahY = 200;arahX = 600;
					}
					if (Flag_untuk_reset == 1){	Tujuan_KoorY = 200; Tujuan_KoorX = 30;	arahY = 200;arahX = 600;}
					if(X_Oddo_cm[5] < 170 && Y_Oddo_cm[5] > 180 && Flag_untuk_reset == 0)Flag_untuk_reset = 1;
					if (X_Oddo_cm[5] < 40 && Y_Oddo_cm[5] > 190)	{	fwd_pwm_3roda_PID(0,0,0);	}
					else Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Tujuan_KoorY,Tujuan_KoorX,arahY,arahX);
				}
				else if (dummy1 == 2)
				{
					if (Flag_untuk_reset == 0){ c_g = 0; c_p = 0;
						Tujuan_KoorY = 100; Tujuan_KoorX = 80;	arahY = 200;arahX = 600;}
					if (Flag_untuk_reset == 1){	Tujuan_KoorY = 220; Tujuan_KoorX = 30;	arahY = 200;arahX = 600;}
					if(X_Oddo_cm[5] < 180 && Y_Oddo_cm[5] < 160 && Flag_untuk_reset == 0)Flag_untuk_reset = 1;
					if (X_Oddo_cm[5] < 40 && Y_Oddo_cm[5] > 190)	{	fwd_pwm_3roda_PID(0,0,0);	}
					else Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Tujuan_KoorY,Tujuan_KoorX,arahY,arahX);
				}
				else {
					if (X_Oddo_cm[5] < 40 && Y_Oddo_cm[5] > 190)	{	fwd_pwm_3roda_PID(0,0,0);	}
					else { Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],200,30,200,600);	}
				}
			}
			else if (Program_Untuk == HYDRA)
			{
				T_HYDRA.Keadaan_Robot = 1;
				if (X_Oddo_cm[5] > 560 && Y_Oddo_cm[5] > 190)	{	fwd_pwm_3roda_PID(0,0,0);	}
				else {	c_g = 0;	c_p = 0;	Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],200,570,200,0); }
			}
		}

	}
}

void Strategi_ORION_MAIN(int Sud_Bola, int Jar_Bola)
{
	if (Flag_Posisi == 0)
	{
		f_oper = 0; c_g = 0; c_p = 0; T_ORION.Keadaan_Robot = 1;
		Flag_Gerak = 1; kickoff_awal = 1;
		Tuas_Algorithm(70, Tuas_Pot);
		Tujuan_KoorY = 0;		Tujuan_KoorX = 100;		arahY = Y_Oddo_cm[5]+ 20; arahX = 600;
		if( Y_Oddo_cm[5] < 80 && Y_Oddo_cm[5] > -20) Flag_Posisi = 1;
		if (dummy1 != 1 ) Flag_Posisi = 1;
	}
	else if (Flag_Posisi == 1)
	{
		if (Prox == 1 && f_oper == 0)
		{
			Tuas_Algorithm(70, Tuas_Pot);
			if (Jar_Bola > SP_Kamera + 40 && kickoff_awal == 1)
			{
				Flag_Gerak = 1; c_g = 0; c_p = 0;
				if (dummy1 == 1 )
				{	Tujuan_KoorY = 5; Tujuan_KoorX = 230;	arahY = Y_Oddo_cm[5]+20; arahX = 600;	}
				else if (dummy1 != 1 )
				{	Tujuan_KoorY = 0; Tujuan_KoorX = 210;	arahY = Y_Oddo_cm[5]+20; arahX = 600;	}
			}
			if (Jar_Bola <= SP_Kamera + 40 && Jar_Bola > 0 && kickoff_awal == 1) kickoff_awal = 3;
			if ( (T_HYDRA.Keadaan_Robot == 3 && dummy1 != 1) && kickoff_awal == 1) kickoff_awal = 3;

			if (kickoff_awal == 3)
			{
				Flag_Gerak = 0;
				c_g = 1;
				if (c_p < 5)
				{
					T_ORION.Keadaan_Robot = 2;
					if (c_p < 2) fwd_pwm_3roda_PID(0,0,0);
					else Rotate_To_Ball();
				}
				else Follow_Ball(Sud_Bola, Jar_Bola, SP_Kamera);
			}
		}
		else if (Prox == 1 && f_oper == 1 && c_p > 2)
		{
			FlagSiapTendang = 0;	Flag_Posisi = 2; c_g = 0; c_p = 0; f_oper = 0;
		}
		else
		{
			T_ORION.Keadaan_Robot = 5;
			Rotate_Kick(T_HYDRA.Koor_X, T_HYDRA.Koor_Y , OPER);
		}
	}
	else if (Flag_Posisi == 2)
	{
		Flag_Gerak = 1; kickoff_awal = 1;
		Tuas_Algorithm(30, Tuas_Pot);
		Tujuan_KoorY = 170;			Tujuan_KoorX = 205;		arahY = Y_Oddo_cm[5];		arahX = 600;
		if(	Y_Oddo_cm[5] < 130 && Y_Oddo_cm[5]>90 && dummy1 == 1)Flag_Posisi = 3;
		if(	Y_Oddo_cm[5] < 130 && Y_Oddo_cm[5]>100 && dummy1 != 1)Flag_Posisi = 3;
	}
	else if (Flag_Posisi == 3)
	{
		Flag_Gerak = 0; c_g = 1;
		if (Prox == 1)
		{
			Tuas_Algorithm(30, Tuas_Pot);
			if (Jar_Bola > 90 && Flag_posisi_receive == 0 && c_p <=15 )
			{
				if (c_p < 8 )fwd_pwm_3roda_PID(0,0,0);
				else receive_ball(Sud_Bola,kanan_lapangan);
			}
			else if (Jar_Bola == 0 && Flag_posisi_receive == 0) {
				Rotate_To_Sudut(90);
				if (abs(Rotate_sdt.error) < 10 ) fwd_pwm_3roda_PID(0,0,0);
				else fwd_pwm_3roda_PID(PWM_Rotate,PWM_Rotate,PWM_Rotate);
			}
			else if ( ((Jar_Bola <= 90 && Jar_Bola > 0) || c_p > 15) && Flag_posisi_receive == 0 )
			{
				Rotate_To_Ball();
				T_ORION.Keadaan_Robot = 3;
				if (Jar_Bola < (SP_Kamera + 15) )Flag_posisi_receive = 1;
			}
			else if (Jar_Bola > 0 && Flag_posisi_receive == 1){	Follow_Ball(Sud_Bola,Jar_Bola,SP_Kamera);	}
		}
		else if (Prox != 1) {	Flag_Posisi = 4;	c_g = 0;	c_p = 0;	}
	}
	else if (Flag_Posisi == 4)
	{
		Tuas_Algorithm(30, Tuas_Pot);
		if (Prox != 1)
		{
			if (X_Oddo_cm[5] > 200  && X_Oddo_cm[5] <= 250)	{	Flag_Gerak = 0; Rotate_Kick(245,600,SHOOT);	}
			else if (X_Oddo_cm[5] > 350  && X_Oddo_cm[5] <  400) {	Flag_Gerak = 0; Rotate_Kick(305,600,SHOOT);	}
			else { Flag_Gerak = 1;	Tujuan_KoorY = 150;	Tujuan_KoorX = 225;	arahY = Y_Oddo_cm[5];	arahX = 600; }
		}
		else if (Prox == 1 && c_p > 4 && f_oper == 1)
		{
			c_g = 0; c_p = 0; Flag_Posisi = 5; f_oper = 0;
		}
		else if (Prox == 1 && FlagSiapTendang == 0) { Flag_Gerak = 0; Follow_Ball(Sud_Bola, Jar_Bola, SP_Kamera); }
	}
}

void Strategi_ORION_ASSIST(int Sud_Bola, int Jar_Bola)
{
	Tuas_Algorithm(80, Tuas_Pot);
	if (Flag_Posisi == 0)
	{
		Flag_Gerak = 1; f_oper = 0;
		if (X_Oddo_cm[5] <= 450) hindar_dummy = 1;
		if (hindar_dummy == 0)
		{
			if (dummy3 == 4)
			{
				Tujuan_KoorY = 120;		Tujuan_KoorX = 435;
				arahY = Y_Oddo_cm[5]-100;	arahX = X_Oddo_cm[5]-84;
			}
			else if (dummy3 == 5)
			{
				Tujuan_KoorY = 160;		Tujuan_KoorX = 425;
				arahY = Y_Oddo_cm[5]-100;	arahX = X_Oddo_cm[5]-84;
			}
			else hindar_dummy = 1;
		}
		else if (hindar_dummy != 0)
		{
			Tujuan_KoorY = 120;		Tujuan_KoorX = 435;		arahY = Y_Oddo_cm[5]-100;	arahX = X_Oddo_cm[5]-84;
		}
		if ( (X_Oddo_cm[5] > (int)(Tujuan_KoorX-8)) && X_Oddo_cm[5] < (int)(Tujuan_KoorX+8) &&
				(Y_Oddo_cm[5] < (int)(Tujuan_KoorY+8) && Y_Oddo_cm[5] > (int)(Tujuan_KoorY-8)) && hindar_dummy == 1 )
			{ Flag_Posisi = 1; }
		if (hindar_dummy == 1 && T_HYDRA.Keadaan_Robot == 5) Flag_Posisi = 1;
	}
	else if (Flag_Posisi == 1)
	{
		Flag_Gerak = 0;
		if (Prox == 1)
		{
			c_g = 1;
			if (c_p <=2) fwd_pwm_3roda_PID(0,0,0);
			if (Jar_Bola > 50 && Flag_posisi_receive == 0 && c_p <= 8 && T_HYDRA.Keadaan_Robot == 1)receive_ball(Sud_Bola,diagonal_lapangan);
			if (Jar_Bola == 0 && Flag_posisi_receive == 0)
			{
				Rotate_To_Sudut(220);
				if (abs(Rotate_sdt.error) < 10 ) fwd_pwm_3roda_PID(0,0,0);
				else fwd_pwm_3roda_PID(PWM_Rotate,PWM_Rotate,PWM_Rotate);
			}
			if ( ( ( (Jar_Bola <= 50 && Jar_Bola > 0) || c_p > 8 ) && Flag_posisi_receive == 0 ) || T_HYDRA.Keadaan_Robot == 2)
			{
				Rotate_To_Ball();
				T_ORION.Keadaan_Robot = 3;
				if (Jar_Bola <= SP_Kamera) Flag_posisi_receive = 1;
			}
			if (Jar_Bola > 0 && Flag_posisi_receive == 1) Follow_Ball(Sud_Bola, Jar_Bola, SP_Kamera);
		}
		else if (Prox != 1) {	Flag_Posisi = 2; c_g = 0; c_p = 0;	}
	}
	else if (Flag_Posisi == 2)
	{
		if (Prox != 1 && f_oper == 0)
		{
			T_ORION.Keadaan_Robot = 1;
			Rotate_Kick(T_HYDRA.Koor_X, T_HYDRA.Koor_Y , OPER);
		}
		else if (Prox == 1 && f_oper == 0) Follow_Ball(Sud_Bola, Jar_Bola, SP_Kamera);
		else if (Prox == 1 && f_oper == 1 && c_p >=5)
		{
			FlagSiapTendang = 0;	c_g = 0;	c_p = 0;	sedang_rotate = 0;
			Flag_Posisi = 3;
		}
	}
	else if (Flag_Posisi == 3)
	{
		Flag_Gerak = 1;
		Tujuan_KoorY = 50; Tujuan_KoorX = 300; arahY = 500; arahX = X_Oddo_cm[5];
		if ( Y_Oddo_cm[5] < (int)(70) && X_Oddo_cm[5] < (int)(350) )Flag_Posisi = 4;
	}
	else if (Flag_Posisi == 4)
	{
		Flag_Gerak = 0;
		fwd_pwm_3roda_PID(0,0,0);
	}
	if(Flag_Gerak == 1) Move_Koordinat_3roda(Y_Oddo_cm[5], X_Oddo_cm[5], Tujuan_KoorY, Tujuan_KoorX, arahY, arahX);
}

void Strategi_ORION2(int Sud_Bola, int Jar_Bola, int Data_Main_Assist)
{
	// THIS STRATEGY USED FOR CHANGE SHOOT PRIORITY EVERY GOAL
	if (Data_Main_Assist == 1) Strategi_ORION_MAIN(Sud_Bola, Jar_Bola);
	else if (Data_Main_Assist == 2) Strategi_ORION_ASSIST(Sud_Bola, Jar_Bola);
}

void Strategi_HYDRA_MAIN(int Sud_Bola, int Jar_Bola)
{
	if (Flag_Posisi == 0)
	{
		f_oper = 0; c_g = 0; c_p = 0; T_HYDRA.Keadaan_Robot = 1;
		Flag_Gerak = 1; kickoff_awal = 1;
		Tuas_Algorithm(70, Tuas_Pot);
		Tujuan_KoorY = 0;		Tujuan_KoorX = 100;		arahY = Y_Oddo_cm[5]+ 20; arahX = 600;
		if( Y_Oddo_cm[5] < 80 && Y_Oddo_cm[5] > -20) Flag_Posisi = 1;
		if (dummy1 != 1 ) Flag_Posisi = 1;
	}
	else if (Flag_Posisi == 1)
	{
		if (Prox == 1 && f_oper == 0)
		{
			Tuas_Algorithm(70, Tuas_Pot);
			if (Jar_Bola > SP_Kamera + 40 && kickoff_awal == 1)
			{
				Flag_Gerak = 1; c_g = 0; c_p = 0;
				if (dummy1 == 1 )
				{	Tujuan_KoorY = 5; Tujuan_KoorX = 230;	arahY = Y_Oddo_cm[5]+20; arahX = 600;	}
				else if (dummy1 != 1 )
				{	Tujuan_KoorY = 0; Tujuan_KoorX = 210;	arahY = Y_Oddo_cm[5]+20; arahX = 600;	}
			}
			if (Jar_Bola <= SP_Kamera + 40 && Jar_Bola > 0 && kickoff_awal == 1) kickoff_awal = 3;
			if ( (T_ORION.Keadaan_Robot == 3 && dummy1 != 1) && kickoff_awal == 1) kickoff_awal = 3;

			if (kickoff_awal == 3)
			{
				Flag_Gerak = 0;
				c_g = 1;
				if (c_p < 5)
				{
					T_HYDRA.Keadaan_Robot = 2;
					if (c_p < 2) fwd_pwm_3roda_PID(0,0,0);
					else Rotate_To_Ball();
				}
				else Follow_Ball(Sud_Bola, Jar_Bola, SP_Kamera);
			}
		}
		else if (Prox == 1 && f_oper == 1 && c_p > 2)
		{
			FlagSiapTendang = 0;	Flag_Posisi = 2; c_g = 0; c_p = 0; f_oper = 0;
		}
		else
		{
			T_HYDRA.Keadaan_Robot = 5;
			Rotate_Kick(T_ORION.Koor_X, T_ORION.Koor_Y , OPER);
		}
	}
	else if (Flag_Posisi == 2)
	{
		Flag_Gerak = 1; kickoff_awal = 1;
		Tuas_Algorithm(30, Tuas_Pot);
		Tujuan_KoorY = 170;			Tujuan_KoorX = 205;		arahY = Y_Oddo_cm[5];		arahX = 600;
		if(	Y_Oddo_cm[5] < 130 && Y_Oddo_cm[5]>90 && dummy1 == 1)Flag_Posisi = 3;
		if(	Y_Oddo_cm[5] < 130 && Y_Oddo_cm[5]>100 && dummy1 != 1)Flag_Posisi = 3;
	}
	else if (Flag_Posisi == 3)
	{
		Flag_Gerak = 0; c_g = 1;
		if (Prox == 1)
		{
			Tuas_Algorithm(30, Tuas_Pot);
			if (Jar_Bola > 90 && Flag_posisi_receive == 0 && c_p <=15 )
			{
				if (c_p < 8 )fwd_pwm_3roda_PID(0,0,0);
				else receive_ball(Sud_Bola,kanan_lapangan);
			}
			else if (Jar_Bola == 0 && Flag_posisi_receive == 0) {
				Rotate_To_Sudut(90);
				if (abs(Rotate_sdt.error) < 10 ) fwd_pwm_3roda_PID(0,0,0);
				else fwd_pwm_3roda_PID(PWM_Rotate,PWM_Rotate,PWM_Rotate);
			}
			else if ( ((Jar_Bola <= 90 && Jar_Bola > 0) || c_p > 15) && Flag_posisi_receive == 0 )
			{
				Rotate_To_Ball();
				T_HYDRA.Keadaan_Robot = 3;
				if (Jar_Bola < (SP_Kamera + 15) )Flag_posisi_receive = 1;
			}
			else if (Jar_Bola > 0 && Flag_posisi_receive == 1){	Follow_Ball(Sud_Bola,Jar_Bola,SP_Kamera);	}
		}
		else if (Prox != 1) {	Flag_Posisi = 4;	c_g = 0;	c_p = 0;	}
	}
	else if (Flag_Posisi == 4)
	{
		Tuas_Algorithm(30, Tuas_Pot);
		if (Prox != 1)
		{
			if (X_Oddo_cm[5] > 200  && X_Oddo_cm[5] <= 250)	{	Flag_Gerak = 0; Rotate_Kick(245,600,SHOOT);	}
			else if (X_Oddo_cm[5] > 350  && X_Oddo_cm[5] <  400) {	Flag_Gerak = 0; Rotate_Kick(305,600,SHOOT);	}
			else { Flag_Gerak = 1;	Tujuan_KoorY = 150;	Tujuan_KoorX = 225;	arahY = Y_Oddo_cm[5];	arahX = 600; }
		}
		else if (Prox == 1 && c_p > 4 && f_oper == 1)
		{
			c_g = 0; c_p = 0; Flag_Posisi = 5; f_oper = 0;
		}
		else if (Prox == 1 && FlagSiapTendang == 0) { Flag_Gerak = 0; Follow_Ball(Sud_Bola, Jar_Bola, SP_Kamera); }
	}
}

void Strategi_HYDRA_ASSIST(int Sud_Bola, int Jar_Bola)
{
	Tuas_Algorithm(80, Tuas_Pot);
	if (Flag_Posisi == 0)
	{
		Flag_Gerak = 1; f_oper = 0;
		if (X_Oddo_cm[5] <= 450) hindar_dummy = 1;
		if (hindar_dummy == 0)
		{
			if (dummy3 == 4)
			{
				Tujuan_KoorY = 120;		Tujuan_KoorX = 435;
				arahY = Y_Oddo_cm[5]-100;	arahX = X_Oddo_cm[5]-84;
			}
			else if (dummy3 == 5)
			{
				Tujuan_KoorY = 160;		Tujuan_KoorX = 425;
				arahY = Y_Oddo_cm[5]-100;	arahX = X_Oddo_cm[5]-84;
			}
			else hindar_dummy = 1;
		}
		else if (hindar_dummy != 0)
		{
			Tujuan_KoorY = 120;		Tujuan_KoorX = 435;		arahY = Y_Oddo_cm[5]-100;	arahX = X_Oddo_cm[5]-84;
		}
		if ( (X_Oddo_cm[5] > (int)(Tujuan_KoorX-8)) && X_Oddo_cm[5] < (int)(Tujuan_KoorX+8) &&
				(Y_Oddo_cm[5] < (int)(Tujuan_KoorY+8) && Y_Oddo_cm[5] > (int)(Tujuan_KoorY-8)) && hindar_dummy == 1 )
			{ Flag_Posisi = 1; }
		if (hindar_dummy == 1 && T_ORION.Keadaan_Robot == 5) Flag_Posisi = 1;
	}
	else if (Flag_Posisi == 1)
	{
		Flag_Gerak = 0;
		if (Prox == 1)
		{
			c_g = 1;
			if (c_p <=2) fwd_pwm_3roda_PID(0,0,0);
			if (Jar_Bola > 50 && Flag_posisi_receive == 0 && c_p <= 8 && T_ORION.Keadaan_Robot == 1)receive_ball(Sud_Bola,diagonal_lapangan);
			if (Jar_Bola == 0 && Flag_posisi_receive == 0)
			{
				Rotate_To_Sudut(220);
				if (abs(Rotate_sdt.error) < 10 ) fwd_pwm_3roda_PID(0,0,0);
				else fwd_pwm_3roda_PID(PWM_Rotate,PWM_Rotate,PWM_Rotate);
			}
			if ( ( ( (Jar_Bola <= 50 && Jar_Bola > 0) || c_p > 8 ) && Flag_posisi_receive == 0 ) || T_HYDRA.Keadaan_Robot == 2)
			{
				Rotate_To_Ball();
				T_HYDRA.Keadaan_Robot = 3;
				if (Jar_Bola <= SP_Kamera) Flag_posisi_receive = 1;
			}
			if (Jar_Bola > 0 && Flag_posisi_receive == 1) Follow_Ball(Sud_Bola, Jar_Bola, SP_Kamera);
		}
		else if (Prox != 1) {	Flag_Posisi = 2; c_g = 0; c_p = 0;	}
	}
	else if (Flag_Posisi == 2)
	{
		if (Prox != 1 && f_oper == 0)
		{
			T_HYDRA.Keadaan_Robot = 1;
			Rotate_Kick(T_ORION.Koor_X, T_ORION.Koor_Y , OPER);
		}
		else if (Prox == 1 && f_oper == 0) Follow_Ball(Sud_Bola, Jar_Bola, SP_Kamera);
		else if (Prox == 1 && f_oper == 1 && c_p >=5)
		{
			FlagSiapTendang = 0;	c_g = 0;	c_p = 0;	sedang_rotate = 0;
			Flag_Posisi = 3;
		}
	}
	else if (Flag_Posisi == 3)
	{
		Flag_Gerak = 1;
		Tujuan_KoorY = 50; Tujuan_KoorX = 300; arahY = 500; arahX = X_Oddo_cm[5];
		if ( Y_Oddo_cm[5] < (int)(70) && X_Oddo_cm[5] < (int)(350) )Flag_Posisi = 4;
	}
	else if (Flag_Posisi == 4)
	{
		Flag_Gerak = 0;
		fwd_pwm_3roda_PID(0,0,0);
	}
	if(Flag_Gerak == 1) Move_Koordinat_3roda(Y_Oddo_cm[5], X_Oddo_cm[5], Tujuan_KoorY, Tujuan_KoorX, arahY, arahX);
}

void Strategi_HYDRA2(int Sud_Bola, int Jar_Bola, int Data_Main_Assist)
{
	// THIS STRATEGY USED FOR CHANGE SHOOT PRIORITY EVERY GOAL
	if (Data_Main_Assist == 1) Strategi_HYDRA_MAIN(Sud_Bola, Jar_Bola);
	else if (Data_Main_Assist == 2) Strategi_HYDRA_ASSIST(Sud_Bola, Jar_Bola);
}

void Reset_Strategi2_ORION(int Data_Main_Assist)
{
	if (Data_Main_Assist == 1)
	{
		if (dummy1 == 1)
		{
			if (Flag_untuk_reset == 0)
			{
				c_g = 0; c_p = 0;
				Tujuan_KoorY = 250; Tujuan_KoorX = 120;	arahY = 200;arahX = 600;
			}
			if (Flag_untuk_reset == 1){	Tujuan_KoorY = 200; Tujuan_KoorX = 30;	arahY = 200;arahX = 600;}
			if(X_Oddo_cm[5] < 170 && Y_Oddo_cm[5] > 180 && Flag_untuk_reset == 0)Flag_untuk_reset = 1;
			if (X_Oddo_cm[5] < 40 && Y_Oddo_cm[5] > 190)	{	fwd_pwm_3roda_PID(0,0,0);	}
			else Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Tujuan_KoorY,Tujuan_KoorX,arahY,arahX);
		}
		else if (dummy1 == 2)
		{
			if (Flag_untuk_reset == 0){ c_g = 0; c_p = 0;
				Tujuan_KoorY = 100; Tujuan_KoorX = 80;	arahY = 200;arahX = 600;}
			if (Flag_untuk_reset == 1){	Tujuan_KoorY = 220; Tujuan_KoorX = 30;	arahY = 200;arahX = 600;}
			if(X_Oddo_cm[5] < 180 && Y_Oddo_cm[5] < 160 && Flag_untuk_reset == 0)Flag_untuk_reset = 1;
			if (X_Oddo_cm[5] < 40 && Y_Oddo_cm[5] > 190)	{	fwd_pwm_3roda_PID(0,0,0);	}
			else Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Tujuan_KoorY,Tujuan_KoorX,arahY,arahX);
		}
		else {
			if (X_Oddo_cm[5] < 40 && Y_Oddo_cm[5] > 190)	{	fwd_pwm_3roda_PID(0,0,0);	}
			else { Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],200,30,200,600);	}
		}
	}
	else if (Data_Main_Assist == 2)
	{
		if (dummy3 == 5)
		{
			if (Flag_untuk_reset == 0){ c_g = 0; c_p = 0;
				Tujuan_KoorY = 90;	Tujuan_KoorX = 440;	arahY = 200; arahX = 600;}
			if (Flag_untuk_reset == 1){	Tujuan_KoorY = 190; Tujuan_KoorX = 570;	arahY = 200;arahX = 0;}

			if (X_Oddo_cm[5] > 400  && Y_Oddo_cm[5] < 150 && Flag_untuk_reset == 0) Flag_untuk_reset = 1;
			if (X_Oddo_cm[5] > 560 && Y_Oddo_cm[5] > 190)	{	fwd_pwm_3roda_PID(0,0,0);	}
			else Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Tujuan_KoorY,Tujuan_KoorX,arahY,arahX);
		}
		else if (dummy3 == 4 && dummy2 == 7)
		{
			if (Flag_untuk_reset == 0) { c_g = 0; c_p = 0;
				Tujuan_KoorY = 140;		Tujuan_KoorX = 425;		arahY = 100;	arahX = 0;	}
			else if (Flag_untuk_reset == 1) { Tujuan_KoorY = 260; Tujuan_KoorX = 440; arahY = 200; arahX = 0;}
			else if (Flag_untuk_reset == 2) { Tujuan_KoorY = 200; Tujuan_KoorX = 570; arahY = 200; arahX = 0;}

			if (X_Oddo_cm[5] > 400  && Y_Oddo_cm[5] < 170 && Flag_untuk_reset == 0) Flag_untuk_reset = 1;
			if (X_Oddo_cm[5] > 400  && Y_Oddo_cm[5] > 180&& Flag_untuk_reset == 1) Flag_untuk_reset = 2;
			if (X_Oddo_cm[5] > 560 && Y_Oddo_cm[5] > 190)	{	fwd_pwm_3roda_PID(0,0,0);	}
			else Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Tujuan_KoorY,Tujuan_KoorX,arahY,arahX);
		}
		else {
			if (X_Oddo_cm[5] > 560 && Y_Oddo_cm[5] > 190)	{	fwd_pwm_3roda_PID(0,0,0);	}
			else {	c_g = 0;	c_p = 0;	Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],200,570,200,0); }
		}
	}
}

void Reset_Strategi2_HYDRA(int Data_Main_Assist)
{
	if (Data_Main_Assist == 1)
	{
		if (dummy3 == 5)
		{
			if (Flag_untuk_reset == 0){ c_g = 0; c_p = 0;
				Tujuan_KoorY = 90;	Tujuan_KoorX = 440;	arahY = 200; arahX = 600;}
			if (Flag_untuk_reset == 1){	Tujuan_KoorY = 190; Tujuan_KoorX = 570;	arahY = 200;arahX = 0;}

			if (X_Oddo_cm[5] > 400  && Y_Oddo_cm[5] < 150 && Flag_untuk_reset == 0) Flag_untuk_reset = 1;
			if (X_Oddo_cm[5] > 560 && Y_Oddo_cm[5] > 190)	{	fwd_pwm_3roda_PID(0,0,0);	}
			else Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Tujuan_KoorY,Tujuan_KoorX,arahY,arahX);
		}
		else if (dummy3 == 4 && dummy2 == 7)
		{
			if (Flag_untuk_reset == 0) { c_g = 0; c_p = 0;
				Tujuan_KoorY = 140;		Tujuan_KoorX = 425;		arahY = 100;	arahX = 0;	}
			else if (Flag_untuk_reset == 1) { Tujuan_KoorY = 260; Tujuan_KoorX = 440; arahY = 200; arahX = 0;}
			else if (Flag_untuk_reset == 2) { Tujuan_KoorY = 200; Tujuan_KoorX = 570; arahY = 200; arahX = 0;}

			if (X_Oddo_cm[5] > 400  && Y_Oddo_cm[5] < 170 && Flag_untuk_reset == 0) Flag_untuk_reset = 1;
			if (X_Oddo_cm[5] > 400  && Y_Oddo_cm[5] > 180&& Flag_untuk_reset == 1) Flag_untuk_reset = 2;
			if (X_Oddo_cm[5] > 560 && Y_Oddo_cm[5] > 190)	{	fwd_pwm_3roda_PID(0,0,0);	}
			else Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Tujuan_KoorY,Tujuan_KoorX,arahY,arahX);
		}
		else {
			if (X_Oddo_cm[5] > 560 && Y_Oddo_cm[5] > 190)	{	fwd_pwm_3roda_PID(0,0,0);	}
			else {	c_g = 0;	c_p = 0;	Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],200,570,200,0); }
		}
	}
	if (Data_Main_Assist == 2)
	{
		if (dummy1 == 1)
		{
			if (Flag_untuk_reset == 0)
			{
				c_g = 0; c_p = 0;
				Tujuan_KoorY = 250; Tujuan_KoorX = 120;	arahY = 200;arahX = 600;
			}
			if (Flag_untuk_reset == 1){	Tujuan_KoorY = 200; Tujuan_KoorX = 30;	arahY = 200;arahX = 600;}
			if(X_Oddo_cm[5] < 170 && Y_Oddo_cm[5] > 180 && Flag_untuk_reset == 0)Flag_untuk_reset = 1;
			if (X_Oddo_cm[5] < 40 && Y_Oddo_cm[5] > 190)	{	fwd_pwm_3roda_PID(0,0,0);	}
			else Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Tujuan_KoorY,Tujuan_KoorX,arahY,arahX);
		}
		else if (dummy1 == 2)
		{
			if (Flag_untuk_reset == 0){ c_g = 0; c_p = 0;
				Tujuan_KoorY = 100; Tujuan_KoorX = 80;	arahY = 200;arahX = 600;}
			if (Flag_untuk_reset == 1){	Tujuan_KoorY = 220; Tujuan_KoorX = 30;	arahY = 200;arahX = 600;}
			if(X_Oddo_cm[5] < 180 && Y_Oddo_cm[5] < 160 && Flag_untuk_reset == 0)Flag_untuk_reset = 1;
			if (X_Oddo_cm[5] < 40 && Y_Oddo_cm[5] > 190)	{	fwd_pwm_3roda_PID(0,0,0);	}
			else Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Tujuan_KoorY,Tujuan_KoorX,arahY,arahX);
		}
		else {
			if (X_Oddo_cm[5] < 40 && Y_Oddo_cm[5] > 190)	{	fwd_pwm_3roda_PID(0,0,0);	}
			else { Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],200,30,200,600);	}
		}
	}
}
void strategi_2(int Sud_Bola, int Jar_Bola, int Data_Main_Assist)
{
	if (Jar_Bola == 0)		LED(BLINK);
	else if (Jar_Bola > 0)	LED(ON);

	if (wifi2020 == 1)
	{
		f_stop = 0; f_berhenti = 0;
		if (R_DATA == 2)
		{
//			Solenoid_Manual_2021(0,0,0,0,0);
			Solenoid_Manual_4Cell_2021(0,0,0,0);
			F_Nilai_I  = 0;		  Flag_Posisi = 0;
			FlagSiapTendang = 0;	Flag_posisi_receive = 0;	c_g = 0; c_p = 0;
			Flag_reset_game = 0;	reset_imu = imu_real;	Flag_untuk_reset = 0;	hindar_dummy = 0;

			if (Data_Main_Assist == 1)
			{
				if (Program_Untuk == HYDRA){	X_Oddo_cm[5] = 570;	Y_Oddo_cm[5] = 200;	}
				if (Program_Untuk == ORION)	{X_Oddo_cm[5] = 30;	Y_Oddo_cm[5] = 200;	}
			}
			if (Data_Main_Assist == 2)
			{
				if (Program_Untuk == HYDRA)	{	X_Oddo_cm[5] = 30;	Y_Oddo_cm[5] = 200;	}
				if (Program_Untuk == ORION)	{	X_Oddo_cm[5] = 570;	Y_Oddo_cm[5] = 200;	}
			}
			R_DATA = 1;
		}
		else
		{
			if (Program_Untuk == ORION) 	Strategi_ORION2(Sud_Bola, Jar_Bola, Data_Main_Assist);
			else if (Program_Untuk == HYDRA)	Strategi_HYDRA2(Sud_Bola, Jar_Bola, Data_Main_Assist);
		}
	}
	else if (wifi2020 == 2)
	{
		Natural_gripper(DRIBBLE_OFF, 0, 0);
//		Solenoid_Manual_2021(0,0,0,0,0);
		Solenoid_Manual_4Cell_2021(0,0,0,0);
		if (Program_Untuk == ORION && Data_Main_Assist == 1) Tuas_Algorithm(45, Tuas_Pot);
		else if (Program_Untuk == ORION && Data_Main_Assist == 2) Tuas_Algorithm(80, Tuas_Pot);
		if (Program_Untuk == HYDRA && Data_Main_Assist == 1) Tuas_Algorithm(80, Tuas_Pot);
		else if (Program_Untuk == HYDRA && Data_Main_Assist == 2) Tuas_Algorithm(45, Tuas_Pot);
		if (f_berhenti == 0){c_g = 0; c_p = 0; f_berhenti = 1;}
		R_DATA = 2;
		fwd_pwm_3roda_PID(0,0,0);
	}
	else if (wifi2020 == 3)
	{
		Natural_gripper(DRIBBLE_OFF, 0, 0);
//		Solenoid_Manual_2021(0,0,0,0,0);
		Solenoid_Manual_4Cell_2021(0,0,0,0);
		R_DATA  = 2;	f_stop = 1; f_berhenti = 0;
		if (Program_Untuk == ORION && Data_Main_Assist == 1) Tuas_Algorithm(45, Tuas_Pot);
		else if (Program_Untuk == ORION && Data_Main_Assist == 2) Tuas_Algorithm(80, Tuas_Pot);
		if (Program_Untuk == HYDRA && Data_Main_Assist == 1) Tuas_Algorithm(80, Tuas_Pot);
		else if (Program_Untuk == HYDRA && Data_Main_Assist == 2) Tuas_Algorithm(45, Tuas_Pot);

		if (c_stop < 2) fwd_pwm_3roda_PID(0,0,0);
		else
		{
			if (Program_Untuk == ORION)
			{
				T_ORION.Keadaan_Robot = 1; kickoff_awal = 1;
				Reset_Strategi2_ORION(Data_Main_Assist);
			}
			else if (Program_Untuk == HYDRA)
			{
				T_HYDRA.Keadaan_Robot = 1; kickoff_awal = 1;
				Reset_Strategi2_HYDRA(Data_Main_Assist);
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------//

//------------------------------------------------- ONLINE RULE 2021  -----------------------------------------------//
/**
 * @brief	MATCH ALGORITHM used for ORION to start the kickoff and pass the ball to HYDRA
 * @retval	None
 */
void KICKOFF_KANAN_ORION(int Sud_Bola, int Jar_Bola)
{
	if (Flag_Posisi == 0)
	{
		Tuas_Algorithm(70, Tuas_Pot);
		f_oper = 0; c_g = 0; c_p = 0; T_ORION.Keadaan_Robot = 1; // keadaan awal robot
		Flag_Gerak = 1; kickoff_awal = 1;
		Tujuan_KoorY = 0;		Tujuan_KoorX = 100;		arahY = Y_Oddo_cm[5]+ 20; arahX = 600;
		if( Y_Oddo_cm[5] < 80 && Y_Oddo_cm[5] > -20) Flag_Posisi = 1;
		if (dummy1 != 1 ) Flag_Posisi = 1;
	}
	else if (Flag_Posisi == 1)
	{
		if (Prox == 1 && f_oper == 0)
		{
			Tuas_Algorithm(70, Tuas_Pot);
			if ((Jar_Bola > SP_Kamera + 40) && kickoff_awal == 1)
			{
				Flag_Gerak =1; c_g = 0; c_p = 0;
				if (dummy1 == 1)
				{ Tujuan_KoorY = 5; Tujuan_KoorX = 230; arahY = Y_Oddo_cm[5]+20; arahX = 600; }
				else if (dummy1 != 1 )
				{	Tujuan_KoorY = 0; Tujuan_KoorX = 210;	arahY = Y_Oddo_cm[5]+20; arahX = 600;	}
			}
			if ((Jar_Bola <= SP_Kamera + 40) && Jar_Bola > 0 && kickoff_awal == 1) kickoff_awal = 3;
			if ( (T_HYDRA.Keadaan_Robot == 3 && dummy1 != 1) && kickoff_awal == 1) kickoff_awal = 3;

			if (kickoff_awal == 3)
			{
				Flag_Gerak = 0; c_g = 1;
				if (c_p < 5)
				{
					T_ORION.Keadaan_Robot = 2; // keadaan robot sedang rotasi untuk mencari bola
					if (c_p < 2) fwd_pwm_3roda_PID(0,0,0); //berhenti sejenak
					else Rotate_To_Ball();
				}
				else Follow_Ball(Sud_Bola, Jar_Bola, SP_Kamera);
			}
		}
		else if (Prox == 1 && f_oper == 1 && c_p > 2)
		{ Flag_Posisi = 2; FlagSiapTendang = 0; c_g = 0; c_p = 0; f_oper = 0; }
		else 
		{
			T_ORION.Keadaan_Robot = 5;	// keadaan robot sedang rotasi untuk menendang
			Rotate_Kick(T_HYDRA.Koor_X, T_HYDRA.Koor_Y, OPER);
		}
	}
	else if (Flag_Posisi == 2)
	{
		Flag_Gerak = 1; kickoff_awal = 1;
		Tuas_Algorithm(70, Tuas_Pot);
		Tujuan_KoorY = 170;			Tujuan_KoorX = 205;		arahY = Y_Oddo_cm[5];		arahX = 600;
		if(	Y_Oddo_cm[5] < 130 && Y_Oddo_cm[5]>90 && dummy1 == 1)Flag_Posisi = 3;
		if(	Y_Oddo_cm[5] < 130 && Y_Oddo_cm[5]>100 && dummy1 != 1)Flag_Posisi = 3;
	}
	else if (Flag_Posisi == 3)
	{
		Flag_Gerak = 0; c_g = 1;
		if (Prox == 1)
		{
			Tuas_Algorithm(70, Tuas_Pot);
			if (Jar_Bola > 90 && Flag_posisi_receive == 0 && c_p <=10 )
			{
				if (c_p < 6 )fwd_pwm_3roda_PID(0,0,0);
				else receive_ball(Sud_Bola,kanan_lapangan);
			}
			else if (Jar_Bola == 0 && Flag_posisi_receive == 0) {
				Rotate_To_Sudut(90);
				if (abs(Rotate_sdt.error) < 10 ) fwd_pwm_3roda_PID(0,0,0);
				else fwd_pwm_3roda_PID(PWM_Rotate,PWM_Rotate,PWM_Rotate);
			}
			else if ( ((Jar_Bola <= 90 && Jar_Bola > 0) || c_p > 10) && Flag_posisi_receive == 0 )
			{
				Rotate_To_Ball();
				T_ORION.Keadaan_Robot = 3; // keadaan ketika robot siap menerima bola
				if (Jar_Bola < (SP_Kamera + 15) )Flag_posisi_receive = 1;
			}
			else if (Jar_Bola > 0 && Flag_posisi_receive == 1){	Follow_Ball(Sud_Bola,Jar_Bola,SP_Kamera);	}
		}
		else if (Prox != 1) {	Flag_Posisi = 4;	c_g = 0;	c_p = 0;	}
	}
	else if (Flag_Posisi == 4)
	{
		if (Prox != 1 && f_oper == 0)
		{
			T_ORION.Keadaan_Robot = 5;
			Rotate_Kick(T_HYDRA.Koor_X, T_HYDRA.Koor_Y , OPER);
		}
		else if (Prox == 1 && f_oper == 0) Follow_Ball(Sud_Bola, Jar_Bola, SP_Kamera);
		else if (Prox == 1 && f_oper == 1 && c_p >=5)
		{
			FlagSiapTendang = 0;	c_g = 0;	c_p = 0;	sedang_rotate = 0;
			Flag_Posisi = 5;
		}
	}
	else if (Flag_Posisi == 5)
	{
		Flag_Gerak = 0;
		if (dummy1 == 1)
		{
			if (Flag_untuk_reset == 0){	Tujuan_KoorY = 270; Tujuan_KoorX = 140;	arahY = Y_Oddo_cm[5];arahX = 600;}
			if (Flag_untuk_reset == 1){	Tujuan_KoorY = 190; Tujuan_KoorX = 30;	arahY = Y_Oddo_cm[5];arahX = 600;}
			if (X_Oddo_cm[5] < 200 && Y_Oddo_cm[5] > 120 && Flag_untuk_reset == 0)Flag_untuk_reset = 1;

			if (X_Oddo_cm[5] < 55 && Y_Oddo_cm[5] > 190){	fwd_pwm_3roda_PID(0,0,0);	}
			else Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],Tujuan_KoorY,Tujuan_KoorX,arahY,arahX);
		}
		else if (dummy1 == 2)
		{
			if (Flag_untuk_reset == 0){	Tujuan_KoorY = 100; Tujuan_KoorX = 80;	arahY = Y_Oddo_cm[5];arahX = 600;}
			if (Flag_untuk_reset == 1){	Tujuan_KoorY = 220; Tujuan_KoorX = 30;	arahY = Y_Oddo_cm[5];arahX = 600;}
			if (X_Oddo_cm[5] < 180 && Y_Oddo_cm[5] < 160 && Flag_untuk_reset == 0)Flag_untuk_reset = 1;

			if (X_Oddo_cm[5] < 40 && Y_Oddo_cm[5] > 190){	fwd_pwm_3roda_PID(0,0,0);	}
			 
		}
		else
		{
			if (X_Oddo_cm[5] < 40 && Y_Oddo_cm[5] > 190) {	fwd_pwm_3roda_PID(0,0,0);	}
			else Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],200,30,Y_Oddo_cm[5],600);
		}
	}
	if (Flag_Gerak == 1) Move_Koordinat_3roda(Y_Oddo_cm[5], X_Oddo_cm[5], Tujuan_KoorY, Tujuan_KoorX, arahY, arahX);
}

/**
 * @brief	MATCH ALGORITHM used for HYDRA to receive ball from ORION
 * @retval	None
 */
void KICKOFF_KANAN_HYDRA(int Sud_Bola, int Jar_Bola)
{
	Tuas_Algorithm(80, Tuas_Pot);
	if (Flag_Posisi == 0)
	{
		Flag_Gerak = 1; f_oper = 0;
		if (X_Oddo_cm[5] <= 450) hindar_dummy = 1;
		if (hindar_dummy == 0)
		{
			if (dummy3 == 4)
			{
				Tujuan_KoorY = 160;		Tujuan_KoorX = 435;
				arahY = Y_Oddo_cm[5]-100;	arahX = X_Oddo_cm[5]-84;
			}
			else if (dummy3 == 5)
			{
				Tujuan_KoorY = 120;		Tujuan_KoorX = 425;
				arahY = Y_Oddo_cm[5]-100;	arahX = X_Oddo_cm[5]-84;
			}
			else hindar_dummy = 1;
		}
		else if (hindar_dummy != 0)
		{
			Tujuan_KoorY = 120;		Tujuan_KoorX = 435;		arahY = Y_Oddo_cm[5]-100;	arahX = X_Oddo_cm[5]-84;
		}
		if ( (X_Oddo_cm[5] > (int)(Tujuan_KoorX-8)) && X_Oddo_cm[5] < (int)(Tujuan_KoorX+8) &&
				(Y_Oddo_cm[5] < (int)(Tujuan_KoorY+8) && Y_Oddo_cm[5] > (int)(Tujuan_KoorY-8)) && hindar_dummy == 1 )
			{ Flag_Posisi = 1; }
		if (hindar_dummy == 1 && T_ORION.Keadaan_Robot == 5) Flag_Posisi = 1;	// paksa ke step berikutnya
	}
	else if (Flag_Posisi == 1)
	{
		Flag_Gerak = 0;
		if (Prox == 1)
		{
			c_g = 1;
			if (c_p <= 2) fwd_pwm_3roda_PID(0,0,0);
			if (Jar_Bola > 50 && Flag_posisi_receive == 0  && (c_p > 2 && c_p <=8) && T_ORION.Keadaan_Robot == 1) receive_ball(sudut_bola, diagonal_lapangan);
			if (Jar_Bola == 0 && Flag_posisi_receive == 0)
			{
				Rotate_To_Sudut(220);
				if (abs(Rotate_sdt.error) < 10) fwd_pwm_3roda_PID(0,0,0);
				else fwd_pwm_3roda_PID(PWM_Rotate,PWM_Rotate,PWM_Rotate);
			}
			if ( ( ( (Jar_Bola <= 50 && Jar_Bola > 0) || c_p > 8 ) && Flag_posisi_receive == 0 ) || T_ORION.Keadaan_Robot == 2)
			{
				//c_p bisa dipercepat biar orion lebih cepet ke state follow ball
				Rotate_To_Ball();
				T_HYDRA.Keadaan_Robot = 3; // keadaan ketika robot siap menerima bola
				if (Jar_Bola <= SP_Kamera) Flag_posisi_receive = 1;
			}
			if (Jar_Bola > 0 && Flag_posisi_receive == 1) Follow_Bola(Sud_Bola, Jar_Bola, SP_Kamera);
		}
		else if (Prox != 1) { Flag_Posisi = 2; c_g = 0; c_p = 0; Flag_posisi_receive = 0; }
	}
	else if (Flag_Posisi == 2)
	{
		if (Prox != 1 && f_oper == 0)
		{
			T_HYDRA.Keadaan_Robot = 5; // keadaan robot sedang rotasi untuk menendang
			Rotate_Kick(T_ORION.Koor_X, T_ORION.Koor_Y, OPER);
		}
		else if (Prox == 1 && f_oper == 0) Follow_Bola(Sud_Bola, Jar_Bola, SP_Kamera);
		else if (Prox == 1 && f_oper == 1 && c_p > 2)
		{
			FlagSiapTendang = 0;	c_g = 0;	c_p = 0;	sedang_rotate = 0;
			Flag_Posisi = 3; f_oper = 0;
		}
	}
	else if (Flag_Posisi == 3)
	{
		Flag_Gerak = 1; kickoff_awal = 1;
		Tuas_Algorithm(40, Tuas_Pot);
		Tujuan_KoorY = 250;			Tujuan_KoorX = 435;		arahY = Y_Oddo_cm[5]-100;	arahX = X_Oddo_cm[5]-84;
		if(	Y_Oddo_cm[5] < 230 && Y_Oddo_cm[5]>190 && dummy3 == 4) Flag_Posisi = 4;
		if(	Y_Oddo_cm[5] < 230 && Y_Oddo_cm[5]>200 && dummy3 != 4) Flag_Posisi = 4;
	}
	else if (Flag_Posisi ==  4)
	{
		Flag_Gerak = 0; c_g = 1;
		if (Prox == 1)
		{
			Tuas_Algorithm(40, Tuas_Pot);
			if (Jar_Bola > 90 && Flag_posisi_receive == 0 && c_p <=10 )
			{
				if (c_p < 6 )fwd_pwm_3roda_PID(0,0,0);
				else receive_ball(Sud_Bola,diagonal_lapangan);
			}
			else if (Jar_Bola == 0 && Flag_posisi_receive == 0) {
				Rotate_To_Sudut(-135);
				if (abs(Rotate_sdt.error) < 10 ) fwd_pwm_3roda_PID(0,0,0);
				else fwd_pwm_3roda_PID(PWM_Rotate,PWM_Rotate,PWM_Rotate);
			}
			else if ( ((Jar_Bola <= 90 && Jar_Bola > 0) || c_p > 10) && Flag_posisi_receive == 0 )
			{
				Rotate_To_Ball();
				T_HYDRA.Keadaan_Robot = 3;	// keadaan ketika robot siap menerima bola
				if (Jar_Bola < (SP_Kamera + 15) )Flag_posisi_receive = 1;
			}
			else if (Jar_Bola > 0 && Flag_posisi_receive == 1){	Follow_Ball(Sud_Bola,Jar_Bola,SP_Kamera);	}
		}
		else if (Prox != 1) {	Flag_Posisi = 5;	c_g = 0;	c_p = 0;	Flag_posisi_receive = 0;}
	}
	else if (Flag_Posisi == 5)
	{
		Tuas_Algorithm(40, Tuas_Pot);
		if (Prox != 1)
		{
			if (X_Oddo_cm[5] > 400  && X_Oddo_cm[5] <= 450)	{	Flag_Gerak = 0; Rotate_Kick(400,600,SHOOT);	}
			// else if (X_Oddo_cm[5] > 350  && X_Oddo_cm[5] <  400) {	Flag_Gerak = 0; Rotate_Kick(305,600,SHOOT);	}
			else { Flag_Gerak = 1;	Tujuan_KoorY = 200;	Tujuan_KoorX = 435;	arahY = 600;	arahX = X_Oddo_cm[5]; }
		}
		else if (Prox == 1 && c_p > 4 && f_oper == 1)
		{
			c_g = 0; c_p = 0; Flag_Posisi = 6; f_oper = 0;
		}
		else if (Prox == 1 && FlagSiapTendang == 0) { Flag_Gerak = 0; Follow_Ball(Sud_Bola, Jar_Bola, SP_Kamera); }
	}
	else if (Flag_Posisi == 6)
	{
		Flag_Gerak = 0;
		fwd_pwm_3roda_PID(0,0,0);
	}
	if(Flag_Gerak == 1) Move_Koordinat_3roda(Y_Oddo_cm[5], X_Oddo_cm[5], Tujuan_KoorY, Tujuan_KoorX, arahY, arahX);
}

/**
 * @brief	MATCH ALGORITHM used for HYDRA to start the kickoff and pass the ball to ORION
 * @retval	None
 */
void KICKOFF_KIRI_HYDRA(int Sud_Bola, int Jar_Bola)
{
	if (Flag_Posisi == 0)
	{
		Tuas_Algorithm(75, Tuas_Pot);
		f_oper = 0; c_g = 0; c_p = 0; T_HYDRA.Keadaan_Robot = 1; // keadaan awal robot
		Flag_Gerak = 1; kickoff_awal = 1;
		Tujuan_KoorY = 0;		Tujuan_KoorX = 500;		arahY = Y_Oddo_cm[5]+ 20; arahX = 0;
		if( Y_Oddo_cm[5] < 80 && Y_Oddo_cm[5] > -20) Flag_Posisi = 1;
		if (dummy3 != 4 ) Flag_Posisi = 1;
	}
	else if (Flag_Posisi == 1)
	{
		if (Prox == 1 && f_oper == 0)
		{
			Tuas_Algorithm(75, Tuas_Pot);
			if ((Jar_Bola > SP_Kamera + 40) && kickoff_awal == 1)
			{
				Flag_Gerak =1; c_g = 0; c_p = 0;
				if (dummy3 == 4)
				{ Tujuan_KoorY = 5; Tujuan_KoorX = 370; arahY = Y_Oddo_cm[5]+20; arahX = 0; }
				else if (dummy3 != 3 )
				{	Tujuan_KoorY = 0; Tujuan_KoorX = 390;	arahY = Y_Oddo_cm[5]+20; arahX = 0;	}
			}
			if ((Jar_Bola <= SP_Kamera + 40) && Jar_Bola > 0 && kickoff_awal == 1) kickoff_awal = 3;
			if ( (T_ORION.Keadaan_Robot == 3 && dummy3 != 4) && kickoff_awal == 1) kickoff_awal = 3;

			if (kickoff_awal == 3)
			{
				Flag_Gerak = 0; c_g = 1;
				if (c_p < 5)
				{
					T_HYDRA.Keadaan_Robot = 2; // keadaan robot sedang rotasi untuk mencari bola
					if (c_p < 2) fwd_pwm_3roda_PID(0,0,0); //berhenti sejenak
					else Rotate_To_Ball();
				}
				else Follow_Ball(Sud_Bola, Jar_Bola, SP_Kamera);
			}
		}
		else if (Prox == 1 && f_oper == 1 && c_p > 2)
		{ Flag_Posisi = 2; FlagSiapTendang = 0; c_g = 0; c_p = 0; f_oper = 0; }
		else 
		{
			T_HYDRA.Keadaan_Robot = 5;	// keadaan robot sedang rotasi untuk menendang
			Rotate_Kick(T_ORION.Koor_X, T_ORION.Koor_Y, OPER);
		}
	}
	else if (Flag_Posisi == 2)
	{
		Flag_Gerak = 1; kickoff_awal = 1;
		Tuas_Algorithm(75, Tuas_Pot);
		Tujuan_KoorY = 170;			Tujuan_KoorX = 405;		arahY = Y_Oddo_cm[5];		arahX = 0;
		if(	Y_Oddo_cm[5] < 130 && Y_Oddo_cm[5]>90 && dummy3 == 4)Flag_Posisi = 3;
		if(	Y_Oddo_cm[5] < 130 && Y_Oddo_cm[5]>100 && dummy3 != 4)Flag_Posisi = 3;
	}
	else if (Flag_Posisi == 3)
	{
		Flag_Gerak = 0; c_g = 1;
		if (Prox == 1)
		{
			Tuas_Algorithm(75, Tuas_Pot);
			if (Jar_Bola > 90 && Flag_posisi_receive == 0 && c_p <=10 )
			{
				if (c_p < 6 )fwd_pwm_3roda_PID(0,0,0);
				else receive_ball(Sud_Bola,kiri_lapangan);
			}
			else if (Jar_Bola == 0 && Flag_posisi_receive == 0) {
				Rotate_To_Sudut(-90);
				if (abs(Rotate_sdt.error) < 10 ) fwd_pwm_3roda_PID(0,0,0);
				else fwd_pwm_3roda_PID(PWM_Rotate,PWM_Rotate,PWM_Rotate);
			}
			else if ( ((Jar_Bola <= 90 && Jar_Bola > 0) || c_p > 10) && Flag_posisi_receive == 0 )
			{
				Rotate_To_Ball();
				T_HYDRA.Keadaan_Robot = 3; // keadaan ketika robot siap menerima bola
				if (Jar_Bola < (SP_Kamera + 15) )Flag_posisi_receive = 1;
			}
			else if (Jar_Bola > 0 && Flag_posisi_receive == 1){	Follow_Ball(Sud_Bola,Jar_Bola,SP_Kamera);	}
		}
		else if (Prox != 1) {	Flag_Posisi = 4;	c_g = 0;	c_p = 0;	}
	}
	else if (Flag_Posisi == 4)
	{
		if (Prox != 1 && f_oper == 0)
		{
			T_HYDRA.Keadaan_Robot = 5;
			Rotate_Kick(T_ORION.Koor_X, T_ORION.Koor_Y , OPER);
		}
		else if (Prox == 1 && f_oper == 0) Follow_Ball(Sud_Bola, Jar_Bola, SP_Kamera);
		else if (Prox == 1 && f_oper == 1 && c_p >=5)
		{
			FlagSiapTendang = 0;	c_g = 0;	c_p = 0;	sedang_rotate = 0;
			Flag_Posisi = 5;
		}
	}
	else if (Flag_Posisi == 5)
	{
		Flag_Gerak = 1; kickoff_awal = 1;
		Tuas_Algorithm(75, Tuas_Pot);
		Tujuan_KoorY = 300;			Tujuan_KoorX = 395;		arahY = 600;		arahX = X_Oddo_cm[5];
		if(	Y_Oddo_cm[5] < 310 && Y_Oddo_cm[5]>290) { Flag_Posisi = 6;	Flag_Gerak = 0;	 fwd_pwm_3roda_PID(0,0,0);}
	}

	if (Flag_Gerak == 1) Move_Koordinat_3roda(Y_Oddo_cm[5], X_Oddo_cm[5], Tujuan_KoorY, Tujuan_KoorX, arahY, arahX);
}

/**
 * @brief	MATCH ALGORITHM used for ORION to receive ball from HYDRA
 * @retval	None
 */
void KICKOFF_KIRI_ORION(int Sud_Bola, int Jar_Bola)
{
	Tuas_Algorithm(70, Tuas_Pot);
	if (Flag_Posisi == 0)
	{
		Flag_Gerak = 1; f_oper = 0;
		if (X_Oddo_cm[5] >= 150) hindar_dummy = 1;
		if (hindar_dummy == 0)
		{
			if (dummy1 == 1)
			{
				Tujuan_KoorY = 160;		Tujuan_KoorX = 165;
				arahY = Y_Oddo_cm[5]-100;	arahX = X_Oddo_cm[5]-84;
			}
			else if (dummy1 == 2)
			{
				Tujuan_KoorY = 120;		Tujuan_KoorX = 175;
				arahY = Y_Oddo_cm[5]-100;	arahX = X_Oddo_cm[5]-84;
			}
			else hindar_dummy = 1;
		}
		else if (hindar_dummy != 0)
		{
			Tujuan_KoorY = 120;		Tujuan_KoorX = 165;		arahY = Y_Oddo_cm[5]-100;	arahX = X_Oddo_cm[5]-84;
		}
		if ( (X_Oddo_cm[5] > (int)(Tujuan_KoorX-8)) && X_Oddo_cm[5] < (int)(Tujuan_KoorX+8) &&
				(Y_Oddo_cm[5] < (int)(Tujuan_KoorY+8) && Y_Oddo_cm[5] > (int)(Tujuan_KoorY-8)) && hindar_dummy == 1 )
			{ Flag_Posisi = 1; }
		if (hindar_dummy == 1 && T_HYDRA.Keadaan_Robot == 5) Flag_Posisi = 1;	// paksa ke step berikutnya
	}
	else if (Flag_Posisi == 1)
	{
		Flag_Gerak = 0;
		if (Prox == 1)
		{
			c_g = 1;
			if (c_p <= 2) fwd_pwm_3roda_PID(0,0,0);
			if (Jar_Bola > 50 && Flag_posisi_receive == 0  && (c_p > 2 && c_p <=8) && T_HYDRA.Keadaan_Robot == 1) receive_ball(sudut_bola, diagonal_lapangan);
			if (Jar_Bola == 0 && Flag_posisi_receive == 0)
			{
				Rotate_To_Sudut(140);
				if (abs(Rotate_sdt.error) < 10) fwd_pwm_3roda_PID(0,0,0);
				else fwd_pwm_3roda_PID(PWM_Rotate,PWM_Rotate,PWM_Rotate);
			}
			if ( ( ( (Jar_Bola <= 50 && Jar_Bola > 0) || c_p > 8 ) && Flag_posisi_receive == 0 ) || T_HYDRA.Keadaan_Robot == 2)
			{
				//c_p bisa dipercepat biar orion lebih cepet ke state follow ball
				Rotate_To_Ball();
				T_ORION.Keadaan_Robot = 3; // keadaan ketika robot siap menerima bola
				if (Jar_Bola <= SP_Kamera) Flag_posisi_receive = 1;
			}
			if (Jar_Bola > 0 && Flag_posisi_receive == 1) Follow_Bola(Sud_Bola, Jar_Bola, SP_Kamera);
		}
		else if (Prox != 1) { Flag_Posisi = 2; c_g = 0; c_p = 0; Flag_posisi_receive = 0; }
	}
	else if (Flag_Posisi == 2)
	{
		if (Prox != 1 && f_oper == 0)
		{
			T_ORION.Keadaan_Robot = 5; // keadaan robot sedang rotasi untuk menendang
			Rotate_Kick(T_HYDRA.Koor_X, T_HYDRA.Koor_Y, OPER);
		}
		else if (Prox == 1 && f_oper == 0) Follow_Bola(Sud_Bola, Jar_Bola, SP_Kamera);
		else if (Prox == 1 && f_oper == 1 && c_p > 2)
		{
			FlagSiapTendang = 0;	c_g = 0;	c_p = 0;	sedang_rotate = 0;
			Flag_Posisi = 3; f_oper = 0;
		}
	}
	else if (Flag_Posisi == 3)
	{
		Flag_Gerak = 1; kickoff_awal = 1;
		Tuas_Algorithm(40, Tuas_Pot);
		Tujuan_KoorY = 250;			Tujuan_KoorX = 165;		arahY = Y_Oddo_cm[5]-100;	arahX = X_Oddo_cm[5]-84;
		if(	Y_Oddo_cm[5] < 230 && Y_Oddo_cm[5]>190 && dummy1 == 4) Flag_Posisi = 4;
		if(	Y_Oddo_cm[5] < 230 && Y_Oddo_cm[5]>200 && dummy1 != 4) Flag_Posisi = 4;
	}
	else if (Flag_Posisi ==  4)
	{
		Flag_Gerak = 0; c_g = 1;
		if (Prox == 1)
		{
			Tuas_Algorithm(40, Tuas_Pot);
			if (Jar_Bola > 90 && Flag_posisi_receive == 0 && c_p <=10 )
			{
				if (c_p < 6 )fwd_pwm_3roda_PID(0,0,0);
				else receive_ball(Sud_Bola,diagonal_lapangan);
			}
			else if (Jar_Bola == 0 && Flag_posisi_receive == 0) {
				Rotate_To_Sudut(135);
				if (abs(Rotate_sdt.error) < 10 ) fwd_pwm_3roda_PID(0,0,0);
				else fwd_pwm_3roda_PID(PWM_Rotate,PWM_Rotate,PWM_Rotate);
			}
			else if ( ((Jar_Bola <= 90 && Jar_Bola > 0) || c_p > 10) && Flag_posisi_receive == 0 )
			{
				Rotate_To_Ball();
				T_ORION.Keadaan_Robot = 3;	// keadaan ketika robot siap menerima bola
				if (Jar_Bola < (SP_Kamera + 15) )Flag_posisi_receive = 1;
			}
			else if (Jar_Bola > 0 && Flag_posisi_receive == 1){	Follow_Ball(Sud_Bola,Jar_Bola,SP_Kamera);	}
		}
		else if (Prox != 1) {	Flag_Posisi = 5;	c_g = 0;	c_p = 0;	Flag_posisi_receive = 0;}
	}
	else if (Flag_Posisi == 5)
	{
		Tuas_Algorithm(40, Tuas_Pot);
		if (Prox != 1)
		{
			if (X_Oddo_cm[5] > 200  && X_Oddo_cm[5] <= 250)	{	Flag_Gerak = 0; Rotate_Kick(400,600,SHOOT);	}
			else if (X_Oddo_cm[5] > 350  && X_Oddo_cm[5] <  400) {	Flag_Gerak = 0; Rotate_Kick(305,600,SHOOT);	}
			else { Flag_Gerak = 1;	Tujuan_KoorY = 200;	Tujuan_KoorX = 225;	arahY = 600;	arahX = X_Oddo_cm[5]; }
		}
		else if (Prox == 1 && c_p > 4 && f_oper == 1)
		{
			c_g = 0; c_p = 0; Flag_Posisi = 6; f_oper = 0;
		}
		else if (Prox == 1 && FlagSiapTendang == 0) { Flag_Gerak = 0; Follow_Ball(Sud_Bola, Jar_Bola, SP_Kamera); }
	}
	else if (Flag_Posisi == 6)
	{
		Flag_Gerak = 0;
		fwd_pwm_3roda_PID(0,0,0);
	}
	if(Flag_Gerak == 1) Move_Koordinat_3roda(Y_Oddo_cm[5], X_Oddo_cm[5], Tujuan_KoorY, Tujuan_KoorX, arahY, arahX);
}

/**
 * @brief	MATCH ALGORITHM used for ORION to receive PASS from HYDRA at corner
 * @retval	None
 */
void CORNER_KANAN_ORION(int Sud_Bola, int Jar_Bola)
{
	if (Flag_Posisi == 0)
	{
		Tuas_Algorithm(70,Tuas_Pot);
		f_oper = 0; c_g = 0; c_p = 0; T_ORION.Keadaan_Robot = 1; // keadaan awal robot
		Flag_Gerak = 1;
		Tujuan_KoorY = 300;		Tujuan_KoorX = 50;		arahY = 600; arahX = 0;
		if( Y_Oddo_cm[5] < 280 && Y_Oddo_cm[5] > 250) { Flag_Posisi = 1; T_ORION.Keadaan_Robot = 4; }
		// if (dummy1 != 1 ) Flag_Posisi = 1;
	}
	else if (Flag_Posisi == 1)
	{
		Flag_Gerak = 0; c_g = 1;
		if (Prox == 1)
		{
			Tuas_Algorithm(70, Tuas_Pot);
			if (Jar_Bola > 90 && Flag_posisi_receive == 0 && c_p <=10 )
			{
				if (c_p < 6 )fwd_pwm_3roda_PID(0,0,0);
				else receive_ball(Sud_Bola,hdp_gawang);
			}
			else if (Jar_Bola == 0 && Flag_posisi_receive == 0) {
				Rotate_To_Sudut(0);
				if (abs(Rotate_sdt.error) < 10 ) fwd_pwm_3roda_PID(0,0,0);
				else fwd_pwm_3roda_PID(PWM_Rotate,PWM_Rotate,PWM_Rotate);
			}
			else if ( ((Jar_Bola <= 90 && Jar_Bola > 0) || c_p > 10) && Flag_posisi_receive == 0 )
			{
				Rotate_To_Ball();
				T_ORION.Keadaan_Robot = 3; // keadaan ketika robot siap menerima bola
				if (Jar_Bola < (SP_Kamera + 15) )Flag_posisi_receive = 1;
			}
			else if (Jar_Bola > 0 && Flag_posisi_receive == 1){	Follow_Ball(Sud_Bola,Jar_Bola,SP_Kamera);	}
		}
		else if (Prox != 1) {	Flag_Posisi = 2;	c_g = 0;	c_p = 0;	}
	}
	else if (Flag_Posisi == 2)
	{
		Flag_Gerak = 1;
		Tuas_Algorithm(70, Tuas_Pot);
		Tujuan_KoorY = 170;			Tujuan_KoorX = 205;		arahY = Y_Oddo_cm[5];		arahX = 600;
		if(	Y_Oddo_cm[5] < 130 && Y_Oddo_cm[5]>90 && dummy1 == 1)Flag_Posisi = 3;
		if(	Y_Oddo_cm[5] < 130 && Y_Oddo_cm[5]>100 && dummy1 != 1)Flag_Posisi = 3;
	}
}
//----------------------------------------------------------------------------------------------------------//

//------------------------------------------------- OFFLINE -----------------------------------------------//
void get_position(int koor_x, int koor_Y)
{
	if (Flag_pos == 0)
	{
		Current_X = koor_x;
		Current_Y = koor_Y;

		if (Current_X <= 150 && Current_Y > 300)													State_Position = 1;
		else if (Current_X <= 150 && (Current_Y > 100 && Current_Y <= 300))							State_Position = 2;
		else if (Current_X <= 150 && Current_Y  <= 100)												State_Position = 3;
		else if ((Current_X <= 400 && Current_X > 150) && Current_Y > 300)							State_Position = 4;
		else if ((Current_X <= 400 && Current_X > 150) && (Current_Y  > 100 && Current_Y <= 300))	State_Position = 5;
		else if ((Current_X <= 400 && Current_X > 150) && Current_Y <= 100)							State_Position = 6;
		else if (Current_X > 400 && Current_Y  > 300)												State_Position = 7;
		else if (Current_X > 400 && (Current_Y > 100 && Current_Y <= 300))							State_Position = 8;
		else if (Current_X > 400 && Current_Y  <= 100)												State_Position = 9;
		Flag_pos = 1; Flag_Gerak = 1;
	}
	else if (Flag_pos == 1)
	{
		if (State_Position == 1)
		{
			Tujuan_KoorY = 200;		Tujuan_KoorX = 100;
			arahY = 450;			arahX = 300;
		}
		else if (State_Position == 2)
		{
			Tujuan_KoorY = 200;		Tujuan_KoorX = 400;
			arahY = 450;			arahX = 200;
		}
		else if (State_Position == 3)
		{
			Tujuan_KoorY = 300;		Tujuan_KoorX = 100;
			arahY = 450;			arahX = 350;
		}
		else if (State_Position == 4)
		{
			Tujuan_KoorY = 300;		Tujuan_KoorX = 400;
			arahY = 450;			arahX = 250;
		}
		else if (State_Position == 5)
		{
			Tujuan_KoorY = 200;		Tujuan_KoorX = 300;
			arahY = 450;			arahX = 300;
		}
		else if (State_Position == 6)
		{
			Tujuan_KoorY = 250;		Tujuan_KoorX = 400;
			arahY = 450;			arahX = 300;
		}
		else if (State_Position == 7)
		{
			Tujuan_KoorY = 200;		Tujuan_KoorX = 350;
			arahY = 450;			arahX = 250;
		}
		else if (State_Position == 8)
		{
			Tujuan_KoorY = 300;		Tujuan_KoorX = 100;
			arahY = 450;			arahX = 300;
		}
		else if (State_Position == 9)
		{
			Tujuan_KoorY = 300;		Tujuan_KoorX = 480;
			arahY = 450;			arahX = 300;
		}

		int error_x = Tujuan_KoorX - X_Oddo_cm[5];
		int error_y = Tujuan_KoorY - Y_Oddo_cm[5];
		error_tendang = sudut_tembak - imu_filter;

		if (abs(error_y) <= 15 && abs(error_x) <= 15 && abs(error_tendang) <7)
		{
			c_g = 1;
			Flag_Gerak = 0;
			LED(BLINK_FAST);
			if (c_p <= 3) fwd_pwm_3roda_PID(0,0,0);
			else if (c_p >= 5) Flag_pos = 2;
//			GOAL(DISCHARGE,Solenoid_set);
		}
		else { Flag_Gerak = 1; }

		if (Flag_Gerak == 1 )Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5], Tujuan_KoorY, Tujuan_KoorX, arahY, arahX);

	}
	else if (Flag_pos == 2) { fwd_pwm_3roda_PID(0,0,0); c_g = 0; c_p = 0; Flag_Gerak = 0;}
}

void strategi_tendang(int sudut_bola, int jarak_bola)
{

	if (jarak_bola < 70 && jarak_bola != 0) Gripper_function(ON,30);	//Gripper_MUNDUR(40,40);
	else {Gripper_OFF();}

	if (Prox != 1)
	{
		get_position(X_Oddo_cm[5], Y_Oddo_cm[5]);
	}

	else if (Prox == 1)
	{
		if(jarak_bola > 0) LED(ON);
		else if (jarak_bola == 0) LED(BLINK);

		Flag_pos = 0;
		Follow_Ball(sudut_bola, jarak_bola, SP_Kamera);
	}
}

int Random (int batas_bawah, int batas_atas)
{
	int range = batas_atas-batas_bawah;
	nilai_random = rand() % range;
	nilai_random +=batas_bawah;
	return nilai_random;
}

void Random_Shoot_Strategy()
{
	if (Prox == 1)
	{
		if (R_Ball > 0) { Flag_Gerak = 1; LED(ON); c_g = 0; c_p = 0; Flag_pos = 1;	}
		else if (R_Ball == 0)
		{
			LED(BLINK);
			Flag_Gerak = 0; c_g = 1;
			if (c_p <= 2) fwd_pwm_3roda_PID(0,0,0);
			else { fwd_pwm_3roda_PID(15,15,15);	}
		}

		if (Flag_Gerak == 1) Follow_Ball(Angle_Ball, Range_Ball, SP_Kamera);
	}
	else if (Prox != 1)
	{
		if (Flag_pos == 1)
		{
			if(Y_Oddo_cm[5] <= 450)
			{
				if(X_Oddo_cm[5] <= 200){ 							//Posisi -1
					Tujuan_KoorY = 500; Tujuan_KoorX = 400;	Shoot_Up = 250;	Shoot_Down = 300;	Solenoid_set = 4;
				}
				else if(X_Oddo_cm[5]>200 &&X_Oddo_cm[5] <= 400){	//Posisi -2
					Tujuan_KoorY = 500; Tujuan_KoorX = X_Oddo_cm[5]+30;	Shoot_Up = 220;	Shoot_Down = 380;	Solenoid_set = 4;
				}
				else if(X_Oddo_cm[5]>400){							//Posisi -3
					Tujuan_KoorY = 500; Tujuan_KoorX = 200;	Shoot_Up = 300;	Shoot_Down = 350;	Solenoid_set = 4;
				}
			}
			else if(Y_Oddo_cm[5]>450 && Y_Oddo_cm[5] <= 595){
				if(X_Oddo_cm[5] <= 200){ 							//Posisi 1
				Tujuan_KoorY = Y_Oddo_cm[5]; Tujuan_KoorX = 400; Shoot_Up = 250;	Shoot_Down = 300;	Solenoid_set = 4;
				}
				else if(X_Oddo_cm[5]>200 &&X_Oddo_cm[5] <= 400){	//Posisi 2
				Tujuan_KoorY = Y_Oddo_cm[5]+100; Tujuan_KoorX = X_Oddo_cm[5]+30;	Shoot_Up = 220;	Shoot_Down = 380;	Solenoid_set = 4;
				}
				else if(X_Oddo_cm[5]>400){							//Posisi 3
				Tujuan_KoorY = Y_Oddo_cm[5]; Tujuan_KoorX = 200;	Shoot_Up = 300;	Shoot_Down = 350;	Solenoid_set = 4;
				}
			}
			else if(Y_Oddo_cm[5]>595 &&Y_Oddo_cm[5] <= 645){
				if(X_Oddo_cm[5] <= 200){							//Posisi 4
				Tujuan_KoorY = Y_Oddo_cm[5]; Tujuan_KoorX = 400;	Shoot_Up = 250;	Shoot_Down = 300;	Solenoid_set = 3;
				}
				else if(X_Oddo_cm[5]>200 &&X_Oddo_cm[5] <= 400){	//Posisi 5
				Tujuan_KoorY = Y_Oddo_cm[5]+50; Tujuan_KoorX = X_Oddo_cm[5]-30;	Shoot_Up = 220;	Shoot_Down = 380;	Solenoid_set = 2;
				}
				else if(X_Oddo_cm[5]>400){							//Posisi 6
				Tujuan_KoorY = Y_Oddo_cm[5]; Tujuan_KoorX = 200;	Shoot_Up = 300;	Shoot_Down = 350;	Solenoid_set = 3;
				}
			}
			else if(Y_Oddo_cm[5]>645 &&Y_Oddo_cm[5] <= 740){
				if(X_Oddo_cm[5] <= 200){							//Posisi 7
				Tujuan_KoorY = Y_Oddo_cm[5]; Tujuan_KoorX = 400;	Shoot_Up = 250;	Shoot_Down = 300;	Solenoid_set = 2;
				}
				else if(X_Oddo_cm[5]>200 &&X_Oddo_cm[5] <= 400){	//Posisi 8
				Tujuan_KoorY = Y_Oddo_cm[5]; Tujuan_KoorX = X_Oddo_cm[5]+50;	Shoot_Up = 220;	Shoot_Down = 380;	Solenoid_set = 1;
				}
				else if(X_Oddo_cm[5]>400){							//Posisi 9
				Tujuan_KoorY = Y_Oddo_cm[5]; Tujuan_KoorX = 200;	Shoot_Up = 300;	Shoot_Down = 380;	Solenoid_set = 2;
				}
			}
			else if(Y_Oddo_cm[5]>740){
				if(X_Oddo_cm[5] <= 200){							//Posisi 10
				Tujuan_KoorY = Y_Oddo_cm[5]-150; Tujuan_KoorX = X_Oddo_cm[5];	Shoot_Up = 300;	Shoot_Down = 350;	Solenoid_set = 2;
				}
				else if(X_Oddo_cm[5]>200 &&X_Oddo_cm[5] <= 400){	//Posisi 11
				Tujuan_KoorY = Y_Oddo_cm[5]-100; Tujuan_KoorX = X_Oddo_cm[5];	Shoot_Up = 220;	Shoot_Down = 380;	Solenoid_set = 1;
				}
				else if(X_Oddo_cm[5]>400){							//Posisi 12
				Tujuan_KoorY = Y_Oddo_cm[5]-150; Tujuan_KoorX = X_Oddo_cm[5];	Shoot_Up = 250;	Shoot_Down = 300;	Solenoid_set = 2;
				}
			}
			nilai_random = Random(Shoot_Up,Shoot_Down);
			Flag_pos = 2;
		}
		int error_x = Tujuan_KoorX - X_Oddo_cm[5];
		int error_y = Tujuan_KoorY - Y_Oddo_cm[5];
		error_tendang = sudut_tembak - imu_filter;

		if (abs(error_y) <= 15 && abs(error_x) <= 15 && abs(error_tendang) <7)
		{
			c_g = 1;
			Flag_Gerak = 0;
			LED(BLINK_FAST);
			if (c_p <= 3) fwd_pwm_3roda_PID(0,0,0);
//			GOAL(DISCHARGE,Solenoid_set);
		}
		else { Flag_Gerak = 1; }

		if (Flag_Gerak == 1 )Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5], Tujuan_KoorY, Tujuan_KoorX, 900, nilai_random);
	}
}

void Strategi_ORION_OFFLINE()
{
	if (Data_Wifi == START_Wifi){}
	else if (Data_Wifi == STOP_Wifi){}
	else if (Data_Wifi == RESET_Wifi){}
	else if (Data_Wifi == WELCOME_Wifi){}
}
//*****************************************************************************************************************//
void Take_Video_Passing()
{
	Gripper_function(ON,30);
	if (Flag_Posisi == 0)
	{
		Flag_Gerak = 1;
		Tuas_Algorithm(60,Tuas_Pot);
		if (Program_Untuk == ORION)
		{
			Tujuan_KoorY = 250; Tujuan_KoorX = 250; arahY = Y_Oddo_cm[5]; arahX = 600;
			if (X_Oddo_cm[5] >= Tujuan_KoorX-20 && Y_Oddo_cm[5] >= Tujuan_KoorY-20){Flag_Posisi = 1; T_ORION.Keadaan_Robot = 1;}
		}
		else if (Program_Untuk == HYDRA)
		{
			Tujuan_KoorY = 250; Tujuan_KoorX = 350; arahY = Y_Oddo_cm[5]; arahX = 0;
			if (X_Oddo_cm[5] >= Tujuan_KoorX-20 && Y_Oddo_cm[5] >= Tujuan_KoorY-20){Flag_Posisi = 1; T_HYDRA.Keadaan_Robot = 3;}
		}
	}
	else if (Flag_Posisi == 1)
	{
		Flag_Gerak = 0;
		T_HYDRA.Keadaan_Robot = 3; T_HYDRA.Koor_X = 350; T_HYDRA.Koor_Y = 250;
		if (Program_Untuk == ORION)
		{
			if (T_HYDRA.Keadaan_Robot == 3 && f_oper == 0)
			{
				T_ORION.Keadaan_Robot = 5;
				Rotate_Kick(T_HYDRA.Koor_X, T_HYDRA.Koor_Y-5,OPER);
			}
			if (Prox == 1 && f_oper == 1 && c_p >= 3) { Flag_Posisi = 2; c_g = 0; c_p = 0; FlagSiapTendang = 0;}
		}
		else if (Program_Untuk == HYDRA)
		{
			if (Prox != 1) Rotate_To_Ball();
			else if (Prox == 1) {T_HYDRA.Keadaan_Robot = 2; Flag_Posisi = 2;}
		}
	}
	else if (Flag_Posisi == 2)
	{
		if (Program_Untuk == ORION)
		{
			Tuas_Algorithm(40,Tuas_Pot);
			if (Prox == 1)
			{
				c_g = 1;
				if (c_p < 4) fwd_pwm_3roda_PID(0,0,0);
				else { T_ORION.Keadaan_Robot = 2; Rotate_To_Ball(); }
			}
			else if (Prox != 1) {T_ORION.Keadaan_Robot = 3; Flag_Posisi = 3; c_g = 0; c_p = 0;}
		}
		else if (Program_Untuk == HYDRA)
		{
			if (T_ORION.Keadaan_Robot == 2 && Prox != 1 && f_oper == 0)
			{
				T_HYDRA.Keadaan_Robot = 5;
				Rotate_Kick(T_ORION.Koor_X, T_ORION.Koor_Y,OPER);
			}
			if (Prox == 1 && f_oper == 1 && c_p >= 3) { Flag_Posisi = 4; c_g = 0; c_p = 0;}
		}
	}
	else if (Flag_Posisi == 3)
	{
		if (Prox != 1)
		{
			Rotate_Kick(305,600,SHOOT);
		}
		if (Prox == 1)
		{
			if (c_p < 4) fwd_pwm_3roda_PID(0,0,0);
			else Flag_Posisi = 4;
		}
	}
	if (Flag_Posisi == 4) {	fwd_pwm_3roda_PID(0,0,0); c_g = 0; c_p = 0;	}
	if (Flag_Gerak == 1) Move_Koordinat_3roda(Y_Oddo_cm[5], X_Oddo_cm[5], Tujuan_KoorY, Tujuan_KoorX, arahY, arahX);
}


void Mode_Striker(){
	lcd_gotoxy(18,0); sprintf(lcd, "%d",Rotary_Switch_MODE);  lcd_putstr(lcd);
	if(kalibrasi_imu == 0)
	{
		lcd_gotoxy(12,0);  sprintf(lcd, "y=K");  lcd_putstr(lcd);
		if (Program_Untuk == HYDRA) {lcd_gotoxy(0,1); sprintf(lcd, "Hai.. Namaku HYDRA...");  lcd_putstr(lcd);}
		if (Program_Untuk == ORION){lcd_gotoxy(0,1); sprintf(lcd, "Hai.. Namaku ORION..");  lcd_putstr(lcd);}
		lcd_gotoxy(0,2);  sprintf(lcd, "Mohon menunggu...");    lcd_putstr(lcd);
		lcd_gotoxy(0,3);  sprintf(lcd, "Geser dikit biar NOL"); lcd_putstr(lcd);
	}
	else if (kalibrasi_imu == 2){lcd_gotoxy(12,0);  sprintf(lcd, "y=%d",(int)imu_filter);lcd_putstr(lcd);
	switch (Rotary_Switch_MODE){
	case 1 :{
			switch (mode){
			case 1:{
				lcd_gotoxy(19,0); sprintf(lcd, "A");  lcd_putstr(lcd);
				break;}
			case 2:{
				lcd_gotoxy(19,0); sprintf(lcd, "B");  lcd_putstr(lcd);
				break;}
			case 3:{
				lcd_gotoxy(19,0); sprintf(lcd, "C");  lcd_putstr(lcd);
				break;}
			case 4:{
				lcd_gotoxy(19,0); sprintf(lcd, "D");  lcd_putstr(lcd);
				break;}
			case 5:{
				lcd_gotoxy(19,0); sprintf(lcd, "E");  lcd_putstr(lcd);
				break;}
			case 6:{
				lcd_gotoxy(19,0); sprintf(lcd, "F");  lcd_putstr(lcd);
				break;}
			}
			break;}
	case 2 :{
		switch (mode){
		case 1:{
			lcd_gotoxy(19,0); sprintf(lcd, "A");  lcd_putstr(lcd);
			break;}
		case 2:{
			lcd_gotoxy(19,0); sprintf(lcd, "B");  lcd_putstr(lcd);
			break;}
		case 3:{
			lcd_gotoxy(19,0); sprintf(lcd, "C");  lcd_putstr(lcd);
			break;}
		case 4:{
			lcd_gotoxy(19,0); sprintf(lcd, "D");  lcd_putstr(lcd);
			break;}
		case 5:{
			lcd_gotoxy(19,0); sprintf(lcd, "E");  lcd_putstr(lcd);
			break;}
		case 6:{
			lcd_gotoxy(19,0); sprintf(lcd, "F");  lcd_putstr(lcd);
			break;}
		}
		break;}
	case 3 :{
		switch (mode){
		case 1:{
			lcd_gotoxy(19,0); sprintf(lcd, "A");  lcd_putstr(lcd);
			break;}
		case 2:{
			lcd_gotoxy(19,0); sprintf(lcd, "B");  lcd_putstr(lcd);
			break;}
		case 3:{
			lcd_gotoxy(19,0); sprintf(lcd, "C");  lcd_putstr(lcd);
			break;}
		case 4:{
			lcd_gotoxy(19,0); sprintf(lcd, "D");  lcd_putstr(lcd);
			break;}
		case 5:{
			lcd_gotoxy(19,0); sprintf(lcd, "E");  lcd_putstr(lcd);
			break;}
		case 6:{
			lcd_gotoxy(19,0); sprintf(lcd, "F");  lcd_putstr(lcd);
			break;}
		}
		break;}
	case 4 :{
		switch (mode){
		case 1:{
			lcd_gotoxy(19,0); sprintf(lcd, "A");  		 lcd_putstr(lcd);
			break;}
		case 2:{
			lcd_gotoxy(19,0); sprintf(lcd, "B");  		  lcd_putstr(lcd);
			break;}
		case 3:{
			lcd_gotoxy(19,0); sprintf(lcd, "C");  		  lcd_putstr(lcd);
			break;}
		case 4:{
			lcd_gotoxy(19,0); sprintf(lcd, "D");  	    lcd_putstr(lcd);
			break;}
		case 5:{
			lcd_gotoxy(19,0); sprintf(lcd, "E");  		 lcd_putstr(lcd);
			break;}
		case 6:{
			lcd_gotoxy(19,0); sprintf(lcd, "F");  			lcd_putstr(lcd);
			break;}
		}
		break;}
	case 5 :{
		switch (mode){
		case 1:{
			lcd_gotoxy(19,0); sprintf(lcd, "A");  lcd_putstr(lcd);
			break;}
		case 2:{
			lcd_gotoxy(19,0); sprintf(lcd, "B");  lcd_putstr(lcd);
			break;}
		case 3:{
			lcd_gotoxy(19,0); sprintf(lcd, "C");  lcd_putstr(lcd);
			break;}
		case 4:{
			lcd_gotoxy(19,0); sprintf(lcd, "D");  lcd_putstr(lcd);
			break;}
		case 5:{
			lcd_gotoxy(19,0); sprintf(lcd, "E");  lcd_putstr(lcd);
			break;}
		case 6:{
			lcd_gotoxy(19,0); sprintf(lcd, "F");  lcd_putstr(lcd);
			break;}
		}
		break;}
	case 6 :{
		switch (mode){
		case 1:{
			lcd_gotoxy(19,0); sprintf(lcd, "A");  lcd_putstr(lcd);
			break;}
		case 2:{
			lcd_gotoxy(19,0); sprintf(lcd, "B");  lcd_putstr(lcd);
			break;}
		case 3:{
			lcd_gotoxy(19,0); sprintf(lcd, "C");  lcd_putstr(lcd);
		 	break;}
		case 4:{
			lcd_gotoxy(19,0); sprintf(lcd, "D");  lcd_putstr(lcd);
			break;}
		case 5:{
			lcd_gotoxy(19,0); sprintf(lcd, "E");  lcd_putstr(lcd);
			break;}
		case 6:{
			lcd_gotoxy(19,0); sprintf(lcd, "F");  lcd_putstr(lcd);
			break;}
		}
		break;}
	}}
}

void Mode_Striker_2()
{
	if(kalibrasi_imu == 0){
		lcd_gotoxy(13,0);  sprintf(lcd, "y=K");  lcd_putstr(lcd);
		if (Program_Untuk == HYDRA) {lcd_gotoxy(0,1); sprintf(lcd, "Hai.. Namaku HYDRA...");  lcd_putstr(lcd);}
		if (Program_Untuk == ORION){lcd_gotoxy(0,1); sprintf(lcd, "Hai.. Namaku ORION..");  lcd_putstr(lcd);}
		lcd_gotoxy(0,2);  sprintf(lcd, "Mohon menunggu...");    lcd_putstr(lcd);
		lcd_gotoxy(0,3);  sprintf(lcd, "Geser dikit biar NOL"); lcd_putstr(lcd);
	}
	else if (kalibrasi_imu == 2){lcd_gotoxy(13,0);  sprintf(lcd, "y=%d",(int)imu_filter);lcd_putstr(lcd);}

	choose_action(UPCLICK,DOWNCLICK,OKCLICK,BACKCLICK,R_UPCLICK,R_DOWNCLICK);

	if (execute == 1) {lcd_gotoxy(19,0);  sprintf(lcd, "P");  lcd_putstr(lcd);}
	else if (execute == 0) {lcd_gotoxy(19,0);  sprintf(lcd, "S");  lcd_putstr(lcd);}

	switch (choose_mode[0]){ // choose global mode
	case 1 :{
		if (execute == 0) {lcd_gotoxy(0,0);  sprintf(lcd, "CAL");  lcd_putstr(lcd);}
		switch (choose_mode[1]){ //choose main mode
		case 1 :{
			if (execute == 0){lcd_gotoxy(0,1);  sprintf(lcd, "MOTOR");  lcd_putstr(lcd); fwd_pwm_3roda_PID(0,0,0);}
			lcd_gotoxy(0,2);  sprintf(lcd, "pwm(%d,%d,%d)",(int)pwm_1,(int)pwm_2,(int)pwm_3); lcd_putstr(lcd);
			lcd_gotoxy(0,3);  sprintf(lcd, "pwmR(%d,%d,%d)",(int)pwm_real_1,(int)pwm_real_2,(int)pwm_real_3); lcd_putstr(lcd);
			switch (choose_mode[2]){ // choose sub mode
			case 1 : {
				if (execute == 0){lcd_gotoxy(6,1);  sprintf(lcd, "MANUAL");  lcd_putstr(lcd);}
				if (execute == 1){	 /*put your strategy here*/}
				break;}
			case 2 : {
				if (execute == 0) {lcd_gotoxy(6,1);  sprintf(lcd, "MAJU");  lcd_putstr(lcd);}
				else if (execute == 1)	{ fwd_pwm_3roda_PID(cnt_mode[2],0, -1*cnt_mode[2]);						}
				break;}
			case 3 : {
				if (execute == 0){lcd_gotoxy(6,1);  sprintf(lcd, "MUNDUR");  lcd_putstr(lcd);}
				else if (execute == 1)	{ fwd_pwm_3roda_PID(-1*cnt_mode[2],0, cnt_mode[2]);						}
				break;}
			case 4 : {
				if (execute == 0) {lcd_gotoxy(6,1);  sprintf(lcd, "KANAN");  lcd_putstr(lcd);}
				else if (execute == 1)	{ fwd_pwm_3roda_PID(0.5*cnt_mode[2],-1*cnt_mode[2], 0.5*cnt_mode[2]);	}
				break;}
			case 5 : {
				if (execute == 0) {lcd_gotoxy(6,1);  sprintf(lcd, "KIRI");  lcd_putstr(lcd);}
				else if (execute == 1)	{ fwd_pwm_3roda_PID(-0.5*cnt_mode[2],cnt_mode[2], -0.5*cnt_mode[2]);	}
				break;}
			case 6 : {
				if (execute == 0) {lcd_gotoxy(6,1);  sprintf(lcd, "ROTATION");  lcd_putstr(lcd);}
				else if (execute == 1)	{ fwd_pwm_3roda_PID(cnt_mode[2], cnt_mode[2], cnt_mode[2]);				}
				break;}
			case 7 : {
				if (execute == 0) {lcd_gotoxy(6,1);  sprintf(lcd, "MT1");  lcd_putstr(lcd);}
				else if (execute == 1)	{ fwd_pwm_3roda_PID(cnt_mode[2], 0, 0);				}
				break;}
			case 8 : {
				if (execute == 0) {lcd_gotoxy(6,1);  sprintf(lcd, "MT2");  lcd_putstr(lcd);}
				else if (execute == 1)	{ fwd_pwm_3roda_PID(0, cnt_mode[2], 0);				}
				break;}
			case 9 : {
				if (execute == 0) {lcd_gotoxy(6,1);  sprintf(lcd, "MT3");  lcd_putstr(lcd);}
				else if (execute == 1)	{ fwd_pwm_3roda_PID(0, 0, cnt_mode[2]);									}
				break;}
			case 10 : { cnt_mode[0] = 1; break;}
			}
			break;}
		case 2 :{
			if (execute == 0) {lcd_gotoxy(0,1);  sprintf(lcd, "SOL Manual");		lcd_putstr(lcd);}
			lcd_gotoxy(0,3);  sprintf(lcd, "Sol(%d,%d,%d,%d)",
					(int)solenoid1_state,(int)solenoid2_state,(int)solenoid3_state,(int)solenoid4_state);lcd_putstr(lcd);
			switch (choose_mode[2]){ // choose sub mode
			case 1 : {
				lcd_gotoxy(5,0);  sprintf(lcd, "CAS ALL");  lcd_putstr(lcd);
				if (execute == 1)	{ Solenoid_Manual_4Cell_2021(0,0,0,0);	}
				break;}
			case 2 : {
				lcd_gotoxy(5,0);  sprintf(lcd, "DIS ALL");  lcd_putstr(lcd);
				if (execute == 1)	{ Solenoid_Manual_4Cell_2021(1,1,1,1);	}
				break;}
			case 3 : {
				lcd_gotoxy(5,0);  sprintf(lcd, "SHOOT 1");  lcd_putstr(lcd);
				if (execute == 1)	{ Solenoid_Manual_4Cell_2021(1,0,0,0);	}
				break;}
			case 4 : {
				lcd_gotoxy(5,0);  sprintf(lcd, "SHOOT 2");  lcd_putstr(lcd);
				if (execute == 1)	{ Solenoid_Manual_4Cell_2021(1,1,0,0);	}
				break;}
			case 5 : {
				lcd_gotoxy(5,0);  sprintf(lcd, "SHOOT 3");  lcd_putstr(lcd);
				if (execute == 1)	{ Solenoid_Manual_4Cell_2021(1,1,1,0);	}
				break;}
			case 6 : {
				lcd_gotoxy(5,0);  sprintf(lcd, "RESERVED");  lcd_putstr(lcd);
				if (execute == 1)	{	}
				break;}
			case 7 : { cnt_mode[0] = 1; break;}
			}
			break;}
		case 3 :{
			if (execute == 0) {lcd_gotoxy(0,1);  sprintf(lcd, "SOL Auto");		lcd_putstr(lcd);}
			if (execute == 1){
				lcd_gotoxy(0,1);  sprintf(lcd, "F_cas=%d",(int)Flag_cas);		lcd_putstr(lcd);
				lcd_gotoxy(10,1); sprintf(lcd, "F_dcas=%d",(int)Siap_tendang);	lcd_putstr(lcd);
				lcd_gotoxy(0,2);  sprintf(lcd, "C_Cas=%d",(int)Counter_cas);	lcd_putstr(lcd);
				lcd_gotoxy(10,2); sprintf(lcd, "C_Dcas=%d",(int)Counter_dcas);	lcd_putstr(lcd);
			}
			lcd_gotoxy(0,3);  sprintf(lcd, "Sol(%d,%d,%d,%d)",
					(int)solenoid1_state,(int)solenoid2_state,(int)solenoid3_state,(int)solenoid4_state);lcd_putstr(lcd);
			switch (choose_mode[2]){ // choose sub mode
			case 1 : {
				lcd_gotoxy(5,0);  sprintf(lcd, "CAS ALL");  lcd_putstr(lcd);
				if (execute == 1)	{ SOLENOID_ALGORITHM_4Cell(CHARGE,1,ALL_MODE);		}
				break;}
			case 2 : {
				lcd_gotoxy(5,0);  sprintf(lcd, "DIS ALL");  lcd_putstr(lcd);
				if (execute == 1)	{ SOLENOID_ALGORITHM_4Cell(DISCHARGE,1,ALL_MODE);		}
				break;}
			case 3 : {
				lcd_gotoxy(5,0);  sprintf(lcd, "PASS CAS");  lcd_putstr(lcd);
				if (execute == 1)	{ SOLENOID_ALGORITHM_4Cell(CHARGE,1,PASSING_MODE);	}
				break;}
			case 4 : {
				lcd_gotoxy(5,0);  sprintf(lcd, "PASS DIS");  lcd_putstr(lcd);
				if (execute == 1)	{ SOLENOID_ALGORITHM_4Cell(DISCHARGE,1,PASSING_MODE);	}
				break;}
			case 5 : {
				lcd_gotoxy(5,0);  sprintf(lcd, "CAS1");  lcd_putstr(lcd);
				if (execute == 1)	{ SOLENOID_ALGORITHM_4Cell(CHARGE,1,SHOOTING_MODE);	}
				break;}
			case 6 : {
				lcd_gotoxy(5,0);  sprintf(lcd, "CAS2");  lcd_putstr(lcd);
				if (execute == 1)	{ SOLENOID_ALGORITHM_4Cell(CHARGE,2,SHOOTING_MODE);	}
				break;}
			case 7 : {
				lcd_gotoxy(5,0);  sprintf(lcd, "CAS3");  lcd_putstr(lcd);
				if (execute == 1)	{ SOLENOID_ALGORITHM_4Cell(CHARGE,3,SHOOTING_MODE);	}
				break;}
			case 8 : {
				lcd_gotoxy(5,0);  sprintf(lcd, "DIS1");  lcd_putstr(lcd);
				if (execute == 1)	{ SOLENOID_ALGORITHM_4Cell(DISCHARGE,1,SHOOTING_MODE);	}
				break;}
			case 9 : {
				lcd_gotoxy(5,0);  sprintf(lcd, "DIS2");  lcd_putstr(lcd);
				if (execute == 1)	{ SOLENOID_ALGORITHM_4Cell(DISCHARGE,2,SHOOTING_MODE);	}
				break;}
			case 10 : {
				lcd_gotoxy(5,0);  sprintf(lcd, "DIS3");  lcd_putstr(lcd);
				if (execute == 1)	{ SOLENOID_ALGORITHM_4Cell(DISCHARGE,3,SHOOTING_MODE);	}
				break;}
			}
			break;}
		case 4 :{
			lcd_gotoxy(0,1);  sprintf(lcd, "GRIP TUAS");  lcd_putstr(lcd);
		 	lcd_gotoxy(7,2); sprintf(lcd, "GL= %d",(int)Griper_Pot1);  lcd_putstr(lcd);
		 	lcd_gotoxy(13,2); sprintf(lcd, "GR= %d",(int)Griper_Pot2);  lcd_putstr(lcd);
			lcd_gotoxy(0,2);  sprintf(lcd, "P= %d",Tuas_Pot);  		lcd_putstr(lcd);
			lcd_gotoxy(0,3); sprintf(lcd, "TU = %d",(int)Tuas_Switch1); lcd_putstr(lcd);
		 	lcd_gotoxy(9,3); sprintf(lcd, "TD = %d",(int)Tuas_Switch2); lcd_putstr(lcd);
			lcd_gotoxy(19,3); sprintf(lcd, "%d",Prox);  			lcd_putstr(lcd);

			switch (choose_mode[2]){ // choose sub mode
			case 1 : {
				lcd_gotoxy(10,1);  sprintf(lcd, "G_ON");  lcd_putstr(lcd);
				if (execute == 0)	{ Gripper_function(OFF, 0);			}
				if (execute == 1)	{ Gripper_function(ON,30);			}
				break;}
			case 2 : {
				lcd_gotoxy(10,1);  sprintf(lcd, "G_BALIK");  lcd_putstr(lcd);
				if (execute == 0)	{ Gripper_function(OFF,0);			}
				if (execute == 1)	{ Gripper_function(BALIK,30); 		}
				break;}
			case 3 : {
				lcd_gotoxy(10,1);  sprintf(lcd, "T_NAIK");  lcd_putstr(lcd);
				if (execute == 0) 	{ Tuas_Manual(0);					}
				if (execute == 1)	{ Tuas_Manual(30);					}
				break;}
			case 4 : {
				lcd_gotoxy(10,1);  sprintf(lcd, "T_TURUN");  lcd_putstr(lcd);
				if (execute == 0)	{ Tuas_Manual(0);					}
				if (execute == 1)	{ Tuas_Manual(-30);					}
				break;}
			case 5 : {
				lcd_gotoxy(10,1);  sprintf(lcd, "T_65");  lcd_putstr(lcd);
				if (execute == 0)	{ Tuas_Manual(0);					}
				if (execute == 1)	{ Tuas_Algorithm(65, Tuas_Pot);		}
				break;}
			case 6 : {
				lcd_gotoxy(10,1);  sprintf(lcd, "T_50");  lcd_putstr(lcd);
				if (execute == 0)	{ Tuas_Manual(0);					}
				if (execute == 1)	{ Tuas_Algorithm(50, Tuas_Pot);		}
				break;}
			case 7 : {
				lcd_gotoxy(10,1);  sprintf(lcd, "T_35");  lcd_putstr(lcd);
				if (execute == 0)	{ Tuas_Manual(0);					}
				if (execute == 1)	{ Tuas_Algorithm(35, Tuas_Pot);		}
				break;}
			case 8 : {
				lcd_gotoxy(10,1);  sprintf(lcd, "G_MAJU");  lcd_putstr(lcd);
				if (execute == 0)	{	fwd_pwm_3roda_PID(0,0,0);		}
				if (execute == 1)	{	 move_angle_3roda(0,30,YES);	}
				break;}
			case 9 : {
				lcd_gotoxy(10,1);  sprintf(lcd, "G_MUNDUR");  lcd_putstr(lcd);
				if (execute == 0)	{	fwd_pwm_3roda_PID(0,0,0);		}
				if (execute == 1)	{	 move_angle_3roda(180,30,YES);	}
				break;}
			case 10 : {
				lcd_gotoxy(10,1);  sprintf(lcd, "G_KANAN");  lcd_putstr(lcd);
				if (execute == 0)	{	fwd_pwm_3roda_PID(0,0,0);		}
				if (execute == 1)	{	 move_angle_3roda(90,30,YES);	}
				break;}
			case 11 : {
				lcd_gotoxy(10,1);  sprintf(lcd, "G_KIRI");  lcd_putstr(lcd);
				Gripper_josh(10,100,30);
				if (execute == 0)	{	fwd_pwm_3roda_PID(0,0,0);		}
				if (execute == 1)	{	 move_angle_3roda(-90,30,YES);	}
				break;}
			case 12 : { cnt_mode[0] = 1; break;}
			}
			break;}
		case 5 :{
			lcd_gotoxy(0,1);  sprintf(lcd, "MOVE");  lcd_putstr(lcd);
			lcd_gotoxy(13,1);  sprintf(lcd, "Yb=%d",(int)Angle_Ball); 						  lcd_putstr(lcd);
			lcd_gotoxy(7,0);  sprintf(lcd, "R=%d",(int)Range_Ball);  						  lcd_putstr(lcd);
		 	lcd_gotoxy(19,3); sprintf(lcd, "%d",(int)Data_Wifi);  							  lcd_putstr(lcd);
		 	if (execute == 1)
		 	{
		 		lcd_gotoxy(0,2);  sprintf(lcd, "pwm(%d,%d,%d)",(int)pwm_1,(int)pwm_2,(int)pwm_3); lcd_putstr(lcd);
		 		lcd_gotoxy(0,3);  sprintf(lcd, "X=%d",(int)X_Oddo_cm[5]);  						  lcd_putstr(lcd);
		 		lcd_gotoxy(10,3); sprintf(lcd, "Y=%d",(int)Y_Oddo_cm[5]);						  lcd_putstr(lcd);
		 	}
			switch (choose_mode[2]){ // choose sub mode
			case 1 : {
				lcd_gotoxy(5,1);  sprintf(lcd, "KOOR A");  lcd_putstr(lcd);
				if (execute == 1)	{ Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],200,100,Y_Oddo_cm[5],600);		}
				break;}
			case 2 : {
				lcd_gotoxy(5,1);  sprintf(lcd, "KOOR B");  lcd_putstr(lcd);
				if (execute == 1)	{ Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],200,300,Y_Oddo_cm[5],600);	}
				break;}
			case 3 : {
				lcd_gotoxy(5,1);  sprintf(lcd, "KOOR C");  lcd_putstr(lcd);
				if (execute == 1)	{ Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],200,300,600,X_Oddo_cm[5]); }
				break;}
			case 4 : {
				lcd_gotoxy(5,1);  sprintf(lcd, "KOOR D");  lcd_putstr(lcd);
				if (execute == 1)	{ Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],300,-100,600,X_Oddo_cm[5]);	}
				break;}
			case 5 : {
				lcd_gotoxy(4,1);  sprintf(lcd, "ANGLE0");  lcd_putstr(lcd);
				if (execute == 1)	{ move_angle_3roda(0,30,YES);	}
				break;}
			case 6 : {
				lcd_gotoxy(4,1);  sprintf(lcd, "ANGLE45");  lcd_putstr(lcd);
				if (execute == 1)	{ move_angle_3roda(45,30,YES);	}
				break;}
			case 7 : {
				lcd_gotoxy(4,1);  sprintf(lcd, "ANGLE90");  lcd_putstr(lcd);
				if (execute == 1)	{ move_angle_3roda(90,30,YES);	}
				break;}
			case 8 : {
				lcd_gotoxy(4,1);  sprintf(lcd, "ANGLE135");  lcd_putstr(lcd);
				if (execute == 1)	{ move_angle_3roda(135,30,YES);	}
				break;}
			case 9 : {
				lcd_gotoxy(4,1);  sprintf(lcd, "ANGLE180");  lcd_putstr(lcd);
				if (execute == 1)	{ move_angle_3roda(180,30,YES);	}
				break;}
			case 10 : {
				lcd_gotoxy(4,1);  sprintf(lcd, "ANGLE-135");  lcd_putstr(lcd);
				if (execute == 1)	{ move_angle_3roda(-135,30,YES);}
				break;}
			case 11 : {
				lcd_gotoxy(4,1);  sprintf(lcd, "ANGLE-90");  lcd_putstr(lcd);
				if (execute == 1)	{ move_angle_3roda(-90,30,YES);	}
				break;}
			case 12 : {
				lcd_gotoxy(4,1);  sprintf(lcd, "ANGLE-45");  lcd_putstr(lcd);
				if (execute == 1)	{ move_angle_3roda(-45,30,YES);	}
				break;}
			}
			break;}
		case 6 :{
			if (execute == 0) {lcd_gotoxy(0,1);  sprintf(lcd, "Rotary");  lcd_putstr(lcd);}

			switch (choose_mode[2]){ // choose sub mode
			case 1 : {
				lcd_gotoxy(7,1);  sprintf(lcd, "INTERNAL");  lcd_putstr(lcd);
				if (execute == 1)
				{	 /*put your strategy here*/
					lcd_gotoxy(0,2); sprintf(lcd, "RI1=%d",(int)rt0_m1.encoder);					  lcd_putstr(lcd);
					lcd_gotoxy(4,3); sprintf(lcd, "RI2=%d",(int)rt0_m2.encoder);					  lcd_putstr(lcd);
					lcd_gotoxy(10,2); sprintf(lcd, "RI3=%d",(int)rt0_m3.encoder);					  lcd_putstr(lcd);

				}
				break;}
			case 2 : {
				lcd_gotoxy(7,1);  sprintf(lcd, "EXTERNAL");  lcd_putstr(lcd);
				if (execute == 1)
				{	 /*put your strategy here*/
				 	lcd_gotoxy(0,3);  sprintf(lcd, "X=%d",(int)X_Oddo_cm[5]);  						  lcd_putstr(lcd);
				 	lcd_gotoxy(10,3); sprintf(lcd, "Y=%d",(int)Y_Oddo_cm[5]);						  lcd_putstr(lcd);
					if (Program_Untuk == ORION)
					{
						lcd_gotoxy(0,2); sprintf(lcd, "RI1=%d",(int)rt_6.encoder);					  lcd_putstr(lcd);
						lcd_gotoxy(0,0); sprintf(lcd, "RI2=%d",(int)rt_7.encoder);					  lcd_putstr(lcd);
						lcd_gotoxy(10,2); sprintf(lcd, "RI3=%d",(int)rt_8.encoder);					  lcd_putstr(lcd);
					}
					if (Program_Untuk == HYDRA)
					{
						lcd_gotoxy(0,2); sprintf(lcd, "RI1=%d",(int)rt_3.encoder);					  lcd_putstr(lcd);
						lcd_gotoxy(0,0); sprintf(lcd, "RI2=%d",(int)rt_4.encoder);					  lcd_putstr(lcd);
						lcd_gotoxy(10,2); sprintf(lcd, "RI3=%d",(int)rt_5.encoder);					  lcd_putstr(lcd);
					}
				}
				break;}
			case 3 : {
				lcd_gotoxy(7,1);  sprintf(lcd, "INTERNAL Rpm+");  lcd_putstr(lcd);
				if (execute == 0) { F_cnt_rotary = 0; fwd_pwm_3roda_PID(0,0,0);}
				if (execute == 1)
				{	 /*put your strategy here*/

					F_cnt_rotary = 1;
					lcd_gotoxy(0,2); sprintf(lcd, "RI1=%d",(int)variabel_rotary1);					  lcd_putstr(lcd);
					lcd_gotoxy(4,3); sprintf(lcd, "RI2=%d",(int)variabel_rotary2);					  lcd_putstr(lcd);
					lcd_gotoxy(10,2); sprintf(lcd, "RI3=%d",(int)variabel_rotary3);					  lcd_putstr(lcd);
					lcd_gotoxy(15,3); sprintf(lcd, "%d",(int)variabel_rotary);					  lcd_putstr(lcd);
					if (cnt_rotary == 50)
					{
						variabel_rotary += 10;
						variabel_rotary1 = abs(rt0_m1.Rpm2);
						variabel_rotary2 = abs(rt0_m2.Rpm2);
						variabel_rotary3 = abs(rt0_m3.Rpm2);

						cnt_rotary += 1;
						if (variabel_rotary > 100) variabel_rotary = 0;
					}
					fwd_pwm_3roda_PID(variabel_rotary,variabel_rotary,variabel_rotary);

				}
				break;}
			case 4 : {
				lcd_gotoxy(7,1);  sprintf(lcd, "INTERNAL Rpm-");  lcd_putstr(lcd);
				if (execute == 0) { F_cnt_rotary = 0; fwd_pwm_3roda_PID(0,0,0);}
				if (execute == 1)
				{	 /*put your strategy here*/

					F_cnt_rotary = 1;
					lcd_gotoxy(0,2); sprintf(lcd, "RI1=%d",(int)variabel_rotary1);					  lcd_putstr(lcd);
					lcd_gotoxy(4,3); sprintf(lcd, "RI2=%d",(int)variabel_rotary2);					  lcd_putstr(lcd);
					lcd_gotoxy(10,2); sprintf(lcd, "RI3=%d",(int)variabel_rotary3);					  lcd_putstr(lcd);
					lcd_gotoxy(15,3); sprintf(lcd, "%d",(int)variabel_rotary);					  lcd_putstr(lcd);
					if (cnt_rotary == 50)
					{
						variabel_rotary -= 10;
						variabel_rotary1 = abs(rt0_m1.Rpm2);
						variabel_rotary2 = abs(rt0_m2.Rpm2);
						variabel_rotary3 = abs(rt0_m3.Rpm2);

						cnt_rotary += 1;
						if (variabel_rotary < -100) variabel_rotary = 0;
					}
					fwd_pwm_3roda_PID(variabel_rotary,variabel_rotary,variabel_rotary);

				}
				break;}
			case 5 : {
				lcd_gotoxy(7,1);  sprintf(lcd, "PWM ROTARY+");  lcd_putstr(lcd);
				if (execute == 1)
				{	 /*put your strategy here*/
					F_cnt_rotary = 1;
					lcd_gotoxy(0,2);  sprintf(lcd, "pwm(%d,%d,%d)",(int)pwm_1,(int)pwm_2,(int)pwm_3); lcd_putstr(lcd);
					lcd_gotoxy(0,3);  sprintf(lcd, "pwmr(%d,%d,%d)",(int)pwm_real_1,(int)pwm_real_2,(int)pwm_real_3); lcd_putstr(lcd);
					if (cnt_rotary == 50)
					{
						variabel_rotary += 10;
						cnt_rotary += 1;
						if (variabel_rotary > 100) variabel_rotary = 0;
					}
					fwd_pwm_3roda_PID(variabel_rotary,variabel_rotary,variabel_rotary);
				}
				break;}
			case 6 : {
				lcd_gotoxy(7,1);  sprintf(lcd, "PWM ROTARY-");  lcd_putstr(lcd);
				if (execute == 1)
				{	 /*put your strategy here*/
					F_cnt_rotary = 1;
					lcd_gotoxy(0,2);  sprintf(lcd, "pwm(%d,%d,%d)",(int)pwm_1,(int)pwm_2,(int)pwm_3); lcd_putstr(lcd);
					lcd_gotoxy(0,3);  sprintf(lcd, "pwmr(%d,%d,%d)",(int)pwm_real_1,(int)pwm_real_2,(int)pwm_real_3); lcd_putstr(lcd);
					if (cnt_rotary == 50)
					{
						variabel_rotary -= 10;
						cnt_rotary += 1;
						if (variabel_rotary < -100) variabel_rotary = 0;
					}
					fwd_pwm_3roda_PID(variabel_rotary,variabel_rotary,variabel_rotary);
				}
				break;}
			case 7 : {
				if (execute == 0)
				{
					fwd_pwm_3roda_PID(0,0,0);
					lcd_gotoxy(7,1);  sprintf(lcd, "PID MOTOR");  lcd_putstr(lcd);
				}
				if (execute == 1)
				{	 /*put your strategy here*/
//					F_cnt_rotary = 1;
					lcd_gotoxy(0,1);  sprintf(lcd, "pwm(%d,%d,%d)",(int)pwm_1,(int)pwm_2,(int)pwm_3); lcd_putstr(lcd);
					lcd_gotoxy(0,2);  sprintf(lcd, "pwmr(%d,%d,%d)",(int)pwm_real_1,(int)pwm_real_2,(int)pwm_real_3); lcd_putstr(lcd);
					fwd_pwm_3roda_PID(60,60,60);
				}
				break;}
			case 8 : { cnt_mode[0] = 1; break;}
			}
			break;}
		}
		break;}
	case 2 :{
		if (execute == 0){lcd_gotoxy(0,0);  sprintf(lcd, "MTC");  lcd_putstr(lcd);}
		switch (choose_mode[1]){ // choose main mode
		case 1 : {
			if (execute == 0){lcd_gotoxy(0,1);  sprintf(lcd, "OFFLINE");  lcd_putstr(lcd);}
			else if (execute ==1)
			{
				lcd_gotoxy(0,0);  sprintf(lcd, "Yb=%d",(int)Angle_Ball); 						  lcd_putstr(lcd);
				lcd_gotoxy(7,0);  sprintf(lcd, "R=%d",(int)Range_Ball);  						  lcd_putstr(lcd);
		 		lcd_gotoxy(0,1);  sprintf(lcd, "pwm(%d,%d,%d)",(int)pwm_1,(int)pwm_2,(int)pwm_3); lcd_putstr(lcd);
		 		lcd_gotoxy(0,2);  sprintf(lcd, "X=%d",(int)X_Oddo_cm[5]);  						  lcd_putstr(lcd);
		 		lcd_gotoxy(10,2); sprintf(lcd, "Y=%d",(int)Y_Oddo_cm[5]);						  lcd_putstr(lcd);
		 		lcd_gotoxy(19,2); sprintf(lcd, "%d",(int)Flag_Posisi);							  lcd_putstr(lcd);
		 		lcd_gotoxy(19,3); sprintf(lcd, "%d",(int)wifi2020);								  lcd_putstr(lcd);
		 		lcd_gotoxy(10,2); sprintf(lcd, "Y=%d",(int)Y_Oddo_cm[5]);						  lcd_putstr(lcd);
			}
			switch (choose_mode[2]){ // choose sub mode
			case 1 : {
				if (execute == 0){
					lcd_gotoxy(0,2);  sprintf(lcd, "RANDOM POSITION");  lcd_putstr(lcd);
					fwd_pwm_3roda_PID(0,0,0);	}
				if (execute == 1){	strategi_tendang(Angle_Ball, Range_Ball);		}
				break;}
			case 2 : {
				if (execute == 0){
					if (T_WarnaTIM == CYAN) {lcd_gotoxy(0,2);  sprintf(lcd, "PLAY CYAN");  lcd_putstr(lcd);}
					if (T_WarnaTIM == MAGENTA) {lcd_gotoxy(0,2);  sprintf(lcd, "PLAY MAGENTA");  lcd_putstr(lcd);}
					fwd_pwm_3roda_PID(0,0,0);	}
				if (execute == 1)
				{
					if (Program_Untuk == ORION) {}
					else if (Program_Untuk == HYDRA) {}
				}
				break;}
			case 3 : {
				if (execute == 0){
					lcd_gotoxy(0,2);  sprintf(lcd, "1 robot");  lcd_putstr(lcd);
					fwd_pwm_3roda_PID(0,0,0);	}
				if (execute == 1)
				{
					Mode_Main_Robot = SATU_ROBOT;
				}
				break;}
			case 4 : {
				if (execute == 0){
					lcd_gotoxy(0,2);  sprintf(lcd, "2 robot");  lcd_putstr(lcd);
					fwd_pwm_3roda_PID(0,0,0);	}
				if (execute == 1)
				{
					Mode_Main_Robot = DUA_ROBOT;
				}
				break;}
			case 5 : {
				if (execute == 0){
					lcd_gotoxy(0,2);  sprintf(lcd, "RESERVED");  lcd_putstr(lcd);
					fwd_pwm_3roda_PID(0,0,0);	}
				if (execute == 1){}
				break;}
			}
			break;}
		case 2 : {
			if (execute == 0) { lcd_gotoxy(0,1);  sprintf(lcd, "ONLINE");  lcd_putstr(lcd); }
			if (execute == 1)
			{
				lcd_gotoxy(0,0);  sprintf(lcd, "Yb=%d",(int)Angle_Ball); 						  lcd_putstr(lcd);
				lcd_gotoxy(7,0);  sprintf(lcd, "R=%d",(int)Range_Ball);  						  lcd_putstr(lcd);
		 		lcd_gotoxy(0,1);  sprintf(lcd, "pwm(%d,%d,%d)",(int)pwm_1,(int)pwm_2,(int)pwm_3); lcd_putstr(lcd);
		 		lcd_gotoxy(0,2);  sprintf(lcd, "X=%d",(int)X_Oddo_cm[5]);  						  lcd_putstr(lcd);
		 		lcd_gotoxy(10,2); sprintf(lcd, "Y=%d",(int)Y_Oddo_cm[5]);						  lcd_putstr(lcd);
//		 		lcd_gotoxy(0,3); sprintf(lcd, "S=%d",(int)State_Position);						  lcd_putstr(lcd);
		 		lcd_gotoxy(19,3); sprintf(lcd, "%d",(int)Prox);									  lcd_putstr(lcd);
		 		lcd_gotoxy(19,2); sprintf(lcd, "%d",(int)Striker_Main_Assist);					  lcd_putstr(lcd);
		 		lcd_gotoxy(17,3); sprintf(lcd, "%d",(int)wifi2020);								  lcd_putstr(lcd);
			}
			switch (choose_mode[2]){ // choose sub mode
			case 1 : {
				if (execute == 0){ lcd_gotoxy(0,2);  sprintf(lcd, "MATCH 1 MANUAL");  lcd_putstr(lcd); }
				if (execute == 1)
				{
					if (Program_Untuk == ORION) Strategi_ORION(Angle_Ball, Range_Ball);
					else if (Program_Untuk == HYDRA) Strategi_HYDRA(Angle_Ball, Range_Ball);
				}
				break;}
			case 2 : {
				if (execute == 0) {lcd_gotoxy(0,2);  sprintf(lcd, "MATCH 1 BS");  lcd_putstr(lcd);}
				if (execute == 1){ strategi_1(Angle_Ball, Range_Ball);		}
				break;}
			case 3 : {
				if (execute == 0) {lcd_gotoxy(0,2);  sprintf(lcd, "MATCH 2.1 MANUAL");  lcd_putstr(lcd);}
				if (execute == 1)
				{
					if (Program_Untuk == ORION) Strategi_ORION_MAIN(Angle_Ball, Range_Ball);
					if (Program_Untuk == HYDRA) Strategi_HYDRA_ASSIST(Angle_Ball, Range_Ball);
				}
				break;}
			case 4 : {
				if (execute == 0){lcd_gotoxy(0,2);  sprintf(lcd, "MATCH 2.2 MANUAL");  lcd_putstr(lcd);}
				if (execute == 1)
				{
					if (Program_Untuk == ORION) Strategi_ORION_ASSIST(Angle_Ball, Range_Ball);
					if (Program_Untuk == HYDRA) Strategi_HYDRA_MAIN(Angle_Ball, Range_Ball);
				}
				break;}
			case 5 : {
				if (execute == 0){lcd_gotoxy(0,2);  sprintf(lcd, "MATCH 2 BS");  lcd_putstr(lcd);}
				if (execute == 1)
				{
					strategi_2(Angle_Ball, Range_Ball, Striker_Main_Assist);
				}
				break;}
			case 6 : {
				if (execute == 0) {
					lcd_gotoxy(0,2);  sprintf(lcd, "FOLLOW BS");  lcd_putstr(lcd);
					fwd_pwm_3roda_PID(0,0,0);	Gripper_OFF();}
				if (execute == 1)
				{
					if (wifi2020 == 1)
					{
						strategi_tendang(Angle_Ball, Range_Ball);
					}
					else { fwd_pwm_3roda_PID(0,0,0); Gripper_OFF();}
				}
				break;}
			case 7 : { cnt_mode[0] = 1; break;}
			}
			break;}
		case 3 : {
			if (execute == 0) {lcd_gotoxy(0,1);  sprintf(lcd, "TAKE VIDEO");  lcd_putstr(lcd);}
			if (execute == 1)
			{
				lcd_gotoxy(0,0);  sprintf(lcd, "Yb=%d",(int)Angle_Ball); 						  lcd_putstr(lcd);
				lcd_gotoxy(7,0);  sprintf(lcd, "R=%d",(int)Range_Ball);  						  lcd_putstr(lcd);
				lcd_gotoxy(0,1);  sprintf(lcd, "pwm(%d,%d,%d)",(int)pwm_1,(int)pwm_2,(int)pwm_3); lcd_putstr(lcd);
				lcd_gotoxy(0,2);  sprintf(lcd, "X=%d",(int)X_Oddo_cm[5]);  						  lcd_putstr(lcd);
				lcd_gotoxy(10,2); sprintf(lcd, "Y=%d",(int)Y_Oddo_cm[5]);						  lcd_putstr(lcd);
				lcd_gotoxy(17,2); sprintf(lcd, "%d",(int)Tuas_Pot);							  	lcd_putstr(lcd);
				lcd_gotoxy(19,3); sprintf(lcd, "%d",(int)Prox);									  lcd_putstr(lcd);
				lcd_gotoxy(14,3); sprintf(lcd, "%d",(int)Flag_Posisi);							  lcd_putstr(lcd);
				lcd_gotoxy(15,3); sprintf(lcd, "%d",(int)FlagSiapTendang);							  lcd_putstr(lcd);

				lcd_gotoxy(17,3); sprintf(lcd, "%d",(int)wifi2020);								  lcd_putstr(lcd);
				lcd_gotoxy(0,3);  sprintf(lcd, "Sol(%d,%d,%d,%d)",
					(int)solenoid1_state,(int)solenoid2_state,(int)solenoid3_state,(int)solenoid4_state);lcd_putstr(lcd);
			}
			switch (choose_mode[2]){ // choose sub mode
			case 1 : {
				if (execute == 0) {
					lcd_gotoxy(0,2);  sprintf(lcd, "ROTATION");  lcd_putstr(lcd);
					fwd_pwm_3roda_PID(0,0,0); LED(OFF);}
				if (execute == 1){	 fwd_pwm_3roda_PID(15,15,15);	LED(BLINK);				}
				break;}
			case 2 : {
				if (execute == 0) {
					lcd_gotoxy(0,2);  sprintf(lcd, "FOLLOW BALL");  lcd_putstr(lcd);
					fwd_pwm_3roda_PID(0,0,0); }
				if (execute == 1){	Follow_Ball(Angle_Ball, Range_Ball, SP_Kamera);	}
				break;}
			case 3 : {
				if (execute == 0) {
				lcd_gotoxy(0,2);  sprintf(lcd, "shoot 50");  lcd_putstr(lcd);
				Tuas_Manual(0); c_g = 0; c_p = 0; Gripper_function(OFF,0);}
				if (execute == 1)
				{
					Gripper_function(ON,30);
					if (Tuas_Pot >= 48 && Tuas_Pot <= 52)
					{
						c_g = 1;
						if (c_p < 4) LED(BLINK_FAST);
						else if (c_p >= 4) Solenoid_Manual_4Cell_2021(1,1,1,0);
					}
					else  {Tuas_Algorithm(50,Tuas_Pot); c_g = 0; c_p = 0;}
				}
				break;}
			case 4 : {
				if (execute == 0) {
				lcd_gotoxy(0,2);  sprintf(lcd, "shoot 70");  lcd_putstr(lcd);
				Tuas_Manual(0); c_g = 0; c_p = 0; Gripper_function(OFF,0);}
				if (execute == 1)
				{
					Gripper_function(ON,30);
					if (Tuas_Pot >= 68 && Tuas_Pot <= 72)
					{
						c_g = 1;
						if (c_p < 4) LED(BLINK_FAST);
						else if (c_p >= 4) Solenoid_Manual_4Cell_2021(1,1,1,0);
					}
					else  {Tuas_Algorithm(70,Tuas_Pot); c_g = 0; c_p = 0;}
				}
				break;}
			case 5 : {
				if (execute == 0) {
				lcd_gotoxy(0,2);  sprintf(lcd, "shoot 30");  lcd_putstr(lcd);
				Tuas_Manual(0); c_g = 0; c_p = 0; Gripper_function(OFF,0);}
				if (execute == 1)
				{
					Gripper_function(ON,30);
					if (Tuas_Pot >= 28 && Tuas_Pot <= 32)
					{
						c_g = 1;
						if (c_p < 4) LED(BLINK_FAST);
						else if (c_p >= 4) Solenoid_Manual_4Cell_2021(1,1,1,0);
					}
					else  {Tuas_Algorithm(30,Tuas_Pot); c_g = 0; c_p = 0;}
				}
				break;}
			case 6 : {
				if (execute == 0) {
					lcd_gotoxy(0,2);  sprintf(lcd, "PASSING");  lcd_putstr(lcd);
					fwd_pwm_3roda_PID(0,0,0); c_g = 0, c_p = 0; Flag_Posisi = 0;
					Gripper_function(OFF,0);
				}
				if (execute == 1)	{	Take_Video_Passing();	}
				break;}
			case 7 : {
				if (execute == 0) {
					lcd_gotoxy(0,2);  sprintf(lcd, "RANDOM SHOOT");  lcd_putstr(lcd);
					fwd_pwm_3roda_PID(0,0,0);
				}
				if (execute == 1)	{	Random_Shoot_Strategy();	}
				break;}
			case 8 : {
				if (execute == 0) {
					lcd_gotoxy(0,2);  sprintf(lcd, "RANDOM POS");  lcd_putstr(lcd);
					fwd_pwm_3roda_PID(0,0,0);	Gripper_OFF();}
				if (execute == 1)	{	strategi_tendang(Angle_Ball, Range_Ball);	}
				break;}
			case 9 : {
				if (execute == 0) {
					lcd_gotoxy(0,2);  sprintf(lcd, "ROTATE GRIP");  lcd_putstr(lcd);
					fwd_pwm_3roda_PID(0,0,0);	Gripper_function(OFF,0);}
				if (execute == 1)	{	fwd_pwm_3roda_PID(15,15,15);	Gripper_function(ON,30);	}
				break;}

			}
			break;}
		case 4 : {
			lcd_gotoxy(0,1);  sprintf(lcd, "UNDER CONSTRUCTION4");  lcd_putstr(lcd);
			switch (choose_mode[2]){ // choose sub mode
			case 1 : {
				lcd_gotoxy(0,2);  sprintf(lcd, "RESERVED1");  lcd_putstr(lcd);
				if (execute == 1){	 /*put your strategy here*/		}
				break;}
			case 2 : {
				lcd_gotoxy(0,2);  sprintf(lcd, "RESERVED2");  lcd_putstr(lcd);
				if (execute == 1){	 /*put your strategy here*/		}
				break;}
			case 3 : {
				lcd_gotoxy(0,2);  sprintf(lcd, "RESERVED3");  lcd_putstr(lcd);
				if (execute == 1){	 /*put your strategy here*/		}
				break;}
			case 4 : {
				lcd_gotoxy(0,2);  sprintf(lcd, "RESERVED4");  lcd_putstr(lcd);
				if (execute == 1){	 /*put your strategy here*/		}
				break;}
			}
			break;}
		}
		break;}
	case 3 :{
		if (execute == 0) { lcd_gotoxy(0,0);  sprintf(lcd, "DEV");  lcd_putstr(lcd);}
		switch (choose_mode[1]){ // choose main mode
		case 1 : {
			lcd_gotoxy(5,0);  sprintf(lcd, "GRIP");  lcd_putstr(lcd);
			lcd_gotoxy(0,2);  sprintf(lcd, "pwm(%d,%d,%d)",(int)pwm_1,(int)pwm_2,(int)pwm_3); lcd_putstr(lcd);
			lcd_gotoxy(19,3); sprintf(lcd, "%d",Prox);  			lcd_putstr(lcd);
//		 	lcd_gotoxy(0,3); sprintf(lcd, "GL= %d",(int)Griper_Pot1);  lcd_putstr(lcd);
//		 	lcd_gotoxy(7,3); sprintf(lcd, "GR= %d",(int)Griper_Pot2);  lcd_putstr(lcd);
			lcd_gotoxy(0,3);  sprintf(lcd, "pwmr(%d,%d,%d)",(int)pwm_real_1,(int)pwm_real_2,(int)pwm_real_3); lcd_putstr(lcd);
//		 	lcd_gotoxy(17,2); sprintf(lcd, "%d",cek_count_gripper);  			lcd_putstr(lcd);
//		 	lcd_gotoxy(17,1); sprintf(lcd, "%d",Flag_steady_grip);  			lcd_putstr(lcd);

//		 	Gripper_josh(100,10,30);
//		 	GRIPPER_BARU(100,10);
			switch (choose_mode[2]){ // choose sub mode
			case 1 : {
				lcd_gotoxy(0,1);  sprintf(lcd, "MAJU");  lcd_putstr(lcd);
				if (execute == 0) {fwd_pwm_3roda_PID(0,0,0);}
				if (execute == 1)
				{	 /*put your strategy here*/
					move_angle_3roda(0,30,YES);
//					Gripper_josh(2,20);
				}
				break;}
			case 2 : {
				lcd_gotoxy(0,1);  sprintf(lcd, "MUNDUR");  lcd_putstr(lcd);
				if (execute == 0) {fwd_pwm_3roda_PID(0,0,0);}
				if (execute == 1)
				{	 /*put your strategy here*/
					move_angle_3roda(180,30,YES);
//					Gripper_josh(2,10);
				}
				break;}
			case 3 : {
				lcd_gotoxy(0,1);  sprintf(lcd, "KANAN");  lcd_putstr(lcd);
				if (execute == 0) {fwd_pwm_3roda_PID(0,0,0);}
				if (execute == 1)
				{	 /*put your strategy here*/
					move_angle_3roda(90,30,YES);
//					Gripper_josh(2,10);
				}
				break;}
			case 4 : {
				lcd_gotoxy(0,1);  sprintf(lcd, "KIRI");  lcd_putstr(lcd);
				if (execute == 0) {fwd_pwm_3roda_PID(0,0,0);}
				if (execute == 1)
				{	 /*put your strategy here*/
					move_angle_3roda(-90,30,YES);
//					Gripper_josh(2,10);
				}
				break;}
			case 5 : {
				lcd_gotoxy(0,1);  sprintf(lcd, "45");  lcd_putstr(lcd);
				if (execute == 0) {fwd_pwm_3roda_PID(0,0,0);}
				if (execute == 1)
				{	 /*put your strategy here*/
					move_angle_3roda(45,30,YES);
//					Gripper_josh(2,10);
				}
				break;}
			case 6 : {
				if (execute == 0)
				{
					lcd_gotoxy(0,1);  sprintf(lcd, "NATURAL");  lcd_putstr(lcd);
					fwd_pwm_3roda_PID(0,0,0);
				}
				if (execute == 1)
				{	 /*put your strategy here*/
			 		lcd_gotoxy(0,1);  sprintf(lcd, "X=%d",(int)X_Oddo_cm[5]);  						  lcd_putstr(lcd);
			 		lcd_gotoxy(10,1); sprintf(lcd, "Y=%d",(int)Y_Oddo_cm[5]);						  lcd_putstr(lcd);
//				 	Gripper1_OUT(10);
//				 	Gripper2_IN(18);
//			 		Gripper1_IN(30);
//				 	Gripper2_IN(30);
//			 		Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],100,100,500,X_Oddo_cm[5]);
					cek_lapangan();
//					Gripper_josh(2,10);
//			 		Flag_cek_count_gripper = 1;
//			 		if (cek_count_gripper <= 50)
//			 		{
//			 			Gripper1_IN(20);
//			 			Gripper2_IN(20);
//			 		}
//			 		else if (cek_count_gripper > 50 && cek_count_gripper <= 100)
//			 		{
//			 			Gripper1_OUT(20);
//			 			Gripper2_OUT(20);
//			 		}
//			 		else { cek_count_gripper = 0;}
				}
				break;}
			case 7 : {
				if (execute == 0)
				{
					lcd_gotoxy(0,1);  sprintf(lcd, "CEK");  lcd_putstr(lcd);
					fwd_pwm_3roda_PID(0,0,0);
				}
				if (execute == 1)
				{	 /*put your strategy here*/
//			 		lcd_gotoxy(0,1);  sprintf(lcd, "X=%d",(int)X_Oddo_cm[5]);  						  lcd_putstr(lcd);
//			 		lcd_gotoxy(10,1); sprintf(lcd, "Y=%d",(int)Y_Oddo_cm[5]);						  lcd_putstr(lcd);
					cek_gripper();
				}
				break;}
			}
			break;}
		case 2 : {
			lcd_gotoxy(5,0);  sprintf(lcd, "RPM");  lcd_putstr(lcd);
			if (execute == 1)
			{
				lcd_gotoxy(0,1);  sprintf(lcd, "pwm(%d,%d,%d)",(int)pwm_1,(int)pwm_2,(int)pwm_3); lcd_putstr(lcd);
				lcd_gotoxy(0,2);  sprintf(lcd, "RPM1= %d",(int)rt0_m1.Rpm2); lcd_putstr(lcd);
				lcd_gotoxy(6,3);  sprintf(lcd, "RPM2= %d",(int)rt0_m2.Rpm2); lcd_putstr(lcd);
				lcd_gotoxy(10,2);  sprintf(lcd, "RPM3= %d",(int)rt0_m3.Rpm2); lcd_putstr(lcd);
			}
			if (execute == 0) fwd_pwm_3roda(0,0,0);
			switch (choose_mode[2]){ // choose sub mode
			case 1 : {
				if (execute == 0) {lcd_gotoxy(0,1);  sprintf(lcd, "30");  lcd_putstr(lcd);}
				if (execute == 1)
				{	 /*put your strategy here*/
					fwd_pwm_3roda_PID(30,30,30);
				}
				break;}
			case 2 : {
				if (execute == 0) {lcd_gotoxy(0,1);  sprintf(lcd, "-30");  lcd_putstr(lcd);}
				if (execute == 1)
				{	 /*put your strategy here*/
					fwd_pwm_3roda_PID(-30,-30,-30);
				}
				break;}
			case 3 : {
				if (execute == 0) {lcd_gotoxy(0,1);  sprintf(lcd, "50");  lcd_putstr(lcd);}
				if (execute == 1)
				{	 /*put your strategy here*/
					fwd_pwm_3roda_PID(50,50,50);
				}
				break;}
			case 4 : {
				if (execute == 0) {lcd_gotoxy(0,1);  sprintf(lcd, "-50");  lcd_putstr(lcd);}
				if (execute == 1)
				{	 /*put your strategy here*/
					fwd_pwm_3roda_PID(-50,-50,-50);
				}
				break;}
			}
			break;}
		case 3 : {
			lcd_gotoxy(0,1);  sprintf(lcd, "koor");  lcd_putstr(lcd);
				lcd_gotoxy(0,2);  sprintf(lcd, "pwm(%d,%d,%d)",(int)pwm_1,(int)pwm_2,(int)pwm_3); lcd_putstr(lcd);
				lcd_gotoxy(0,3);  sprintf(lcd, "X=%d",(int)X_Oddo_cm[5]);  						  lcd_putstr(lcd);
		 		lcd_gotoxy(10,3); sprintf(lcd, "Y=%d",(int)Y_Oddo_cm[5]);						  lcd_putstr(lcd);
		 		lcd_gotoxy(19,2); sprintf(lcd, "%d",Flag_Posisi);						  lcd_putstr(lcd);
		 		lcd_gotoxy(19,3); sprintf(lcd, "%d",Flag_tahan);						  lcd_putstr(lcd);

			if (execute == 0) fwd_pwm_3roda(0,0,0);
			switch (choose_mode[2]){ // choose sub mode
			case 1 : {
				lcd_gotoxy(6,1);  sprintf(lcd, "A");  lcd_putstr(lcd);
				if (execute == 1)
				{	 /*put your strategy here*/
					Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],0,0,500,X_Oddo_cm[5]);
				}
				break;}
			case 2 : {
				lcd_gotoxy(6,1);  sprintf(lcd, "B");  lcd_putstr(lcd);
				if (execute == 1)
				{	 /*put your strategy here*/
					Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],400,0,500,X_Oddo_cm[5]);
				}
				break;}
			case 3 : {
				lcd_gotoxy(6,1);  sprintf(lcd, "C");  lcd_putstr(lcd);
				if (execute == 1)
				{	 /*put your strategy here*/
					Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],400,400,500,X_Oddo_cm[5]);
				}
				break;}
			case 4 : {
				lcd_gotoxy(6,1);  sprintf(lcd, "D");  lcd_putstr(lcd);
				if (execute == 1)
				{	 /*put your strategy here*/
					Move_Koordinat_3roda(Y_Oddo_cm[5],X_Oddo_cm[5],0,400,500,X_Oddo_cm[5]);
				}
				break;}
			case 5 : {
				lcd_gotoxy(6,1);  sprintf(lcd, "CEK");  lcd_putstr(lcd);
				if (execute == 1)
				{
					cek_lapangan();
				}
				break;}
			case 6 : { cnt_mode[0] = 1; break;}
			}
			break;}
		case 4 : {
			if (execute == 0) {lcd_gotoxy(0,1);  sprintf(lcd, "FOLLOW");  lcd_putstr(lcd);}
			if (execute == 1)
			{
				lcd_gotoxy(0,0);  sprintf(lcd, "Yb=%d",(int)Angle_Ball); 						  lcd_putstr(lcd);
				lcd_gotoxy(7,0);  sprintf(lcd, "R=%d",(int)Range_Ball);  						  lcd_putstr(lcd);
		 		lcd_gotoxy(0,1);  sprintf(lcd, "pwm(%d,%d,%d)",(int)pwm_1,(int)pwm_2,(int)pwm_3); lcd_putstr(lcd);
		 		lcd_gotoxy(0,2);  sprintf(lcd, "X=%d",(int)X_Oddo_cm[5]);  						  lcd_putstr(lcd);
		 		lcd_gotoxy(10,2); sprintf(lcd, "Y=%d",(int)Y_Oddo_cm[5]);						  lcd_putstr(lcd);
			}
			switch (choose_mode[2]){ // choose sub mode
			case 1 : {
				if (execute == 0)
				{
					lcd_gotoxy(7,1);  sprintf(lcd, "BALL");  lcd_putstr(lcd);
					fwd_pwm_3roda_PID(0,0,0);
				}
				if (execute == 1){	 Follow_Ball(Angle_Ball, Range_Ball,SP_Kamera);		}
				break;}
			case 2 : {
				if (execute == 0)
				{
					lcd_gotoxy(7,1);  sprintf(lcd, "BOLA");  lcd_putstr(lcd);
					fwd_pwm_3roda_PID(0,0,0);
				}
				if (execute == 1){	 Follow_Bola(Angle_Ball, Range_Ball,SP_Kamera);		}
				break;}
			case 3 : {
				lcd_gotoxy(0,2);  sprintf(lcd, "RESERVED3");  lcd_putstr(lcd);
				if (execute == 1){	 /*put your strategy here*/		}
				break;}
			case 4 : {
				lcd_gotoxy(0,2);  sprintf(lcd, "RESERVED4");  lcd_putstr(lcd);
				if (execute == 1){	 /*put your strategy here*/		}
				break;}
			}
			break;}
		}
	break;}
	}
}
