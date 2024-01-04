#include <immintrin.h>
#include <iostream>
using namespace std;
int main() {
    // Example vector with 64 elements
    float values[64] = {
        1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0,
        9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
        17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
        25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0,
        33.0, 34.0, 35.0, 36.0, 37.0, 38.0, 39.0, 40.0,
        41.0, 42.0, 43.0, 44.0, 45.0, 46.0, 47.0, 48.0,
        49.0, 50.0, 51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
        57.0, 58.0, 59.0, 60.0, 61.0, 62.0, 63.0, 64.0
    };
    float ans[8];
 int q=0;
    // Load the values into an AVX register
    for(int i=0;i<64;i+=8){
    __m256 vec = _mm256_loadu_ps(&values[i]);

    // Add the elements in the vector to a single scalar value
    __m128 sum128 = _mm256_extractf128_ps(vec, 0); // Extract the lower 128 bits
    sum128 = _mm_add_ps(sum128, _mm256_extractf128_ps(vec, 1)); // Add the upper 128 bits

    sum128 = _mm_hadd_ps(sum128, sum128); // Horizontal add
    sum128 = _mm_hadd_ps(sum128, sum128);

    float result;
    _mm_store_ss(&result, sum128); // Store the result in a scalar float
ans[q++]=result;
   

}

__m256 vec = _mm256_loadu_ps(ans);

    // Add the elements in the vector to a single scalar value
    __m128 sum128 = _mm256_extractf128_ps(vec, 0); // Extract the lower 128 bits
    sum128 = _mm_add_ps(sum128, _mm256_extractf128_ps(vec, 1)); // Add the upper 128 bits

    sum128 = _mm_hadd_ps(sum128, sum128); // Horizontal add
    sum128 = _mm_hadd_ps(sum128, sum128);
    float result;
    _mm_store_ss(&result, sum128); 
    cout<<result;

}