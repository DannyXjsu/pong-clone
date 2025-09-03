/**
 * @file pong_player.c
 */

#include "app.h"
#include "pong_player.h"
#include "utils.h"

#include <stdio.h>

float speed_shared = DEFAULT_PLAYER_SPEED;

static Player player[PLAYER_COUNT];
static Vector2 pos[PLAYER_COUNT];
static Vector2 size[PLAYER_COUNT];

Player* pPlayer[PLAYER_COUNT];

Color background = {0, 0, 0, 1.0};
Color foreground = {1.0, 1.0, 1.0, 1.0};

/**
 * Initialize players.
 */
inline void initialize_players() {
    for (unsigned int i = 0; i < PLAYER_COUNT; i++) {
        pPlayer[i] = &player[i];
        player[i].position = &pos[i];
        player[i].size = &size[i];

        player[i].points = 0;
        player[i].position->y = (float)window_height / 2;
        player[i].size->x = 8.0f;
        player[i].size->y = 80.0f;
    }
    reset_players();
}

inline void reset_players() {
    player[PLAYER_ONE].position->y = (float)window_height / 2;
    player[PLAYER_TWO].position->y = (float)window_height / 2;
    player[PLAYER_ONE].position->x = 16.0;
    player[PLAYER_TWO].position->x = (float)window_width - 16.0 - player[PLAYER_TWO].size->x;
}

/**
 * Process players.
 *
 * @param delta_time Time since last frame.
 */
inline void process_players(double delta_time) {
    // Get inputs
    // FIXME: do input handling in another function and allow for multiple keys to do one function
    const bool *keys = app_get_input_keys();
    // Player 1
    if (keys[SDL_SCANCODE_W])
        player[PLAYER_ONE].position->y -= speed_shared * delta_time;
    if (keys[SDL_SCANCODE_S])
        player[PLAYER_ONE].position->y += speed_shared * delta_time;
    // Player 2
    if (keys[SDL_SCANCODE_UP])
        player[PLAYER_TWO].position->y -= speed_shared * delta_time;
    if (keys[SDL_SCANCODE_DOWN])
        player[PLAYER_TWO].position->y += speed_shared * delta_time;

    // Preventing players from leaving the screen
    for (unsigned int i = 0; i < PLAYER_COUNT; i++) {
        if (player[i].position->y < 0.0f)
            player[i].position->y = 0;
        else if (player[i].position->y + player[i].size->y > window_height)
            player[i].position->y = window_height - player[i].size->y;
    }
}

/**
 * Render players.
 */
inline void draw_players() {
    SDL_Renderer *renderer = app_get_renderer();
    for (unsigned int i = 0; i < PLAYER_COUNT; i++) {
        SDL_FRect rect = vec_to_rect(player[i].position, player[i].size);
        SDL_RenderFillRect(renderer, &rect);

        if (app_debug){
            // bcol sets color to foreground to draw debug stuff, 'i' is used to differenciate between players
            Color bcol = {0.0, 1.0, i, 1.0};
            app_set_draw_color(&bcol);
            Vector2 pos1 = {0.0, (player[i].position->y + player[i].size->y/2)};
            Vector2 pos2 = {window_width, (player[i].position->y + player[i].size->y/2)};
            app_draw_line(&pos1, &pos2);
            app_set_draw_color(&foreground);
        }
    }
}
