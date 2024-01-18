#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <vector>

using std::cout;
using std::generate;
using std::vector;
__global__ void tiledmat(int* a,int* b,int* c,int n)
{
    int blockx=blockIdx.x;
    int threadx=threadIdx.x;
    int blocky=blockIdx.y;
    int thready=threadIdx.y;
__shared__ int A[256];
 __shared__ int B[256];
    
int temp=0;


//global row and columns
  
    int row= blocky*blockDim.y + thready;
    int col= blockx*blockDim.x + threadx;

    for(int i=0;i<n;i+=blockDim.x)
    {
        A[blocky*blockDim.x + threadx]= a[row*n + i + threadx];
        B[blocky*blockDim.x + threadx]=b[i*n + thready*n+ col];
         __syncthreads();
        for(int j=0;j<blockDim.x;j++)
        {
            temp+=A[threadIdx.y * blockDim.x + j]*B[j * blockDim.x + threadIdx.x];
        }
        __syncthreads();
    }
   c[row*n+col]=temp;
}
void verify_result(vector<int> &a, vector<int> &b, vector<int> &c,int n) {
  // For every row...
  for (int i = 0; i < n; i++) {
    // For every column...
    for (int j = 0; j < n; j++) {
      // For every element in the row-column pair
      int tmp = 0;
      for (int k = 0; k < n; k++) {
        // Accumulate the partial results
        tmp += a[i * n + k] * b[k * n + j];
      }

      // Check against the CPU result
      assert(tmp == c[i * n + j]);
    }
  }
}
int main()
{
    int n=1024;

    size_t bytes =n*n*sizeof(int);

    vector<int> a(n*n);
    vector<int> b(n*n);
    vector<int> c(n*n);
  int *d_a, *d_b, *d_c;
  cudaMalloc(&d_a, bytes);
  cudaMalloc(&d_b, bytes);
  cudaMalloc(&d_c, bytes);

  // Copy data to the device
  cudaMemcpy(d_a,a.data(), bytes, cudaMemcpyHostToDevice);
  cudaMemcpy(d_b,b.data(), bytes, cudaMemcpyHostToDevice);
    for(int i=0;i<n*n;i++)
    {
        a.push_back(rand()%100);
        b.push_back(rand()%100);
    }
dim3 threads(16,16);
dim3 blocks(n/16,n/16);
  
    tiledmat<<<blocks,threads>>>(d_a,d_b,d_c,n);
    cudaMemcpy(c.data(), d_c, bytes, cudaMemcpyDeviceToHost);
    verify_result(a, b,c,n);

 cout << "COMPLETED SUCCESSFULLY\n";

}