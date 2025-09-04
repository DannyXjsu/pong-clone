/**
 * @file pong_ball.h
 * @brief Pong ball functions and definitions.
 *
 * @author DannyXjsu
 * @version 1.0
 * @date 2025-09-01
 */

#ifndef PONG_BALL_H_
#define PONG_BALL_H_

#include "math.h"
#include <math.h>

/**
 * Default speed of the ball.
 */
#define DEFAULT_BALL_SPEED 4.0

/**
 * Speed gain on ball bounce.
 */
#define BALL_SPEED_GAIN_ON_BOUNCE 0.20

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
 * Ball class.
 */
typedef struct Ball{
    /** Speed of the ball. */
    float speed;
    /** Velocity of the ball. */
    Vector2 velocity;
    /** Position of the ball. */
    Vector2 position;
    /** Size of the ball. */
    Vector2 size;

    void (*reset)();
    bool (*is_touching_player)(unsigned int);
    bool (*is_heading_towards)(unsigned int);
} Ball;

/**
 * Ball instance.
 */
extern Ball* pBall;

/**
 * Event for when the ball bounces.
 */
extern void bounce(void);

/**
 * Initialize ball.
 */
extern void initialize_ball();

/**
 * Process the ball.
 *
 * @param delta_time Time since last frame.
 */
extern void process_ball(double delta_time);

/**
 * Render ball.
 */
extern void draw_ball();

#endif