#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#define MAX_HOURS 24

typedef struct date_point {
    char* date;
    int hour;
} date_point_t;

typedef struct user_input {
    date_point_t start;
    date_point_t end;
    int kwh;
    int duration;
} user_input_t;

typedef struct schedule {
    date_point_t start;
    date_point_t end;
    date_point_t charging_hours[MAX_HOURS];
} schedule_t;

typedef struct {
    int hour;
    double price;
} price_point;

user_input_t prompt_for_input();
int compare_price(const void *a, const void *b);
int get_prices(user_input_t input,bool today,price_point prices[MAX_HOURS]);
void sort_arr(price_point prices[], int count);
int charge_hours(user_input_t input);
schedule_t schedule_charging(user_input_t input);
int schedule_optimal_plan(user_input_t input);