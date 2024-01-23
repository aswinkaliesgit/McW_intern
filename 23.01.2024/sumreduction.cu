%%cu
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>

using std::accumulate;
using std::cout;
using std::generate;
using std::vector;

__global__ void temp(int *input, int *output)
{
    __shared__ int sum[256];

    int t_id = blockIdx.x * blockDim.x + threadIdx.x;

    sum[threadIdx.x] = input[t_id];
    __syncthreads();

    for (int s = 1; s < blockDim.x; s *= 2)
    {
        int index = 2 * s * threadIdx.x;
        if (index < blockDim.x)
        {
            sum[index] += sum[index + s];
        }
        __syncthreads();
    }

    if (threadIdx.x == 0)
        output[blockIdx.x] = sum[0];
}

void verify(const vector<int> &output)
{
   
    std::cout<<output[0]<<"\n";
    assert(output[0] == 65536);
}

int main()
{
    int N = 1<<16;
    size_t bytes = N * sizeof(int);

    vector<int> input(N);
    vector<int> output(N);

    for (int i = 0; i < N; i++)
    {
        input[i] = 1;
    }

    int *d_input, *d_output;

    cudaMalloc(&d_input, bytes);
    cudaMalloc(&d_output, bytes);
    cudaMemcpy(d_input, input.data(), bytes, cudaMemcpyHostToDevice);

    int threads = 256;
    int grids = N / threads;

    temp<<<grids, threads>>>(d_input, d_output);
    temp<<<1, threads>>>(d_output, d_output);

    cudaMemcpy(output.data(), d_output, bytes, cudaMemcpyDeviceToHost);

    verify(output);

    cout << "COMPLETED SUCCESSFULLY\n";

    return 0;
}

