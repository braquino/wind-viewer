#include <time.h>
#include <stdlib.h>
#include "windpoint.h"

void windpoint_move(WindPoint *wp)
{
    wp->pos.x += wp->speed.x;
    wp->pos.y += wp->speed.y;
}

WindPoint* windpoint_new(float x, float y)
{
    WindPoint* wp = malloc(sizeof(WindPoint));
    wp->pos = (Vector2){x, y};
    wp->speed = (Vector2){0, 0};
    wp->start_time = time(NULL);
    return wp;
}

bool windpoint_expired(WindPoint* wp, int seconds)
{
    return (wp->start_time + seconds < time(NULL));
}

WindPoint* windpoint_new_rand(Vector2 min_pos, Vector2 max_pos)
{
    float x = ((double)rand() / (double)RAND_MAX) * (max_pos.x - min_pos.x) + min_pos.x;
    float y = ((double)rand() / (double)RAND_MAX) * (max_pos.y - min_pos.y) + min_pos.y;
    return windpoint_new(x, y);
}

void windpoint_set_rand_speed(WindPoint* wp, Vector2 min_speed, Vector2 max_speed)
{
    float x_speed = ((double)rand() / (double)RAND_MAX) * (max_speed.x - min_speed.x) + min_speed.x;
    float y_speed = ((double)rand() / (double)RAND_MAX) * (max_speed.y - min_speed.y) + min_speed.y;
    wp->speed = (Vector2){x_speed, y_speed};
}

void windpoint_drawn(WindPoint* wp, int expiration)
{
    Color c = RED;
    c.a = (1 - (time(NULL) - wp->start_time) / (float)expiration) * 255;
    DrawCircleV(wp->pos, 3, c);
}