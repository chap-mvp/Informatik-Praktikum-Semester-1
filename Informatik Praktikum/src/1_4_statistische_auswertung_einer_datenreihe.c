/*
 Filename  : 1_4_statistische_auswertung_einer_datenreihe.c
 Program   : 
 Input     : 
 Output    : 
 Author    : Akram, M. Issmaeel
 Version   : V01 - 06.12.2025
 */

#include <stdio.h>

int main () {
    int seriesResistors[10] = {0};
    int breakPoint = 0;
    
    for (int i = 0; i < 5; i++) {
        scanf("%d, ", &seriesResistors[i]);
        if (seriesResistors[i] != 0) {
            breakPoint++;
        }
    }
    
    // for (int i = 0; i < 5; i++)
    // {
    //     int c = getchar();
    //     if (c == 'X')
    //     {
    //         break;
    //     }
    //     seriesResistors[i] = c;
    // }
    
    for (int i = 0; i < 5; i++) {
        printf("[%d] ", seriesResistors[i]);
    }
}