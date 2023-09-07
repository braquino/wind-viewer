#ifndef WINDPOINT_H
#define WINDPOINT_H

#include "raylib.h"

typedef struct WindPoint
{
    Vector2 pos;
    Vector2 speed;
    long start_time;
} WindPoint;

// Changes position based on speed
void windpoint_move(WindPoint *wp);

/**
 * Creates new WindPoint
 * 
 * @param x start position
 * @param y start position
 */
WindPoint* windpoint_new(float x, float y);

/**
 * Check if WindPoint is expired
 * 
 * @param wp 
 * @param seconds max seconds of life
 */
bool windpoint_expired(WindPoint* wp, int seconds);

// Creates a new WindPoint at random position
WindPoint* windpoint_new_rand(Vector2 min_pos, Vector2 max_pos);

// Sets random speed to a WindPoint
void windpoint_set_rand_speed(WindPoint* wp, Vector2 min_speed, Vector2 max_speed);

/**
 * Drawn a windpoint on raylib
 * 
 * @param wp 
 * @param expiration seconds to expire this WindPoint
 */
void windpoint_drawn(WindPoint* wp, int expiration);

#endif