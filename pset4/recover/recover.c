#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        return 2;
    }

    BYTE *buffer = malloc(512 * sizeof(BYTE));
    if (buffer == NULL)
    {
        fclose(card);
        return 2;
    }

    int count = 0;
    char *filename = "000.jpg";
    FILE *img = fopen(filename, "w");
    if (img == NULL)
    {
        fclose(card);
        free(buffer);
        return 3;
    }

    while (fread(buffer, sizeof(BYTE), 512, card) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (count == 0)
            {
                fwrite(buffer, sizeof(BYTE), 512, img);
                count++;
            }
            else
            {
                fclose(img);
                filename = malloc(8);
                sprintf(filename, "%03i.jpg", count);
                img = fopen(filename, "w");
                if (img == NULL)
                {
                    fclose(img);
                    fclose(card);
                    free(buffer);
                    free(filename);
                    return 3;
                }

                free(filename);
                fwrite(buffer, sizeof(BYTE), 512, img);
                count++;
            }
        }
        else
        {
            if (count != 0)
            {
                fwrite(buffer, sizeof(BYTE), 512, img);
            }
        }
    }
    fclose(img);
    fclose(card);
    free(buffer);
}