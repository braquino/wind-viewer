#include <time.h>
#include <stdlib.h>
#include "unity.h"
#include "windpoint.h"
#include "station.h"

void tearDown(void)
{

}

void setUp(void)
{

}

void test_windpoint_new(void)
{
    WindPoint* wp = windpoint_new(10.5, 20.34);
    TEST_ASSERT_EQUAL_FLOAT(10.5, wp->pos.x);
    TEST_ASSERT_EQUAL_FLOAT(20.34, wp->pos.y);
    TEST_ASSERT_EQUAL_FLOAT(0, wp->speed.x);
    TEST_ASSERT_EQUAL_FLOAT(0, wp->speed.y);
    time_t now = time(NULL);
    TEST_ASSERT_TRUE(wp->start_time <= now && wp->start_time > now - 2);
    free(wp);
}

void test_windpoint_move(void)
{
    WindPoint* wp = windpoint_new(10, 20);
    wp->speed = (Vector2){0.5, 0.2};
    windpoint_move(wp);
    TEST_ASSERT_EQUAL_FLOAT(10.5, wp->pos.x);
    TEST_ASSERT_EQUAL_FLOAT(20.2, wp->pos.y);
    free(wp);
}

void test_windpoint_expired(void)
{
    WindPoint* wp = windpoint_new(0,0);
    time_t now = time(NULL);
    wp->start_time = now - 20;
    TEST_ASSERT_TRUE(windpoint_expired(wp, 10));
    TEST_ASSERT_FALSE(windpoint_expired(wp, 30));
}

void test_windpoint_new_rand(void)
{
    for (int i=0; i<1000; i++){
        WindPoint* wp = windpoint_new_rand((Vector2){50, 50}, (Vector2){1000, 300});
        TEST_ASSERT_TRUE(wp->pos.x >= 50);
        TEST_ASSERT_TRUE(wp->pos.y >= 50);
        TEST_ASSERT_TRUE(wp->pos.x <= 1000);
        TEST_ASSERT_TRUE(wp->pos.y <= 300);
        free(wp);
    }
}

void test_direction_to_vector(void)
{
    Vector2 v = direction_to_vector(0);
    TEST_ASSERT_FLOAT_WITHIN(0.0001, 0, v.x);
    TEST_ASSERT_EQUAL_FLOAT(-1, v.y);

    v = direction_to_vector(45);
    TEST_ASSERT_EQUAL_FLOAT(0.7071069, v.x);
    TEST_ASSERT_EQUAL_FLOAT(-0.7071069, v.y);

    v = direction_to_vector(90);
    TEST_ASSERT_EQUAL_FLOAT(1, v.x);
    TEST_ASSERT_FLOAT_WITHIN(0.0001, 0, v.y);

    v = direction_to_vector(135);
    TEST_ASSERT_EQUAL_FLOAT(0.7071069, v.x);
    TEST_ASSERT_EQUAL_FLOAT(0.7071069, v.y);

    v = direction_to_vector(180);
    TEST_ASSERT_FLOAT_WITHIN(0.0001, 0, v.x);
    TEST_ASSERT_EQUAL_FLOAT(1, v.y);

    v = direction_to_vector(225);
    TEST_ASSERT_EQUAL_FLOAT(-0.7071069, v.x);
    TEST_ASSERT_EQUAL_FLOAT(0.7071069, v.y);

    v = direction_to_vector(270);
    TEST_ASSERT_EQUAL_FLOAT(-1, v.x);
    TEST_ASSERT_FLOAT_WITHIN(0.0001, 0, v.y);

    v = direction_to_vector(315);
    TEST_ASSERT_EQUAL_FLOAT(-0.7071069, v.x);
    TEST_ASSERT_EQUAL_FLOAT(-0.7071069, v.y);

    v = direction_to_vector(360);
    TEST_ASSERT_FLOAT_WITHIN(0.0001, 0, v.x);
    TEST_ASSERT_EQUAL_FLOAT(-1, v.y);
}

void stations_influence_wpoint(void)
{
    // TODO: implement
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_windpoint_new);
    RUN_TEST(test_windpoint_move);
    RUN_TEST(test_windpoint_expired);
    RUN_TEST(test_windpoint_new_rand);
    RUN_TEST(test_direction_to_vector);
    return UNITY_END();
}