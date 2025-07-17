/**
 * @file app.h
 * Application definitions.
 *
 * @author DannyXjsu
 * @version 1.1
 * @date 2025-07-15
 */

#ifndef APP_H_
#define APP_H_
#include <SDL3/SDL_render.h>

/**
 * Title of the window.
 */
#define WINDOW_TITLE "Pong Clone"

/**
 * Width of the window.
 */
#define WINDOW_WIDTH 640

/**
 * Height of the window.
 */
#define WINDOW_HEIGHT 480

/**
 * Scale of debug text displayed
 */
#define TEXT_SCALE 2.0

/**
 * The previous time of the process.
 */
extern unsigned long previous_time;

/**
 * Current process time to calculate delta time.
 */
extern unsigned long current_time;

/**
 * Processing status
 *
 * If true, completely stops processing of app (excluding delta time calculation).
 */
extern bool pause;

/**
 * Initialize the application.
 */
extern void app_initialize(void);

/**
 * Handle app inputs
 *
 * Args:
 *     *appstate: SDL3 App state.
 *     *event: SDL3 Event struct.
 */
extern void app_handle_inputs(void *appstate, SDL_Event *event);

/**
 * Process the application.
 */
extern void app_process(void);

/**
 * Render the application.
 *
 * Args:
 *     *renderer: SDL3 Renderer struct.
 */
extern void app_render(SDL_Renderer *renderer);

/**
 * Finalize the application.
 */
extern void app_finalize(void);

#endif // APP_H_
