#include "ultrasonic.h"

//code taken from MatGonPer 

void ultrasonic_init(void);
void ultrasonic_trigger(void);
uint8_t ultrasonic_ready(void);

uint16_t ultrasonic_get_dist(void); 