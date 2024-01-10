#include <immintrin.h>
#include <xmmintrin.h>
#include <iostream>
#include<chrono>
using namespace std;
int main() {
   using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
  __m128 row0,row1,row2,row3;
  __m256 vec_one,vec_two,vec_three;
    float matrix1[8][8] = {
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8}
    };
     float matrix2[8][8] = {
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8}
    };


    float transpose[8][8];
   auto t1 = high_resolution_clock::now();
    for(int i=0;i<8;i+=4){
      for(int j=0;j<8;j+=4){
    row0 = _mm_load_ps(&matrix1[i][j]);
    row1 = _mm_load_ps(&matrix1[i+1][j]);
    row2 = _mm_load_ps(&matrix1[i+2][j]);
    row3 = _mm_load_ps(&matrix1[i+3][j]);

    _MM_TRANSPOSE4_PS(row0, row1, row2, row3);
    _mm_storeu_ps(&transpose[j][i],row0);
   _mm_storeu_ps(&transpose[j+1][i],row1);
    _mm_storeu_ps(&transpose[j+2][i],row2);
     _mm_storeu_ps(&transpose[j+3][i],row3);
    }}

for(int i=0;i<8;i++)
{
   
            vec_one = _mm256_loadu_ps(&matrix2[i][0]);
            
  for(int j=0;j<8;j++){
vec_two = _mm256_loadu_ps(&transpose[j][0]);
vec_three= _mm256_mul_ps(vec_one,vec_two);

            __m128 sum128 = _mm256_extractf128_ps(vec_three, 0);
            sum128 = _mm_add_ps(sum128, _mm256_extractf128_ps(vec_three, 1));
            sum128 = _mm_hadd_ps(sum128, sum128);
            sum128 = _mm_hadd_ps(sum128, sum128);
            
            float ans;
            _mm_store_ss(&ans, sum128);
           matrix1[i][j]=ans;

  }
  cout<<endl;
}
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double = t2 - t1;
    std::cout << ms_double.count() << "ms\n";

     for(int i=0;i<8;i++)
     {
      for(int j=0;j<8;j++)
      {
        std::cout<<matrix1[i][j]<<" ";
      }
      std::cout<<endl;
     }

    return 0;
}
