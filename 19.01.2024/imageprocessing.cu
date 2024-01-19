%%cu
#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>

#pragma pack(push, 1) // Pack structures without padding

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
__global__  void temp(Pixel *x,int size)
{
    int id= blockDim.x*blockIdx.x + threadIdx.x;
    if(id<size)
    {
        x[id].red=255-x[id].red;
          x[id].blue=255-x[id].blue;
          x[id].green=255-x[id].green;
    }
}

int main() {
    const char* filename = "input.bmp";
    Bitmap bitmap;

    readBitmap(filename, bitmap);
    std::cout << "Width: " << bitmap.header.width << std::endl;
    std::cout << "Height: " << bitmap.header.height << std::endl;
    Pixel firstPixel = bitmap.pixels[0];
    std::cout << "First Pixel - R: " << static_cast<int>(bitmap.pixels[10].red) << " G: " << static_cast<int>(firstPixel.green) << " B: " << static_cast<int>(firstPixel.blue) << std::endl;

    Pixel *d_pixel ;
    cudaMalloc(&d_pixel, bitmap.header.height * bitmap.header.width * sizeof(Pixel));
   cudaMemcpy(d_pixel, bitmap.pixels.data(), bitmap.header.height * bitmap.header.width * sizeof(Pixel), cudaMemcpyHostToDevice);
    int threadsize=1024;
    int blocks=(bitmap.header.height * bitmap.header.width+threadsize - 1) / threadsize;

  temp<<<blocks,threadsize>>>(d_pixel,bitmap.header.height * bitmap.header.width);
 std::vector<Pixel> a;
  a.reserve(bitmap.header.height * bitmap.header.width);


     cudaMemcpy(a.data(), d_pixel, bitmap.header.height * bitmap.header.width * sizeof(Pixel), cudaMemcpyDeviceToHost);
     std::cout<<(int(a[10].red));
  return 0;
}


