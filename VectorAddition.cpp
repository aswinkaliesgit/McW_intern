#include <immintrin.h>
#include <iostream>
#include <chrono>

int main() {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    int size=65535;


    int final_size = size + (8 - (size % 8));
    float a[final_size] = {0};
    float b[final_size] = {0};
    float ans[final_size] = {0};
     
    for (int i = 0; i < size; i++)
         a[i]=i;
    for (int j = 0; j < size; j++)
         b[j]=j;

    auto t1 = high_resolution_clock::now();
    __m256 vec_one;
    __m256 vec_two;
    __m256 vec_three;
    for (int i = 0; i < final_size; i += 8) {
        vec_one = _mm256_load_ps(&a[i]);
        vec_two = _mm256_load_ps(&b[i]);
        vec_three = _mm256_add_ps(vec_one, vec_two);
        _mm256_store_ps(&ans[i], vec_three);
    }
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double = t2 - t1;
    std::cout << ms_double.count() ;

    // for (int i = 0; i < size; i++)
    //     std::cout << ans[i] << " ";
    
    std::cout << std::endl;

    auto t3 = high_resolution_clock::now();
    for (int i = 0; i < final_size; i++) {
        ans[i] = a[i] + b[i];
    }
    auto t4 = high_resolution_clock::now();
    ms_double = t4 - t3;
    std::cout << ms_double.count();

    return 0;
}
