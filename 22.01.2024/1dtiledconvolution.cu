%%cu
#include<iostream>
#include<algorithm>
#include<vector>
#include<cassert>
const int outwidth = 4;

__global__ void temp(int * input, int *output, int * mask, int width)
{
    int tx = threadIdx.x;
    int index_o = blockIdx.x * outwidth + threadIdx.x;
    int index_i = index_o -2;
    int temp1 = 0;
    __shared__ int input_s[8];
    if ((index_i) >= 0 && (index_i) < width)
    {
        input_s[tx] = input[index_i];
    }
    else
    {
        input_s[tx] = 0;
    }
    __syncthreads();
    if (tx < outwidth)
    {
        temp1 = 0;
        for (int j = 0; j < 5; j++)
            temp1 += mask[j] * input_s[j + tx];
        output[index_o] = temp1;
    }
}

void serial_temp(const std::vector<int>& input, const std::vector<int>& mask, std::vector<int>& output, int width)
{
    for (int i = 0; i < width; i++)
    {
        int temp = 0;
        for (int j = 0; j < 5; j++)
        {
            int index = i - (5 / 2) + j;
            if (index >= 0 && index < width)
            {
                temp += mask[j] * input[index];
            }
        }
        output[i] = temp;
    }
}
int main()
{
    int width = 1024;
    size_t bytes = sizeof(int) * width;
    // Host data
    std::vector<int> input;
    input.reserve(width);
    std::vector<int> mask;
    mask.reserve(5);
    std::vector<int> output;
    output.reserve(width);
    // Generate random input and mask
    for (int i = 0; i < width; i++)
    {
        input.push_back(rand() % 100);
    }
    for (int i = 0; i < 5; i++)
    {
        mask.push_back(rand() % 100);
    }
    // Allocate device memory
    int* d_i, *d_m, *d_o;
    cudaMalloc(&d_i, bytes);
    cudaMalloc(&d_m, 5 * sizeof(int));
    cudaMalloc(&d_o, bytes);

    cudaMemcpy(d_i, input.data(), bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_m, mask.data(), 5 * sizeof(int), cudaMemcpyHostToDevice);
    // Launch GPU kernel
    int threads = 99;
    int blocks = (width + threads - 1) / threads;
    temp<<<blocks, threads>>>(d_i, d_o, d_m, width);
    cudaMemcpy(output.data(), d_o, bytes, cudaMemcpyDeviceToHost);
    std::vector<int> serial_output(width);
    serial_temp(input, mask, serial_output, width);
    for (int i = 0; i < 5; i++)
    {
        std::cout << "Element " << i << " - GPU: " << output[i] << " | Serial: " << serial_output[i] << std::endl;
    }
    std::cout << "Verification completed." << std::endl;
    cudaFree(d_i);
    cudaFree(d_m);
    cudaFree(d_o);
    return 0;
}






