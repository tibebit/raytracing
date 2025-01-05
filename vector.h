// Fabio Tiberio SM3201378
#ifndef VECTOR_H
#define VECTOR_H
#include <math.h>

typedef struct {
    float x;
    float y;
    float z;
} Vector;

float dot_product(Vector a, Vector b);
Vector normalize(Vector v);
Vector subtract(Vector a, Vector b);

#endif
