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
    int min, max;
    printf("What is the range of values you would like to guess? (min, max) - ");
    scanf("(%d, %d)", &min, &max);                               

    float allowedTries = ceil(((float)max - (float)min) * 0.1f); 

    srand(time(NULL));
    int randomNumber;
    randomNumber = min + rand() % (max - min + 1);              

    int userGuesses = randomNumber + 1;

    int guessCount = 0;

    if (allowedTries <= 1)
        printf("You have %.0f try!\n", allowedTries);
    else
        printf("You have %.0f tries!\n", allowedTries);

    while (guessCount < allowedTries)
    {
        printf("\nPlease guess a number! ");                    
        scanf("%d", &userGuesses);
        guessCount++;

        if (userGuesses < min || userGuesses > max)
        {
            printf("Out of range input!\n");
            guessCount--;
        }

        if (userGuesses < randomNumber)
            printf("The number is smaller!\n");
        else if (userGuesses > randomNumber)
            printf("The number is larger!\n");

        if (userGuesses == randomNumber)
        {
            if (guessCount == 1)
                printf("You guessed correctly in %d try!", guessCount);
            else
                printf("You guessed correctly in %d tries!", guessCount);  
            return 0;
        }
    }

    printf("You didn't guess the number %d!", randomNumber);
}