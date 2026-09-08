#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    FILE *card = fopen(argv[1], "rb");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    uint8_t buffer[512];
    FILE *img_file = NULL;
    int img_count = 0;
    char filename[8];

    while (fread(buffer, 1, 512, card) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (img_file != NULL)
            {
                fclose(img_file);
            }
            sprintf(filename, "%03i.jpg", img_count);
            img_file = fopen(filename, "w");
            if (img_file == NULL)
            {
                printf("Could not create output image %s\n", filename);
                fclose(card);
                return 1;
            }
            img_count++;
        }
        if (img_file != NULL)
        {
            fwrite(buffer, sizeof(BYTE), 512, img_file);
        }
    }
    if (img_file != NULL)
    {
        fclose(img_file);
    }

    fclose(card);

    return 0;
}
