#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>

typedef enum{
    INPUT=1,
    OUTPUT=0
} gpio_dir_t;

typedef enum{
    HIGH = 1,
    LOW = 0
} gpio_write_t;

#endif 