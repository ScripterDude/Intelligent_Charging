#include "main.h"
#include "graph_tool.h"



int main(){

    printf("[MAIN] Program started\n");

    user_input_t input = prompt_for_input();


    schedule_charging(input);


    return 0;
}


user_input_t prompt_for_input() {
    user_input_t input;

    input.start.date = "2026-09-15";
    input.start.hour = 8;

    input.end.date = "2026-09-16";
    input.end.hour = 18;

    input.kwh = 40;
    input.duration = 5;

    return input;
}

int compare_price(const void *a, const void *b)
{
    const price_point *pa = a;
    const price_point *pb = b;

    if (pa->price < pb->price) return -1;
    if (pa->price > pb->price) return 1;
    return 0;
}

void sort_arr(price_point prices[], int count)
{
    qsort(prices, count, sizeof(price_point), compare_price);
}

int charge_hours(user_input_t input) {
    return 5;
}

schedule_t schedule_charging(user_input_t input)
{
    schedule_t new_schedule;

    int hours_to_charge = charge_hours(input);

    price_point prices_today[MAX_HOURS];
    price_point prices_tomorrow[MAX_HOURS];

    int today_count = get_prices(input, true, prices_today);
    int tomorrow_count = get_prices(input, false, prices_tomorrow);

    sort_arr(prices_today, today_count);
    sort_arr(prices_tomorrow, tomorrow_count);

    printf("TODAY:\n");
    for (int i = 0; i < today_count; i++) {
        printf("Hour: %d Price: %.5f\n",
               prices_today[i].hour,
               prices_today[i].price);
    }

    printf("\nTOMORROW:\n");
    for (int i = 0; i < tomorrow_count; i++) {
        printf("Hour: %d Price: %.5f\n",
               prices_tomorrow[i].hour,
               prices_tomorrow[i].price);
    }

    int today_i = 0;
    int tomorrow_i = 0;

    for (int i = 0; i < hours_to_charge; i++) {

        if (prices_today[today_i].price <= prices_tomorrow[tomorrow_i].price) {

            new_schedule.charging_hours[i].hour =
                prices_today[today_i].hour;

            new_schedule.charging_hours[i].date =
                input.start.date;

            today_i++;

        } else {

            new_schedule.charging_hours[i].hour =
                prices_tomorrow[tomorrow_i].hour;

            new_schedule.charging_hours[i].date =
                input.end.date;

            tomorrow_i++;
        }
    }

    new_schedule.start = input.start;
    new_schedule.end = input.end;

    printf("\nOPTIMAL CHARGETIME:\n");
    for (int i = 0; i < hours_to_charge; i++) {
        printf("%s Hour: %d\n",
               new_schedule.charging_hours[i].date,
               new_schedule.charging_hours[i].hour);
    }

    call_graph(hours_to_charge, new_schedule, input);

    return new_schedule;
}

int schedule_optimal_plan(user_input_t input) {
    return 0;
}

int get_prices(
    user_input_t input,
    bool today,
    price_point prices[MAX_HOURS]
)
{
    const char *date = today ? input.start.date : input.end.date;

    if (date == NULL) {
        printf("Invalid date\n");
        return 0;
    }

    char year[5];
    char month[3];
    char day[3];

    if (sscanf(
            date,
            "%4[0-9]-%2[0-9]-%2[0-9]",
            year,
            month,
            day
        ) != 3)
    {
        printf("Invalid date format: %s\n", date);
        return 0;
    }

    char command[256];

    snprintf(
        command,
        sizeof(command),
        "python -u -c \"import api_manager; "
        "api_manager.print_prices('%s','%s','%s')\"",
        year,
        month,
        day
    );

    FILE *fp = popen(command, "r");

    if (fp == NULL) {
        printf("Failed to run Python\n");
        return 0;
    }

    int i = 0;

    while (
        i < MAX_HOURS &&
        fscanf(fp, "%d %lf", &prices[i].hour, &prices[i].price) == 2
    ) {
        i++;
    }

    pclose(fp);

    return i;
}