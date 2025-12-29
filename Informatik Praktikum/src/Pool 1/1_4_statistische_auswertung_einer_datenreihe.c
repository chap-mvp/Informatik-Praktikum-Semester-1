/*
 Filename  : 1_4_statistische_auswertung_einer_datenreihe.c
 Program   : Calculates important values for resistors in series
 Input     : There are no input parameters which are used in main
 Output    : There are no return values
 Author    : Akram, M. Issmaeel
 Version   : V02 - 20.12.2025
 */

#include <stdio.h>
#include <math.h>

int main()
{
    float seriesResistors[100] = {0};

    printf("Enter your resistors, enter X and press enter to exit: ");
    for (int i = 0; i < 100; i++)
    {
        scanf("%f, ", &seriesResistors[i]);
        if (seriesResistors[i] == 'X')
            break;
    }

    // Calculate resistor count
    float resistors = 0;
    for (int i = 0; i < 10; i++)
        if (seriesResistors[i] != 0)
            resistors++;

    // Calculate sum of resistors
    float resistorsSum = 0;
    for (int i = 0; i < resistors; i++)
        resistorsSum += seriesResistors[i];

    // Calculate the mean of the resistors
    float meanResistors = resistorsSum / resistors;

    // Find smallest and largest resistor
    float smallestResistor = seriesResistors[0];
    float largestResistor = seriesResistors[0];
    for (int i = 0; i < resistors; i++)
    {
        if (seriesResistors[i] < smallestResistor)
            smallestResistor = seriesResistors[i];
        if (seriesResistors[i] > largestResistor)
            largestResistor = seriesResistors[i];
    }

    // Part of standard deviation: Σ(x_i - mean)²
    float sum = 0;
    for (int i = 0; i < resistors; i++)
        sum += pow((float)seriesResistors[i] - (float)meanResistors, 2);
    // Finish standard deviation
    float standardDeviation = sqrt((float)sum / ((float)resistors - 1));

    printf("Resistors: ");
    for (int i = 0; i < resistors; i++)
        printf("[%.2f] ", seriesResistors[i]);

    (resistors > 1)
        ? (printf("\nResistor Count: %.0f\nMean: %.2f\nMin: %.2f\nMax: %.2f\nStandard Deviation: %.2f\n", resistors, meanResistors, smallestResistor, largestResistor, standardDeviation)) // With standard deviation
        : (printf("\nResistor Count: %.0f\nMean: %.2f\nMin: %.2f\nMax: %.2f\nStandard Deviation: N.A\n", resistors, meanResistors, smallestResistor, largestResistor)); // With standard deviation
}