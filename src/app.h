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
#include "math.h"
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

//extern SDL_Window *window;
//extern SDL_Renderer *renderer;

extern float default_scale;

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
 * @brief Get pointer to SDL Window
 * @warning Window must have been initialized @ref app_initialize
 * @return SDL_Window* pointer to the window
 */
extern SDL_Window* app_get_window();

/**
 * @brief Get pointer to SDL Renderer
 * @warning Renderer must have been initialized @ref app_initialize
 * @return SDL_Renderer* 
 */
extern SDL_Renderer* app_get_renderer();

/**
 * @brief Calculate the time between frames
 * 
 * @return const double delta time
 */
extern const double app_get_delta_time();

/**
 * @brief Get array of current frame input keys (SDL)
 * 
 * @return true if pressed
 * @return false if not pressed
 */
extern const bool* app_get_input_keys();

/**
 * Initialize the application.
 */
extern int app_initialize(void);

/**
 * Handle app inputs
 *
 * @param appstate SDL3 App state.
 * @param event SDL3 Event struct.
 */
extern void app_handle_inputs(void *appstate, SDL_Event *event);

/**
 * Process the application.
 */
extern void app_process(void);

/**
 * @brief  Clear the screen
 * 
 */
extern void app_clear_screen();
/**
 * @brief Set render scale
 * 
 * @param scale Scale factor
 */
extern void app_set_scale(const float scale);
/**
 * @brief Finish rendering and present to the screen
 * 
 */
extern void app_render_finish();

extern bool app_draw_text(Vector2 position, float scale, const char* fmt, ...);

/**
 * Render the application.
 */
extern void app_render(void);

/**
 * Finalize the application.
 */
extern void app_finalize(void);

#endif // APP_H_
