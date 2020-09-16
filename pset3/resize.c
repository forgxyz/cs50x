#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    //ensure enough cmd line inputs are specified
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    //ensure n is an integer <= 100
    int n = atoi(argv[1]);
//TODO** add isdigit to if/end right here.
    if (n > 100)
    {
        printf("n must be and integer less than or equal to 100.\n");
        return 2;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    //open input file
    FILE *infileR = fopen(infile, "r");
    //check for validity
    if (infileR == NULL)
    {
        printf("File does not exist.\n");
        return 3;
    }

    //open output file
    FILE *outfileW = fopen(outfile, "w");
    if (outfileW == NULL)
    {
        fclose(infileR);
        printf("File does not exist.\n");
        return 4;
    }

    //read infile's headers
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, infileR);
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, infileR);

    //check type to ensure it is a 24-bit BMP
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outfileW);
        fclose(infileR);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }
    //store measurements of the original image
    int paddingOld = (4 - (bi.biWidth * sizeof(RGBTRIPLE) % 4)) % 4;
    int heightOld = abs(bi.biHeight);
    int widthOld = bi.biWidth;

    //Build Outfile
    //size info needs to change appropriately
    bi.biWidth *= n;
    bi.biHeight *= n;
    //Determine padding needed for new file
    int paddingNew = (4 - (bi.biWidth * sizeof(RGBTRIPLE) % 4)) % 4;
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + paddingNew) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    //Write BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outfileW);
    //Write BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outfileW);

    //Time to write the pixels
    //Iterate through scanlines
    for (int i = 0; i < heightOld; i++)
    {
        //second level for loop to copy the line again
        for (int j = 0; j < n; j++)
        {
            //iterate through pixels
            for (int k = 0; k < widthOld; k++)
            {
                //Temporary data storage
                RGBTRIPLE tempRGB;
                fread(&tempRGB, sizeof(RGBTRIPLE), 1, infileR);

                //Copy & write the pixel to outfile n times
                for (int l = 0; l < n; l++)
                {
                    fwrite(&tempRGB, sizeof(RGBTRIPLE), 1, outfileW);
                }
            }
            //Write padding, if any
            for (int m = 0; m < paddingNew; m++)
            {
                fputc(0x00, outfileW);
            }

            //Reset cursor to start of scanline to copy again
            if (j < n - 1)
            {
                fseek(infileR, -(widthOld * sizeof(RGBTRIPLE)), SEEK_CUR);
            }
        }
        //if there was padding in the infile, skip ahead paddingOld bytes (to next scanline)
        fseek(infileR, paddingOld, SEEK_CUR);
    }
    //Copying done, close the files.
    fclose(infileR);
    fclose(outfileW);
    return 0;
}
