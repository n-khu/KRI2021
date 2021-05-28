#ifndef ENSPARTAN_PUSHBUTTON_H
#define ENSPARTAN_PUSHBUTTON_H

extern int execute, Flag_mt;
extern int Flag_action;
extern int cnt_mode[10];
extern int choose_mode[3];

void main_pushbutton(int up, int down, int ok, int back, int R_up, int R_down);
void choose_action(int up, int down, int ok, int back, int R_up, int R_down);

#endif
