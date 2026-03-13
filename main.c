#include <avr/io.h>
#include <util/delay.h>

#include "gpio.h"

int main(){
    gpio_init();
    gpio_set(LED_BUILTIN,OUTPUT); 
    while(1){
        gpio_toggle(LED_BUILTIN);
        _delay_ms(1000);
    }
    return 0;
    
}