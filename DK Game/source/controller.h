#ifndef controller
#define controller

void Init_GPIO();
//void initSNES();
void Write_Latch(int pin, int w);
void Write_Clock(int pin, int w);
int Read_Data(int pin);
void wait(unsigned int s);
void SNES(unsigned int* buttons);

#endif