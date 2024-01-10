#include <immintrin.h>
#include <iostream>

void multiplyAndAccumulateRows(const float matrix1[8][16], const float matrix2[8][16], float result[8]) {
    __m256 row0, row1, row2, row3, row4, row5, row6, row7;
    __m256 row8, row9, row10, row11, row12, row13, row14, row15;

    for (int j = 0; j < 16; ++j) {
        
        row0 = _mm256_loadu_ps(&matrix1[0][j]);
        row1 = _mm256_loadu_ps(&matrix1[1][j]);
        row2 = _mm256_loadu_ps(&matrix1[2][j]);
        row3 = _mm256_loadu_ps(&matrix1[3][j]);
        row4 = _mm256_loadu_ps(&matrix1[4][j]);
        row5 = _mm256_loadu_ps(&matrix1[5][j]);
        row6 = _mm256_loadu_ps(&matrix1[6][j]);
        row7 = _mm256_loadu_ps(&matrix1[7][j]);

       
        row8 = _mm256_loadu_ps(&matrix2[j][0]);
        row9 = _mm256_loadu_ps(&matrix2[j][1]);
        row10 = _mm256_loadu_ps(&matrix2[j][2]);
        row11 = _mm256_loadu_ps(&matrix2[j][3]);
        row12 = _mm256_loadu_ps(&matrix2[j][4]);
        row13 = _mm256_loadu_ps(&matrix2[j][5]);
        row14 = _mm256_loadu_ps(&matrix2[j][6]);
        row15 = _mm256_loadu_ps(&matrix2[j][7]);

      
        row0 = _mm256_mul_ps(row0, row8);
        row1 = _mm256_mul_ps(row1, row9);
        row2 = _mm256_mul_ps(row2, row10);
        row3 = _mm256_mul_ps(row3, row11);
        row4 = _mm256_mul_ps(row4, row12);
        row5 = _mm256_mul_ps(row5, row13);
        row6 = _mm256_mul_ps(row6, row14);
        row7 = _mm256_mul_ps(row7, row15);

        
        row0 = _mm256_add_ps(row0, row1);
        row2 = _mm256_add_ps(row2, row3);
        row4 = _mm256_add_ps(row4, row5);
        row6 = _mm256_add_ps(row6, row7);

        row0 = _mm256_add_ps(row0, row2);
        row4 = _mm256_add_ps(row4, row6);

        
        _mm256_storeu_ps(&result[j], _mm256_add_ps(row0, row4));
    }
}

int main() {
 
    float matrix1[8][16];
    float matrix2[8][16];

   
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 16; ++j) {
            matrix1[i][j] = static_cast<float>(i * 16 + j + 1);
        }
    }

  
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 16; ++j) {
            matrix2[i][j] = static_cast<float>(i * 16 + j + 129);
        }
    }

  
    float result[8];

    
    multiplyAndAccumulateRows(matrix1, matrix2, result);

    
    std::cout << "Result matrix:" << std::endl;
    for (int i = 0; i < 8; ++i) {
        std::cout << result[i] << "\t";
    }
    std::cout << std::endl;

    return 0;
}
