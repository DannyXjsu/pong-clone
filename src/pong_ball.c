/**
 * @file pong_ball.c
 */


#include "app.h"
#include "math.h"
#include "pong.h"
#include "pong_ball.h"
#include "pong_player.h"

#include <stdlib.h>

Ball ball;


/**
 * Initialize ball.
 */
inline void initialize_ball() {
    ball.speed = DEFAULT_BALL_SPEED;
    ball.size.x = ball.size.y = 8;

    reset_ball();
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


// FIXME: I think the bounce factor is not center-aligned, so it just calculates from the top-left
// of the ball, instead of center, not an issue with the player
// FIXME above might be fixed, it's hard to tell
inline void bounce() {
    const unsigned int _player = is_ball_heading_towards(PLAYER_ONE) ? PLAYER_ONE : PLAYER_TWO;
    const float player_center_height = player[_player].position.y + player[_player].size.y / 2;
    const float ball_center_height = ball.position.y + ball.size.y / 2;
    float bounce_height_factor = (player_center_height - ball_center_height) / player[_player].size.y;
    bounce_height_factor = bounce_height_factor * 2;
    //bounce_height_factor = clamp(bounce_height_factor*100, -0.5, 0.5); // fixed bounce factor

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

inline bool is_ball_heading_towards(unsigned int _player){
    const unsigned int dir_to = ball.velocity.x < 0.0f ? PLAYER_ONE : PLAYER_TWO;
    return dir_to == _player;
}

/**
 * Process the ball.
 *
 * @param delta_time Time since last frame.
 */
inline void process_ball(double delta_time) {
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

    // Detecting collision with players
    if(is_ball_heading_towards(PLAYER_ONE)){
        if (is_ball_touching_player(PLAYER_ONE))
            bounce();
    } else {
        if (is_ball_touching_player(PLAYER_TWO))
            bounce();
    }
    
    // Detecting collisions with wall
    if (ball.position.x + ball.size.x < 0.0f || ball.position.x > window_width) {
       score();
    }
}

/**
 * Render ball.
 *
 * @param renderer SDL renderer instance.
 */
inline void draw_ball() {
    SDL_Renderer* renderer = app_get_renderer();
    SDL_FRect rect = vec_to_rect(&ball.position, &ball.size);
    SDL_RenderFillRect(renderer, &rect);

    if (app_debug){
        Color bcol = {1.0, 0.0, 1.0, 1.0};
        app_set_draw_color(&bcol);
        SDL_RenderLine(renderer, 0.0, (ball.position.y + ball.size.y/2), window_width, (ball.position.y + ball.size.y/2));
        app_set_draw_color(&foreground);
    }
}