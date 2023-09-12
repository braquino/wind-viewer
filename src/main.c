#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "raylib.h"
#include "maputils.h"

#define MAX_POINTS 400
#define POINT_EXPIRATION 50


int main(void)
{
    InitWindow(800, 600, "Wind Viewer");
    SetTargetFPS(60);

    WindPoint* wpoints[MAX_POINTS];
    for (int i=0; i<MAX_POINTS; i++)
        wpoints[i] = NULL;
    
    Station s1 = {(Vector2){300, 200}, 0, 15};
    Station s2 = {(Vector2){450, 200}, 90, 15};
    Station s3 = {(Vector2){300, 350}, 180, 15};
    Station s4 = {(Vector2){450, 350}, 270, 15};
    Station* stations[] = {&s1, &s2, &s3, &s4};

    while(!WindowShouldClose())
    {
        clean_expired_windpoints(wpoints, MAX_POINTS, POINT_EXPIRATION);
        populate_random_windpoints(wpoints, MAX_POINTS, (Rectangle){375, 275, 50, 50});

        for (int i=0; i<MAX_POINTS; i++)
        {
            if (wpoints[i] != NULL)
                stations_influence_wpoint(stations, 4, wpoints[i]);
        }

        time_t now = time(NULL);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            for (int i=0; i<MAX_POINTS; i++)
            {
                if (wpoints[i] != NULL){
                    WindPoint* wp = wpoints[i];
                    windpoint_drawn(wp, POINT_EXPIRATION);
                    windpoint_move(wp);
                }
            }
            for (int i=0; i<4; i++)
            {
                Station *s = stations[i];
                station_drawn(s);
                s->direction += 0.5;
            }

            DrawText(TextFormat("time: %ld", now), 20, 560, 20, BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}