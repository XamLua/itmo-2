#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//structures

struct __attribute__((packed)) bmp_header 
{
    uint16_t bfType;    //file type, must be 'BM'
    uint32_t bfileSize; //bitmap file size in bytes
    uint16_t bfReserved_1; //reserved, must be 0
    uint16_t bfReserved_2; //reserved, must be 0
    uint32_t bOffBits;  //the offset, in bytes, from the beginning of the BITMAPFILEHEADER structure to the bitmap bits.
};

struct __attribute__((packed)) bmp_header_info
{
    uint32_t biSize;            // size of this structure in bytes
    uint32_t biWidth;           // the width of the bitmap, in pixels.
    uint32_t biHeight;          // the height of the bitmap, in pixels.
    uint16_t biPlanes;          // the number of planes for the target device. This value must be set to 1.
    uint16_t biBitCount;        // the number of bits-per-pixel.
    uint32_t biCompression;     // the type of compression 
    uint32_t biSizeImage;       // the size, in bytes, of the image
    uint32_t biXPelsPerMeter;   // the horizontal resolution, in pixels-per-meter, of the target device for the bitmap.
    uint32_t biYPelsPerMeter;   // the vertical resolution, in pixels-per-meter, of the target device for the bitmap.
    uint32_t biClrUsed;         // the number of color indexes in the color table that are actually used by the bitmap.
    uint32_t biClrImportant;    // the number of color indexes that are required for displaying the bitmap.

};

struct __attribute__((packed)) Color_table
{
    
};

struct pixel_t
{
    uint8_t r;
    uint8_t g;
    uint8_t b;

};

struct image_t
{
    uint16_t bits_per_pixel;
    uint32_t color_table_size;
    uint32_t width, height;
    struct pixel_t* color_data;
    uint8_t* pixels_data;
};

//enums
enum read_status 
{
    READ_OK,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER

};

enum write_status 
{
    WRITE_OK,
    WRITE_ERROR

};


//functions

enum read_status from_bmp(FILE* in, struct image_t* const read);

enum write_status to_bmp(FILE* out, struct image_t const* img );

struct image_t rotate_right_90(struct image_t const image);

struct image_t rotate_left_90(const struct image_t image);

struct image_t rotate_any(const struct image_t img, const int dgr);
