/*
 Filename  : 1_3_zeichenketten_prüfen.c
 Program   :
 Input     :
 Output    :
 Author    : Akram, M. Issmaeel
 Version   : V01 - 06.12.2025
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