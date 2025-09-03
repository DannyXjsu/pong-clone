/**
 * @file pong_player.h
 * @brief Pong player functions and definitions.
 *
 * @author DannyXjsu
 * @version 1.0
 * @date 2025-09-01
 */


#ifndef PONG_PLAYER_H_
#define PONG_PLAYER_H_

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
    /** Position of the player. */
    Vector2 *position;
    /** Size of the player. */
    Vector2 *size;
} Player;

/**
 * Players array.
 */
extern Player* pPlayer[PLAYER_COUNT];

/**
 * Shared (between players) speed value.
 */
extern float speed_shared;

/**
 * Initialize players.
 */
extern void initialize_players();

/**
 * Reset players to their initial positions.
 */
extern void reset_players(void);


/**
 * Process players.
 *
 * @param delta_time Time since last frame.
 */
extern void process_players(double delta_time);

/**
 * Render players.
 */
extern void draw_players(); 

#endif