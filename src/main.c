#include "drivers/gpio.h"
#include "drivers/timer.h"
#include "drivers/uart.h"
#include "drivers/motor.h"
#include "drivers/ir.h"
#include "drivers/ultrasonic.h"

#include "app/vision.h"

#include <util/delay.h>
#include <stdlib.h>

int main(void) {
    timer0_init();
    uart_init();
    ultrasonic_init();

    while (1) {
        vision_update();
        if(get_dist(FRONT) < 5){
            printStr("FRONT");
            printStr("\n");
            _delay_ms(100);
        }
        else if(get_dist(LEFT) < 5){
            printStr("LEFT");
            printStr("\n");
            _delay_ms(100);
        }
        else if(get_dist(RIGHT) < 5){
            printStr("RIGHT");                                           
            printStr("\n");
            _delay_ms(100);
        }

    }
}