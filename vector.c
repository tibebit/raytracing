// Fabio Tiberio SM3201378
#include "vector.h"

float vector_length(Vector v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float dot_product(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector normalize(Vector v) {
    float length = vector_length(v);
    return (Vector){v.x/length, v.y/length,v.z/length};
}

Vector subtract(Vector a, Vector b) {
    return (Vector){a.x - b.x, a.y - b.y, a.z - b.z};
}