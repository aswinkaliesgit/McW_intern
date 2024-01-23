%%cu
#include<iostream>
#include<cassert>
#include<cstdlib>
#include <fstream>
#include <cstdint>
#include <vector>

#define maskdim 3

#define maskoffset (maskdim/2)
#define N 575
__constant__ int mask[maskdim*maskdim];
#pragma pack(push, 1)

struct BitmapHeader {
    uint16_t signature;
    uint32_t fileSize;
    uint32_t reserved;
    uint32_t dataOffset;
    uint32_t headerSize;
    int32_t  width;
    int32_t  height;
    uint16_t planes;
    uint16_t bitDepth;
    uint32_t compression;
    uint32_t imageSize;
    int32_t  xPixelsPerMeter;
    int32_t  yPixelsPerMeter;
    uint32_t colorsUsed;
    uint32_t colorsImportant;
};
#pragma pack(pop)

struct Pixel {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};

struct Bitmap {
    BitmapHeader header;
    std::vector<Pixel> pixels;
};

void readBitmap(const char* filename, Bitmap& bitmap) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    file.read(reinterpret_cast<char*>(&bitmap.header), sizeof(BitmapHeader));

    if (bitmap.header.signature != 0x4D42 || bitmap.header.bitDepth != 24 || bitmap.header.compression != 0) {
        std::cerr << "Invalid BMP file format or unsupported features." << std::endl;
        file.close();
        return;
    }

    uint32_t rowSize = (bitmap.header.width * 3 + 3) & ~3;
    bitmap.pixels.resize(bitmap.header.height * bitmap.header.width);

    for (int y = bitmap.header.height - 1; y >= 0; --y) {
        file.read(reinterpret_cast<char*>(bitmap.pixels.data() + y * bitmap.header.width), rowSize);
    }

    file.close();
}

void writeBitmap(const char* filename, const Bitmap& bitmap) {
    std::ofstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    file.write(reinterpret_cast<const char*>(&bitmap.header), sizeof(BitmapHeader));

    uint32_t rowSize = (bitmap.header.width * 3 + 3) & ~3;

    for (int y = bitmap.header.height - 1; y >= 0; --y) {
        file.write(reinterpret_cast<const char*>(bitmap.pixels.data() + y * bitmap.header.width), rowSize);
    }

    file.close();
}

__global__ void convolution_2d(Pixel *matrix, Pixel *result)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    int startrow = row - maskoffset;
    int startcol = col - maskoffset;
    int temp1 = 0;
    int temp2 = 0;
    int temp3 = 0;

    for (int i = 0; i < maskdim; i++)
    {
        for (int j = 0; j < maskdim; j++)
        {
            if (startrow + i >= 0 && (startrow + i) < N && startcol + j >= 0 && (startcol + j) < N)
            {
                temp1 += matrix[(startrow + i) * N + (startcol + j)].red * mask[i * maskdim + j];
                temp2 += matrix[(startrow + i) * N + (startcol + j)].blue * mask[i * maskdim + j];
                temp3 += matrix[(startrow + i) * N + (startcol + j)].green * mask[i * maskdim + j];
            }
        }
    }

    if (row < N && col < N)
    {
        result[row * N + col].red = temp1;
        result[row * N + col].blue = temp2;
        result[row * N + col].green = temp3;
    }
}

int main()
{
    int *result = new int[N * N];

    int hmask[3 * 3] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};

    cudaMemcpyToSymbol(mask, hmask, sizeof(int) * maskdim * maskdim);
    const char *filename = "input.bmp";
    Bitmap bitmap;

    readBitmap(filename, bitmap);
    std::cout << "Width: " << bitmap.header.width << std::endl;
    Pixel *d_pixel;
    Pixel *d_result;
    cudaMalloc(&d_pixel, bitmap.header.height * bitmap.header.width * sizeof(Pixel));
    cudaMalloc(&d_result, bitmap.header.height * bitmap.header.width * sizeof(Pixel));
    cudaMemcpy(d_pixel, bitmap.pixels.data(), bitmap.header.height * bitmap.header.width * sizeof(Pixel), cudaMemcpyHostToDevice);

    std::cout << "Width: " << bitmap.header.width << std::endl;
    std::cout << "Height: " << bitmap.header.height << std::endl;

    dim3 blockSize(16, 16);
    dim3 gridSize((bitmap.header.width + blockSize.x - 1) / blockSize.x, (bitmap.header.height + blockSize.y - 1) / blockSize.y);
    convolution_2d<<<gridSize, blockSize>>>(d_pixel, d_result);

    std::vector<Pixel> a(bitmap.header.height * bitmap.header.width);
    cudaMemcpy(a.data(), d_result, bitmap.header.height * bitmap.header.width * sizeof(Pixel), cudaMemcpyDeviceToHost);

    Bitmap modifiedBitmap;
    modifiedBitmap.header = bitmap.header;
    modifiedBitmap.pixels = a;

    writeBitmap("output.bmp", modifiedBitmap);

    cudaFree(d_pixel);
    cudaFree(d_result);

    delete[] result;

    return 0;
}
