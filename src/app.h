/**
 * @file app.h
 * @brief Application definitions.
 *
 * @author DannyXjsu
 * @version 1.0
 * @date 2025-07-15
 */

#ifndef APP_H_
#define APP_H_
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>

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
extern Uint64 previous_time;

/**
 * @brief Current time.
 *
 * Current process time to calculate delta time.
 */
extern Uint64 current_time;

/**
 * @brief Initialize the application.
 *
 * Initialize the application.
 */
extern void app_initialize();

/**
 * @brief Process the application.
 *
 * Process the application.
 */
extern void app_process();

/**
 * @brief Render the application.
 *
 * Render the application.
 */
extern void app_render(SDL_Renderer *renderer);

/**
 * @brief Finalize the application.
 *
 * Finalize the application.
 */
extern void app_finalize();

#endif // APP_H_
