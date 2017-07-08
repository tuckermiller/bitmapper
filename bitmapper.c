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
    unsigned char pixelData[bitmapInfoHeader.imageDataSize];
    fseek(filePtr, bitmapFileHeader.imageDataOffset, SEEK_SET);
    fread(pixelData, sizeof(pixelData), 1, filePtr);

    // Do test operation on the pixel data
    // For now, assume 24 bit color


    // A counter for the current byte in the current row of pixel data
    int rowByteCounter = 0;

    // Each row is padded so that its number of bytes is a multiple of 4
    int rowPadding = 0;
    int bytesPerRow = bitmapInfoHeader.imageWidth * 3;
    if (bytesPerRow % 4 != 0)
    {
        rowPadding = 4 - (bytesPerRow % 4);
    }

    int i = 0;
    int pixelInRow = 0;
    while(i < sizeof(pixelData))
    {
        int averageColor = (pixelData[i] + pixelData[i + 1] + pixelData[i + 2]) / 3;
        pixelData[i] = averageColor;
        pixelData[i + 1] = averageColor;
        pixelData[i + 2] = averageColor;
        if (pixelInRow == bitmapInfoHeader.imageWidth - 1)
        {
            i += rowPadding + 3;
            pixelInRow = 0;
        } else
        {
            i += 3;
            pixelInRow ++;
        }
    }

    fseek(filePtr, bitmapFileHeader.imageDataOffset, SEEK_SET);
    fwrite(pixelData, 1, sizeof(pixelData), filePtr);

    fclose(filePtr);

    return 0;
}