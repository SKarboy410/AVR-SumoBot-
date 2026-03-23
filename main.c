#include "gpio.h"
#include "timer.h"
#include "uart.h"

int main(){
    timer0_init();    
    uart_init();
    while(1){
        if(delay_ms(1000)){
            printNum(999);
            printStr("\n");
        }
            
    }
    
    return 0;
    
}