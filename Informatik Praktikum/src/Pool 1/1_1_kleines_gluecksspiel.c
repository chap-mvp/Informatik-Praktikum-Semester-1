/*
 Filename  : 1_1_kleines_gluecksspiel.c
 Program   : Plays a game with the user, where user has to guess a random number between 2 values
 Input     : Minimum and maximum for the interval in which to play, the user guessing the number
 Output    : Whether user wins/loses, is above or below the value to be guessed and the value itself.
 Author    : Akram, M. Issmaeel
 Version   : V01 - 06.12.2025

 Checklist :
    ✓ - per Zufall eine natürliche Zahl generieren, wobei die Untergrenze und die Obergrenze des Wertebereichs zuvor als natürliche Zahlen von der Tastatur eingelesen werden sollen
    ✓ - die maximale Anzahl für die Rateversuche berechnen, welche 10% des eingegebenen Wertebereichs betragen soll (aufrunden)
    ✓ - für jeden Rateversuch eine natürliche Zahl von der Tastatur einlesen (Testzahl) und mit der zu erratenden Zahl vergleichen
    ✓ - sinnvolle Fehlerbehandlungen ausführen, falls nicht zulässige Zahlenwerte für die Grenzen des Wertebereichs oder die Testzahl eingegeben werden
    ✓ - ausgeben, ob die Testzahl größer oder kleiner ist als die zu erratende Zahl
    ✓ - bei Übereinstimmung der Testzahl mit der zu erratenden Zahl das Spiel als gewonnen beenden und die Anzahl der benötigen Rateversuche ausgeben
    ✓ - bei Erreichen der maximalen Anzahl Rateversuche das Spiel als verloren beenden und die zu erratende Zahl ausgeben
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
int main()
{
    // Input for largest and smallest values
    int min, max;
    printf("What is the range of values you would like to guess? Only enter integers in this form: min,max - ");
    
    // min, max seperately
    if (scanf("%d,%d", &min, &max) != 1)
    {
        printf("\nInvalid value! breaking...");
        return 0;
    }

    if (max < min)
    {
        int temp = max;
        max = min;
        min = temp;
    }

    // Calculate allowed number of guesses
    float allowedTries = ceil(((float)max - (float)min) * 0.1f);
    if (allowedTries == 0)
    {
        allowedTries = 1;
    }

    // Generate random number
    srand(time(NULL));
    int randomNumber;
    randomNumber = min + rand() % (max - min + 1);

    // For later comparison issues: random number != usersGuess ONLY for initialization. e.g. without initialization the randomly assigned value could b same as the FIRST randomly generated number, although highly unlikely, it would cause the program to end immediately.
    int usersGuess = randomNumber + 1;

    // Keep track of guesses
    int guessCount = 0;
    // Prints how many guesses the player has
    if (allowedTries <= 1)
    {
        printf("You have %.0f try!\n", allowedTries); // singular
    }
    else
    {
        printf("You have %.0f tries!\n", allowedTries); // plural
    }
    // Start when allowed tries amount has not been reached
    while (guessCount < allowedTries)
    {
        // Ask user for guess
        printf("\nPlease guess a number! ");
        if (scanf("%d", &usersGuess) == 0)
        {
            printf("\nInvalid value! breaking...");
            return 0;
        }
        else
            guessCount++;
        // Check if guess is in range, if not, decrement guess count
        if (usersGuess < min || usersGuess > max)
        {
            printf("Out of range input!\n");
            guessCount--;
            // continue;
        }

        // Tell user if the guess is above or below the number to be guessed
        if (usersGuess < randomNumber)
        {
            printf("The number you guessed is too small!\n");
        }
        else if (usersGuess > randomNumber)
        {
            printf("The number you guessed is too large!\n");
        }
        // If user guesses the number correctly
        if (usersGuess == randomNumber)
        {
            if (guessCount == 1)
            {
                printf("You guessed correctly in %d try!", guessCount);
            }
            else
            {
                printf("You guessed correctly in %d tries!", guessCount);
            }
            return 0;
        }
    }

    // If the user cannot guess the number, print the random number
    printf("You couldn't guess the number %d!", randomNumber);
    return 0;
}