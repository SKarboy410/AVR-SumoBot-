#include <util/delay.h>

#include "gpio.h"
#include "timer.h"
#include "uart.h"

int main(){
    timer0_init();    
    uart_init();
    gpio_set(LED_BUILTIN,OUTPUT);
        while(1){
        if(delay_ms(1000)){
            gpio_toggle(LED_BUILTIN);
            printByte(gpio_read(LED_BUILTIN));
            printStr("\n");

        }
    }
    
    return 0;
    
}