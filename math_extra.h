#pragma once

#include <math.h>


// True if lower < x < upper
int in_range(int x, int lower, int upper);

// Clamps the value of x to the range [-limit, limit]
float clamp(float x, float limit);

// Returns the sign of x (-1, 0, or 1).
int sgn(float x);

// Returns either -1.0 or 1.0, randomly
//float coin_flip();

//calculate the magnitude of the cross product
float cross(float x1, float y1,float x2,float y2);