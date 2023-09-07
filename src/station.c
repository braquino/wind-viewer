#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "station.h"

Vector2 direction_to_vector(float direction)
{
    float angle180 = 360 - ((int)direction % 360);
    float radians = angle180 * (PI / 180);
    return (Vector2){-sin(radians), -cos(radians)};
}

void station_drawn(Station* s)
{
    DrawCircleV(s->pos, 4, DARKBLUE);
    Vector2 v = direction_to_vector(s->direction);
    double factor = 30;
    Vector2 endline = {v.x * factor + s->pos.x, v.y * factor + s->pos.y};
    DrawLineV(s->pos, endline, DARKBLUE);
}

Station* station_new(Vector2 pos, float direction, float wind_speed)
{
    Station* s = malloc(sizeof(Station));
    s->pos = pos;
    s->direction = direction;
    s->wind_speed = wind_speed;
    return s;
}