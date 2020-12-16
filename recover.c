#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
#define BLOCK 512
int jpgfc = 0;

int main(int argc, char *argv[])
{
    //check command line input
    if (argc != 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }

    char *file = argv[1];

    //open forensic file
    FILE *inputfile = fopen(file, "r");

    //check if file is valid
    if (inputfile == NULL)
    {
        printf("Usage: ./recover image");
        return 1;
    }

    char jpgfile[8];
    FILE *jpgfileptr = NULL;
    BYTE buffer[BLOCK];
    //read 512 bytes from inputfile to buffer
    //read until end of file

    while (fread(buffer, BLOCK, 1, inputfile) == 1)
    {

        //read the first four bytes to see if it is jpg, if so write it in new jpgfile
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //if is the 1st jpgfile in inputfile
            if (jpgfileptr == NULL)
            {
                //open a new jpg file and write to it all bytes from buffer
                sprintf(jpgfile, "%03i.jpg", jpgfc);
                jpgfileptr = fopen(jpgfile, "w");
                fwrite(buffer, sizeof(buffer), 1, jpgfileptr);

                //increment one for jpg file
                jpgfc++;
            }

            //if is the 2nd+ jpgfile in inputfile
            else if (jpgfileptr !=  NULL)
            {
                //close opened(last) jpg file
                fclose(jpgfileptr);

                //create a new jpg file and write to it all bytes from buffer
                sprintf(jpgfile, "%03i.jpg", jpgfc);
                jpgfileptr = fopen(jpgfile, "w");
                fwrite(buffer, sizeof(buffer), 1, jpgfileptr);

                //increment one for jpg file
                jpgfc++;
            }

        }

        //keep writing to unfinished jpg file from buffer
        else if (jpgfileptr != NULL)
        {
            fwrite(buffer, sizeof(buffer), 1, jpgfileptr);
        }
    }

    // close input file from  memory card
    fclose(inputfile);
    fclose(jpgfileptr);

}
