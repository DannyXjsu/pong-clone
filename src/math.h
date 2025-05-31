#ifndef MATH_H_
#define MATH_H_

typedef struct {
  union {
    struct {
      float x;
      float y;
    };
    struct {
      float w;
      float h;
    };
    // Access x or y like an array
    float v[2];
  };
} Vector2;

extern float length(Vector2 *vector);
extern Vector2 normalize(Vector2 *vector);
extern float invertf(float num);

#endif // MATH_H_
