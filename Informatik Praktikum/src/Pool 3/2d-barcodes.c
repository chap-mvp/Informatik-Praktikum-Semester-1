/*
 Filename  : 2d-barcodes.c
 Program   : User account management system with creation, deletion, editing, and login authentication
 Input     : There are no input parameters which are used in main
 Output    : The return value is always 0
 Author    : Akram, M. Issmaeel
 Version   : V02 - 03.02.2026
 */

// LIBRARIES
#include <stdio.h>
#include <string.h>

// Global Variables
#define MAX_LENGTH 255
#define MAX_BARCODE_SIZE 128
#define MAX_BARCODE_BITS (MAX_BARCODE_SIZE * MAX_BARCODE_SIZE)
#define MAX_BARCODE_BYTES (MAX_BARCODE_BITS / 8)

// Function Declarationa
int encode(const char *input, unsigned char barcode[], int *size);
int write_barcode(const unsigned char barcode[], int size, const char *filename);
int read_barcode(unsigned char barcode[], int *size, const char *filename);
int decode(const unsigned char barcode[], int size, char *output, int *error);

// Input: None
// Output: Generates/Reads a file with a QR-Code relating to a string
int main(void)
{
    int choice;
    char filename[256];

    unsigned char barcode[MAX_BARCODE_BYTES];
    int size;

    printf("1 - Encode\n2 - Decode\nWahl: ");
    scanf("%d", &choice);
    while (getchar() != '\n')
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
            return 0;

        int decode_result = decode(barcode, size, output, &error);

        if (decode_result == 0)
        {
            printf("Decoded string: %s\n", output);
            if (error)
                printf("The String might contain errors\n");
        }
        else
        {
            printf("Error: Invalid barcode format\n");
        }
    }
    else
    {
        printf("Invalid Input!\n");
        return 0;
    }
}

// INPUT: String to encode, byte array for barcode output, pointer to store barcode dimension
// OUTPUT: 0 on success, 1 on error; populates barcode[] with bit-packed data and sets *size to square dimension
// Encodes string as: [1-byte length][string bytes][2-byte 0x0000 terminator][2-byte checksum][padding], then maps to square grid reading right-to-left per row
int encode(const char *input, unsigned char barcode[], int *size)
{
    // Flush remaining newline from previous input
    while (getchar() != '\n')
        ;
    
    // Calculate actual string length up to MAX_LENGTH
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

    // Build data structure: [length byte][string bytes][0x0000 terminator][2-byte checksum]
    unsigned char temp_buffer[1024];
    int buf_pos = 0;

    // Store length as single byte
    sprintf((char *)&temp_buffer[buf_pos], "%c", (unsigned char)len);
    buf_pos += 1;

    // Store each character of input string
    for (int i = 0; i < len; i++)
    {
        sprintf((char *)&temp_buffer[buf_pos], "%c", (unsigned char)input[i]);
        buf_pos += 1;
    }

    // Add 2-byte terminator (0x0000)
    sprintf((char *)&temp_buffer[buf_pos], "%c%c", 0x00, 0x00);
    buf_pos += 2;   

    // Calculate checksum: sum all nibbles (4-bit halves) of length and data bytes, keep lower 16 bits
    unsigned int hex_sum = 0;
    hex_sum += (len >> 4) & 0x0F;  // High nibble of length
    hex_sum += len & 0x0F;          // Low nibble of length

    for (int i = 0; i < len; i++)
    {
        unsigned char ch = (unsigned char)input[i];
        hex_sum += (ch >> 4) & 0x0F;  // High nibble
        hex_sum += ch & 0x0F;          // Low nibble
    }

    // Store checksum as 2 bytes (16 bits)
    unsigned int checksum = hex_sum & 0xFFFF;
    sprintf((char *)&temp_buffer[buf_pos], "%c%c",
            (unsigned char)((checksum >> 8) & 0xFF),
            (unsigned char)(checksum & 0xFF));
    buf_pos += 2;

    // Calculate minimum square dimension needed to hold all data bits
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
 
    // Calculate total capacity and pad with alternating 0xEC, 0x11 bytes (common QR padding pattern)
    int total_bits = (*size) * (*size);
    int total_nibbles = (total_bits + 3) / 4;

    unsigned char fill[] = {0xEC, 0x11};
    int fill_idx = 0;

    while (buf_pos < (total_nibbles + 1) / 2)
    {
        sprintf((char *)&temp_buffer[buf_pos], "%c", fill[fill_idx]);
        buf_pos++;
        fill_idx ^= 1;  // Alternate between 0xEC and 0x11
    }

    // Handle odd nibble count by removing last byte if it extends beyond needed nibbles
    if ((total_nibbles % 2) == 1 && buf_pos * 2 > total_nibbles)
    {
        buf_pos--;
    }

    // Initialize output barcode byte array
    int total_bytes = (total_bits + 7) / 8;
    memset(barcode, 0, total_bytes);

    // Extract all bytes into nibble stream (each byte becomes two 4-bit values)
    unsigned char nibble_stream[MAX_BARCODE_BITS / 4];
    int nib_idx = 0;

    for (int i = 0; i < buf_pos; i++)
    {
        if (nib_idx < total_nibbles)
            nibble_stream[nib_idx++] = (temp_buffer[i] >> 4) & 0x0F;  // High nibble
        if (nib_idx < total_nibbles)
            nibble_stream[nib_idx++] = temp_buffer[i] & 0x0F;         // Low nibble
    }

    // Map nibble bits to barcode grid: each row reads right-to-left, rows proceed top-to-bottom
    // Bit position in stream = row * size + (size-1-col), meaning rightmost column gets first bits
    for (int row = 0; row < *size; row++)
    {
        for (int col = 0; col < *size; col++)
        {
            int bit_in_stream = row * (*size) + ((*size - 1) - col);  // Right-to-left mapping

            // Extract bit from nibble stream (nibbles store 4 bits each, MSB first within nibble)
            int nibble_idx = bit_in_stream / 4;
            int bit_in_nibble = 3 - (bit_in_stream % 4);  // Bit 0 is MSB, bit 3 is LSB
            int bit_value = (nibble_stream[nibble_idx] >> bit_in_nibble) & 1;

            // Store bit in output barcode array (row-major, left-to-right storage)
            int bit_index = row * (*size) + col;
            if (bit_value)
                barcode[bit_index / 8] |= (1 << (7 - (bit_index % 8)));
        }
    }

    return 0;
}


// INPUT: Byte array containing barcode bits, dimension of square, output filename
// OUTPUT: 0 on success, 1 on file error; writes barcode as ASCII '0'/'1' grid to file
// Writes each bit of the barcode as a character ('0' or '1') in row-major order, one row per line
int write_barcode(const unsigned char barcode[], int size, const char *filename)
{
    FILE *f = fopen(filename, "w");
    if (!f)
        return 1;

    // Write each bit as ASCII '0' or '1', one row per line
    for (int r = 0; r < size; r++)
    {
        for (int c = 0; c < size; c++)
        {
            int bit = r * size + c;  // Row-major linear index
            int val = (barcode[bit / 8] >> (7 - bit % 8)) & 1;  // Extract bit from byte
            fprintf(f, "%d", val);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    return 0;
}

// INPUT: Byte array to populate, pointer to store dimension, input filename
// OUTPUT: 0 on success, 1 on error; reads file into barcode[] and sets *size to detected square dimension
// Validates file is square grid of '0'/'1' characters, then packs bits into byte array in row-major order
int read_barcode(unsigned char barcode[], int *size, const char *filename)
{
    FILE *f = fopen(filename, "r");
    char line[1024];
    int rows = 0, cols = 0;

    if (!f)
        return 1;

    // First pass: validate square dimensions and character validity
    while (fgets(line, sizeof(line), f))
    {
        int len = 0;
        while (line[len] && line[len] != '\n')
            len++;
        if (rows == 0)
            cols = len;
        else if (len != cols)  // All rows must have same length
        {
            fclose(f);
            return 1;
        }
        rows++;
    }

    // Validate square grid within size limits
    if (rows != cols || rows > MAX_BARCODE_SIZE || rows < 1)
    {
        fclose(f);
        return 1;
    }

    *size = rows;
    int bytes = (rows * rows + 7) / 8;
    for (int i = 0; i < bytes; i++)
        barcode[i] = 0;

    // Second pass: read bits into barcode array
    rewind(f);
    for (int r = 0; r < rows; r++)
    {
        fgets(line, sizeof(line), f);
        for (int c = 0; c < cols; c++)
        {
            char ch = line[c];
            if (ch != '0' && ch != '1')  // Validate character is binary digit
            {
                fclose(f);
                return 1;
            }
            if (ch == '1')
            {
                int bit = r * cols + c;  // Row-major linear index
                barcode[bit / 8] |= 1 << (7 - bit % 8);  // Set bit in byte
            }
        }
    }

    fclose(f);
    return 0;
}

// INPUT: Byte array with barcode data, dimension, output string buffer, error flag pointer
// OUTPUT: 0 if decodable (sets *error=1 if checksum/padding wrong), 1 if structure invalid; writes decoded string to output[]
// Reverses encode mapping (right-to-left nibble extraction), validates length/terminator/checksum/padding, extracts original string
int decode(const unsigned char barcode[], int size, char *output, int *error)
{
    *error = 0;

    int total_bits = size * size;
    int total_nibbles = (total_bits + 3) / 4;

    // Reconstruct nibble stream by reversing the encode mapping (right-to-left per row)
    unsigned char nibble_stream[MAX_BARCODE_BITS / 4];
    memset(nibble_stream, 0, sizeof(nibble_stream));

    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            int bit_in_stream = row * size + ((size - 1) - col);  // Reverse right-to-left mapping

            int nibble_idx = bit_in_stream / 4;
            int bit_in_nibble = 3 - (bit_in_stream % 4);

            int bit_index = row * size + col;  // Row-major storage index
            int bit_value = (barcode[bit_index / 8] >> (7 - (bit_index % 8))) & 1;

            if (bit_value)
                nibble_stream[nibble_idx] |= (1 << bit_in_nibble);
        }
    }

    int nib_idx = 0;

    // Extract length (stored as 2 nibbles = 1 byte)
    if (nib_idx + 2 > total_nibbles)
        return 1;

    int len = (nibble_stream[nib_idx] << 4) | nibble_stream[nib_idx + 1];
    nib_idx += 2;

    if (len > MAX_LENGTH || len < 1)
        return 1;

    // Verify sufficient data: length (2 nibbles) + data (len*2 nibbles) + terminator (4 nibbles) + checksum (4 nibbles)
    if (nib_idx + (len * 2) + 4 + 4 > total_nibbles)
        return 1;

    // Extract string data (each character is 2 nibbles = 1 byte)
    for (int i = 0; i < len; i++)
    {
        unsigned char ch = (nibble_stream[nib_idx] << 4) | nibble_stream[nib_idx + 1];
        output[i] = ch;
        nib_idx += 2;
    }
    output[len] = '\0';

    // Verify terminator is 0x0000 (4 nibbles of zeros)
    if (nibble_stream[nib_idx] != 0 || nibble_stream[nib_idx + 1] != 0 ||
        nibble_stream[nib_idx + 2] != 0 || nibble_stream[nib_idx + 3] != 0)
    {
        *error = 1;  // Terminator mismatch indicates corruption
    }
    nib_idx += 4;

    // Recalculate checksum and compare with stored value
    unsigned int hex_sum = 0;
    hex_sum += (len >> 4) & 0x0F;
    hex_sum += len & 0x0F;

    for (int i = 0; i < len; i++)
    {
        unsigned char ch = (unsigned char)output[i];
        hex_sum += (ch >> 4) & 0x0F;
        hex_sum += ch & 0x0F;
    }

    // Extract stored checksum (4 nibbles = 2 bytes)
    unsigned int stored_checksum = (nibble_stream[nib_idx] << 12) |
                                   (nibble_stream[nib_idx + 1] << 8) |
                                   (nibble_stream[nib_idx + 2] << 4) |
                                   nibble_stream[nib_idx + 3];
    nib_idx += 4;

    if ((hex_sum & 0xFFFF) != stored_checksum)
        *error = 1;  // Checksum mismatch indicates corruption

    // Verify remaining padding nibbles match expected 0xEC, 0x11 pattern
    unsigned char fill[] = {0xEC, 0x11};
    int fill_idx = 0;

    while (nib_idx < total_nibbles)
    {
        unsigned char expected_nibble;
        if (nib_idx % 2 == 0)
            expected_nibble = (fill[fill_idx] >> 4) & 0x0F;  // High nibble of fill byte
        else
        {
            expected_nibble = fill[fill_idx] & 0x0F;  // Low nibble of fill byte
            fill_idx ^= 1;  // Alternate between 0xEC and 0x11
        }

        if (nibble_stream[nib_idx] != expected_nibble)
            *error = 1;  // Padding mismatch indicates corruption

        nib_idx++;
    }

    return 0;
}