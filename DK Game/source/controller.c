#include "controller.h"
#include "uart.h"


//Constant values and base addresses
#define CLK 11
#define LAT 9
#define DAT 10
#define INPUT 0
#define OUTPUT 1

#define GPIO_BASE   0xFE200000
#define CLO_REG 0xFE003004     
#define GPSET0  7
#define GPCLR0  10
#define GPLEV0  13
unsigned *gpio = (unsigned*)GPIO_BASE;
unsigned *clo = (unsigned*)CLO_REG;


#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |= (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))


//initializing the gpio lines
void Init_GPIO(){
    INP_GPIO( CLK ); // CLK
    OUT_GPIO( CLK );
    INP_GPIO( LAT ); // LATCH
    OUT_GPIO( LAT );
    INP_GPIO( DAT ); // DATA
}

//method that writes to the latch line
void Write_Latch(int pin, int w){
    if(w==1){
        gpio[GPSET0] = 1 << pin;
    }
    else {
        gpio[GPCLR0] = 1 << pin;
    }
}

//method that reads form the clock line
void Write_Clock(int pin, int w){
     if(w==1){
        gpio[GPSET0] = 1 << pin;
    }
    else {
        gpio[GPCLR0] = 1 << pin;
    }
}

//method that reads from the data line
int Read_Data(int pin){
    int v;
    v = (gpio[GPLEV0]>>pin)&1;
    return v;

}

//method that waits for a given time interval, passed in as a parameter
void wait(unsigned int s){
    unsigned c = *clo + s;
    while(c > *clo);
}

// reads the buttons presssed and then stores them in an array
void SNES(unsigned int* buttons){

    //writes 1 to the clock line
    Write_Clock(CLK, 1);
    //writes 1 to the latch line
    Write_Latch(LAT, 1);
    //waits for 12 microseconds
    wait(12);
    //writes 0 to the latch line
    Write_Latch(LAT, 0);
    //loops through the buttons array
    for(int i = 1; i<= 16; i++){
        //waits for 6 microseconds
        wait(6);
        //writes 0 to the clock line
        Write_Clock(CLK, 0);
        //waits for 6 microseconds
        wait(6);
        //stores the value read from the data line in b
        int b = Read_Data(DAT);
        //sets the array at the given index to b
        buttons[i] = b;
        //writes 1 to the clock line
        Write_Clock(CLK, 1);
    }
}