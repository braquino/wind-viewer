#include "maputils.h"
#include <stdlib.h>
#include <math.h>

void populate_random_windpoints(WindPoint* wpoints[], int length, Rectangle area)
{
    for (int i=0; i<length; i++)
    {
        if (wpoints[i] == NULL && ((float)rand() / RAND_MAX) < 0.001) {
            WindPoint* wp = windpoint_new_rand((Vector2){area.x, area.y}, (Vector2){area.x + area.width, area.y + area.height});
            windpoint_set_rand_speed(wp, (Vector2){-0.5,-0.5}, (Vector2){0.5,0.5});
            wpoints[i] = wp;
        }
    }
}

void clean_expired_windpoints(WindPoint* wpoints[], int length, int seconds_to_expire)
{
    for (int i=0; i<length; i++)
    {
        if (wpoints[i] != NULL && windpoint_expired(wpoints[i], seconds_to_expire)) {
            WindPoint* wp = wpoints[i];
            wpoints[i] = NULL;
            free(wp);
        }
            
    }
}

void stations_influence_wpoint(Station* stations[], int stations_len, WindPoint* wp)
{
    double sum_distance = 0;
    double sum_x_product = 0;
    double sum_y_product = 0;

    for (int i=0; i<stations_len; i++)
    {
        Station* s = stations[i];
        double distance = sqrt(pow(s->pos.x - wp->pos.x, 2) + pow(s->pos.y - wp->pos.x, 2));
        sum_distance += distance;
        Vector2 v_direction = direction_to_vector(s->direction);
        sum_x_product += v_direction.x * distance * s->wind_speed * WIND_SPEED_FACTOR;
        sum_y_product += v_direction.y * distance * s->wind_speed * WIND_SPEED_FACTOR;
    }
    if (sum_distance > 0)
        wp->speed = (Vector2){sum_x_product / sum_distance, sum_y_product / sum_distance};
}