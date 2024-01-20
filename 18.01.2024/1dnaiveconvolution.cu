#include<iostream>
#include<vector>
#include <cassert>

__global__ void conv_naive(int *d_n,int *d_m,int* d_p,int n,int maskwidth)
{
    int threadid=(blockIdx.x*blockDim.x)+ threadIdx.x;
    
       int radius = maskwidth/2;
       int start= threadid-radius;
     int temp=0;
    for(int j=0;j<maskwidth;j++)
    {
        if((start+j)>=0 && (start+j<n))
        {
           temp+=d_n[start+j]*d_m[j]; 
        }
    }
    d_p[threadid]=temp;
}
void verify_result(int *array, int *mask, int *result, int n, int m) {
  int radius = m / 2;
  int temp;
  int start;
  for (int i = 0; i < n; i++) {
    start = i - radius;
    temp = 0;
    for (int j = 0; j < m; j++) {
      if ((start + j >= 0) && (start + j < n)) {
        temp += array[start + j] * mask[j];
      }
    }
    std::cout<<temp<<" "<<result[i]<<" "<<"\n";
    assert(temp == result[i]);
  }
}
int main()
{
    int n=1024;
    size_t bytes=n*sizeof(int);
    std::vector<int> N;
       N.reserve(n);
    std::vector<int> M;
    M.reserve(5);
    std::vector<int> P;
    P.reserve(n);

    for(int i=0;i<n;i++)
    {
        N.push_back(rand()%100);
    }
    
    for(int i=0;i<5;i++)
    {
        M.push_back(rand()%100);
    }

    int *d_n,*d_m,*d_p;
    cudaMalloc(&d_n,bytes);
    cudaMalloc(&d_m,5*sizeof(int));
    cudaMalloc(&d_p,bytes);

  cudaMemcpy(d_n, N.data(), bytes, cudaMemcpyHostToDevice);
  cudaMemcpy(d_m, M.data(),5*sizeof(int), cudaMemcpyHostToDevice);
    
    int threadnumber=256;
    int blocknumber=(n+threadnumber-1)/threadnumber;
    conv_naive<<<blocknumber,threadnumber>>>(d_n,d_m,d_p,n,5);
      cudaMemcpy(P.data(), d_p, bytes, cudaMemcpyDeviceToHost);

       verify_result(N.data(), M.data(), P.data(), n,5);

  std::cout << "COMPLETED SUCCESSFULLY\n";

}