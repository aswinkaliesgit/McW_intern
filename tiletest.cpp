// #include <immintrin.h>
// #include <iostream>
// #include <vector>

// // Struct to hold __m256 directly
// struct AVXVector {
//     __m256 vector;

//     // Default constructor (you can add other constructors if needed)
//     AVXVector() {}

//     // Constructor to set __m256 vector
//     AVXVector(__m256 existingVector) : vector(existingVector) {}
// };

// int main() {
//     // Example: Declare a vector of AVXVector
//     std::vector<AVXVector> vectorOfVectors;

//     // Example: Push an existing __m256 vector
//     __m256 myExistingVector = _mm256_set_ps(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f);
//     vectorOfVectors.push_back(AVXVector(myExistingVector));

//     // Example: Push another existing __m256 vector
//     __m256 anotherExistingVector = _mm256_set_ps(2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
//     vectorOfVectors.push_back(AVXVector(anotherExistingVector));

//     // Accessing elements
//     std::cout << "Elements of vectorOfVectors:" << std::endl;
//     for (const auto& avxVec : vectorOfVectors) {
//         float elements[8];
//         _mm256_storeu_ps(elements, avxVec.vector);
//         for (int i = 0; i < 8; ++i) {
//             std::cout << elements[i] << "\t";
//         }
//         std::cout << std::endl;
//     }

//     return 0;
// }
#include <immintrin.h>
#include <iostream>

// void multiplyAndAccumulateRows(const float matrix1[8][16], const float matrix2[8][16], float result[8]) {
//     __m256 row0, row1, row2, row3, row4, row5, row6, row7;
//     __m256 row8, row9, row10, row11, row12, row13, row14, row15;

//     for (int j = 0; j < 16; ++j) {
//         // Load rows from matrix1
//         row0 = _mm256_loadu_ps(&matrix1[0][j]);
//         row1 = _mm256_loadu_ps(&matrix1[1][j]);
//         row2 = _mm256_loadu_ps(&matrix1[2][j]);
//         row3 = _mm256_loadu_ps(&matrix1[3][j]);
//         row4 = _mm256_loadu_ps(&matrix1[4][j]);
//         row5 = _mm256_loadu_ps(&matrix1[5][j]);
//         row6 = _mm256_loadu_ps(&matrix1[6][j]);
//         row7 = _mm256_loadu_ps(&matrix1[7][j]);

//         // Load rows from matrix2
//         row8 = _mm256_loadu_ps(&matrix2[j][0]);
//         row9 = _mm256_loadu_ps(&matrix2[j][1]);
//         row10 = _mm256_loadu_ps(&matrix2[j][2]);
//         row11 = _mm256_loadu_ps(&matrix2[j][3]);
//         row12 = _mm256_loadu_ps(&matrix2[j][4]);
//         row13 = _mm256_loadu_ps(&matrix2[j][5]);
//         row14 = _mm256_loadu_ps(&matrix2[j][6]);
//         row15 = _mm256_loadu_ps(&matrix2[j][7]);

//         // Multiply corresponding rows
//         row0 = _mm256_mul_ps(row0, row8);
//         row1 = _mm256_mul_ps(row1, row9);
//         row2 = _mm256_mul_ps(row2, row10);
//         row3 = _mm256_mul_ps(row3, row11);
//         row4 = _mm256_mul_ps(row4, row12);
//         row5 = _mm256_mul_ps(row5, row13);
//         row6 = _mm256_mul_ps(row6, row14);
//         row7 = _mm256_mul_ps(row7, row15);

//         // Accumulate results
//         row0 = _mm256_add_ps(row0, row1);
//         row2 = _mm256_add_ps(row2, row3);
//         row4 = _mm256_add_ps(row4, row5);
//         row6 = _mm256_add_ps(row6, row7);

//         row0 = _mm256_add_ps(row0, row2);
//         row4 = _mm256_add_ps(row4, row6);

//         // Store the final result
//         _mm256_storeu_ps(&result[j], _mm256_add_ps(row0, row4));
//     }
// }

int main() {
    // Example matrices filled with values 1.0 to 128.0
     __m256 row0, row1, row2, row3, row4, row5, row6, row7;
    float matrix1[8][16];
    float matrix2[8][16];

    // Fill matrix1 with values 1.0 to 128.0
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 16; ++j) {
            matrix1[i][j] = static_cast<float>(i * 16 + j + 1);
        }
    }

    // Fill matrix2 with values 129.0 to 256.0
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 16; ++j) {
            matrix2[i][j] = static_cast<float>(i * 16 + j + 129);
        }
    }
        row0 = _mm256_loadu_ps(&matrix1[0][0]);
        row1 = _mm256_loadu_ps(&matrix1[1][0]);
        row2 = _mm256_loadu_ps(&matrix1[2][0]);
        row3 = _mm256_loadu_ps(&matrix1[3][0]);
        row4 = _mm256_loadu_ps(&matrix1[4][0]);
        row5 = _mm256_loadu_ps(&matrix1[5][0]);
        row6 = _mm256_loadu_ps(&matrix1[6][0]);
        row7 = _mm256_loadu_ps(&matrix1[7][0]);
    // Result matrix
    float result[8];
      _mm256_storeu_ps(&result[0], row0);
       _mm256_storeu_ps(&result[1], row0);
        _mm256_storeu_ps(&result[2], row0);
         _mm256_storeu_ps(&result[3], row0);
          _mm256_storeu_ps(&result[4], row0);
           _mm256_storeu_ps(&result[5], row0);
            _mm256_storeu_ps(&result[6], row0);
             _mm256_storeu_ps(&result[7], row0);
    // Call the multiplication function
    // multiplyAndAccumulateRows(matrix1, matrix2, result);

    // Print the result


    std::cout << "Result matrix:" << std::endl;
    for (int i = 0; i < 8; ++i) {
        std::cout << result[i] << "\t";
    }
    std::cout << std::endl;

    return 0;
}
