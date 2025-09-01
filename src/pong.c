/**
 * @file pong.c
 */

#include "app.h"
#include "pong.h"
#include "pong_player.h"
#include "pong_ball.h"
#include "math.h"
#include "utils.h"

#include <SDL3/SDL_stdinc.h>
#include <math.h>
#include <stdlib.h>


inline void score() {
    const unsigned int _player = ball.velocity.x > 0.0f ? PLAYER_ONE : PLAYER_TWO;
    player[_player].points++;
    ball.velocity.x = invert(ball.velocity.x);
    speed_shared = DEFAULT_PLAYER_SPEED;

    reset_ball();
    reset_players();
}


inline void pong_initialize(){
    initialize_ball();
    initialize_players();
}


/**
 * Render center line.
 *
 * @param renderer SDL renderer instance.
 */
static inline void draw_center_line() {
    SDL_Renderer *renderer = app_get_renderer();
    SDL_RenderLine(renderer, (float)window_width / 2, 0.0f,
                   (float)window_width / 2, window_height);
}


inline void pong_render(){
    SDL_Renderer* renderer = app_get_renderer();

    // Set foreground color
    app_set_draw_color(&foreground);
    // Render player points counter
    app_draw_text((Vector2){window_width / 3, 32}, TEXT_SCALE, "%u", player[0].points);
    app_draw_text((Vector2){window_width - window_width / 3, 32}, TEXT_SCALE, "%u", player[1].points);

    if (app_debug){
        app_draw_text((Vector2){16,48}, 1.2, "%s=%.2f", var2str(ball.position.x), ball.position.x);
        app_draw_text((Vector2){16,64}, 1.2, "%s=%.2f", var2str(ball.position.y), ball.position.y);
        app_draw_text((Vector2){16,80}, 1.2, "%s=%.2f", var2str(ball.velocity.x), ball.velocity.x);
        app_draw_text((Vector2){16,96}, 1.2, "%s=%.2f", var2str(ball.velocity.y), ball.velocity.y);
        app_draw_text((Vector2){16,112}, 1.2, "%s=%.2f", var2str(ball.size.w), ball.size.w);
        app_draw_text((Vector2){16,128}, 1.2, "%s=%.2f", var2str(ball.size.h), ball.size.h);
        app_draw_text((Vector2){16,144}, 1.2, "%s=%.2f", var2str(ball.speed), ball.speed);

        app_draw_text((Vector2){16,window_height-48}, 1.2, "%s=%.2f", var2str(player[0].position.x), player[0].position.x);
        app_draw_text((Vector2){16,window_height-64}, 1.2, "%s=%.2f", var2str(player[0].position.y), player[0].position.y);
        app_draw_text((Vector2){16,window_height-80}, 1.2, "%s=%.2f", var2str(player[0].size.w), player[0].size.w);
        app_draw_text((Vector2){16,window_height-96}, 1.2, "%s=%.2f", var2str(player[0].size.h), player[0].size.h);
        app_draw_text((Vector2){16,window_height-112}, 1.2, "%s=%d", var2str(player[0].points), player[0].points);

        app_draw_text((Vector2){window_width-300,window_height-48}, 1.2, "%s=%.2f", var2str(player[1].position.x), player[1].position.x);
        app_draw_text((Vector2){window_width-300,window_height-64}, 1.2, "%s=%.2f", var2str(player[1].position.y), player[1].position.y);
        app_draw_text((Vector2){window_width-300,window_height-80}, 1.2, "%s=%.2f", var2str(player[1].size.w), player[1].size.w);
        app_draw_text((Vector2){window_width-300,window_height-96}, 1.2, "%s=%.2f", var2str(player[1].size.h), player[1].size.h);
        app_draw_text((Vector2){window_width-300,window_height-112}, 1.2, "%s=%d", var2str(player[1].points), player[1].points);
    }

    // Inform the players the game is paused
    if (pause){
        //SDL_RenderDebugText(renderer, ((float)window_width/2 - 70) / TEXT_SCALE, ((float)window_height/2 - 16) / TEXT_SCALE, "Game Paused");
        app_draw_text((Vector2){((float)window_width/2 - 70), ((float)window_height/2 - 16)}, TEXT_SCALE, "Game Paused");
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
