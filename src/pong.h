/**
 * @file pong.h
 * @brief Definitions for the Pong game.
 *
 * @author DannyXjsu
 * @version 1.0
 * @date 2025-07-15
 */

#ifndef PONG_H_
#define PONG_H_

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

#include "math.h"

/**
 * @brief Number of players in the game.
 */
#define PLAYER_COUNT 2 // You probably don't want to change this

/**
 * @brief Player one index.
 */
#define PLAYER_ONE 0

/**
 * @brief Player two index.
 */
#define PLAYER_TWO 1

/**
 * @brief Default speed of the ball.
 */
#define DEFAULT_BALL_SPEED 4.0

/**
 * @brief Speed gain on ball bounce.
 */
#define BALL_SPEED_GAIN_ON_BOUNCE 0.5

/**
 * @brief Size in pixels of the ball.
 */
#define BALL_SIZE 8

/**
 * @brief Starting position of the ball on the X-axis.
 */
#define BALL_START_POSITION_X WINDOW_HEIGHT/2

/**
 * @brief Starting position of the ball on the Y-axis.
 */
#define BALL_START_POSITION_Y BALL_START_POSITION_X

/**
 * @brief Default speed of the player.
 */
#define DEFAULT_PLAYER_SPEED 8.0

/**
 * @brief Player speed gain on ball bounce.
 */
#define PLAYER_SPEED_GAIN_ON_BOUNCE 0.1

/**
 * @brief Player class.
 */
typedef struct {
    /** Points/score of the player. */
    unsigned int points;
    // ## Sharing properties
    // Asserting
    _Static_assert(sizeof(SDL_FRect) == sizeof(Vector2) * 2,
                 "Player struct union layout is incompatible, SDL_FRect "
                 "mismatches (Vector2 * 2)");
    union {
        struct {
            /** Position of the player. */
            Vector2 position;
            /** Size of the player. */
            Vector2 size;
        };
        /** SDL rectangle of the player. */
        SDL_FRect rect;
    };
} Player;

/**
 * @brief Ball class.
 */
typedef struct {
    /** Speed of the ball. */
    float speed;
    /** Velocity of the ball. */
    Vector2 velocity;
    // ## Sharing properties
    // Asserting
    _Static_assert(sizeof(SDL_FRect) == sizeof(Vector2) * 2,
                 "Player struct union layout is incompatible, SDL_FRect "
                 "mismatches (Vector2 * 2)");
    union {
        struct {
            /** Position of the ball. */
            Vector2 position;
            /** Size of the ball. */
            Vector2 size;
        };
        /** SDL rectangle of the ball. */
        SDL_FRect rect;
    };
} Ball;

/**
 * @brief Players array.
 */
extern Player player[PLAYER_COUNT];

/**
 * @brief Ball instance.
 */
extern Ball ball;

/**
 * @brief Shared (between players) speed value.
 */
extern float speed_shared;

/**
 * @brief Check if the ball is touching a player.
 *
 * @param _player Player index.
 * @return true if the ball is touching the player, false otherwise.
 */
extern bool is_ball_touching_player(unsigned int _player);

/**
 * @brief Event for when a player scores.
 */
extern void score(void);

/**
 * @brief Event for when the ball bounces.
 */
extern void bounce(void);

/**
 * @brief Reset the ball to the center of the screen.
 */
extern void reset_ball(void);

/**
 * @brief Reset players to their initial positions.
 */
extern void reset_players(void);

/**
 * @brief Initialize players.
 */
extern void initialize_players(void);

/**
 * @brief Initialize ball.
 */
extern void initialize_ball(void);

/**
 * @brief Process the ball.
 *
 * @param delta_time Time since last frame.
 */
extern void process_ball(double delta_time);

/**
 * @brief Process players.
 *
 * @param delta_time Time since last frame.
 */
extern void process_players(double delta_time);

/**
 * @brief Render players.
 *
 * @param renderer SDL renderer instance.
 */
extern void render_players(SDL_Renderer *renderer);

/**
 * @brief Render ball.
 *
 * @param renderer SDL renderer instance.
 */
extern void render_ball(SDL_Renderer *renderer);

/**
 * @brief Render center line.
 *
 * @param renderer SDL renderer instance.
 */
extern void render_center_line(SDL_Renderer *renderer);

#endif // PONG_H_
