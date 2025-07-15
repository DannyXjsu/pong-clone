#include "pong.h"
#include "app.h"

#include <math.h>

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
    player[PLAYER_ONE].position.x = 16.0;
    player[PLAYER_TWO].position.x = (float)WINDOW_WIDTH - 16.0 - player[1].size.x;
}

inline void render_players(SDL_Renderer *renderer) {
    for (unsigned int i = 0; i < PLAYER_COUNT; i++) {
        SDL_RenderFillRect(renderer, &player[i].rect);
    }
}

inline void initialize_ball() {
    ball.speed = DEFAULT_BALL_SPEED;
    ball.position.x = ball.position.y = (float)WINDOW_HEIGHT / 2;
    ball.size.x = ball.size.y = 8;

    ball.velocity.x = ball.speed;
    ball.velocity.y = ball.speed / 4;
    ball.velocity = normalize(&ball.velocity);
    ball.velocity.x *= ball.speed;
    ball.velocity.y *= ball.speed;
}

inline void reset_ball() {
    ball.position.x = (float)WINDOW_WIDTH / 2;
    ball.position.y = (float)WINDOW_HEIGHT / 2;
    ball.speed = DEFAULT_BALL_SPEED;
    // FIXME: Directions could be random
    ball.velocity = normalize(&ball.velocity);
    ball.velocity.x *= ball.speed;
    ball.velocity.y *= ball.speed;
}

inline void render_ball(SDL_Renderer *renderer) {
    SDL_RenderFillRect(renderer, &ball.rect);
}

extern void render_center_line(SDL_Renderer *renderer) {
    SDL_RenderLine(renderer, (float)WINDOW_WIDTH / 2, 0.0f,
                   (float)WINDOW_WIDTH / 2, WINDOW_HEIGHT);
}

inline void scored() {
    ball.velocity.x = invertf(ball.velocity.x);
    speed_shared = DEFAULT_PLAYER_SPEED;
    reset_ball();
}

// FIXME: Add a little bit of randomness in the direction of the bounce to
// prevent endless bouncing back and forth
inline void bounced() {
    ball.velocity.x = invertf(ball.velocity.x);
    ball.speed += BALL_SPEED_GAIN_ON_BOUNCE;

    speed_shared += PLAYER_SPEED_GAIN_ON_BOUNCE;

    ball.velocity = normalize(&ball.velocity);
    ball.velocity.x *= ball.speed;
    ball.velocity.y *= ball.speed;
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
    if (ball.position.y <= 0.0f)
        ball.velocity.y = fabsf(ball.velocity.y);
    else if (ball.position.y + ball.size.y >= WINDOW_HEIGHT)
        ball.velocity.y = -fabsf(ball.velocity.y);

    // Detecting collision with players and wall
    // Heading towards player 1
    if (ball.velocity.x < 0.0f) {
        // If touching player
        if (is_ball_touching_player(0)) {
            if (ball.position.y <
                    player[PLAYER_ONE].position.y + player[PLAYER_ONE].size.y / 2)
                ball.velocity.y = -fabsf(ball.velocity.y);
            else
                ball.velocity.y = fabsf(ball.velocity.y);
            bounced();
        } // If hit wall
        else if (ball.position.x + ball.size.x < 0.0f) {
            player[PLAYER_TWO].points++;
            scored();
        }
    } else if (ball.velocity.x > 0.0f) { // Heading towards player 2
        // If touching player
        if (is_ball_touching_player(1)) {
            if (ball.position.y <
                    player[PLAYER_TWO].position.y + player[PLAYER_TWO].size.y / 2)
                ball.velocity.y = -fabsf(ball.velocity.y);
            else
                ball.velocity.y = fabsf(ball.velocity.y);
            bounced();
        }
        // If hit wall
        else if (ball.position.x > WINDOW_WIDTH) {
            player[PLAYER_ONE].points++;
            scored();
        }
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
