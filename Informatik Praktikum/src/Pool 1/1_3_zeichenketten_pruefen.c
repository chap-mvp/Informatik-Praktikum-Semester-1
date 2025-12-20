/*
 Filename  : 1_3_zeichenketten_pruefen.c
 Program   : Checks whether one string is inside the other
 Input     : Both strings for checking
 Output    : Which string is inside which
 Author    : Akram, M. Issmaeel
 Version   : V02 - 20.12.2025
 */

#include <stdio.h>
#include <stdbool.h>
#define STRING_LENTH 100

int main()
{
    int length1 = 0;
    char string1[STRING_LENTH] = {0};

    int length2 = 0;
    char string2[STRING_LENTH] = {0};

    printf("Enter your first string of letters, press enter to continue (Z_1) - ");
    for (int i = 0; i < STRING_LENTH - 1; i++)
    {
        char c = getchar();
        if (c == '\n')
            break;

        // For invalid characters
        if ((c != 'A') && (c != 'C') && (c != 'D') && (c != '\n'))
        {
            printf("Wrong input, breaking...");
            return 0;
        }

        string1[i] = c;
        length1++;
    }

    printf("Enter your second string of letters, press enter to continue (Z_2)  - ");
    for (int i = 0; i < STRING_LENTH; i++)
    {
        char c = getchar();
        if (c == '\n')
            break;

        // For invalid characters
        if ((c != 'A') && (c != 'C') && (c != 'D') && (c != '\n'))
        {
            printf("Wrong input, breaking...");
            return 0;
        }
        string2[i] = c;
        length2++;
    }

    // Print the lengths of both strings
    printf("Z_1: [%d] \nZ_2: [%d]", length1, length2);

    // Check which string is longer and swap
    bool wasSwapped;
    if (length1 < length2)
    {
        char temp[STRING_LENTH];
        for (int i = 0; i < STRING_LENTH; i++)
        {
            temp[i] = string2[i];
            string2[i] = string1[i];
            string1[i] = temp[i];
        }

        int tempValue = 0;
        tempValue = length2;
        length2 = length1;
        length1 = tempValue;

        // if swapping happens, true for print at successful end
        wasSwapped = true;
    }

    int matchCount = 0;
    int positionLargeStrand;

    for (int i = 0; i < length1; i++)
    {
        for (int j = 0; j < length2; j++)
        {
            // If a match is found check block wise for complete match
            if (string2[j] == string1[i + j])
            {
                matchCount++;
                positionLargeStrand = i;
            }
            else
                matchCount = 0;
            // if the block is the same size as the smaller string, a full match is found
            if (matchCount == length2)
            {
                printf("\nElements match from the %d. character onwards\n", positionLargeStrand + 1);

                for (int i = 0; i < STRING_LENTH; i++)
                {
                    if (string1[i] == 0)
                        break;
                    printf("[%c]", string1[i]);
                }

                printf("\n");

                for (int i = 0; i < positionLargeStrand; i++)
                    printf("   ");

                for (int i = 0; i < STRING_LENTH; i++)
                {
                    if (string2[i] == 0)
                        break;
                    printf("[%c]", string2[i]);
                }

                printf("\n");

                wasSwapped ? printf("Z_1 is in Z_2") : printf("Z_2 is in Z_1");
                return 0;
            }
        }
    }
    printf("\nNeither strands fit into eachother!");
    return 0;
}