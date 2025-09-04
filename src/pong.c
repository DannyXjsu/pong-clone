/**
 * @file pong.c
 */

#include "app.h"
#include "pong.h"
#include "pong_player.h"
#include "pong_ball.h"
#include "math.h"
#include "utils.h"

#include <math.h>
#include <stdio.h>

static const char *score_wav = "score.wav";
Sound *score_sound = NULL;

inline void score() {
    const unsigned int _player = pBall->velocity.x > 0.0 ? PLAYER_ONE : PLAYER_TWO;
    pPlayer[_player]->points++;
    pBall->velocity.x = invert(pBall->velocity.x);
    speed_shared = DEFAULT_PLAYER_SPEED;

    app_play_sound(score_sound);

    pBall->reset();
    for(int i = 0; i < PLAYER_COUNT; i++)
        pPlayer[i]->reset();
}


inline void pong_initialize(){
    score_sound = app_load_sound(score_wav);
    initialize_ball();
    initialize_players();
    pong_reset();
}

inline void pong_reset(){
    pBall->reset();
    for(int i = 0; i < PLAYER_COUNT; i++){
        pPlayer[i]->reset();
        pPlayer[i]->points = 0;
    }
}


static inline void draw_center_line() {
    Vector2 pos1 = {(float)window_width / 2, 0.0};
    Vector2 pos2 = {(float)window_width / 2, window_height};
    app_draw_line(&pos1, &pos2);
}


inline void pong_render(){
    // Set foreground color
    app_set_draw_color(&foreground);
    // Render player points counter
    app_draw_text(&(Vector2){window_width / 3, 32}, TEXT_SCALE, "%u", pPlayer[0]->points);
    app_draw_text(&(Vector2){window_width - window_width / 3, 32}, TEXT_SCALE, "%u", pPlayer[1]->points);

    if (app_debug){
        app_draw_text(&(Vector2){16,48}, 1.2, "%s=%.2f", var2str(pBall->position.x), pBall->position.x);
        app_draw_text(&(Vector2){16,64}, 1.2, "%s=%.2f", var2str(pBall->position.y), pBall->position.y);
        app_draw_text(&(Vector2){16,80}, 1.2, "%s=%.2f", var2str(pBall->velocity.x), pBall->velocity.x);
        app_draw_text(&(Vector2){16,96}, 1.2, "%s=%.2f", var2str(pBall->velocity.y), pBall->velocity.y);
        app_draw_text(&(Vector2){16,112}, 1.2, "%s=%.2f", var2str(pBall->size.w), pBall->size.w);
        app_draw_text(&(Vector2){16,128}, 1.2, "%s=%.2f", var2str(pBall->size.h), pBall->size.h);
        app_draw_text(&(Vector2){16,144}, 1.2, "%s=%.2f", var2str(pBall->speed), pBall->speed);

        app_draw_text(&(Vector2){16,window_height-48}, 1.2, "%s=%.2f", var2str(pPlayer[0]->position.x), pPlayer[0]->position.x);
        app_draw_text(&(Vector2){16,window_height-64}, 1.2, "%s=%.2f", var2str(pPlayer[0]->position.y), pPlayer[0]->position.y);
        app_draw_text(&(Vector2){16,window_height-80}, 1.2, "%s=%.2f", var2str(pPlayer[0]->size.w), pPlayer[0]->size.w);
        app_draw_text(&(Vector2){16,window_height-96}, 1.2, "%s=%.2f", var2str(pPlayer[0]->size.h), pPlayer[0]->size.h);
        app_draw_text(&(Vector2){16,window_height-112}, 1.2, "%s=%d", var2str(pPlayer[0]->points), pPlayer[0]->points);

        app_draw_text(&(Vector2){window_width-300,window_height-48}, 1.2, "%s=%.2f", var2str(pPlayer[1]->position.x), pPlayer[1]->position.x);
        app_draw_text(&(Vector2){window_width-300,window_height-64}, 1.2, "%s=%.2f", var2str(pPlayer[1]->position.y), pPlayer[1]->position.y);
        app_draw_text(&(Vector2){window_width-300,window_height-80}, 1.2, "%s=%.2f", var2str(pPlayer[1]->size.w), pPlayer[1]->size.w);
        app_draw_text(&(Vector2){window_width-300,window_height-96}, 1.2, "%s=%.2f", var2str(pPlayer[1]->size.h), pPlayer[1]->size.h);
        app_draw_text(&(Vector2){window_width-300,window_height-112}, 1.2, "%s=%d", var2str(pPlayer[1]->points), pPlayer[1]->points);
    }

    // Inform the players the game is paused
    if (pause){
        app_draw_text(&(Vector2){((float)window_width/2 - 70), ((float)window_height/2 - 16)}, TEXT_SCALE, "Game Paused");
    }


    draw_players();
    draw_ball();
    draw_center_line();
}


inline void pong_process(){
    const float dt = app_get_delta_time();
    process_ball(dt);
    process_players(dt);
}
