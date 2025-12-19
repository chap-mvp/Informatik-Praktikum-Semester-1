/*
 Filename  : 1_3_zeichenketten_prüfen.c
 Program   :
 Input     :
 Output    :
 Author    : Akram, M. Issmaeel
 Version   : V01 - 07.12.2025d

 Checklist  :
    ✓ - die Zeichenketten z_1 und z_2 von der Tastatur einlesen und auf zulässige Zeichen prüfen (Falls unzulässige Zeichen vorkommen, ist eine Fehlermeldung auf dem Bildschirm auszugeben.)
    ✓ - die Längen der Zeichenketten ermitteln
    ✓ - prüfen ob die kürzere der beiden Zeichenketten in der anderen Zeichenkette enthalten ist und dabei die Position in der längeren Zeichenkette ermitteln, ab der zum ersten Mal eine Übereinstimmung vorliegt
    ✓ - in einer Zeile auf dem Bildschirm folgendes ausgeben: die längere Zeichenkette, die kürzere Zeichenkette, das Testergebnis als Text (z.B. „z2 ist in zl enthalten") und die Position, ab der die kürzere Zeichenkette erstmals in der längeren enthalten ist.
 */

#include <stdio.h>

int main()
{
    // Sizes for both arrays with "buffers"
    int strandSize = 100;
    // Calculate user input sizes for both strands
    int largeStrandSize = 0, smallStrandSize = 0;
    // Where the overlap starts
    int positionlargeStrand;

    // large string input and size calculation
    int z_1 = 0;
    char largeStrand[strandSize];
    printf("Enter your large string of letters - ");
    for (int i = 0; i < strandSize; i++)
    {
        char c = getchar();
        if (c == '\n')
            break;
        largeStrand[i] = c;
        z_1++;
    }

    for (int i = z_1; i < strandSize; i++)
        largeStrand[i] = 0;

    for (int i = 0; i < strandSize; i++)
        if (largeStrand[i] != 0)
            largeStrandSize++;
        else
            break;

    // small string input and size calculation
    int z_2 = 0;
    char smallStrand[strandSize];
    printf("Enter your small string of letters - ");
    for (int i = 0; i < strandSize; i++)
    {
        char c = getchar();
        if (c == '\n')
        {
            break;
        }
        smallStrand[i] = c;
        z_2++;
    }

    for (int i = z_2; i < strandSize; i++)
        smallStrand[i] = 0;

    for (int i = 0; i < strandSize; i++)
    {
        if (smallStrand[i] != 0)
        {
            smallStrandSize++;
        }
        else
        {
            break;
        }
    }

    // Print the lengths of both strings
    printf("\nlarge: [%d] \nsmall: [%d]", largeStrandSize, smallStrandSize);

    int smallStrandSizeCheck = 0;

    for (int i = 0; i < largeStrandSize; i++)
    {
        for (int j = 0; j < smallStrandSize; j++)
        {
            // compare the values in order, if they are the same for the length of the smallstrand size, end the code, else check from the second letter in the large string and so on.
            if (smallStrand[j] == largeStrand[i + j])
            {
                smallStrandSizeCheck++;
                positionlargeStrand = i;
            }
            else
                smallStrandSizeCheck = 0;
            if (smallStrandSizeCheck == smallStrandSize)
            {
                printf("\nElements match from the %d. character onwards\n", positionlargeStrand + 1);
                for (int i = 0; i < strandSize; i++)
                {
                    if (largeStrand[i] == 0)
                    {
                        break;
                    }
                    printf("[%c]", largeStrand[i]);
                }

                printf("\n");

                for (int i = 0; i < positionlargeStrand; i++)
                {
                    printf("   ");
                }

                for (int i = 0; i < strandSize; i++)
                {
                    if (smallStrand[i] == 0)
                    {
                        break;
                    }
                    printf("[%c]", smallStrand[i]);
                }
                return 0;
            }
        }
    }
    printf("\nThe strands do not fit into eachother!");
}