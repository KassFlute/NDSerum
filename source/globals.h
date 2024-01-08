#pragma once

#include <nds.h>

extern int16_t main_buffer[4800]; // main buffer storing the sound (to be copied to the stream buffer)
extern int main_buffer_length;    // main buffer length (in samples)

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

// All the wave types
typedef enum {
    SAW_WAVE,
    SIN_WAVE,
    WHITE_NOISE,
    SQUARE_WAVE
} WaveType;

// Type capable of storing multiple types of data in the same variable
union DataUnion {
    float f;
    int i;
    WaveType w;
    unsigned char bytes[4];
};
