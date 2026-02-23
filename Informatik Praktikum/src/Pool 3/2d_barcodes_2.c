/*
 Filename  : 2d-barcodes.c
 Program   : User account management system with creation, deletion, editing, and login authentication
 Input     : None
 Output    : Return value of main() is always 0
 Author    : Akram, M. Issmaeel
 Version   : V02 - 03.02.2026
 */

#include <stdio.h>
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

    unsigned char barcode[MAX_BARCODE_BYTES]; /* raw bit-packed barcode data */
    int size;                                 /* side length of the square grid */

    printf("1 - Encode\n2 - Decode\nWahl: ");
    scanf("%d", &choice);
    while (getchar() != '\n') /* flush newline left by scanf */
        ;

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
            return 0;

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
            return 0;
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
            return 0;

        int decode_result = decode(barcode, size, output, &error);

        if (decode_result == 0)
        {
            printf("Decoded string: %s\n", output);
            /* NOTE: error flag branches are swapped — logic is inverted here */
            if (error)
                printf("The String might contain errors\n");
            else
                printf("Error: Invalid barcode format\n");
        }
        else
        {
            printf("Invalid Input");
            return 0;
        }
    }
}

// Input: input string, barcode[] output buffer, size output pointer
// Output: Returns 0 on success, 1 on error; fills barcode[] and sets *size
// Encodes input string into a square bit-grid: length byte, raw chars, 0x00 terminator, nibble checksum, 0xEC/0x11 padding
int encode(const char *input, unsigned char barcode[], int *size)
{
    while (getchar() != '\n') /* NOTE: stray input flush — may block if stdin is clean */
        ;

    int len = 0;
    while (len < MAX_LENGTH && input[len] != '\0')
        len++;

    printf("length of your string: %d\n", len);

    if (len >= MAX_LENGTH)
    {
        printf("Warning: String too long, truncated to 255 characters\n");
        len = MAX_LENGTH;
    }

    if (len < 1)
    {
        printf("Error: String is empty!\n");
        return 1;
    }

    unsigned char temp_buffer[1024]; /* staging buffer before bit-packing */
    int buf_pos = 0;

    /* write length byte */
    sprintf((char *)&temp_buffer[buf_pos], "%c", (unsigned char)len);
    buf_pos += 1;

    /* write raw string bytes */
    for (int i = 0; i < len; i++)
    {
        sprintf((char *)&temp_buffer[buf_pos], "%c", (unsigned char)input[i]);
        buf_pos += 1;
    }

    /* write two 0x00 terminator bytes */
    sprintf((char *)&temp_buffer[buf_pos], "%c%c", 0x00, 0x00);
    buf_pos += 2;

    /* checksum: sum of all nibbles in length byte + all character bytes */
    unsigned int hex_sum = 0;
    hex_sum += (len >> 4) & 0x0F;
    hex_sum += len & 0x0F;

    for (int i = 0; i < len; i++)
    {
        unsigned char ch = (unsigned char)input[i];
        hex_sum += (ch >> 4) & 0x0F;
        hex_sum += ch & 0x0F;
    }

    /* write checksum as 2 bytes, big-endian */
    unsigned int checksum = hex_sum & 0xFFFF;
    sprintf((char *)&temp_buffer[buf_pos], "%c%c",
            (unsigned char)((checksum >> 8) & 0xFF),
            (unsigned char)(checksum & 0xFF));
    buf_pos += 2;

    /* find smallest square grid that fits all data bits */
    int data_bits = buf_pos * 8;
    int side = 1;
    while (side * side < data_bits)
        side++;

    *size = side;

    if (*size > MAX_BARCODE_SIZE)
    {
        printf("Error: Barcode too large!\n");
        return 1;
    }

    int total_bits = (*size) * (*size);
    int total_nibbles = (total_bits + 3) / 4;

    /* pad remaining space with alternating 0xEC / 0x11 */
    unsigned char fill[] = {0xEC, 0x11};
    int fill_index = 0;

    while (buf_pos < (total_nibbles + 1) / 2)
    {
        sprintf((char *)&temp_buffer[buf_pos], "%c", fill[fill_index]);
        buf_pos++;
        fill_index ^= 1;
    }

    /* trim one byte if nibble count is odd and we overshot */
    if ((total_nibbles % 2) == 1 && buf_pos * 2 > total_nibbles)
    {
        buf_pos--;
    }

    int total_bytes = (total_bits + 7) / 8;
    memset(barcode, 0, total_bytes);

    /* extract nibble stream from temp_buffer, high nibble first */
    unsigned char nibble_stream[MAX_BARCODE_BITS / 4];
    int nibble_index = 0;

    for (int i = 0; i < buf_pos; i++)
    {
        if (nibble_index < total_nibbles)
            nibble_stream[nibble_index++] = (temp_buffer[i] >> 4) & 0x0F;
        if (nibble_index < total_nibbles)
            nibble_stream[nibble_index++] = temp_buffer[i] & 0x0F;
    }

    /* write nibble stream into grid; col is mirrored (size-1-col) so stream runs right-to-left per row */
    for (int row = 0; row < *size; row++)
    {
        for (int col = 0; col < *size; col++)
        {
            int bit_in_stream = row * (*size) + ((*size - 1) - col);

            int nibble_index = bit_in_stream / 4;
            int bit_in_nibble = 3 - (bit_in_stream % 4);
            int bit_value = (nibble_stream[nibble_index] >> bit_in_nibble) & 1;

            int bit_index = row * (*size) + col;
            if (bit_value)
                barcode[bit_index / 8] |= (1 << (7 - (bit_index % 8)));
        }
    }

    return 0;
}

// Input: barcode[] bit-packed grid, size (side length), filename string
// Output: Returns 0 on success, 1 if file cannot be opened
// Writes barcode grid to a text file as rows of '0'/'1' characters, one row per line
int write_barcode(const unsigned char barcode[], int size, const char *filename)
{
    FILE *f = fopen(filename, "w");
    if (!f)
        return 1;

    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            int bit = row * size + col;
            int val = (barcode[bit / 8] >> (7 - bit % 8)) & 1;
            fprintf(f, "%d", val);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    return 0;
}

// Input: barcode[] output buffer, size output pointer, filename string
// Output: Returns 0 on success, 1 on format or I/O error; fills barcode[] and sets *size
// Reads a square '0'/'1' text grid from file, validates dimensions, and packs bits into barcode[]
int read_barcode(unsigned char barcode[], int *size, const char *filename)
{
    FILE *f = fopen(filename, "r");
    char line[1024];
    int rows = 0, cols = 0;

    if (!f)
        return 1;

    /* first pass: count rows and validate consistent column width */
    while (fgets(line, sizeof(line), f))
    {
        int len = 0;
        while ((line[len]) && (line[len] != '\n'))
            len++;
        if (rows == 0)
            cols = len;
        else if (len != cols) /* ragged grid — invalid */
        {
            fclose(f);
            return 1;
        }
        rows++;
    }

    /* must be square, within bounds, and non-empty */
    if (rows != cols || rows > MAX_BARCODE_SIZE || rows < 1)
    {
        fclose(f);
        return 1;
    }

    *size = rows;
    int bytes = (rows * rows + 7) / 8;
    for (int i = 0; i < bytes; i++)
        barcode[i] = 0;

    rewind(f);

    /* second pass: pack bits into barcode[] */
    for (int row = 0; row < rows; row++)
    {
        fgets(line, sizeof(line), f);
        for (int col = 0; col < cols; col++)
        {
            char ch = line[col];
            if (ch != '0' && ch != '1')
            {
                fclose(f);
                return 1;
            }
            if (ch == '1')
            {
                int bit = row * cols + col;
                barcode[bit / 8] |= 1 << (7 - bit % 8);
            }
        }
    }

    fclose(f);
    return 0;
}

// Input: barcode[] bit-packed grid, size (side length), output char buffer, error flag pointer
// Output: Returns 0 on success, 1 if frame is structurally unreadable; sets *error=1 on checksum/terminator/padding mismatch
// Reverses encode(): extracts nibble stream, parses length/chars/terminator/checksum/padding, writes decoded string to output
int decode(const unsigned char barcode[], int size, char *output, int *error)
{
    *error = 0;

    int total_bits = size * size;
    int total_nibbles = (total_bits + 3) / 4;

    unsigned char nibble_stream[MAX_BARCODE_BITS / 4];
    memset(nibble_stream, 0, sizeof(nibble_stream));

    /* reconstruct nibble stream using same column-reversal as encode */
    for (int row = 0; row < size; row++)
        for (int col = 0; col < size; col++)
        {
            int bit_in_stream = row * size + ((size - 1) - col);

            int nibble_index = bit_in_stream / 4;
            int bit_in_nibble = 3 - (bit_in_stream % 4);

            int bit_index = row * size + col;
            int bit_value = (barcode[bit_index / 8] >> (7 - (bit_index % 8))) & 1;

            if (bit_value)
                nibble_stream[nibble_index] |= (1 << bit_in_nibble);
        }

    int nibble_index = 0;

    if (nibble_index + 2 > total_nibbles)
        return 1;

    /* read length from first two nibbles (one byte, high nibble first) */
    int len = (nibble_stream[nibble_index] << 4) | nibble_stream[nibble_index + 1];
    nibble_index += 2;

    if (len > MAX_LENGTH || len < 1)
        return 1;

    /* bounds check: len chars (2 nibbles each) + 4 terminator nibbles + 4 checksum nibbles */
    if (nibble_index + (len * 2) + 4 + 4 > total_nibbles)
        return 1;

    /* read character bytes */
    for (int i = 0; i < len; i++)
    {
        unsigned char ch = (nibble_stream[nibble_index] << 4) | nibble_stream[nibble_index + 1];
        output[i] = ch;
        nibble_index += 2;
    }
    output[len] = '\0';

    /* verify two 0x00 terminator bytes (4 nibbles must all be zero) */
    if (nibble_stream[nibble_index] != 0 ||
        nibble_stream[nibble_index + 1] != 0 ||
        nibble_stream[nibble_index + 2] != 0 ||
        nibble_stream[nibble_index + 3] != 0)
    {
        *error = 1;
    }
    nibble_index += 4;

    /* recompute checksum and compare against stored value */
    unsigned hex_sum = 0;
    hex_sum += (len >> 4) & 0x0F;
    hex_sum += len & 0x0F;

    for (int i = 0; i < len; i++)
    {
        unsigned char ch = (unsigned char)output[i];
        hex_sum += (ch >> 4) & 0x0F;
        hex_sum += ch & 0x0F;
    }

    /* stored checksum: 4 nibbles, big-endian 16-bit value */
    unsigned int stored_checksum = (nibble_stream[nibble_index] << 12) |
                                   (nibble_stream[nibble_index + 1] << 8) |
                                   (nibble_stream[nibble_index + 2] << 4) |
                                   (nibble_stream[nibble_index + 3]);
    nibble_index += 4;

    if ((hex_sum & 0xFFFF) != stored_checksum)
        *error = 1;

    /* verify padding: alternating 0xEC / 0x11, nibble by nibble */
    unsigned char fill[] = {0xEC, 0x11};
    int fill_index = 0;

    while (nibble_index < total_nibbles)
    {
        unsigned char expected_nibble;
        if (nibble_index % 2 == 0)
            expected_nibble = (fill[fill_index] >> 4) & 0x0F;
        else
        {
            expected_nibble = fill[fill_index] & 0x0F;
            fill_index ^= 1;
        }

        if (nibble_stream[nibble_index] != expected_nibble)
            *error = 1;

        nibble_index++;
    }
    return 0;
}