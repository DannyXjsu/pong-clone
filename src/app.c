/**
 * @file app.c
 */

#include "app.h"
#include "pong.h"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>

/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

float default_scale = 1.0;

unsigned long previous_time = 0;
unsigned long current_time = 0;
bool pause = false;

inline SDL_Window* app_get_window(){
    return window;
}

inline SDL_Renderer* app_get_renderer(){
    return renderer;
}

inline const double app_get_delta_time(){
    // Usually the ticks or "counter" is multiplied by 1000 to convert ms to seconds, but that gives me weird results,
    // multiplying by 60 seems more stable and how it felt like using VSync
    return (const double)((current_time - previous_time)*60 / (double)SDL_GetPerformanceFrequency());
}

inline const bool* app_get_input_keys(){
    SDL_PumpEvents();
    return SDL_GetKeyboardState(NULL);
}

inline int app_initialize() {
    // ###### Initialize SDL ######
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    if (!SDL_CreateWindowAndRenderer(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, 0,
                &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    // Initialize pong stuff
    pong_initialize();

    current_time = SDL_GetPerformanceCounter();

    return SDL_APP_CONTINUE;
}

inline void app_handle_inputs(void *appstate, SDL_Event *event){
    switch(event->type){
        case SDL_EVENT_KEY_DOWN:
            if (event->key.scancode == SDL_SCANCODE_ESCAPE)
                pause = !pause;
   }
}

inline void app_process() {
    // Getting delta time
    previous_time = current_time;
    current_time = SDL_GetPerformanceCounter();
    const float dt = app_get_delta_time();

    // Handle pausing
    if (pause){
        return;
    }

    pong_process();
}

inline void app_clear_screen(){
    /* clear the window to the draw color. */
    SDL_RenderClear(renderer);
}

inline void app_set_scale(const float scale){
    SDL_SetRenderScale(renderer, scale, scale);
}

inline void app_render_finish(){
    /* put the newly-cleared rendering on the screen. */
    SDL_RenderPresent(renderer);
}

/**
 * @brief Render text to the screen
 * 
 * Works very similar to SDL @ref SDL_RenderDebugTextFormat
 * 
 * @param position Position in the screen
 * @param scale Scale of the text
 * @param fmt Text (format)
 * @param ... Formatting arguments
 * 
 * @return true on success or false on failure; call SDL_GetError() for more information.
 */
inline bool app_draw_text(Vector2 position, float scale, const char* fmt, ...){
    va_list ap;
    va_start(ap, fmt);

    app_set_scale(TEXT_SCALE);

    // fast path to avoid unnecessary allocation and copy. If you're going through the dynapi, there's a good chance
    // you _always_ hit this path, since it probably had to process varargs before calling into the jumptable.
    if (SDL_strcmp(fmt, "%s") == 0) {
        const char *str = va_arg(ap, const char *);
        va_end(ap);
        return SDL_RenderDebugText(renderer, position.x / TEXT_SCALE, position.y / TEXT_SCALE, str);
    }

    char *str = NULL;
    const int rc = SDL_vasprintf(&str, fmt, ap);
    va_end(ap);

    if (rc == -1) {
        return false;
    }

    const bool retval = SDL_RenderDebugText(renderer, position.x / TEXT_SCALE, position.y / TEXT_SCALE, str);
    SDL_free(str);
    app_set_scale(default_scale);
    return retval;
}

inline void app_render() {
    //SDL_Renderer* renderer = app_get_renderer();
    // Render the application
    SDL_SetRenderDrawColorFloat(
        renderer, 0.0, 0.0, 0.0,
        SDL_ALPHA_OPAQUE_FLOAT); /* new color, full alpha. */

    /* clear the window to the draw color. */
    app_clear_screen();
    app_set_scale(default_scale);

    pong_render();

    app_render_finish();
}

inline void app_finalize() {
    // Finalize the application
}
