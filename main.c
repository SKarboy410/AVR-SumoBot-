#include <util/delay.h>

#include "gpio.h"
#include "timer.h"

int main(){        
    gpio_set(LED_BUILTIN,OUTPUT);
    timer0_init();
    while(1){
        if(delay_ms(1000))
            gpio_toggle(LED_BUILTIN);
            
    }
    
    return 0;
    
}