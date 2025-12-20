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

int main()
{
    // Sizes for both arrays with "buffers"
    int strandSize = 100;
    // Where the overlap starts
    int positionLargeStrand;

    // large string input and size calculation
    int length1 = 0;
    char string1[strandSize];

    printf("Enter your first string of letters - ");
    for (int i = 0; i < strandSize - 1; i++)
    {
        char c = getchar();
        if (c == '\n')
            break;

        if ((c != 'A') && (c != 'C') && (c != 'D') && (c != '\n'))
        {
            printf("Wrong input, breaking...");
            return 0;
        }

        string1[i] = c;
        length1++;
    }

    for (int i = length1; i < strandSize; i++)
        string1[i] = 0;

    // small string input and size calculation
    int length2 = 0;
    char string2[strandSize];
    printf("Enter your small string of letters - ");
    for (int i = 0; i < strandSize; i++)
    {
        char c = getchar();
        if (c == '\n')
            break;

        if ((c != 'A') && (c != 'C') && (c != 'D') && (c != '\n'))
        {
            printf("Wrong input, breaking...");
            return 0;
        }
        string2[i] = c;
        length2++;
    }

    for (int i = length2; i < strandSize; i++)
        string2[i] = 0;

    bool wasSwapped;

    if (length1 < length2)
    {
        char temp[strandSize];
        for (int i = 0; i < strandSize; i++)
        {
            temp[i] = string2[i];
            string2[i] = string1[i];
            string1[i] = temp[i];
        }

        int tempValue = 0;
        tempValue = length2;
        length2 = length1;
        length1 = tempValue;
        wasSwapped = true;
    }

    // Print the lengths of both strings
    printf("large: [%d] \nsmall: [%d]", length1, length2);

    int matchCount = 0;

    for (int i = 0; i < length1; i++)
    {
        for (int j = 0; j < length2; j++)
        {
            // compare the values in order, if they are the same for the length of the smallstrand size, end the code, else check from the second letter in the large string and so on.
            if (string2[j] == string1[i + j])
            {
                matchCount++;
                positionLargeStrand = i;
            }
            else
                matchCount = 0;
            if (matchCount == length2)
            {
                printf("\nElements match from the %d. character onwards\n", positionLargeStrand + 1);
                for (int i = 0; i < strandSize; i++)
                {
                    if (string1[i] == 0)
                        break;

                    printf("[%c]", string1[i]);
                }

                printf("\n");

                for (int i = 0; i < positionLargeStrand; i++)
                    printf("   ");

                for (int i = 0; i < strandSize; i++)
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
}