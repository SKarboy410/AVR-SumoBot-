#include "vision.h"
#include "ultrasonic.h"


static uint16_t dist[3] = {0};

uint16_t filter_dist(uint16_t new, uint16_t old){

    if(old != 0 &&  abs((int)new - (int)old) > 50)
        return old;
    
    return new;

}

void vision_update(){
    ultrasonic_update();

    // Front
    if(ultrasonic_main_ready()){
        uint16_t raw = ultrasonic_main_get_dist();
        dist[0] = filter_dist(raw,dist[0]);
    }

    // Left
    if(ultrasonic_side[0].ready){
        uint16_t raw = ultrasonic_side_get_dist(0);
        dist[1] = filter_dist(raw,dist[1]);
    }

    // Right
    if(ultrasonic_side[1].ready){
        uint16_t raw = ultrasonic_side_get_dist(1);
        dist[2] = filter_dist(raw,dist[2]);
    }
}

uint16_t get_dist(us_dir dir){
    if(dir == MAIN)
        return dist[0];
    else if(dir == LEFT)
        return dist[1];
    else if(dir == RIGHT)
        return dist[2];
    else
        return 0;
}
