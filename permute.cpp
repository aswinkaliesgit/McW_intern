#include <immintrin.h>
#include <iostream>
#include <chrono>
using namespace std;
int main() {
    float matrix1[8][8] = {
        {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0},
        {9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0},
        {17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0},
        {25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0},
        {33.0, 34.0, 35.0, 36.0, 37.0, 38.0, 39.0, 40.0},
        {41.0, 42.0, 43.0, 44.0, 45.0, 46.0, 47.0, 48.0},
        {49.0, 50.0, 51.0, 52.0, 53.0, 54.0, 55.0, 56.0},
        {57.0, 58.0, 59.0, 60.0, 61.0, 62.0, 63.0, 64.0}
    };
__m256 reg1,reg2,reg3,reg4,reg5,reg6,reg7,reg8,reg9,reg10,reg11;
   reg1 = _mm256_loadu_ps (&matrix1[0][0]);
   reg2= _mm256_loadu_ps(&matrix1[1][0]);
   reg3= _mm256_loadu_ps(&matrix1[2][0]);
    reg4= _mm256_loadu_ps(&matrix1[3][0]);
  reg5= _mm256_unpacklo_ps (reg1, reg2);
  reg6=_mm256_unpacklo_ps (reg3, reg4);
float ans[8];
   _mm256_storeu_ps(ans,reg5);

for(int i=0;i<8;i++)
{
  cout<<ans[i]<<"\t";
}
cout<<endl;
 _mm256_storeu_ps(ans,reg6);
    
    for(int i=0;i<8;i++)
{
  cout<<ans[i]<<"\t";
}
cout<<endl;
  reg7=_mm256_unpacklo_ps (reg5, reg6);
     _mm256_storeu_ps(ans,reg7);
         for(int i=0;i<8;i++)
{
  cout<<ans[i]<<"\t";
}
    cout<<endl;
reg8= _mm256_permute_ps (reg7,0b11011000);
      _mm256_storeu_ps(ans,reg8);
         for(int i=0;i<8;i++)
{
  cout<<ans[i]<<"\t";
}
    
}
