#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[1], "r");
    if(file ==  NULL)
    {
        return 1;
    }

    BYTE buffer[512];
    int index = 0;
    bool reading = false;
    char filename[8];
    FILE *img;
    while(fread(buffer, 512, 1, file) == 1)
    {
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(filename, "%03i.jpg", index);
            printf("%s", filename);
            img = fopen(filename, "w");
            fwrite(buffer, 512, 1, img);
            index++;
        } else {
           fwrite(buffer, 512, 1, img);
        }
    }
}
