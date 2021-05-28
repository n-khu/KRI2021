#include <include_lib.h>


int main(void)
{
	inisialisasi_universal();
	kalibrasi_lapangan();
	setting_robot();

    while(1)
    {
//    	LED(BLINK);
    	USART4_send();
    	Odometry_Rotary();
//    	SetMode();
//    	Mode_Striker();
    	Mode_Striker_2();
    	if (Counter_Clear_LCD >= 5) ENSPARTAN_LCD_CLEAR();
    }
}

