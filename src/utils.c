#include "utils.h"

SDL_FRect vec_to_rect(Vector2* pos, Vector2* size){
    return (SDL_FRect){pos->x, pos->y, size->w, size->h};
}