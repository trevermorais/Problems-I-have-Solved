#include <cs50.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int HEADERSIZE = 44;

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    FILE *output = fopen(argv[2], "wb");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);
    fclose(input);
    fclose(output);

    FILE *ipt = fopen(argv[1], "rb");
    unsigned char inp[44];
    size_t inp_read = fread(&inp, 1, 44, ipt);

    FILE *opt = fopen(argv[2], "wb");
    if (opt != NULL)
    {
        size_t bytes_written = fwrite(inp, 1, 44, opt);
    }

    int16_t package;
    while (fread(&package, 2, 1, ipt) == 1)
    {
        package = package * factor;
        fwrite(&package, 2, 1, opt);
    }
    fclose(ipt);
    fclose(opt);
    return 0;
}
