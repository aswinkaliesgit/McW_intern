#include <immintrin.h>
#include <iostream>

int main() {
    float a[8][8] = {
        {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0},
        {9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0},
        {17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0},
        {25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0},
        {33.0, 34.0, 35.0, 36.0, 37.0, 38.0, 39.0, 40.0},
        {41.0, 42.0, 43.0, 44.0, 45.0, 46.0, 47.0, 48.0},
        {49.0, 50.0, 51.0, 52.0, 53.0, 54.0, 55.0, 56.0},
        {57.0, 58.0, 59.0, 60.0, 61.0, 62.0, 63.0, 64.0}
    };

    float b[8][8] = {
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8}
    };

    __m256 vec_one;
    __m256 vec_two;
    __m256 vec_three;

    for (int i = 0; i < 8; ++i) {
        __m256 row = _mm256_loadu_ps(&a[i][0]);
        float rowValues[8];
        _mm256_storeu_ps(rowValues, row);

        float colValues[8];
        for (int j = 0; j < 8; j++) {
            for (int z = 0; z < 8; z++)
                colValues[z] = b[z][j];

            vec_one = _mm256_loadu_ps(&rowValues[0]);
            vec_two = _mm256_loadu_ps(&colValues[0]);
            vec_three = _mm256_mul_ps(vec_one, vec_two);

            __m128 sum128 = _mm256_extractf128_ps(vec_three, 0);
            sum128 = _mm_add_ps(sum128, _mm256_extractf128_ps(vec_three, 1));
            sum128 = _mm_hadd_ps(sum128, sum128);
            sum128 = _mm_hadd_ps(sum128, sum128);
            
            float ans;
            _mm_store_ss(&ans, sum128);
            std::cout << ans << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
