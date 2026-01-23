#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_LENGTH 255
#define MAX_BARCODE_SIZE 128
#define MAX_BARCODE_BITS (MAX_BARCODE_SIZE * MAX_BARCODE_SIZE)
#define MAX_BARCODE_BYTES (MAX_BARCODE_BITS / 8)

int encode(const char *input, unsigned char barcode[], int *size);
int write_barcode(const unsigned char barcode[], int size, const char *filename);
int read_barcode(unsigned char barcode[], int *size, const char *filename);
int decode(const unsigned char barcode[], int size, char *output, int *error);

int main(void)
{
    int choice;
    char filename[256];

    unsigned char barcode[MAX_BARCODE_BYTES];
    int size;

    printf("1 - Encode\n2 - Decode\nWahl: ");
    scanf("%d", &choice);
    while (getchar() != '\n');

    if (choice == 1)
    {
        char input[MAX_LENGTH + 1];
        int i;

        printf("Input: ");
        for (i = 0; i < MAX_LENGTH; i++)
        {
            char c = getchar();
            if (c == '\n')
                break;
            input[i] = c;
        }
        input[i] = '\0';

        if (encode(input, barcode, &size) != 0)
            return 1;

        printf("File Name: ");
        for (i = 0; i < 255; i++)
        {
            char c = getchar();
            if (c == '\n')
                break;
            filename[i] = c;
        }
        filename[i] = '\0';

        if (write_barcode(barcode, size, filename) != 0)
            return 1;

        printf("2D-Barcode in file: %s\n", filename);
    }
    else if (choice == 2)
    {
        int i;
        char output[MAX_LENGTH + 1];
        int error;

        printf("Filename: ");
        for (i = 0; i < 255; i++)
        {
            char c = getchar();
            if (c == '\n')
                break;
            filename[i] = c;
        }
        filename[i] = '\0';

        if (read_barcode(barcode, &size, filename) != 0)
            return 1;

        if (decode(barcode, size, output, &error) != 0)
            return 1;

        printf("Decoded string: %s\n", output);
        if (error)
            printf("The String might contain errors\n");
    }
    else
    {
        printf("Invalid Input!\n");
        return 1;
    }

    return 0;
}

int encode(const char *input, unsigned char barcode[], int *size)
{
    int len = strlen(input);

    if (len > MAX_LENGTH)
        len = MAX_LENGTH;

    int total_bits = 8 + len * 8 + 16 + 16;
    *size = (int)ceil(sqrt(total_bits));
    *size = ((*size + 3) / 4) * 4;

    if (*size > MAX_BARCODE_SIZE)
    {
        printf("Fehler: Barcode zu groß\n");
        return 1;
    }

    int total_bytes = ((*size) * (*size)) / 8;
    for (int i = 0; i < total_bytes; i++)
        barcode[i] = 0;

    /* length */
    barcode[0] = (unsigned char)len;
    int bit_pos = 8;

    /* data */
    for (int i = 0; i < len; i++)
    {
        barcode[bit_pos / 8] |= input[i] >> (bit_pos % 8);
        if (bit_pos % 8 != 0)
            barcode[bit_pos / 8 + 1] |= input[i] << (8 - bit_pos % 8);
        bit_pos += 8;
    }

    /* separator */
    bit_pos += 16;

    /* checksum */
    unsigned int checksum = len;
    for (int i = 0; i < len; i++)
        checksum += (unsigned char)input[i];
    checksum &= 0xFFFF;

    barcode[bit_pos / 8] |= (checksum >> 8);
    barcode[bit_pos / 8 + 1] |= (checksum & 0xFF);
    bit_pos += 16;

    /* padding */
    unsigned char fill[] = {0xEC, 0x11};
    int f = 0;
    while (bit_pos < (*size * *size))
    {
        barcode[bit_pos / 8] |= fill[f];
        bit_pos += 8;
        f ^= 1;
    }

    return 0;
}

int write_barcode(const unsigned char barcode[], int size, const char *filename)
{
    FILE *f = fopen(filename, "w");
    if (!f)
        return 1;

    for (int r = 0; r < size; r++)
    {
        for (int c = size - 1; c >= 0; c--)
        {
            int bit = r * size + c;
            int val = (barcode[bit / 8] >> (7 - bit % 8)) & 1;
            fprintf(f, "%d", val);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    return 0;
}

int read_barcode(unsigned char barcode[], int *size, const char *filename)
{
    FILE *f = fopen(filename, "r");
    char line[1024];
    int rows = 0, cols = 0;

    if (!f)
        return 1;

    while (fgets(line, sizeof(line), f))
    {
        int len = 0;
        while (line[len] && line[len] != '\n')
            len++;
        cols = len;
        rows++;
    }

    if (rows != cols || rows > MAX_BARCODE_SIZE)
    {
        fclose(f);
        return 1;
    }

    *size = rows;
    int bytes = (rows * rows + 7) / 8;
    for (int i = 0; i < bytes; i++)
        barcode[i] = 0;

    rewind(f);
    for (int r = 0; r < rows; r++)
    {
        fgets(line, sizeof(line), f);
        for (int c = cols - 1; c >= 0; c--)
        {
            if (line[cols - 1 - c] == '1')
            {
                int bit = r * cols + c;
                barcode[bit / 8] |= 1 << (7 - bit % 8);
            }
        }
    }

    fclose(f);
    return 0;
}

int decode(const unsigned char barcode[], int size, char *output, int *error)
{
    *error = 0;
    int len = barcode[0];

    if (len > MAX_LENGTH)
        return 1;

    unsigned int checksum = len;
    for (int i = 0; i < len; i++)
    {
        output[i] = barcode[1 + i];
        checksum += (unsigned char)output[i];
    }
    output[len] = '\0';

    unsigned int stored =
        (barcode[1 + len + 2] << 8) | barcode[1 + len + 3];

    if ((checksum & 0xFFFF) != stored)
        *error = 1;

    return 0;
}