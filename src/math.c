/**
 * @file math.c
 */

#include <math.h>
#include "math.h"

inline float length(Vector2 *vector) {
    return sqrtf(vector->x * vector->x + vector->y * vector->y);
}

inline Vector2 normalize(Vector2 *vector) {
    const float _length = length(vector);
    if (_length == 0.0f)
        return (Vector2){0, 0};
    return (Vector2){vector->x / _length, vector->y / _length};
}

inline float invertf(float num){
    return num *= -1.0;
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
