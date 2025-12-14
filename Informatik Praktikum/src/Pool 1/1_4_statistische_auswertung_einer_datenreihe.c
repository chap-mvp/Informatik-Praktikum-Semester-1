/*
 Filename  : 1_4_statistische_auswertung_einer_datenreihe.c
 Program   :
 Input     :
 Output    :
 Author    : Akram, M. Issmaeel
 Version   : V01 - 12.12.2025

    ✓ - die Messreihe einschließlich Endkennzeichen von der Tastatur einlesen
    ✓ - die Anzahl n der auszuwertenden Widerstandswerte ermitteln
    ✓ - den arithmetischen Mittelwert i der Widerstände berechnen
    ✓ - den größten und kleinsten Widerstandswert der Messreihe ermitteln
    ✓ - die Standardabweichung s der Messreihe berechnen
    ✓ - die eingelesenen Widerstandswerte und alle Berechnungsergebnisse auf dem Bildschirm ausgeben
 */

#include <stdio.h>
#include <math.h>

int main()
{
    // Set all values in the array to 0
    float seriesResistors[100] = {0};

    // Enter the resistor, exit by entering X and pressing "enter"
    printf("Enter your resistors: ");
    for (int i = 0; i < 100; i++)
    {
        scanf("%f, ", &seriesResistors[i]);
        if (seriesResistors[i] == 'X')
        {
            break;
        }
    }

    // Calculate resistor count
    float resistors = 0;
    for (int i = 0; i < 10; i++)
        if (seriesResistors[i] != 0)
            resistors++;

    // Calculate sum of resistors (since they are in series)
    float resistorsSum = 0;
    for (int i = 0; i < resistors; i++)
        resistorsSum += seriesResistors[i];

    // Calculate the mean of the resistors
    float meanResistors = resistorsSum / resistors;

    // Calculate smallest resistor
    float smallestResistor = seriesResistors[0];
    for (int i = 0; i < resistors; i++)
        if (seriesResistors[i] < smallestResistor)
            smallestResistor = seriesResistors[i];

    // Calculate largest resistor
    float largestResistor = seriesResistors[0];
    for (int i = 0; i < resistors; i++)
        if (seriesResistors[i] > largestResistor)
            largestResistor = seriesResistors[i];

    // Calculate the sum for the standard deviation formula ((x_i - x_[average])^2)
    // fix variable name
    float sum = 0;
    for (int i = 0; i < resistors; i++)
        sum += pow((float)seriesResistors[i] - (float)meanResistors, 2);

    // Calculate the standard deviation
    float standardDeviation = sqrt((float)sum / ((float)resistors - 1));

    // Print the Resistor values
    printf("Resistors: ");
    for (int i = 0; i < resistors; i++)
        printf("[%.2f] ", seriesResistors[i]);

    // Print all the calculated values
    printf("\nResistor Count: %.0f\nMean: %.2f\nMax: %.2f\nMin: %.2f\nStandard Deviation: %.2f\n", resistors, meanResistors, smallestResistor, largestResistor, standardDeviation);
}