#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#pragma pack(push, 1)
typedef struct BitmapFileHeader {
    uint16_t fileType;
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t imageDataOffset;
} BitmapFileHeader;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct BitmapInfoHeader {
    uint32_t headerSize;
    int32_t imageWidth;
    int32_t imageHeight;
    uint16_t colorPlanes;
    uint16_t bitsPerPixel;
    uint32_t compressionMethod;
    uint32_t imageDataSize;
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    uint32_t numColorsUsed;
    uint32_t numImportantColorsUsed;
} BitmapInfoHeader;
#pragma pack(pop)

int main (int argc, char *argv[]) {
    // Open file from first argument
    FILE *filePtr = fopen(argv[1], "rb+");

    if(filePtr == NULL)
        return -1;

    // Read file header
    BitmapFileHeader bitmapFileHeader;
    fread(&bitmapFileHeader, sizeof(BitmapFileHeader), 1, filePtr);

    // Read image info header
    BitmapInfoHeader bitmapInfoHeader;
    fread(&bitmapInfoHeader, sizeof(BitmapInfoHeader), 1, filePtr);
    
    // Read pixel data
    
   return 0;
}