#include "drivers/gpio.h"
#include "drivers/timer.h"
#include "drivers/uart.h"
#include "drivers/motor.h"
#include "drivers/ir.h"
#include "drivers/ultrasonic.h"

#include <util/delay.h>
#include <stdlib.h>

int main(void) {
    timer0_init();
    uart_init();
    ultrasonic_init();

    uint16_t front = 0;
    uint16_t left  = 0;
    uint16_t right = 0;

    while (1) {

        ultrasonic_update();
      
        if (ultrasonic_main_ready())
            front = ultrasonic_main_get_dist();
        
        if (us[0].ready)
            left = ultrasonic_side_get_dist(0);
        
        if (us[1].ready)
            right = ultrasonic_side_get_dist(1);
        
        printNum(right);
        printStr("\n");   
    

        _delay_ms(100);
    }
}