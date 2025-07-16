/**
 * @file app.h
 * @brief Application definitions.
 *
 * @author DannyXjsu
 * @version 1.1
 * @date 2025-07-15
 */

#ifndef APP_H_
#define APP_H_
#include <SDL3/SDL_render.h>

/**
 * @brief Title of the window.
 */
#define WINDOW_TITLE "Pong Clone"

/**
 * @brief Width of the window.
 */
#define WINDOW_WIDTH 640

/**
 * @brief Height of the window.
 */
#define WINDOW_HEIGHT 480

/**
 * @brief Previous time.
 *
 * The previous time of the process.
 */
extern unsigned long previous_time;

/**
 * @brief Current time.
 *
 * Current process time to calculate delta time.
 */
extern unsigned long current_time;

/**
 * @brief Processing status
 *
 * If true, completely stops processing of app (excluding delta time calculation)
 */
extern bool pause;

/**
 * @brief Initialize the application.
 */
extern void app_initialize(void);

/**
 * @brief Handle app inputs
 */
extern void app_handle_inputs(void *appstate, SDL_Event *event);

/**
 * @brief Process the application.
 */
extern void app_process(void);

/**
 * @brief Render the application.
 */
extern void app_render(SDL_Renderer *renderer);

/**
 * @brief Finalize the application.
 */
extern void app_finalize(void);

#endif // APP_H_
