/**
 * @file app.c
 */

#include "app.h"
#include "pong.h"
#include "utils.h"

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_filesystem.h>
#include <SDL3/SDL_audio.h>

#include <stdio.h>
#include <stdlib.h>

/**
 * Default width of the window.
 */
#define DEFAULT_WINDOW_WIDTH 640

/**
 * Default height of the window.
 */
#define DEFAULT_WINDOW_HEIGHT 480

/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

static float default_scale = 1.0;

/**
 * The previous time of the process.
 */
static unsigned long previous_time = 0;
/**
 * Current process time to calculate delta time.
 */
static unsigned long current_time = 0;

// Audio
static SDL_AudioDeviceID audio_device = 0;
/* things that are playing sound (the audiostream itself, plus the original data, so we can refill to loop. */
static Sound *sounds = NULL;

static int argc;
static char **argv;

static bool enable_vsync = false;

unsigned int window_width = DEFAULT_WINDOW_WIDTH;
unsigned int window_height = DEFAULT_WINDOW_HEIGHT;

bool pause = false;
bool app_loop = true;
bool app_debug = false;

inline SDL_Window* app_get_window(){
    return window;
}

inline SDL_Renderer* app_get_renderer(){
    return renderer;
}

inline const double app_get_delta_time(){
    // Usually the ticks or "counter" is multiplied by 1000 to convert ms to seconds, but that gives me weird results,
    // multiplying by 60 seems more stable and how it felt like using VSync
    return (const double)((current_time - previous_time) * 60 / (double)SDL_GetPerformanceFrequency());
}

inline const bool* app_get_input_keys(){
    SDL_PumpEvents();
    return SDL_GetKeyboardState(NULL);
}

// Avoid using this function
inline bool app_parameter_exists(const char* param){
    return app_get_parameter_index(param) != -1 ? true : false;
}

inline int app_get_parameter_index(const char* param){
    for(size_t i = 0; i < argc; i++){
        if (strcmp(argv[i], param) == 0){
            return i;
        }
    }
    return -1;
}

inline const char* app_get_parameter_value(size_t index){
    if (index >= argc-1) return "___ERR";
    if (argv[index+1][0] == '-') return "___NOVAL";
    return (const char*)argv[index+1];
}

inline const char* app_get_parameter_value_by_name(const char* param)
{
    size_t index = app_get_parameter_index(param);
    if (index >= argc || index == -1) return "___ERR";
    if (argv[index+1][0] == '-') return "___NOVAL";
    return (const char*)argv[index+1];
}

inline void app_clear_screen(){
    /* clear the window to the draw color. */
    SDL_RenderClear(renderer);
}

inline void app_set_scale(const float scale){
    SDL_SetRenderScale(renderer, scale, scale);
}

inline float app_get_scale(){
    float scale;
    // I ignore the 2 dimensional scale SDL offers, I only care about a single value
    // I don't think I can pass null to the function, so the Y scale will end up being \
    // the most significant value.
    SDL_GetRenderScale(renderer, &scale, &scale);
    return scale;
}

inline void app_render_finish(){
    app_set_scale(default_scale);
    /* put the newly-cleared rendering on the screen. */
    SDL_RenderPresent(renderer);
}

inline void app_set_draw_color(Color* col){
    SDL_SetRenderDrawColorFloat(renderer, col->r, col->g, col->b, col->a);
}

inline bool app_draw_line(Vector2 *pos1, Vector2 *pos2){
    return SDL_RenderLine(renderer, pos1->x, pos1->y, pos2->x, pos2->y);
}

inline bool app_draw_rect(Vector2 *position, Vector2 *size){
    SDL_FRect rect = vec_to_rect(position, size);
    return SDL_RenderFillRect(renderer, &rect);
}

inline bool app_draw_text(Vector2 *position, float scale, const char* fmt, ...){
    va_list ap;
    va_start(ap, fmt);

    app_set_scale(scale);

    // fast path to avoid unnecessary allocation and copy. If you're going through the dynapi, there's a good chance
    // you _always_ hit this path, since it probably had to process varargs before calling into the jumptable.
    if (SDL_strcmp(fmt, "%s") == 0) {
        const char *str = va_arg(ap, const char *);
        va_end(ap);
        return SDL_RenderDebugText(renderer, position->x / scale, position->y / scale, str);
    }

    char *str = NULL;
    const int rc = SDL_vasprintf(&str, fmt, ap);
    va_end(ap);

    if (rc == -1) {
        return false;
    }

    const bool retval = SDL_RenderDebugText(renderer, position->x / scale, position->y / scale, str);
    SDL_free(str);
    app_set_scale(default_scale);
    return retval;
}

inline void app_handle_parameters(int _argc, const char **_argv){
    // Store arguments
    argc = _argc;
    argv = (char**)_argv;

    if (app_get_parameter_index("-d") != -1){
        app_debug = true;
        printf("APP:Debug enabled\n");
    }
 
    #ifdef SCALING
    { // Allow custom scale - BROKEN!!!
        int _app_scale_param = app_get_parameter_index("-s");
        if (_app_scale_param != -1){
            float _app_scale = SDL_atof(app_get_parameter_value(_app_scale_param));
            default_scale = _app_scale < 1.0 ? default_scale : _app_scale;
        }
        app_debug ? printf("APP:%s=%d\n", var2str(default_scale), default_scale) : 0;
    }
    #endif

    { // Vsync
        if(app_get_parameter_index("-v") != 1){
            enable_vsync = true;
            app_debug ? printf("APP:VSync Enabled\n") : 0;
        }
    }

    { // Get window dimensions
        int _app_w_index = app_get_parameter_index("-w");
        int _app_h_index = app_get_parameter_index("-h");
        int _app_w = atoi(app_get_parameter_value(_app_w_index));
        int _app_h = atoi(app_get_parameter_value(_app_h_index));
        // If parameters exist, set dimensions, otherwise, ignore
        window_width = _app_w_index != -1 ? _app_w : window_width;
        window_height = _app_h_index != -1 ? _app_h : window_height;
        // If valid dimentions, set so, otherwise, ignore
        window_width = window_width < DEFAULT_WINDOW_WIDTH/3 ? DEFAULT_WINDOW_WIDTH/3 : window_width;
        window_height = window_height < DEFAULT_WINDOW_HEIGHT/3 ? DEFAULT_WINDOW_HEIGHT/3 : window_height;

        app_debug ? printf("APP:%s=%d\n", var2str(window_width), window_width) : 0;
        app_debug ? printf("APP:%s=%d\n", var2str(window_height), window_height) : 0;
    }

    { // Set colors
        Color8 _fg = color_to_color8(&foreground);
        Color8 _bg = color_to_color8(&background);

        if(app_parameter_exists("-fr")){
            _fg.r = (uint8_t)atoi(app_get_parameter_value_by_name("-fr"));
            foreground.r = (float)_fg.r/255;
        }
        if(app_parameter_exists("-fg")){
            _fg.g = (uint8_t)atoi(app_get_parameter_value_by_name("-fg"));
            foreground.g = (float)_fg.g/255;
        }
        if(app_parameter_exists("-fb")){
            _fg.b = (uint8_t)atoi(app_get_parameter_value_by_name("-fb"));
            foreground.b = (float)_fg.b/255;
        }

        if(app_parameter_exists("-br")){
            _bg.r = (uint8_t)atoi(app_get_parameter_value_by_name("-br"));
            background.r = (float)_bg.r/255;
        }
        if(app_parameter_exists("-bg")){
            _bg.g = (uint8_t)atoi(app_get_parameter_value_by_name("-bg"));
            background.g = (float)_bg.g/255;
        }
        if(app_parameter_exists("-bb")){
            _bg.b = (uint8_t)atoi(app_get_parameter_value_by_name("-bb"));
            background.b = (float)_bg.b/255;
        }
    }
}

inline Sound* app_load_sound(const char *file_name){
    sounds = (Sound*)malloc(sizeof(sounds) + sizeof(Sound*));
    if (sounds == NULL){
        printf("Failed to allocate memory for audio file: %s - size: %lu+%lu\n", file_name, sizeof(sounds), sizeof(Sound*));
        return NULL;
    }

    int i;
    for (i=0; i < arraysize(sounds); i++);
    SDL_AudioSpec spec;
    char *wav_path = NULL;

    /* Load the .wav files from wherever the app is being run from. */
    SDL_asprintf(&wav_path, "%s%s", SDL_GetBasePath(), file_name);  /* allocate a string of the full file path */
    if (!SDL_LoadWAV(wav_path, &spec, &sounds[i].wav_data, &sounds[i].wav_data_len)) {
        SDL_Log("Couldn't load .wav file: %s", SDL_GetError());
        SDL_free(wav_path);  /* done with this string. */
        return NULL;
    } else
        printf("Loaded WAV: %s\n", wav_path);

    /* Create an audio stream. Set the source format to the wav's format (what
       we'll input), leave the dest format NULL here (it'll change to what the
       device wants once we bind it). */
    sounds[i].stream = SDL_CreateAudioStream(&spec, NULL);
    if (!sounds[i].stream) {
        SDL_Log("Couldn't create audio stream: %s", SDL_GetError());
    } else if (!SDL_BindAudioStream(audio_device, sounds[i].stream)) {  /* once bound, it'll start playing when there is data available! */
        SDL_Log("Failed to bind '%s' stream to device: %s", file_name, SDL_GetError());
    }
    
    SDL_free(wav_path);  /* done with this string. */
    return &sounds[i];
}

inline bool app_play_sound(const Sound* sound){
    if (sound != NULL){
        SDL_PutAudioStreamData(sound->stream, sound->wav_data, (int) sound->wav_data_len);
        return true;
    }
    printf("Unable to play sound\n");
    return false;
}

inline int app_initialize() {
    #ifdef SCALING
    window_width *= default_scale;
    window_height *= default_scale;
    #endif

    // ###### Initialize SDL ######
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    if (!SDL_CreateWindowAndRenderer(WINDOW_TITLE, window_width, window_height, 0,
                &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (enable_vsync){
        SDL_SetRenderVSync(renderer,SDL_RENDERER_VSYNC_ADAPTIVE);
    }

    /* open the default audio device in whatever format it prefers; our audio streams will adjust to it. */
    audio_device = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    if (audio_device == 0) {
        SDL_Log("Couldn't open audio device: %s", SDL_GetError());
        //return SDL_APP_FAILURE;
    }

    printf("SDL Initialized\n");

    // Initialize pong stuff
    pong_initialize();

    current_time = SDL_GetPerformanceCounter();

    return SDL_APP_CONTINUE;
}

inline void app_handle_events(){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch(event.type){
        case SDL_EVENT_QUIT:
            app_loop = false;
            break;
        case SDL_EVENT_KEY_DOWN:
            switch (event.key.scancode){
                case SDL_SCANCODE_P:
                case SDL_SCANCODE_PAUSE:
                case SDL_SCANCODE_ESCAPE:
                    pause = !pause;
                    break;
                case SDL_SCANCODE_R:
                    pong_reset();
                    break;
                case SDL_SCANCODE_Q:
                    app_loop = false;
                    break;
                case SDL_SCANCODE_D:
                    app_debug = !app_debug;
                    break;
                case SDL_SCANCODE_UNKNOWN:
                default:
                break;
            }
            break;
        }
    }
}

inline void app_process() {
    // Getting delta time
    previous_time = current_time;
    current_time = SDL_GetPerformanceCounter();

    // Handle pausing
    if (pause){
        return;
    }

    pong_process();
}

inline void app_render() {
    //SDL_Renderer* renderer = app_get_renderer();
    // Render the application
    app_set_draw_color(&background);

    /* clear the window to the draw color. */
    app_clear_screen();

    pong_render();

    app_render_finish();
}

inline void app_finalize() {
    SDL_CloseAudioDevice(audio_device);

    for (int i = 0; i < arraysize(sounds); i++) {
        if (sounds[i].stream) {
            SDL_DestroyAudioStream(sounds[i].stream);
        }
        SDL_free(sounds[i].wav_data);
    }

    free(sounds);
}
