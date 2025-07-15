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

double clamp(double d, double min, double max) {
  const double t = d < min ? min : d;
  return t > max ? max : t;
}
