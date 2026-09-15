#include <stdio.h>
#include <stdlib.h>

typedef struct user_input{
int start;
int end;
int kwh;
int duration;
} user_input_t;

typedef struct schedule{
int start;
int end;
int charge_start;
int charge_duration;

} schedule_t;
schedule_t generate_empty_time_schedule(user_input_t input);
user_input_t prompt_for_input(){
    user_input_t input;
    printf("Enter parking time, next pickup time, required kwh \n");
    
    int result = scanf("%d %d %d", &input.start, &input.end, &input.kwh);
    while (result !=3){
        printf("Invalid input\n");
        printf("Enter parking time, next pickup time, required kwh \n");
        result = scanf("%d %d %d", &input.start, &input.end, &input.kwh);
    }
    input.duration = (input.end-input.start);
    // if negative number, time suggest its next day.
    if (input.duration<0){
        //eksempel: afleverer kl 12:00 henter igen 08:30. input.start+x=24
        int x=input.start - 24;
        int time_to_add = -x+input.end;
        input.duration = time_to_add;
    }
    printf("Duration: %d", input.duration);
    generate_empty_time_schedule(input);
    return input;
};

int schedule_optimal_plan(user_input_t input){
    
    //get_price_interval(input.start,input.end);
    //get_optimal_charging_time();
}

schedule_t generate_empty_time_schedule(user_input_t input){
    schedule_t test;
    //arrays require constant size, therefore we convert duration to const
    system("python3 -c \"import api_manager; api_manager.get_price_data()\"");


    
    return test;
}