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
    int userInputStringSize = 50;
    char userInputString[userInputStringSize];
    char allowedLetters[][6] = {{'C', 'D', 'H', 'Q', 'T', 'Y'},
                                {0, 0, 0, 0, 0, 0}};

    printf("Enter your string of letters here: ");

    for (int i = 0; i < userInputStringSize; i++)
    {
        char c = getchar();
        if (c == '\n')
            break;

        for (int j = 0; j < 6; j++)
        {
            if (c == allowedLetters[0][j])          // If the letter is allowed
                allowedLetters[1][j]++;             // Increase its counter

            if (c != 'C' &&                         // If the letter is NOT allowed
                c != 'D' &&
                c != 'H' &&
                c != 'Q' &&
                c != 'T' &&
                c != 'Y')
            {
                printf("Wrong Input! Restart!");    // Printf an error and
                return 0;                           // exit the program
            }
        }
        userInputString[i] = c;                     // Assign the input values to an array
    }

    int newStringSize = 0;                          // Check for the amount of letters
    for (int i = 0; i < 6; i++)
        newStringSize += allowedLetters[1][i];      // Get the sum

    char sortedUserInput[newStringSize];            // Create a new array with its length as the sum
    int stringSizeCounter = 0;

    for (int i = 0; i < 6; i++)                     // Print the letters in order as often as they are given
        for (int j = 0; j < allowedLetters[1][i]; j++)
        {
            sortedUserInput[stringSizeCounter] = allowedLetters[0][i];
            stringSizeCounter++;
        }

    for (int i = 0; i < newStringSize; i++)         // Print the sorted array
        printf("%c", sortedUserInput[i]);

    printf("\nYou entered %d characters!\n", newStringSize);    // Print the letter amount

    for (int i = 0; i < newStringSize; i++)         // Print the letter counts
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