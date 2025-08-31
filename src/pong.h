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
 * Number of players in the game.
 */
#define PLAYER_COUNT 2 // You probably don't want to change this

/**
 * Player one index.
 */
#define PLAYER_ONE 0

/**
 * Player two index.
 */
#define PLAYER_TWO 1

/**
 * Default speed of the ball.
 */
#define DEFAULT_BALL_SPEED 4.0

/**
 * Speed gain on ball bounce.
 */
#define BALL_SPEED_GAIN_ON_BOUNCE 0.5

/**
 * Size in pixels of the ball.
 */
#define BALL_SIZE 8

/**
 * Starting position of the ball on the X-axis.
 */
#define BALL_START_POSITION_X WINDOW_HEIGHT/2

/**
 * Starting position of the ball on the Y-axis.
 */
#define BALL_START_POSITION_Y BALL_START_POSITION_X

/**
 * Default speed of the player.
 */
#define DEFAULT_PLAYER_SPEED 8.0

/**
 * Player speed gain on ball bounce.
 */
#define PLAYER_SPEED_GAIN_ON_BOUNCE 0.1

/**
 * Player class.
 */
typedef struct {
    /** Points/score of the player. */
    unsigned int points;
    struct {
        /** Position of the player. */
        Vector2 position;
        /** Size of the player. */
        Vector2 size;
    };
} Player;

/**
 * Ball class.
 */
typedef struct {
    /** Speed of the ball. */
    float speed;
    /** Velocity of the ball. */
    Vector2 velocity;
    struct {
        /** Position of the ball. */
        Vector2 position;
        /** Size of the ball. */
        Vector2 size;
    };
} Ball;

/**
 * Players array.
 */
extern Player player[PLAYER_COUNT];

/**
 * Ball instance.
 */
extern Ball ball;

/**
 * Shared (between players) speed value.
 */
extern float speed_shared;

/**
 * Check if the ball is touching a player.
 *
 * @param _player Player index.
 * @return True if the ball is touching the player, false otherwise.
 */
extern bool is_ball_touching_player(unsigned int _player);

/**
 * Event for when a player scores.
 */
extern void score(void);

/**
 * Event for when the ball bounces.
 */
extern void bounce(void);

/**
 * Reset the ball to the center of the screen.
 */
extern void reset_ball(void);

/**
 * Reset players to their initial positions.
 */
extern void reset_players(void);

extern void pong_initialize();

extern void pong_process();

extern void pong_render();

#endif // PONG_H_
