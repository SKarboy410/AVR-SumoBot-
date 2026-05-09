#ifndef VISION_H
#define VISION_H

#include "util.h"

typedef enum{
    MAIN,
    LEFT,
    RIGHT
}us_dir;

uint16_t filter_dist(uint16_t new, uint16_t old);
void vision_update();
uint16_t get_dist(us_dir dir);


#endif