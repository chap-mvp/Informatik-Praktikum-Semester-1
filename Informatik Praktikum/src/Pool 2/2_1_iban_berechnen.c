/*
 Filename  : 2_1_iban_berechnen.c
 Program   : Validates and generates German IBANs using BLZ and account numbers
 Input     : There are no input parameters which are used in main
 Output    : The return value is always 0
 Author    : Akram, M. Issmaeel
 Version   : V01 - 06.01.2026
 */

#include <stdio.h>
#include <stdbool.h>

#define IBAN_SIZE 22
#define IBAN_AMOUNT 2

// IBAN structure: holds validity flag and 22-digit array
typedef struct iban
{
    bool isfree;
    int iban[IBAN_SIZE];
} iban;

iban iban_list[IBAN_AMOUNT];

// Input: None
// Output: Initializes all IBAN slots with DE country code and zeros
// Initializes all IBANs in the list with default DE country code and zeros
void iban_clearer()
{
    for (int i = 0; i < IBAN_AMOUNT; i++)
    {
        iban_list[i].isfree = true;
        iban_list[i].iban[0] = 'D';
        iban_list[i].iban[1] = 'E';
        iban_list[i].iban[2] = 0;
        iban_list[i].iban[3] = 0;
        for (int j = 4; j < IBAN_SIZE; j++)
            iban_list[i].iban[j] = 0;
    }
}

// Input: index - position in iban_list
// Output: Prints formatted IBAN breakdown (country code, check digits, BLZ, account number)
// Outputs formatted IBAN: country code, check digits, BLZ, account number
void iban_printer(int index)
{
    int arr[22];
    for (int i = 0; i < 22; i++)
        arr[i] = iban_list[index].iban[i];

    printf("Ländercode : %c%c\n", arr[0], arr[1]);
    printf("Prüfzahl   : %d%d\n", arr[2], arr[3]);
    printf("BLZ        : %d%d%d%d%d%d%d%d\n", arr[4], arr[5], arr[6], arr[7], arr[8], arr[9], arr[10], arr[11]);
    printf("Kontonummer: %d%d%d%d%d%d%d%d%d%d\n", arr[12], arr[13], arr[14], arr[15], arr[16], arr[17], arr[18], arr[19], arr[20], arr[21]);

    printf("Step 3: This is a valid IBAN\n");

    printf("\n");
}

// Input: index - position in iban_list
// Output: Returns calculated 2-digit check value using modulo-97 algorithm per ISO 13616
// Calculates IBAN check digits using modulo-97 algorithm per ISO 13616
int iban_pp_calc(int index)
{
    int remainder = 0;
    int de_code[6] = {1, 3, 1, 4, 0, 0}; // DE encoded as 1314, check digits as 00

    // Process BLZ and account number
    for (int i = 4; i < IBAN_SIZE + 6; i++)
    {
        if (i < IBAN_SIZE)
        {
            remainder *= 10;
            remainder += iban_list[index].iban[i];
            remainder %= 97;
        }
        // Append country code and placeholder check digits
        if (i >= IBAN_SIZE)
        {
            remainder *= 10;
            remainder += de_code[i - IBAN_SIZE];
            remainder %= 97;
        }
    }

    // Check digits = 98 - remainder
    remainder = 98 - remainder;

    iban_list[index].iban[2] = remainder / 10;
    iban_list[index].iban[3] = remainder % 10;

    printf("Step 2: Done\n");

    return iban_list[index].iban[2] * 10 + iban_list[index].iban[3];
}

// Input: blz_check - 8-digit BLZ array
// Output: Returns true if BLZ exists in branches.txt, false otherwise
// Validates BLZ against branches.txt file
bool branch_lookup(int blz_check[8])
{
    FILE *file = fopen("branches.txt", "r");
    if (file == NULL)
    {
        printf("File not found\n");
        return false;
    }

    char blz_file[256];

    // Read each line and compare first 8 digits with input BLZ
    while (fgets(blz_file, sizeof(blz_file), file) != NULL)
    {
        bool match = true;
        for (int i = 0; i < 8; i++)
        {
            if (blz_check[i] != (int)blz_file[i] - 48)
            {
                match = false;
                break;
            }
        }

        if (match)
        {
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

// Input: index - position in iban_list; prompts user for BLZ (8 digits) and account number (10 digits)
// Output: Generates complete IBAN with check digits, validates BLZ, prints result
// Accepts BLZ and account number from user, generates IBAN with check digits
void iban_generator(int index)
{
    int count = 0;

    printf("DEXX[________]XXXXXXXXXX (8 digits) - ");

    // Read BLZ (8 digits)
    int i = 0;
    for (i = 4; i < 13; i++)
    {
        char c = getchar();
        if (c == '\n')
            break;
        if (c < '0' && c > '9')
        {
            printf("Wrong input!\n\n");
            return;
        }
        count++;
        if (i < 13)
            iban_list[index].iban[i] = c - 48;
    }

    
    // Validate BLZ against branches file
    int blz_check[8];
    for (int i = 0; i < 8; i++)
        blz_check[i] = iban_list[index].iban[i + 4];
    bool a = branch_lookup(blz_check);

    if (!a)
    {
        printf("Invalid BLZ\n\n");
        return;
    }
    
    // Left-pad BLZ with zeros if fewer than 8 digits
    if (count < 8)
    {
        int shift = 8 - count;
        for (int j = 11; j >= 4 + shift; j--)
            iban_list[index].iban[j] = iban_list[index].iban[j - shift];
        for (int j = 4; j < 4 + shift; j++)
            iban_list[index].iban[j] = 0;
    }

    count = 0;
    printf("DEXXXXXXXXXX[__________] (10 digits) - ");

    // Read account number (10 digits)
    for (int i = 12; i < IBAN_SIZE + 1; i++)
    {
        char c = getchar();
        if (c == '\n')
            break;
        if (c < '0' || c > '9')
        {
            printf("Wrong input!\n\n");
            return;
        }
        count++;

        if (i == IBAN_SIZE && c != '\0')
        {
            printf("Too many values!\n");
            while (getchar() != '\n')
                ;
            return;
        }
        if (i < IBAN_SIZE)
            iban_list[index].iban[i] = c - 48;
    }

    // Left-pad account number with zeros if fewer than 10 digits
    if (count < 10)
    {
        int shift = 10 - count;
        for (int j = IBAN_SIZE - 1; j >= 12 + shift; j--)
            iban_list[index].iban[j] = iban_list[index].iban[j - shift];
        for (int j = 12; j < 12 + shift; j++)
            iban_list[index].iban[j] = 0;
    }


    printf("Step 1: Done\n");

    iban_pp_calc(index);
    iban_printer(index);
}

// Input: index - position in iban_list; reads BLZ.txt file with BLZ and account pairs
// Output: Generates and prints IBANs for all valid entries in file
// Reads BLZ.txt file, parses BLZ and account pairs, generates IBANs for each
void parse_blz_file(int index)
{
    FILE *file = fopen("BLZ.txt", "r");
    if (file == NULL)
        return;

    char blz_account_line[256];

    while (fgets(blz_account_line, sizeof(blz_account_line), file) != NULL)
    {
        int i = 0;
        int blz_index = 0;
        int account_index = 0;
        int skip_line = 0;

        int blz_temp[8];
        int account_temp[10];

        // Parse BLZ (first 8 digits before space)
        while (blz_account_line[i] != '\0' && blz_account_line[i] != '\n')
        {
            if (blz_account_line[i] == ' ')
            {
                i++;
                break;
            }
            if (blz_account_line[i] >= '0' && blz_account_line[i] <= '9')
            {
                blz_temp[blz_index] = blz_account_line[i] - 48;
                blz_index++;
            }
            else
            {
                skip_line = 1;
                break;
            }

            i++;
        }

        if (skip_line)
            continue;

        // Skip whitespace
        while (blz_account_line[i] == ' ')
            i++;

        // Left-pad BLZ with zeros
        int shift = 8 - blz_index;
        for (int k = 7; k >= shift; k--)
            blz_temp[k] = blz_temp[k - shift];
        for (int k = 0; k < shift; k++)
            blz_temp[k] = 0;

        // Parse account number (10 digits after space)
        while (blz_account_line[i] != '\0' && blz_account_line[i] != '\n')
        {
            if (blz_account_line[i] >= '0' && blz_account_line[i] <= '9')
            {
                account_temp[account_index] = blz_account_line[i] - 48;
                account_index++;
                if (account_index > 10) // Detect overflow
                {
                    skip_line = 1;
                    break;
                }
            }
            else
            {
                skip_line = 1;
                break;
            }
            i++;
        }

        if (skip_line)
            continue;

        // Left-pad account number with zeros
        shift = 10 - account_index;
        for (int k = 9; k >= shift; k--)
            account_temp[k] = account_temp[k - shift];
        for (int k = 0; k < shift; k++)
            account_temp[k] = 0;

        // Store country code
        iban_list[index].iban[0] = 'D'; // Convert letter to numeric
        iban_list[index].iban[1] = 'E';

        // Store BLZ and account number in IBAN structure
        for (int k = 0; k < 8; k++)
            iban_list[index].iban[4 + k] = blz_temp[k];

        for (int k = 0; k < 10; k++)
            iban_list[index].iban[12 + k] = account_temp[k];

        // Validate BLZ
        int blz_check[8];
        for (int i = 0; i < 8; i++)
            blz_check[i] = iban_list[index].iban[i + 4];

        bool a = branch_lookup(blz_check);
        if (!a)
        {
            printf("Invalid BLZ\n\n");
            continue;
        }

        iban_pp_calc(index);
        iban_printer(index);
        index++;
    }

    fclose(file);
}

// Input: index - position in iban_list; prompts user for complete 22-character IBAN
// Output: Validates check digits by recalculating and comparing, prints result
// Accepts full IBAN from user and validates check digits
void full_iban_check(int index)
{
    char IBAN[22];

    printf("Enter you IBAN here: ");

    // Read 22-character IBAN
    for (int i = 0; i < 23; i++)
    {
        char c = getchar();
        if (c == '\n')
            break;
        if (c < '0' && c > '9')
        {
            printf("Wrong input!\n\n");
            return;
        }
        if (i == 22 && c != '\0')
        {
            printf("Too many values!\n\n");
            return;
        }
        if (i < 22)
            IBAN[i] = c;
    }

    // Verify country code
    if (IBAN[0] != 'D' || IBAN[1] != 'E')
    {
        printf("Wrong letters!");
        return;
    }

    // Validate BLZ
    int blz_check[8];
    for (int i = 0; i < 8; i++)
        blz_check[i] = (int)IBAN[i + 4] - 48;
    bool a = branch_lookup(blz_check);

    if (!a)
    {
        printf("Invalid BLZ\n\n");
        return;
    }

    // Store IBAN in structure
    iban_list[index].iban[0] = 'D';
    iban_list[index].iban[1] = 'E';

    for (int i = 4; i < 22; i++)
        iban_list[index].iban[i] = (int)IBAN[i] - 48;

    printf("Step 1: Done\n");

    // Recalculate check digits
    iban_pp_calc(index);

    // Compare recalculated check digits with input
    for (int i = 2; i < 4; i++)
        if (iban_list[index].iban[i] != (int)IBAN[i] - 48)
        {
            printf("The Iban is wrong!\n");
            return;
        }

    iban_printer(index);
}

// Input: none
// Output: Executes selected task in loop until exit
int main()
{
    iban_clearer();

    while (1)
    {
        int index = 0;
        if (iban_list[index].isfree == true)
        {
            int task;
            printf("--------------------------------------------\n");
            printf("Which task would you like to do?\n"
                   "Press 1: Generate IBAN from BLZ and ACCOUNT#\n"
                   "Press 2: Check whole IBAN\n"
                   "Press 3: Generate IBAN from BLZ.txt\n");
            scanf("%d", &task);

            // Consume remaining newline
            while (getchar() != '\n')
                ;

            if (task == 1)
                iban_generator(index);
            else if (task == 2)
                full_iban_check(index);
            else if (task == 3)
                parse_blz_file(index);
            else if (task == 4)
                return 0;
            else
                printf("Invalid Task\n");

            index++;
        }
        else
            return 0;
    }
}