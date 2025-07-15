#include <SDL3/SDL_timer.h>
#include <stdio.h>

#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "app.h"
#include "pong.h"

Uint64 previous_time = 0;
Uint64 current_time = 0;

/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    // ###### Initialize SDL ######

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    if (!SDL_CreateWindowAndRenderer(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, 0,
                                     &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderVSync(renderer, false);

    // ###### Initialize pong stuff ######
    initialize_players();
    initialize_ball();

    current_time = SDL_GetPerformanceCounter();

    return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    switch (event->type) {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS; /* end the program, reporting success to the OS. */
        break;
    }
    return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate) {
    // Getting delta time
    previous_time = current_time;
    current_time = SDL_GetPerformanceCounter();
    // Usually the ticks or "counter" is multiplied by 1000 to convert ms to seconds, but that gives me weird results,
    // multiplying by 60 seems more stable and how it felt like using VSync
    float dt = (double)((current_time - previous_time)*60 / (double)SDL_GetPerformanceFrequency());

    process_players(dt);
    process_ball(dt);

    // ###### Rendering ######
    SDL_SetRenderDrawColorFloat(
        renderer, 0.0, 0.0, 0.0,
        SDL_ALPHA_OPAQUE_FLOAT); /* new color, full alpha. */

    /* clear the window to the draw color. */
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColorFloat(renderer, 1.0, 1.0, 1.0, SDL_ALPHA_OPAQUE_FLOAT);

    SDL_SetRenderScale(renderer, 2.0, 2.0);
    SDL_RenderDebugTextFormat(renderer, (((float)WINDOW_WIDTH) / 3) / 2, 16,
                              "%u", player[0].points);
    SDL_RenderDebugTextFormat(renderer,
                              (WINDOW_WIDTH - ((float)WINDOW_WIDTH) / 3) / 2, 16,
                              "%u", player[1].points);

    SDL_SetRenderScale(renderer, 1, 1);
    render_players(renderer);
    render_ball(renderer);
    render_center_line(renderer);

    /* put the newly-cleared rendering on the screen. */
    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    /* SDL will clean up the window/renderer for us. */
}
