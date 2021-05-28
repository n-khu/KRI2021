#ifndef ENSPARTAN_ALGORITHM_H
#define ENSPARTAN_ALGORITHM_H

void Parsing_Data(void);
void Parsing_Data_Online(void);
void Parsing_Data_Offline(void);
void Hitung_Pengali_Terpisah();
void Hitung_Pengali();
void kecepatan_robot();
void Counter_Start_Wifi(void);
void convert_encoder();
void Odometry_Ball_Selection(void);
void Waktu_Solenoid();
void Gripper_Lepas();
void ProxMode();
void LED (int state);
void Odometry_Rotary(void);

//**************** FUNGSI SOLENOID ***************************//
void Solenoid_Manual_2021(int S1, int S2, int S3, int S4, int S5);
void Solenoid_Manual_4Cell_2021(int S1, int S2, int S3, int S4);
void SOLENOID_ALGORITHM(int kondisi, int jumlah, int mode);
void SOLENOID_ALGORITHM_4Cell(int kondisi, int jumlah, int mode);

//**************** FUNGSI CONVERT ***************************//
void convert_Rpm_2_PWM(int speed1, int speed2, int speed3);

//**************** FUNGSI GRIPPER ***************************//
void Gripper1_IN(int PWM_Gripper_Kiri);
void Gripper1_OUT(int PWM_Gripper_Kiri);
void Gripper1_OFF();
void Gripper2_IN(int PWM_Gripper_Kanan);
void Gripper2_OUT(int PWM_Gripper_Kanan);
void Gripper2_OFF();
void Gripper_OFF();
void Gripper_IN(int PWM_Gripper);
void Gripper_OUT(int PWM_Gripper);
void Gripper_NATURAL(int PWM_Gripper);
void Gripper_function(int mode_gripper, int spd_grip);

void Gripper_MAJU(int PWM_Gripper_kiri, int PWM_Gripper_kanan);
void Gripper_MUNDUR(int PWM_Gripper_kiri, int PWM_Gripper_kanan);
void Gripper_KANAN(int PWM_Gripper_kiri, int PWM_Gripper_kanan);
void Gripper_KIRI(int PWM_Gripper_kiri, int PWM_Gripper_kanan);
void Natural_gripper (int direction, int spd_grip_kiri, int spd_grip_kanan);
float posisi_grip(float Setpoint, float feedback, float K_p, float K_i, float K_d );
void state_grip();
void steady_grip();
void Gripper_josh(int distance_ball, int set_distance_ball, int spd_grip);
void GRIPPER_BARU(int distance_ball, int set_distance_ball);
void waktu_cek_gripper();
void cek_gripper();
void fuzzy_input(int L_grip, int R_grip);
int fuzzy_output_left(int L_grip, int R_grip);
int fuzzy_output_right(int L_grip, int R_grip);
int fuzzy_pwm_gripper(int value_grip);
void fuzzy_gripper();
//**********************************************************//

//******************* FUNGSI TUAS ***************************//
void Feedback_Tuas();
void Tuas_Manual(int spd_tuas);
void Setting_Tuas(int Sp_Tuas);
float PID_Tuas(float setpoint, float feedback ,float K_p,float K_i);
void Tuas_Algorithm(int Sp_Tuas, int Feedback_Tuas);
//**********************************************************//

void fwd_pwm_3roda(int speed1,int speed2,int speed3);
void fwd_pwm_3roda_PID(int speed1,int speed2,int speed3);
void move_angle_3roda(double theta,int speed, int move);
int koordinat_to_sudut(int x0, int y0, int x1, int y1);
void Follow_Ball(int sud, int jar, int set);
void Follow_Bola(int sud, int jar, int set);
void Move_Koordinat_3roda(int x0, int y0, int x1, int y1, int x2, int y2);

//******************* FUNGSI ROTASI *************************//

int Hadap(int Setpoint);
void Rotate_To_Sudut(int sp_yaw);
void Rotate_To_cm(int x, int y, int ball, int penendang_rotate);
void Rotate_Kick(int x, int y, int kick);
void Rotate_To_Ball();
void receive_ball(int Sud, int hadap);
//**********************************************************//

float PID_function(float erroorrr ,float K_p,float K_i);
float PID_motor_1(float setpoint, float feedback ,float K_p,float K_i);
float PID_motor_2(float setpoint, float feedback ,float K_p,float K_i);
float PID_motor_3(float setpoint, float feedback ,float K_p,float K_i);

//******************** STRATEGI TAHUN 2021 *****************//
//---------------------TANPA KAMERA DAN BS------------------//

void cek_lapangan();

void Strategi_HYDRA(int Sud_Bola, int Jar_Bola);
void Strategi_ORION(int Sud_Bola, int Jar_Bola);
void strategi_1(int Sud_Bola, int Jar_Bola);

void Strategi_ORION_MAIN(int Sud_Bola, int Jar_Bola);
void Strategi_ORION_ASSIST(int Sud_Bola, int Jar_Bola);
void Strategi_ORION2(int Sud_Bola, int Jar_Bola, int Data_Main_Assist);
void Strategi_HYDRA_MAIN(int Sud_Bola, int Jar_Bola);
void Strategi_HYDRA_ASSIST(int Sud_Bola, int Jar_Bola);
void Strategi_HYDRA2(int Sud_Bola, int Jar_Bola, int Data_Main_Assist);

void Reset_Strategi2_ORION(int Data_Main_Assist);
void Reset_Strategi2_HYDRA(int Data_Main_Assist);
void strategi_2(int Sud_Bola, int Jar_Bola, int Data_Main_Assist);

void get_position(int koor_x, int koor_Y);
void strategi_tendang(int sudut_bola, int jarak_bola);
//----------------------------------------------------------//

void KICKOFF_KANAN_ORION(int Sud_Bola, int Jar_Bola);
void KICKOFF_KANAN_HYDRA(int Sud_Bola, int Jar_Bola);
void KICKOFF_KIRI_ORION(int Sud_Bola, int Jar_Bola);
void KICKOFF_KIRI_HYDRA(int Sud_Bola, int Jar_Bola);

//**********************************************************//
void Mode_Striker();
void Mode_Striker_2();


#endif
