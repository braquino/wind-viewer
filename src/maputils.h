#ifndef MAPUTILS_H
#define MAPUTILS_H

#include "windpoint.h"
#include "station.h"
#include "raylib.h"

#define WIND_SPEED_FACTOR 0.02
#define MAX_DISTANCE 100

void populate_random_windpoints(WindPoint* wpoints[], int length, Rectangle area);

void clean_expired_windpoints(WindPoint* wpoints[], int length, int seconds_to_expire);

// Set WindPoint speed and direction based on array of Station
void stations_influence_wpoint(Station* stations[], int stations_len, WindPoint* wp);

#endif