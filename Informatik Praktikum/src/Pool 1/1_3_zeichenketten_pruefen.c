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
    int longStrandSize = 0, smolStrandSize = 0;
    // Where the overlap starts
    int positionLongStrand;

    // Long string input and size calculation
    int z_1 = 1;
    char longStrand[strandSize];
    printf("Enter your long string of letters - ");
    for (int i = 0; i < strandSize; i++)
    {
        char c = getchar();
        if (c == '\n')
            break;
        longStrand[i] = c;
        z_1++;
    }

    for (int i = z_1; i < strandSize; i++)
        longStrand[i] = 0;

    for (int i = 0; i < strandSize; i++)
        if (longStrand[i] != 0)
            longStrandSize++;
        else
            break;

    // Smol string input and size calculation
    int z_2 = 1;
    char smolStrand[strandSize];
    printf("Enter your smol string of letters - ");
    for (int i = 0; i < strandSize; i++)
    {
        char c = getchar();
        if (c == '\n')
            break;
        smolStrand[i] = c;
        z_2++;
    }

    for (int i = z_2; i < strandSize; i++)
        smolStrand[i] = 0;

    for (int i = 0; i < strandSize; i++)
        if (smolStrand[i] != 0)
            smolStrandSize++;
        else
            break;

    // Print the lengths of both strings
    printf("\nlong: [%d] \nsmol: [%d]", longStrandSize, smolStrandSize);

    int smolStrandSizeCheck = 0;

    for (int i = 0; i < longStrandSize; i++)
    {
        for (int j = 0; j < smolStrandSize; j++)
        {
            // compare the values in order, if they are the same for the length of the smallstrand size, end the code, else check from the second letter in the long string and so on.
            if (smolStrand[j] == longStrand[i + j])
            {
                smolStrandSizeCheck++;
                positionLongStrand = i;
            }
            else
                smolStrandSizeCheck = 0;
            if (smolStrandSizeCheck == smolStrandSize)
            {
                printf("\nElements match from the %d. character onwards\n", positionLongStrand + 1);
                for (int i = 0; i < strandSize; i++)
                {
                    if (longStrand[i] == 0)
                    {
                        break;
                    }
                    printf("[%c] ", longStrand[i]);
                }
                printf("\n");
                for (int i = 0; i < strandSize; i++)
                {
                    if (smolStrand[i] == 0)
                    {
                        break;
                    }
                    printf("[%c] ", smolStrand[i]);
                }
                return 0;
            }
        }
    }
    printf("\nThe strands do not fit into eachother!");
}