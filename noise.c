#include "noise.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


float noise_buffer[64*1024];
int noise_position;
int noise_length;


//-----------------------------------------------------------
// Initialise noise buffer

void noise_init() {
    noise_position = 0;
    noise_length = 1024*64;

    for (int x=0; x<noise_length-1; x++) {
        noise_buffer[x] = ((float)(rand() % 65536)/32768)-1;
    }
}

//-----------------------------------------------------------
// Initialise noise buffer

float noise_tick() {
    float out = noise_buffer[noise_position];
    noise_position++;

    if (noise_position > noise_length-1)
        noise_position = 0;

    return out;
}

//-----------------------------------------------------------
// Initialise noise buffer

void noise_cleanup() {
}
