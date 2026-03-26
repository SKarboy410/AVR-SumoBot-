#include "gpio.h"
#include "timer.h"
#include "uart.h"
#include "pwm.h"

#include <util/delay.h>

int main(){
    pwm_init();
    while(1){
        pwm_set_duty_cycle(MOTOR1_EN,1);
        pwm_set_duty_cycle(MOTOR2_EN,69);
        
    }
    
    return 0;
    
}