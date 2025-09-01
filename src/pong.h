/**
 * @file pong.h
 * @brief Definitions for the Pong game.
 *
 * @author DannyXjsu
 * @version 1.1
 * @date 2025-09-01
 */

#ifndef PONG_H_
#define PONG_H_

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

#include "utils.h"
#include "math.h"


extern Color background;
extern Color foreground;

/**
 * Event for when a player scores.
 */
extern void score(void);

extern void pong_initialize();

extern void pong_process();

extern void pong_render();

#endif // PONG_H_
