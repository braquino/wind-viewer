#ifndef STATION_H
#define STATION_H

#include "raylib.h"

typedef struct Station {
    Vector2 pos;
    float direction;
    float wind_speed;
} Station;

// Render Station on Raylib
void station_drawn(Station* s);

// Creates new Station on heap
Station* station_new(Vector2 pos, float direction, float wind_speed);

// Convert 360 grades direction to x y vector, from 0 to 1
Vector2 direction_to_vector(float angle);

#endif