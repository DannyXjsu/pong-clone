#include "app.h"
#include "pong.h"
#include <SDL3/SDL_timer.h>

Uint64 previous_time = 0;
Uint64 current_time = 0;

inline void app_initialize()
{
    // Initialize pong stuff
    initialize_players();
    initialize_ball();

    current_time = SDL_GetPerformanceCounter();
}

inline void app_process()
{
    // Getting delta time
    previous_time = current_time;
    current_time = SDL_GetPerformanceCounter();
    // Usually the ticks or "counter" is multiplied by 1000 to convert ms to seconds, but that gives me weird results,
    // multiplying by 60 seems more stable and how it felt like using VSync
    float dt = (double)((current_time - previous_time)*60 / (double)SDL_GetPerformanceFrequency());

    process_players(dt);
    process_ball(dt);
}

inline void app_render(SDL_Renderer *renderer)
{
    // Render the application
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
}

inline void app_finalize()
{
    // Finalize the application
}
