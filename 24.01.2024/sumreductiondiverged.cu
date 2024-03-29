%%cuda


#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <numeric>

using std::accumulate;
using std::generate;
using std::cout;
using std::vector;

#define SHMEM_SIZE 256

__global__ void sumReduction(int *v, int *v_r) {

	__shared__ int partial_sum[SHMEM_SIZE];

	int tid = blockIdx.x * blockDim.x + threadIdx.x;

	// Load elements into shared memory
	partial_sum[threadIdx.x] = v[tid];
	__syncthreads();

	// Iterate of log base 2 the block dimension
	for (int s = 1; s < blockDim.x; s *= 2) {

		if (threadIdx.x % (2 * s) == 0) {
			partial_sum[threadIdx.x] += partial_sum[threadIdx.x + s];
		}
		__syncthreads();
	}

	if (threadIdx.x == 0) {
		v_r[blockIdx.x] = partial_sum[0];
	}
}

int main() {

	int N = 1 << 16;
	size_t bytes = N * sizeof(int);


	vector<int> h_v(N);
	vector<int> h_v_r(N);


  generate(begin(h_v), end(h_v), [](){ return rand() % 10; });


	int *d_v, *d_v_r;
	cudaMalloc(&d_v, bytes);
	cudaMalloc(&d_v_r, bytes);
	

	cudaMemcpy(d_v, h_v.data(), bytes, cudaMemcpyHostToDevice);
	

	const int TB_SIZE = 256;
	int GRID_SIZE = N / TB_SIZE;
	sumReduction<<<GRID_SIZE, TB_SIZE>>>(d_v, d_v_r);

	sumReduction<<<1, TB_SIZE>>> (d_v_r, d_v_r);
	cudaMemcpy(h_v_r.data(), d_v_r, bytes, cudaMemcpyDeviceToHost);
	assert(h_v_r[0] == std::accumulate(begin(h_v), end(h_v), 0));

	cout << "COMPLETED SUCCESSFULLY\n";

	return 0;
}
