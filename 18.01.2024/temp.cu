%%cu
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

__global__ void temp(int *a,int *b,int n)
{
    int id= (blockIdx.x*blockDim.x)+threadIdx.x;
    if(id<n) b[id]=a[id]-100;
  
}
void verify_result(std::vector<int> &a,std::vector<int> &b)
{
    for(int i=0;i<1024;i++)
    {
        assert(a[i]-100==b[i]);
         std::cout<<a[i]<<"\t"<<b[i]<<"\n";
    }
    
}
int main()
{
    int N=1024;
    size_t bytes =sizeof(int)*N;
      std::vector<int> a;
  a.reserve(N);
     std::vector<int> b;
  b.reserve(N);
      for (int i = 0; i < N; i++) {
    a.push_back(rand() % 100);}
     int *d_a, *d_b;
      cudaMalloc(&d_a, bytes);
  cudaMalloc(&d_b, bytes);
    cudaMemcpy(d_a, a.data(), bytes, cudaMemcpyHostToDevice);
    int numthreads= 1024;

    int numblocks=1;
    temp<<<numblocks,numthreads>>>(d_a,d_b,1024);

 cudaMemcpy(b.data(), d_b, bytes, cudaMemcpyDeviceToHost);
    verify_result(a,b);
    std::cout<<"completed";
}
