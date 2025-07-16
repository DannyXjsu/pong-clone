/**
 * @file pong.c
 */

#include "pong.h"
#include "app.h"
#include "math.h"

#include <SDL3/SDL_stdinc.h>
#include <math.h>
#include <stdlib.h>

float speed_shared = DEFAULT_PLAYER_SPEED;

Player player[PLAYER_COUNT];
Ball ball;

inline void initialize_players() {
    for (unsigned int i = 0; i < PLAYER_COUNT; i++) {
        player[i].points = 0;
        player[i].position.y = (float)WINDOW_HEIGHT / 2;
        player[i].size.x = 8.0f;
        player[i].size.y = 64.0f;
    }
    reset_players();
}

inline void render_players(SDL_Renderer *renderer) {
    for (unsigned int i = 0; i < PLAYER_COUNT; i++) {
        SDL_RenderFillRect(renderer, &player[i].rect);
    }
}

inline void initialize_ball() {
    ball.speed = DEFAULT_BALL_SPEED;
    ball.size.x = ball.size.y = 8;

    reset_ball();
}

inline void reset_ball() {
    ball.position.x = (float)WINDOW_WIDTH / 2;
    ball.position.y = (float)WINDOW_HEIGHT / 2;
    ball.speed = DEFAULT_BALL_SPEED;

    Vector2 direction = {clamp(rand() - RAND_MAX / 2, -1, 1), clamp(SDL_randf() - 0.5f, -0.5f, 0.5f)};
    ball.velocity = normalize(&direction);
    ball.velocity.x *= ball.speed;
    ball.velocity.y *= ball.speed;
}

inline void reset_players() {
    player[PLAYER_ONE].position.y = (float)WINDOW_HEIGHT / 2;
    player[PLAYER_TWO].position.y = (float)WINDOW_HEIGHT / 2;
    player[PLAYER_ONE].position.x = 16.0;
    player[PLAYER_TWO].position.x = (float)WINDOW_WIDTH - 16.0 - player[PLAYER_TWO].size.x;
}

inline void render_ball(SDL_Renderer *renderer) {
    SDL_RenderFillRect(renderer, &ball.rect);
}

extern void render_center_line(SDL_Renderer *renderer) {
    SDL_RenderLine(renderer, (float)WINDOW_WIDTH / 2, 0.0f,
                   (float)WINDOW_WIDTH / 2, WINDOW_HEIGHT);
}

inline void score() {
    const unsigned int _player = ball.velocity.x > 0.0f ? PLAYER_ONE : PLAYER_TWO;
    player[_player].points++;
    ball.velocity.x = invert(ball.velocity.x);
    speed_shared = DEFAULT_PLAYER_SPEED;

    reset_ball();
    reset_players();
}

// FIXME: Add a little bit of randomness in the direction of the bounce to
// prevent endless bouncing back and forth
// FIXME: The randomness thing from the FIXME above is somewhat implemented, there is no "randomness"
// since it's just the factor of the distance from the player's center to the ball's position, but
// it makes it seem random
// FIXME: I think the bounce factor is not center-aligned, so it just calculates from the top-left
// of the ball, instead of center, but at least with the player is truly the center.
inline void bounce() {
    const unsigned int _player = ball.velocity.x < 0.0f ? PLAYER_ONE : PLAYER_TWO;
    const float player_center_ypos = player[_player].position.y + player[_player].size.y / 2;
    float bounce_height_factor = (player_center_ypos - ball.position.y) / player[_player].size.y;
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

inline void process_ball(double delta_time) {
    // Applying velocity and such
    for (unsigned int i = 0; i < 2; i++) {
        ball.position.v[i] += ball.velocity.v[i] * delta_time;
    }

    // Detecting collision with floor and ceiling
    if (ball.position.y <= 0.0f){
        ball.velocity.y = fabsf(ball.velocity.y);
    }
    else if (ball.position.y + ball.size.y >= WINDOW_HEIGHT){
        ball.velocity.y = -fabsf(ball.velocity.y);
    }

    // Detecting collision with players and wall
    for (unsigned int i = 0; i < PLAYER_COUNT; i++){
        if (is_ball_touching_player(i)){
            bounce();
        }
    }
    // If hit wall
    if (ball.position.x + ball.size.x < 0.0f || ball.position.x > WINDOW_WIDTH) {
       score();
    }
}

inline void process_players(double delta_time) {
    // Get inputs
    SDL_PumpEvents();
    const bool *keys = SDL_GetKeyboardState(NULL);
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
        else if (player[i].position.y + player[i].size.y > WINDOW_HEIGHT)
            player[i].position.y = WINDOW_HEIGHT - player[i].size.y;
    }
}
