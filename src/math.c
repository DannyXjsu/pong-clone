/**
 * @file math.c
 */

#include <math.h>
#include "math.h"

inline float length(Vector2 *vector) {
    return sqrtf(vector->x * vector->x + vector->y * vector->y);
}

inline void normalize(Vector2 *vector) {
    const float _length = length(vector);
    vector->x = _length == 0.0f ? 0.0 : vector->x / _length;
    vector->y = _length == 0.0f ? 0.0 : vector->y / _length;
}

inline float dot(Vector2 *vector1, Vector2 *vector2){
    return vector1->x * vector2->x + vector1->y * vector2->y;
}

inline int inverti(int num){
    return num *= -1;
}

inline float invertf(float num){
    return num *= -1.0f;
}

inline double invertd(double num){
    return num *= (double)-1.0;
}

inline int clampi(int n, int min, int max) {
    const int t = n < min ? min : n;
    return t > max ? max : t;
}

inline float clampf(float n, float min, float max) {
    const float t = n < min ? min : n;
    return t > max ? max : t;
}

inline double clampd(double n, double min, double max) {
    const double t = n < min ? min : n;
    return t > max ? max : t;
}
