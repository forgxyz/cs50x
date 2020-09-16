# Questions

## What's `stdint.h`?

It is a header file that defines integer types with exact, maximum or minimum widths. They might be signed or unsigned integers.

The "width" of an integer type is the number of bits used to store its value in a pure binary system; the actual type may use more bits than that (for example, a 28-bit type could be stored in 32 bits of actual storage). An N-bit signed type has values in the range -2N-1 or 1-2N-1 to 2N-1-1, while an N-bit unsigned type has values in the range 0 to 2N-1.
https://pubs.opengroup.org/onlinepubs/9699919799/

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

The datatype 'uint8_t' is an unsigned integer 8 bits (one byte) in size.
'int32_t' is a signed integer 32 bits (4 bytes) in size.
The unsigned integers have a minimum value of 0 whereas the signed integers minimum value is -2^(n-1). Where n is the number of bits.
The maximum value for an unsigned integer is 2^n - 1 whereas the signed integer has a maximum value of 2^(n-1) - 1.

The difference is because the unsigned integer cannot have a value less than 0. So, the unsigned integer can hold up to 2^n - 1 positive values. The signed integer includes both positie and negative integers. So, 2^(n-1) - 1 effectively cuts the potential positive values in half to account for the negative spectrum. The - 1 is because 0 is included.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?
From bmp.h:
typedef uint8_t  BYTE; //unsigned 8-bit integer = 1 byte
typedef uint32_t DWORD; //unsigned 32-bit integer = 4 bytes
typedef int32_t  LONG; //signed 32-bit integer = 4 bytes
typedef uint16_t WORD; //unsigned 16-bit integer = 2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

BITMAPFILEHEADER is the 14 byte header for a .BMP file. The first two bytes are bfType of type WORD. WORD is a unsigned 16-bit integer.
The first two bytes indicate the filetype: BM, in ASCII 66 77, in hexadecimal 0x42 0x4D

## What's the difference between `bfSize` and `biSize`?

bfSize is defined in BITMAPFILEHEADER and is a DWORD.
 - The size, in bytes, of the bitmap file.
biSIZE is defined in BITMAPINFOHEADER and is a DWORD.
 - The number of bytes required by the structure.
Both are unsigned 32-bit integers.

## What does it mean if `biHeight` is negative?

A negative biHeight indicates the BMP is top-down and the origin is the top left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount
The number of bits-per-pixel. The biBitCount member of the BITMAPINFOHEADER structure determines the number of bits that define each pixel and the maximum number of colors in the bitmap.

## Why might `fopen` return `NULL` in `copy.c`?

fopen might return NULL if the file cannot be opened. The file may not exist, may have been mistyped, or may be corrupted.

## Why is the third argument to `fread` always `1` in our code?

The 1 corresponds with the number of items being read from the file. 
    Is it able to find just the BITMAPFILEHEADER or BITMAPINFOHEADER because we are telling the function the exact size via sizeof()? Or does the declaration the line before have something to do with that?
    Both are datatypes defined in bmp.h so the bf and bi variables (pointers?) are BMP specific datatypes. I think the sizeof() is how the proper part of the file is read.

## What value does `copy.c` assign to `padding` if `bi.biWidth` is `3`?

int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
sizeof(RGBTRIPLE) = 
typedef struct
{
    BYTE rgbtBlue;
    BYTE rgbtGreen;
    BYTE rgbtRed;
} __attribute__((__packed__))
RGBTRIPLE;
So, RGBTRIPLE is 3 BYTES
(4 - (3 * 3) % 4) % 4;
(4 - 9 % 4) % 4;
(4 - 1) % 4
3 % 4 = 3

## What does `fseek` do?

This sets the file position indicator to a certain location. It adds bytes (in this case the int variable padding) to a location.

## What is `SEEK_CUR`?

SEEK_CUR is the third argument in fseek. It adds the offset (padding) to the current position indicator in the file.
fsek at SEEK_CUR is effectively moving the cursor forward in a text editor by offset spaces.
