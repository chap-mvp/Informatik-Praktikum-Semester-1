/*
 Filename  : 1_3_zeichenketten_prüfen.c
 Program   :
 Input     :
 Output    :
 Author    : Akram, M. Issmaeel
 Version   : V01 - 07.12.2025

    ✗ - die Zeichenketten z_1 und z_2 von der Tastatur einlesen und auf zulässige Zeichen prüfen (Falls unzulässige Zeichen vorkommen, ist eine Fehlermeldung auf dem Bildschirm auszugeben.)
    ✗ - die Längen der Zeichenketten ermitteln
    ✗ - prüfen ob die kürzere der beiden Zeichenketten in der anderen Zeichenkette enthalten ist und dabei die Position in der längeren Zeichenkette ermitteln, ab der zum ersten Mal eine Übereinstimmung vorliegt
    ✗ - in einer Zeile auf dem Bildschirm folgendes ausgeben: die längere Zeichenkette, die kürzere Zeichenkette, das Testergebnis als Text (z.B. „z2 ist in zl enthalten") und die Position, ab der die kürzere Zeichenkette erstmals in der längeren enthalten ist.
 */

#include <stdio.h>

int main()
{
    char longStrand[] = {"ACCADCAACADCC"};
    char smolStrand[] = {"ACDC"};
    int smolStrandCount = 0;

    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (smolStrand[j] == longStrand[i + j])
                smolStrandCount++;
            else
                smolStrandCount = 0;
            if(smolStrandCount == 4) {
                printf("ITS IN!");
                return 0;
            }
        }
    }
    printf("nub");
}