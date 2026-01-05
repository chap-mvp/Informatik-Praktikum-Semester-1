/*
 Filename  : 2_2_parkscheinautomat_simulieren.c
 Program   : Parking meter simulator with time-based fee calculation and payment processing
 Input     : Opening/closing hours, currency denominations for payment
 Output    : Entry/exit times, parking duration, fees, change breakdown, receipt
 Author    : Akram, M. Issmaeel
 Version   : V01 - 06.01.2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure to store time in hours, minutes, seconds format
typedef struct set_time
{
    int hours;
    int minutes;
    int seconds;
} set_time;

// array[0] = entry time, array[1] = duration, array[2] = exit time
set_time array[3];

int paid_money[7];
int return_money[5];

// Input: None, prompts user for currency denominations
// Output: Returns total sum of all denominations entered
float get_money_sum()
{
    float sum = 0.0f;
    int count;

    printf("10 euro notes: ");
    scanf("%d", &count);
    paid_money[0] = count;
    sum += count * 10.0f;

    printf("5 euro notes: ");
    scanf("%d", &count);
    paid_money[1] = count;
    sum += count * 5.0f;

    printf("2 euro coins: ");
    scanf("%d", &count);
    paid_money[2] = count;
    sum += count * 2.0f;

    printf("1 euro coins: ");
    scanf("%d", &count);
    paid_money[3] = count;
    sum += count * 1.0f;

    printf("50 cent coins: ");
    scanf("%d", &count);
    paid_money[4] = count;
    sum += count * 0.5f;

    printf("20 cent coins: ");
    scanf("%d", &count);
    paid_money[5] = count;
    sum += count * 0.2f;

    printf("10 cent coins: ");
    scanf("%d", &count);
    paid_money[6] = count;
    sum += count * 0.1f;

    return sum;
}

// Input: seconds - total seconds, h/m/s - pointers to store converted values
// Output: Converts total seconds into hours, minutes, seconds components via pointers
void seconds_to_hms(int seconds, int *h, int *m, int *s)
{
    *h = seconds / 3600;
    *m = (seconds % 3600) / 60;
    *s = seconds % 60;
}

// Input: time_spent_seconds - parking duration in seconds
// Output: Returns parking cost based on tiered pricing (first 10 min free, then 1.60€/1.40€/1.00€ per hour)
float calculate_cost(int time_spent_seconds)
{
    int minutes = time_spent_seconds / 60;

    // First 10 minutes free
    if (minutes <= 10)
        return 0.0;

    minutes -= 10; // Subtract free period

    float cost = 0.0;
    // Round up to next full hour for any partial hour started
    int hours_started = (minutes + 59) / 60;

    // Apply tiered pricing structure
    for (int i = 1; i <= hours_started; i++)
    {
        if (i == 1)
            cost += 1.60; // First hour
        else if (i == 2 || i == 3)
            cost += 1.40; // Hours 2-3
        else
            cost += 1.00; // Subsequent hours
    }

    return cost;
}

// Input: change - amount of change to return in euros
// Output: Prints change breakdown using largest denominations first (greedy algorithm)
void change_extractor(float change)
{
    // Convert to cents to avoid floating point precision issues
    int cents = (int)(change * 100 + 0.5);

    if (cents >= 200)
    {
        printf("%d x 2€\n", cents / 200);
        return_money[0] = cents / 200;
        cents = cents % 200;
    }
    if (cents >= 100)
    {
        printf("%d x 1€\n", cents / 100);
        return_money[1] = cents / 100;
        cents = cents % 100;
    }
    if (cents >= 50)
    {
        printf("%d x 50c\n", cents / 50);
        return_money[2] = cents / 50;
        cents = cents % 50;
    }
    if (cents >= 20)
    {
        printf("%d x 20c\n", cents / 20);
        return_money[3] = cents / 20;
        cents = cents % 20;
    }
    if (cents >= 10)
    {
        printf("%d x 10c\n", cents / 10);
        return_money[4] = cents / 10;
        cents = cents % 10;
    }
}

// Input: Opening/closing hours from user, system time for entry
// Output: Simulates parking session with entry/exit times, calculates fees, processes payment, prints receipt
int main()
{
    // Get current system time
    time_t raw_time;
    struct tm *time_info;
    time(&raw_time);
    time_info = localtime(&raw_time);

    srand(time(NULL)); // Seed random number generator

    int opening_hour = 0;
    int closing_hour = 0;

    // Get and validate opening hour
    printf("What time does it open? ");
    scanf("%d", &opening_hour);

    if (opening_hour >= 24 || opening_hour < 0)
    {
        printf("Wrong opening time!");
        return 0;
    }

    // Get and validate closing hour
    printf("What time does it close? ");
    scanf("%d", &closing_hour);
    if (closing_hour == 0)
        closing_hour = 24; // Midnight represented as 24

    if (closing_hour > 24 || closing_hour < 0)
    {
        printf("Wrong closing time!");
        return 0;
    }

    // Ensure opening hour is before closing hour
    if (opening_hour >= closing_hour)
    {
        printf("Wrong time inputs!");
        return 0;
    }

    // Check if current time is before opening hours
    if (time_info->tm_hour < opening_hour)
    {
        printf("The place still closed, please come back later!\n");
        return 0;
    }

    // Check if current time is after closing hours
    if (time_info->tm_hour >= closing_hour)
    {
        printf("The place has closed, have a nice day!\n");
        return 0;
    }

    // Record entry time from system clock
    array[0].hours = time_info->tm_hour;
    array[0].minutes = time_info->tm_min;
    array[0].seconds = time_info->tm_sec;

    printf("Entered: %02d:%02d:%02d\n", array[0].hours, array[0].minutes, array[0].seconds);

    // Calculate maximum possible parking duration until closing
    int current_seconds = array[0].hours * 3600 + array[0].minutes * 60 + array[0].seconds;
    int closing_seconds = closing_hour * 3600;
    int max_duration = closing_seconds - current_seconds;

    // Generate random parking duration within allowed time
    int duration_seconds = rand() % max_duration;

    int h, m, s;

    // Store duration in array[1]
    seconds_to_hms(duration_seconds, &h, &m, &s);
    array[1].hours = h;
    array[1].minutes = m;
    array[1].seconds = s;
    printf("Time spent: %02d:%02d:%02d\n", array[1].hours, array[1].minutes, array[1].seconds);

    // Calculate and store exit time in array[2]
    int exit_seconds = current_seconds + duration_seconds;
    seconds_to_hms(exit_seconds, &h, &m, &s);
    array[2].hours = h;
    array[2].minutes = m;
    array[2].seconds = s;
    printf("Exited: %02d:%02d:%02d\n", h, m, s);

    // Calculate parking fee based on duration
    float debt = calculate_cost(duration_seconds);

    printf("You have to pay %.2f!\n", debt);

    float paid = 0;

    // Loop until sufficient payment received
    while (paid < debt)
    {
        paid = get_money_sum();
        if (paid < debt)
            printf("Please pay the correct amount, your money has been returned!\n");
    }

    printf("You paid %.2f\n", paid);

    // Calculate and display change
    float change = paid - debt;
    printf("Your change is %.2f€\n", change);

    change_extractor(change); // Break down change into denominations

    // Print formatted receipt with all transaction details
    printf("[---------RECEIPT---------]\n"
           "[DATUM:         %02d.%02d.%02d]\n"
           "[Einfahrtszeit: %02d:%02d:%02d  ]\n"
           "[Ausfahrtzeit:  %02d:%02d:%02d  ]\n"
           "[Parkdauer:     %02d:%02d:%02d  ]\n"
           "[Parkgebühr:    %2.2f      ]\n"
           "[Gezahlt:       %2.2f     ]\n"
           "[Rückgeld:      %2.2f      ]\n",
           time_info->tm_mday, time_info->tm_mon + 1, time_info->tm_year + 1900,
           array[0].hours, array[0].minutes, array[0].seconds,
           array[2].hours, array[2].minutes, array[2].seconds,
           array[1].hours, array[1].minutes, array[1].seconds,
           debt, paid, change);
    printf("Paid: S10 - [%d], S5 - [%d], M2 - [%d], M1 - [%d], M50 - [%d], M20 - [%d], M10 - [%d]\n"
           "Received:                  M2 - [%d], M1 - [%d], M50 - [%d], M20 - [%d], M10 - [%d]\n",
           paid_money[0], paid_money[1], paid_money[2], paid_money[3], paid_money[4], paid_money[5], paid_money[6], return_money[0], return_money[1], return_money[2], return_money[3], return_money[4]);
}