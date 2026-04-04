#include "gpio.h"
#include "timer.h"
#include "uart.h"
#include "motor.h"
#include "ir.h"


int main(){
    motor_init();
    while(1){
        motor_right(FORWARD,100);
        motor_left(REVERSE,100);
    }
    
    return 0;
}