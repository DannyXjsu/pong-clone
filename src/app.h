/**
 * @file app.h
 * @brief Application definitions.
 *
 * @author DannyXjsu
 * @version 1.2
 * @date 2025-09-01
 */

#ifndef APP_H_
#define APP_H_
#include "math.h"
#include "utils.h"
#include <SDL3/SDL_render.h>

/**
 * Title of the window.
 */
#define WINDOW_TITLE "Pong Clone"

/**
 * Default width of the window.
 */
#define DEFAULT_WINDOW_WIDTH 640

/**
 * Default height of the window.
 */
#define DEFAULT_WINDOW_HEIGHT 480

/**
 * Scale of debug text displayed
 */
#define TEXT_SCALE 2.0

//extern SDL_Window *window;
//extern SDL_Renderer *renderer;

extern unsigned int window_width;
extern unsigned int window_height;

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
 * If true, pause processing of app (excluding delta time calculation).
 */
extern bool pause;

/**
 * Controls main loop
 *
 * If false, stop main loop (continue to app_finalize and exit app)
 */
extern bool app_loop;

extern bool app_debug;

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
 * @brief Handles passed arguments (parameters) to the program
 * 
 * Also stores them for easy access using @ref app_get_parameter_index and @ref app_get_parameter_value
 * 
 * @param _argc 
 * @param _argv 
 */
extern void app_handle_parameters(int _argc, const char **_argv);

/**
 * Initialize the application.
 */
extern int app_initialize();

/**
 * Handle app events
 *
 */
extern void app_handle_events();

/**
 * Process the application.
 */
extern void app_process(void);

/**
 * @brief Iterates through all passed arguments to find if parameter (argument) exists
 * 
 * @param param Name (key) of the parameter (argument)
 * @return true if exists
 * @return false if it doesn't exist
 * @deprecated Use @ref app_get_parameter_index() instead.
 */
extern bool app_parameter_exists(const char* param);

/**
 * @brief Iterates through all passed arguments to find if parameter (argument) exists.
 * 
 * @param param Name (key) of the parameter (argument)
 * @return int Index of the parameter, -1 if not found.
 * @see @ref app_get_parameter_value
 */
extern int app_get_parameter_index(const char* param);

/**
 * @brief Get the value of parameter using an index
 * 
 * @param index Index of parameter.
 * @return Value of parameter, returns ___ERR if failed, returns ___NOVAL if parameter value is not a valid value (like if value is an argument that starts with '-')
 * @see @ref app_get_parameter_index
 */
extern const char* app_get_parameter_value(size_t index);

/**
 * @brief Get the value of parameter using a key (name of parameter)
 * 
 * @param param Name (key) of parameter (argument)
 * @return Value of parameter, returns ___ERR if failed, returns ___NOVAL if parameter value is not a valid value (like if value is an argument that starts with '-')
 * @see @ref app_get_parameter_value and @ref app_get_parameter_index
 */
extern const char* app_get_parameter_value_by_name(const char* param);

/**
 * @brief  Clear the screen
 */
extern void app_clear_screen();

/**
 * @brief Set render scale
 * 
 * @param scale Scale factor
 */
extern void app_set_scale(const float scale);

/**
 * @brief Get current one dimensional scale
 * 
 * @return float Current scale
 */
extern float app_get_scale();

/**
 * @brief Finish rendering and present to the screen
 * 
 */
extern void app_render_finish();

/**
 * @brief Sets drawing color
 * 
 * @param col Drawing color
 */
extern void app_set_draw_color(Color* col);

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
