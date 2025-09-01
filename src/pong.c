/**
 * @file pong.c
 */

#include "pong.h"
#include "app.h"
#include "math.h"
#include "utils.h"

#include <SDL3/SDL_stdinc.h>
#include <math.h>
#include <stdlib.h>

float speed_shared = DEFAULT_PLAYER_SPEED;

Player player[PLAYER_COUNT];
Ball ball;

/**
 * Initialize players.
 */
static inline void initialize_players() {
    for (unsigned int i = 0; i < PLAYER_COUNT; i++) {
        player[i].points = 0;
        player[i].position.y = (float)window_height / 2;
        player[i].size.x = 8.0f;
        player[i].size.y = 80.0f;
    }
    reset_players();
}

/**
 * Initialize ball.
 */
static inline void initialize_ball() {
    ball.speed = DEFAULT_BALL_SPEED;
    ball.size.x = ball.size.y = 8;

    reset_ball();
}

inline void pong_initialize(){
    initialize_ball();
    initialize_players();
}

inline void reset_ball() {
    ball.position.x = (float)window_width / 2;
    ball.position.y = (float)window_height / 2;
    ball.speed = DEFAULT_BALL_SPEED;

    Vector2 direction = {clamp(rand() - RAND_MAX / 2, -1, 1), clamp(SDL_randf() - 0.5f, -0.5f, 0.5f)};
    ball.velocity = normalize(&direction);
    ball.velocity.x *= ball.speed;
    ball.velocity.y *= ball.speed;
}

inline void reset_players() {
    player[PLAYER_ONE].position.y = (float)window_height / 2;
    player[PLAYER_TWO].position.y = (float)window_height / 2;
    player[PLAYER_ONE].position.x = 16.0;
    player[PLAYER_TWO].position.x = (float)window_width - 16.0 - player[PLAYER_TWO].size.x;
}

/**
 * Render players.
 *
 * @param renderer SDL renderer instance.
 */
static inline void draw_players(SDL_Renderer *renderer) {
    for (unsigned int i = 0; i < PLAYER_COUNT; i++) {
        SDL_FRect rect = vec_to_rect(&player[i].position, &player[i].size);
        SDL_RenderFillRect(renderer, &rect);

        if (app_debug){
            Color bcol = {0.0, 1.0, i, 1.0};
            Color df = {1.0, 1.0, 1.0, 1.0};
            app_set_draw_color(&bcol);
            SDL_RenderLine(renderer, 0.0, (player[i].position.y + player[i].size.y/2), window_width, (player[i].position.y + player[i].size.y/2));
            app_set_draw_color(&df);
        }
    }
}

/**
 * Render ball.
 *
 * @param renderer SDL renderer instance.
 */
static inline void draw_ball(SDL_Renderer *renderer) {
    SDL_FRect rect = vec_to_rect(&ball.position, &ball.size);
    SDL_RenderFillRect(renderer, &rect);

    if (app_debug){
        Color bcol = {1.0, 0.0, 1.0, 1.0};
        Color df = {1.0, 1.0, 1.0, 1.0};
        app_set_draw_color(&bcol);
        SDL_RenderLine(renderer, 0.0, (ball.position.y + ball.size.y/2), window_width, (ball.position.y + ball.size.y/2));
        app_set_draw_color(&df);
    }
}

/**
 * Render center line.
 *
 * @param renderer SDL renderer instance.
 */
static inline void draw_center_line(SDL_Renderer *renderer) {
    SDL_RenderLine(renderer, (float)window_width / 2, 0.0f,
                   (float)window_width / 2, window_height);
}

inline void pong_render(){
    SDL_Renderer* renderer = app_get_renderer();

    // Set foreground color
    Color fg = (Color){1.0, 1.0, 1.0, 1.0};
    app_set_draw_color(&fg);
    app_set_scale(TEXT_SCALE);
    // Render player points counter
    app_draw_text((Vector2){window_width / 3, 32}, TEXT_SCALE, "%u", player[0].points);
    app_draw_text((Vector2){window_width - window_width / 3, 32}, TEXT_SCALE, "%u", player[1].points);

    // Inform the players the game is paused
    if (pause){
        //SDL_RenderDebugText(renderer, ((float)window_width/2 - 70) / TEXT_SCALE, ((float)window_height/2 - 16) / TEXT_SCALE, "Game Paused");
        app_draw_text((Vector2){((float)window_width/2 - 70), ((float)window_height/2 - 16)}, TEXT_SCALE, "Game Paused");
    }

    app_set_scale(default_scale);

    draw_players(renderer);
    draw_ball(renderer);
    draw_center_line(renderer);
}

inline void score() {
    const unsigned int _player = ball.velocity.x > 0.0f ? PLAYER_ONE : PLAYER_TWO;
    player[_player].points++;
    ball.velocity.x = invert(ball.velocity.x);
    speed_shared = DEFAULT_PLAYER_SPEED;

    reset_ball();
    reset_players();
}

// FIXME: I think the bounce factor is not center-aligned, so it just calculates from the top-left
// of the ball, instead of center, not an issue with the player
// FIXME above might be fixed, it's hard to tell
inline void bounce() {
    const unsigned int _player = ball.velocity.x < 0.0f ? PLAYER_ONE : PLAYER_TWO;
    const float player_center_height = player[_player].position.y + player[_player].size.y / 2;
    const float ball_center_height = ball.position.y + ball.size.y / 2;
    float bounce_height_factor = (player_center_height - ball_center_height) / player[_player].size.y;
    bounce_height_factor = bounce_height_factor * 2;

    ball.velocity = normalize(&ball.velocity);
    Vector2 bounce_direction = {invert(ball.velocity.x), -bounce_height_factor};

    if (ball.position.y <
            player[_player].position.y + player[_player].size.y / 2)
        ball.velocity.y = -fabsf(ball.velocity.y);
    else
        ball.velocity.y = fabsf(ball.velocity.y);

    ball.speed += BALL_SPEED_GAIN_ON_BOUNCE;
    speed_shared += PLAYER_SPEED_GAIN_ON_BOUNCE;

    ball.velocity = normalize(&bounce_direction);
    ball.velocity.x *= ball.speed;
    ball.velocity.y *= ball.speed;

    if (_player == PLAYER_ONE)
        ball.position.x = player[_player].position.x + player[_player].size.w;
    else
        ball.position.x = player[_player].position.x - ball.size.w;
}

// FIXME: This is a crude collision detection and fails to prevent skipping in
// high ball velocity
// FIXME: Thanks to delta time, the skipping in collision is somewhat fixed,
// it's still present, but it now requires ridiculous speed to skip the player
// collision
inline bool is_ball_touching_player(unsigned int _player) {
    return (
        ball.position.x <= player[_player].position.x + player[_player].size.x &&
        ball.position.x + ball.size.x >= player[_player].position.x &&
        ball.position.y + ball.size.y > player[_player].position.y &&
        ball.position.y < player[_player].position.y + player[_player].size.y);
}

/**
 * Process the ball.
 *
 * @param delta_time Time since last frame.
 */
static inline void process_ball(double delta_time) {
    // Applying velocity and such
    for (unsigned int i = 0; i < 2; i++) {
        ball.position.v[i] += ball.velocity.v[i] * delta_time;
    }

    // Detecting collision with floor and ceiling
    if (ball.position.y <= 0.0f){
        ball.velocity.y = fabsf(ball.velocity.y);
    }
    else if (ball.position.y + ball.size.y >= window_height){
        ball.velocity.y = -fabsf(ball.velocity.y);
    }

    // Detecting collision with players and wall
    for (unsigned int i = 0; i < PLAYER_COUNT; i++){
        if (is_ball_touching_player(i)){
            bounce();
        }
    }
    // If hit wall
    if (ball.position.x + ball.size.x < 0.0f || ball.position.x > window_width) {
       score();
    }
}

/**
 * Process players.
 *
 * @param delta_time Time since last frame.
 */
static inline void process_players(double delta_time) {
    // Get inputs
    const bool *keys = app_get_input_keys();
    // Player 1
    if (keys[SDL_SCANCODE_W])
        player[PLAYER_ONE].position.y -= speed_shared * delta_time;
    if (keys[SDL_SCANCODE_S])
        player[PLAYER_ONE].position.y += speed_shared * delta_time;
    // Player 2
    if (keys[SDL_SCANCODE_UP])
        player[PLAYER_TWO].position.y -= speed_shared * delta_time;
    if (keys[SDL_SCANCODE_DOWN])
        player[PLAYER_TWO].position.y += speed_shared * delta_time;

    // Preventing players from leaving the screen
    for (unsigned int i = 0; i < PLAYER_COUNT; i++) {
        if (player[i].position.y < 0.0f)
            player[i].position.y = 0;
        else if (player[i].position.y + player[i].size.y > window_height)
            player[i].position.y = window_height - player[i].size.y;
    }
}

inline void pong_process(){
    const float dt = app_get_delta_time();
    process_ball(dt);
    process_players(dt);
}
