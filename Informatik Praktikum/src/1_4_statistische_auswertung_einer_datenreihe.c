/*
 Filename  : 1_4_statistische_auswertung_einer_datenreihe.c
 Program   :
 Input     :
 Output    :
 Author    : Akram, M. Issmaeel
 Version   : V01 - 07.12.2025

    ✗ - die Messreihe einschließlich Endkennzeichen von der Tastatur einlesen
    ✗ - die Anzahl n der auszuwertenden Widerstandswerte ermitteln
    ✗ - den arithmetischen Mittelwert i der Widerstände berechnen
    ✗ - den größten und kleinsten Widerstandswert der Messreihe ermitteln
    ✗ - die Standardabweichung s der Messreihe berechnen, wobei gilt:
    
    ✗ - die eingelesenen Widerstandswerte und alle Berechnungsergebnisse auf dem Bildschirm ausgeben
 */

#include <stdio.h>

int main()
{
    int seriesResistors[10] = {0};
    int breakPoint = 0;

    for (int i = 0; i < 5; i++) {
        scanf("%d, ", &seriesResistors[i]);
        if (seriesResistors[i] != 0) {
            breakPoint++;
        }
    }

    printf("%d", breakPoint);

    for (int i = 0; i < 5; i++)
    {
        printf("[%d] ", seriesResistors[i]);
    }
}