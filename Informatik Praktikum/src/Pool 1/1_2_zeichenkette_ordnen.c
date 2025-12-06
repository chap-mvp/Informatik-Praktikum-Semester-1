/*
 Filename  : 1_2_zeichenkette_ordnen.c
 Program   : Sorts user input alphabetically
 Input     : User inputs a string of 6 characters in random order 
 Output    : Pseudo sorts the string alphabetically, and tells how often a character was used. Skips illegal characters.
 Author    : Akram, M. Issmaeel
 Version   : V01 - 06.12.2025
 */

#include <stdio.h>

int main()
{
    int charSize = 50;
    char allowedLetters[][6] = {{'C', 'D', 'H', 'Q', 'T', 'Y'},
                                {0, 0, 0, 0, 0, 0}};

    char userInput[50] = {0}; 

    for (int i = 0; i < charSize; i++)
        printf("%c", userInput[i]);

    printf("Enter your string of letters here:\n");
    for (int i = 0; i < charSize; i++)
    {
        int c = getchar();
        if (c == '\n')
        {
            break;
        }
        for (int j = 0; j < 6; j++)
        {
            if ((char)c == allowedLetters[0][j])
            {
                allowedLetters[1][j]++;
            }
        }
        userInput[i] = (char)c;
    }

    int newStringSize = 0;
    for (int i = 0; i < 6; i++)
        newStringSize += allowedLetters[1][i];

    printf("You entered %d characters!\n", newStringSize);

    char sortedUserInput[newStringSize];
    int stringSizeCounter = 0;

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < allowedLetters[1][i]; j++)
        {
            sortedUserInput[stringSizeCounter] = allowedLetters[0][i];
            stringSizeCounter++;
        }

    for (int i = 0; i < newStringSize; i++)
    {
        printf("%c", sortedUserInput[i]);
    }

    printf("\n");

    for (int i = 0; i < 6; i++)
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