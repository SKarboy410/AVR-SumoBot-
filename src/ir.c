#include "ir.h"
#include "gpio.h"

void ir_init(){
    gpio_write(IR1,HIGH);
    gpio_write(IR2,HIGH);

}

uint8_t ir_read(ir_dir ir){
    if(ir == FRONT)
        return !gpio_read(IR1);
    else if(ir == BACK)
        return !gpio_read(IR2);
    else
        return 0;
}