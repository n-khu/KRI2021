#include "enspartan_pushbutton.h"

int Flag_pushbutton;
int execute, Flag_mt;
int cnt_mode[10];
int choose_mode[3];

int Flag_action = 0;
int x = 3;	// sesuaikan dengan jumlah global mode
int y = 6;	// sesuaikan dengan jumlah main mode
int z = 12;	// sesuaikan dengan jumlah sub mode

//////////////////////////////////////
// choose_mode[0] for global mode	//
// choose_mode[1] for main mode		//
// choose_mode[2] for sub mode		//
//////////////////////////////////////

void main_pushbutton(int up, int down, int ok, int back, int R_up, int R_down)
{
	if (up && Flag_pushbutton == 0)
	{
		Flag_pushbutton = 1;
		cnt_mode[0]++;
	}
	else if (down && Flag_pushbutton == 0)
	{
		Flag_pushbutton = 1;
		cnt_mode[0]--;
	}
	else if(ok && Flag_pushbutton == 0)
	{
		Flag_pushbutton = 1;
		Flag_mt = 1;
		cnt_mode[2] = 0;
		cnt_mode[1] = 1;
	}
	else if (back && Flag_pushbutton == 0)
	{
		Flag_pushbutton = 1;
		cnt_mode[1] = 2;
	}
	else if (R_up && Flag_pushbutton == 0)
	{
		Flag_pushbutton = 1;
		cnt_mode[2]++;
	}
	else if (R_down && Flag_pushbutton == 0)
	{
		Flag_pushbutton = 1;
		cnt_mode[2]--;
	}
	if (up == 0 && down == 0 && ok == 0 && back == 0 && R_up == 0 && R_down == 0 && Flag_pushbutton == 1)
	{
		Flag_pushbutton = 0;
		Flag_mt = 0;
		cnt_mode[1] = 0;
	}
}
void choose_action(int up, int down, int ok, int back, int R_up, int R_down)
{
	main_pushbutton(up, down, ok, back, R_up, R_down);

	if (Flag_action == 0)
	{
		choose_mode[0] = cnt_mode[0];
		if (cnt_mode[0] > x) cnt_mode[0] = 1;
		else if (cnt_mode[0] <= 0) cnt_mode[0] = x;
		if (cnt_mode[1] == 1)
		{
			cnt_mode[0] = 1;
			cnt_mode[1] = 0;
			Flag_action++;
		}
	}
	else if (Flag_action == 1)
	{
		choose_mode[1] = cnt_mode[0];
		if (cnt_mode[0] > y) cnt_mode[0] = 1;
		else if (cnt_mode[0] <= 0) cnt_mode[0] = y;
		if (cnt_mode[1] == 1)
		{
			cnt_mode[0] = 1;
			cnt_mode[1] = 0;
			Flag_action++;
		}
		else if (cnt_mode[1] == 2)
		{
			cnt_mode[0] = choose_mode[0];
			choose_mode[1] = 0;
			cnt_mode[1] = 0;
			Flag_action--;
		}
	}
	else if (Flag_action == 2)
	{
		choose_mode[2] = cnt_mode[0];
		if (cnt_mode[0] > z) cnt_mode[0] = 1;
		else if (cnt_mode[0] <= 0) cnt_mode[0] = z;
		if (cnt_mode[1] == 1)
		{
			cnt_mode[1] = 0;
			execute = 1;
			Flag_action++;
		}
		else if (cnt_mode[1] == 2 && execute == 0)
		{
			cnt_mode[0] = choose_mode[1];
			choose_mode[2] = 0;
			cnt_mode[1] = 0;
			Flag_action--;
		}
	}
	else if (Flag_action == 3)
	{
		if (cnt_mode[1] == 2 && execute == 1)
		{
			cnt_mode[0] = choose_mode[2];
			cnt_mode[1] = 0;
			execute = 0;
			Flag_action--;
		}
	}
}
