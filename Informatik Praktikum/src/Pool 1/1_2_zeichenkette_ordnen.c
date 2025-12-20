/*
 Filename  : 1_2_zeichenkette_ordnen.c
 Program   : Sorts user input alphabetically
 Input     : User inputs a string of 6 characters in random order
 Output    : Pseudo sorts the string alphabetically, and tells how often a character was used. Skips illegal characters.
 Author    : Akram, M. Issmaeel
 Version   : V03 - 20.12.2025
 */

#include <stdio.h>
#define MAX_INPUT_SIZE 50
#define NUM_VALID_CHARS 6

int main()
{
    char userString[MAX_INPUT_SIZE];

    // Set a 2D array for allowed letters and their respective counters
    char allowedLetters[][NUM_VALID_CHARS] = {{'C', 'D', 'H', 'Q', 'T', 'Y'},
                                              {0, 0, 0, 0, 0, 0}};

    printf("Enter your string of letters below, you are allowed only C, D, H, Q, T, Y\nYour String, press enter to exit: ");

    // so long as user has less inputs than the array allows
    for (int i = 0; i < MAX_INPUT_SIZE; i++)
    {
        // store values in a variable and end if its a newline character
        char c = getchar();
        if (c == '\n')
            break;

        // if the value is inside the 2D array, increase its counter, else print error
        for (int j = 0; j < NUM_VALID_CHARS; j++)
        {
            if (c == allowedLetters[0][j])
                allowedLetters[1][j]++;

            // Errorhandling for correct input
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
        userString[i] = c;
    }

    // Get the total letters assigned to the array by the sum of the counter
    int newStringSize = 0;
    for (int i = 0; i < NUM_VALID_CHARS; i++)
        newStringSize += allowedLetters[1][i];

    char sortedOutput[newStringSize];

    int stringSizeCounter = 0;

    // Print the letters in order as often as they are given
    for (int i = 0; i < NUM_VALID_CHARS; i++)
        for (int j = 0; j < allowedLetters[1][i]; j++)
        {
            sortedOutput[stringSizeCounter] = allowedLetters[0][i];
            stringSizeCounter++;
        }

    printf("Sort String: ");
    // Print the sorted array
    for (int i = 0; i < newStringSize; i++)
        printf("%c", sortedOutput[i]);

    printf("\nYou entered %d characters!\n", newStringSize);

    // Print the letter counts, if 0, dont print
    for (int i = 0; i < NUM_VALID_CHARS; i++)
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
    return 0;
}