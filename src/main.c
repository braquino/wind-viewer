#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "raylib.h"
#include "maputils.h"

#define MAX_POINTS 400
#define POINT_EXPIRATION 15


int main(void)
{
    InitWindow(800, 600, "Wind Viewer");
    SetTargetFPS(60);

    WindPoint* wpoints[MAX_POINTS];
    for (int i=0; i<MAX_POINTS; i++)
        wpoints[i] = NULL;
    
    Station s = {(Vector2){50, 50}, 0, 15};

    while(!WindowShouldClose())
    {
        clean_expired_windpoints(wpoints, MAX_POINTS, POINT_EXPIRATION);
        populate_random_windpoints(wpoints, MAX_POINTS, (Rectangle){375, 275, 50, 50});

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
            station_drawn(&s);
            DrawText(TextFormat("angolo: %f", s.direction), 20, 530, 20, BLACK);
            DrawText(TextFormat("time: %ld", now), 20, 560, 20, BLACK);
        EndDrawing();
        s.direction += 0.5;
    }
    CloseWindow();
    return 0;
}