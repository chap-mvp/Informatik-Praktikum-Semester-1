/*
 Filename  : 1_2_zeichenkette_ordnen.c
 Program   : Sorts user input alphabetically
 Input     : User inputs a string of 6 characters in random order
 Output    : Pseudo sorts the string alphabetically, and tells how often a character was used. Skips illegal characters.
 Author    : Akram, M. Issmaeel
 Version   : V02 - 07.12.2025

 Checklist  :
    ✓ - die Zeichenkette k über die Tastatur einlesen und auf zulässige Zeichen prüfen (Falls unzulässige Zeichen vorkommen, ist eine Fehlermeldung auf dem Bildschirm auszugeben.)
    ✓ - die Länge der Zeichenkette ermitteln
    ✓ - die in k enthaltenen Zeichen und deren Anzahl ermitteln
    ✓ - die alphabetisch sortierte Zeichenkette z berechnen
    ✓ - eine Ausgabe analog zum obigen Beispiel auf dem Bildschirm erzeugen
 */

#include <stdio.h>

int main()
{
    // Set the array size
    int userInputStringSize = 50;
    char userInputString[userInputStringSize];
    // Set a 2D array for allowed letters and their respective counters
    char allowedLetters[][6] = {{'C', 'D', 'H', 'Q', 'T', 'Y'},
                                {0, 0, 0, 0, 0, 0}};

    // Ask for input
    printf("Enter your string of letters here: you are allowed only C, D, H, Q, T, Y\n");

    // so long as user has less inputs than the array allows
    for (int i = 0; i < userInputStringSize; i++)
    {
        // store values in a variable and end if its a newline character
        char c = getchar();
        if (c == '\n')
            break;

        // if the value is inside the 2D array, increase its counter, else print error
        for (int j = 0; j < 6; j++)
        { 
            if (c == allowedLetters[0][j])
                allowedLetters[1][j]++;

            if (c != 'C' &&
                c != 'D' &&
                c != 'H' &&
                c != 'Q' &&
                c != 'T' &&
                c != 'Y')
            {
                printf("Wrong Input! Restart!");
                return 0;
            }
        }
        // Assign the value to an array
        userInputString[i] = c;
    }

    // Get the total letters assigned to the array by the sum of the counter
    int newStringSize = 0;
    for (int i = 0; i < 6; i++)
        newStringSize += allowedLetters[1][i]; //as much as user entered

    // Create a new array with its length as the sum
    char sortedUserInput[newStringSize];

    // increase the value inside the loop from outside the loop
    int stringSizeCounter = 0;

    // Print the letters in order as often as they are given
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < allowedLetters[1][i]; j++)
        {
            sortedUserInput[stringSizeCounter] = allowedLetters[0][i];
            stringSizeCounter++;
        }

    // Print the sorted array
    for (int i = 0; i < newStringSize; i++)
        printf("%c", sortedUserInput[i]);

    // Print the letter amount
    printf("\nYou entered %d characters!\n", newStringSize);

    // Print the letter counts, if 0, dont print
    for (int i = 0; i < newStringSize; i++) 
        if (allowedLetters[1][i] != 0)
        {
            if (i == 0)
                printf("C(%d) ", allowedLetters[1][i]);
            if (i == 1)
                printf("D(%d) ", allowedLetters[1][i]);
            if (i == 2)
                printf("H(%d) ", allowedLetters[1][i]);
            if (i == 3)
                printf("Q(%d) ", allowedLetters[1][i]);
            if (i == 4)
                printf("T(%d) ", allowedLetters[1][i]);
            if (i == 5)
                printf("Y(%d) ", allowedLetters[1][i]);
        }
}