/*
 Filename  : 1_1_kleines_gluecksspiel.c
 Program   : User has to guess a value in a range
 Input     : There are no input parameters which are used in main
 Output    : The return value is always 0
 Author    : Akram, M. Issmaeel
 Version   : V02 - 20.12.2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main()
{
    int minValue = 0, maxValue = 0;
    printf("What is the range of values you would like to guess? Only enter integers in this form, press enter to exit - ");

    // Errorhandling for correct input
    if (scanf("%d,%d", &minValue, &maxValue) != 2)
    {
        printf("\nInvalid value! breaking...");
        return 0;
    }

    // Ensure min is actually smaller than max
    if (maxValue < minValue)
    {
        int temp = maxValue;
        maxValue = minValue;
        minValue = temp;
    }

    // Calculate the guesses the player has
    float allowedTries = ceil(((float)maxValue - (float)minValue) * 0.1f);
    if (allowedTries == 0)
    {
        allowedTries = 1;
    }

    srand(time(NULL));
    int randomNumber = 0;
    randomNumber = minValue + rand() % (maxValue - minValue + 1);

    // Initialize to invalid value to ensure first comparison works
    int usersGuess = randomNumber + 1;

    // Keep track of guesses
    int guessCount = 0;

    if (allowedTries <= 1)
        printf("You have %.0f try!\n", allowedTries); // singular
    else
        printf("You have %.0f tries!\n", allowedTries); // plural

    // as long as the guesses dont go over the allowed amount
    while (guessCount < allowedTries)
    {
        // Ask user for guess
        printf("\nPlease guess a number! ");

        // Errorhandling for correct input
        if (scanf("%d", &usersGuess) == 0)
        {
            printf("\nInvalid value! breaking...");
            return 0;
        }
        // If no error, increment guess counter
        else
            guessCount++;

        // If out of bound guess, decrement guess counter
        if (usersGuess < minValue || usersGuess > maxValue)
        {
            printf("Out of range input!\n");
            guessCount--;
        }

        // Tell the user if their guess is smaller or larger
        if (usersGuess < randomNumber)
            printf("The number you guessed is too small!\n");
        else if (usersGuess > randomNumber)
            printf("The number you guessed is too large!\n");

        // If user guesses the number correctly
        if (usersGuess == randomNumber)
        {
            if (guessCount == 1)
                printf("You guessed correctly in %d try!", guessCount); // singular
            else
                printf("You guessed correctly in %d tries!", guessCount); // plural
            return 0;
        }
    }

    // If the user cannot guess the number, print the random number
    printf("You couldn't guess the number %d!", randomNumber);
    return 0;
}