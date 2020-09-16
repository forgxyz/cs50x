//Recover jpg files from a .raw sourcefile
//24 - 27 September 2019

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
void copyBlock(FILE *infile, FILE *outfile);

int main(int argc, char *argv[])
{
    //Check command line input
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover input.raw\n");
        return 1;
    }
    //Validate input file
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        fprintf(stderr, "File cannot be opened.\n");
        return 2;
    }

    //determine size of input file and the number of blocks
    fseek(infile, 0, SEEK_END);
    int blockSize = 512, fileSize = ftell(infile), blocks = fileSize / blockSize, start = 0, count = 0;
    fseek(infile, 0, SEEK_SET);

    //determine initial file name & open first file
    char *JPGfileName = malloc(sizeof(char) * 8);
    sprintf(JPGfileName, "%03i.jpg", count);
    FILE *workingJPG = fopen(JPGfileName, "w");
    if (workingJPG == NULL)
    {
        fprintf(stderr, "Output file error.\n");
        return 3;
    }

    //loop through every block in the input file
    for (int i = 0; i < blocks; i++)
    {
        //ensure starting point is the beginning of the block
        fseek(infile, blockSize * i, SEEK_SET);

        //check the first four bytes for jpg signature
        BYTE tempByte;
        fread(&tempByte, sizeof(BYTE), 1, infile); //read input byte by byte
        if (tempByte == 255)
        {
            fread(&tempByte, sizeof(BYTE), 1, infile);
            if (tempByte == 216)
            {
                fread(&tempByte, sizeof(BYTE), 1, infile);
                if (tempByte == 255)
                {
                    fread(&tempByte, sizeof(BYTE), 1, infile);
                    if (tempByte >= 224 && tempByte <= 239)
                    {
                        start = 1; //start of a .jpg found!
                        count++; //counter for filename
                    }
                    else
                    {
                        start = 0;
                    }
                }
                else
                {
                    start = 0;
                }
            }
            else
            {
                start = 0;
            }
        }
        else
        {
            start = 0;
        }
        fseek(infile, blockSize * i, SEEK_SET); //ensure copying from start of block
        if (start == 1) //start of new .jpg
        {
            if (count > 1)
            {
                //not the first jpg found, close the previous file
                fclose(workingJPG);
                sprintf(JPGfileName, "%03i.jpg", (count - 1));
                workingJPG = fopen(JPGfileName, "w");
                copyBlock(infile, workingJPG);
            }
            else
            {
                //first jpg signature found, begin copy
                copyBlock(infile, workingJPG);
            }
        }
        else if (start == 0 && count > 0) //no jpg signature found, copy to open file
        {
            copyBlock(infile, workingJPG);
        }
    }
    //All blocks have been iterated through
    fclose(workingJPG); //close the final .jpg
    fclose(infile); //close the input file
    free(JPGfileName); //free char* memory
    return 0; //success
}

void copyBlock(FILE *infile, FILE *outfile)
{
    int blockSize = 512;
    for (int i = 0; i < blockSize; i++)
    {
        BYTE tempBuffer;
        fread(&tempBuffer, sizeof(BYTE), 1, infile);
        fwrite(&tempBuffer, sizeof(BYTE), 1, outfile);
    }
}
