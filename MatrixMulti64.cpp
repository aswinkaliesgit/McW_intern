#include <iostream>
#include <chrono>

const int N = 64; // Size of the matrices (N x N)

void multiplyMatrix(float A[N][N], float  B[N][N], float  result[N][N]) {
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
  

}

int main() {
     using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    float A[N][N];
    float  B[N][N] ;
    int value = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = ++value;
            B[i][j] = value;
        }
    }


    




    float  result[N][N];
auto t1 = high_resolution_clock::now();
    multiplyMatrix(A, B, result);
  auto t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double = t2 - t1;
    std::cout << ms_double.count() << "ms\n";

    std::cout << "Result Matrix:\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << result[i][j] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
