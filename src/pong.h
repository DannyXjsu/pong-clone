#ifndef PONG_H_
#define PONG_H_

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

#include "math.h"

#define PLAYER_COUNT 2 // You probably don't want to change this

#define DEFAULT_BALL_SPEED 4.0
#define BALL_SPEED_GAIN_ON_BOUNCE 0.5
#define BALL_SIZE 8
#define BALL_START_POSITION_X WINDOW_HEIGHT/2
#define BALL_START_POSITION_Y BALL_START_POSITION_X

#define DEFAULT_PLAYER_SPEED 8.0
#define PLAYER_SPEED_GAIN_ON_BOUNCE 0.05

typedef struct {
  unsigned int points;
  // ## Sharing properties
  // Asserting
  _Static_assert(sizeof(SDL_FRect) == sizeof(Vector2) * 2,
                 "Player struct union layout is incompatible, SDL_FRect "
                 "mismatches (Vector2 * 2)");
  union {
    struct {
      Vector2 position;
      Vector2 size;
    };
    SDL_FRect rect;
  };
} Player;

typedef struct {
  float speed;
  Vector2 velocity;
  // ## Sharing properties
  // Asserting
  _Static_assert(sizeof(SDL_FRect) == sizeof(Vector2) * 2,
                 "Player struct union layout is incompatible, SDL_FRect "
                 "mismatches (Vector2 * 2)");
  union {
    struct {
      Vector2 position;
      Vector2 size;
    };
    SDL_FRect rect;
  };
} Ball;

extern Player player[PLAYER_COUNT];
extern Ball ball;
extern float speed_shared;

extern bool is_ball_touching_player(unsigned int who);

extern void scored(void);
extern void bounced(void);
extern void reset_ball(void);

extern void initialize_players(void);
extern void initialize_ball(void);

extern void process_ball(double delta_time);
extern void process_players(double delta_time);

extern void render_players(SDL_Renderer *renderer);
extern void render_ball(SDL_Renderer *renderer);
extern void render_center_line(SDL_Renderer *renderer);

#endif // PONG_H_
