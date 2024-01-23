%%cu
#include<iostream>
#include<cassert>
#include<cstdlib>

#define maskdim 3

#define maskoffset (maskdim/2)
#define N 1024
__constant__ int mask[maskdim*maskdim];

__global__ void convolution_2d(int *matrix, int* result)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    int startrow = row - maskoffset;
    int startcol = col - maskoffset;
    int temp = 0;

    for (int i = 0; i < maskdim; i++)
    {
        for (int j = 0; j < maskdim; j++)
        {
            if (startrow+i >= 0 && (startrow + i) < N && startcol+j >= 0 && (startcol + j) < N)
            {
                temp += matrix[(startrow + i) * N + (startcol + j)] * mask[i * maskdim + j];
            }
        }
    }

    if (row < N && col < N) {
        result[row * N + col] = temp;
    }
}

void verify_result(int *m, int *mask, int *result) {
    int temp;
    int offset_r;
    int offset_c;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            temp = 0;

            for (int k = 0; k < maskdim; k++) {
                offset_r = i - maskoffset + k;

                for (int l = 0; l < maskdim; l++) {
                    offset_c = j - maskoffset + l;

                    if (offset_r >= 0 && offset_r < N && offset_c >= 0 && offset_c < N) {
                        temp += m[offset_r * N + offset_c] * mask[k * maskdim + l];
                    }
                }
            }
         //std::cout<<result[i * N + j]<<"\t"<<temp<<"\n";
            assert(result[i * N + j] == temp);
        }
    }
}

int main()
{
    size_t bytes = sizeof(int) * N * N;
    int *matrix = new int[N * N];
    int *result = new int[N * N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[N * i + j] = rand() % 100;
        }
    }

    int *hmask = new int[maskdim * maskdim];
    for (int i = 0; i < maskdim; i++) {
        for (int j = 0; j < maskdim; j++) {
            hmask[maskdim * i + j] = rand() % 100;
        }
    }

    cudaMemcpyToSymbol(mask, hmask, sizeof(int) * maskdim * maskdim);

    int *d_matrix;
    int *d_result;
    cudaMalloc(&d_matrix, bytes);
    cudaMalloc(&d_result, bytes);
    cudaMemcpy(d_matrix, matrix, bytes, cudaMemcpyHostToDevice);

    int THREADS = 16;
    int BLOCKS = (N + THREADS - 1) / THREADS;
    dim3 block_dim(THREADS, THREADS);
    dim3 grid_dim(BLOCKS, BLOCKS);

    convolution_2d<<<grid_dim, block_dim>>>(d_matrix, d_result);
    cudaMemcpy(result, d_result, bytes, cudaMemcpyDeviceToHost);

    verify_result(matrix, hmask, result);

    std::cout << "COMPLETED SUCCESSFULLY!\n";
    delete[] matrix;
    delete[] result;
    delete[] hmask;

    cudaFree(d_matrix);
    cudaFree(d_result);

    return 0;
}
