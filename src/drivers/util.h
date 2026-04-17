#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>
#include <stdbool.h>

typedef enum{
    INPUT=1,
    OUTPUT=0
} gpio_dir_t;

typedef enum{
    HIGH = 1,
    LOW = 0
} gpio_write_t;


// //itoa implementation
// void reverse(char str[], int length)
// {
//     int start = 0;
//     int end = length - 1;
//     while (start < end) {
//         char temp = str[start];
//         str[start] = str[end];
//         str[end] = temp;
//         end--;
//         start++;
//     }
// }

// char* citoa(int num, char* str, int base)
// {
//     int i = 0;
//     bool isNegative = false;
    
//     if (num == 0) {
//         str[i++] = '0';
//         str[i] = '\0';
//         return str;
//     }

//     if (num < 0 && base == 10) {
//         isNegative = true;
//         num = -num;
//     }

//     while (num != 0) {
//         int rem = num % base;
//         str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
//         num = num / base;
//     }
    
//     if (isNegative)
//         str[i++] = '-';

//     str[i] = '\0'; 
//     reverse(str, i);

//     return str;
// }

#endif 