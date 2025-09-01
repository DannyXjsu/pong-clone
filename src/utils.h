#ifndef UTILS_H_
#define UTILS_H_

#include "math.h"
#include <SDL3/SDL_rect.h>

#define var2str(var) #var

typedef struct
{
    float r;
    float g;
    float b;
    float a;
} Color;

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} Color8;

extern Color8 color_to_color8(Color* col);

extern Color color8_to_color(Color8* col);

extern SDL_FRect vec_to_rect(Vector2* pos, Vector2* size);

extern int binary_search(int arr[], int max, int target);

#endif