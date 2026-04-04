#ifndef IR_H
#define IR_H

#include "util.h"

typedef enum{
    FRONT,
    BACK
} ir_dir;

void ir_init();
uint8_t ir_read(ir_dir ir);

#endif