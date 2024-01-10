#include <immintrin.h>
#include <xmmintrin.h>
#include <iostream>
#include <chrono>
#include <vector>

using namespace std;
struct AVXVector {
    __m256 vector;

    AVXVector() {}
  
    AVXVector(__m256 existingVector) : vector(existingVector) {}
    __m256 toM256() const {
        return vector;
    }
};

int main()
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    float matrix1[64][64] ;
    float matrix2[64][64];
    float ans[64][64]={0};
 
int value=0;
    for(int i=0;i<64;i++)
    {
        for(int j=0;j<64;j++)
        {
            matrix1[i][j]=++value;
            matrix2[i][j]=value;
        }
    }
__m256 row0, row1, row2, row3, row4, row5, row6, row7, row8, row9, row10, row11, row12, row13,row14,row15,row16,row17,row18,row19,row20,row21,row22,row23,row24,row25,row26,row27,row28,row29,row30,row31,row32,row33,row34,row35,row36,row37,row38;
auto t1 = high_resolution_clock::now();
for(int i=0;i<64;i+=8)
{
    for(int k=0;k<64;k+=8){
    for(int j=0;j<64;j+=8)
    {
       
           
           row23=_mm256_loadu_ps(&matrix1[i][j]);
           row24=_mm256_loadu_ps(&matrix1[i+1][j]);
           row25=_mm256_loadu_ps(&matrix1[i+2][j]);
           row26=_mm256_loadu_ps(&matrix1[i+3][j]);
           row27=_mm256_loadu_ps(&matrix1[i+4][j]);
           row28=_mm256_loadu_ps(&matrix1[i+5][j]);
           row29=_mm256_loadu_ps(&matrix1[i+6][j]);
           row30=_mm256_loadu_ps(&matrix1[i+7][j]);// Loading eight rows of matrix 1 of size 8*8 tile  from  64*64
             
 row14 = _mm256_loadu_ps(&matrix2[j][k]);
    row15= _mm256_loadu_ps(&matrix2[j+1][k]);
    row16 = _mm256_loadu_ps(&matrix2[j+2][k]);
    row17 = _mm256_loadu_ps(&matrix2[j+3][k]);   //loading first 4 rows of matrix 2 to take transpose of the 8*8 tile
    
    row5 = _mm256_unpacklo_ps(row14, row15);
    row6 = _mm256_unpacklo_ps(row16, row17);

    row0 = _mm256_unpacklo_ps(row5, row6);
    row1 = _mm256_unpackhi_ps(row5, row6);
    
    __m256i permuteOrder = _mm256_set_epi32(7, 5, 6, 4, 3, 1, 2, 0);

    row0 = _mm256_permutevar8x32_ps(row0, permuteOrder);
    row1 = _mm256_permutevar8x32_ps(row1, permuteOrder);

    permuteOrder = _mm256_set_epi32(3, 1, 2, 0, 7, 6, 5, 4);
    row2 = _mm256_permutevar8x32_ps(row0, permuteOrder);
    row3 = _mm256_permutevar8x32_ps(row1, permuteOrder);

    row18 = _mm256_loadu_ps(&matrix2[j+4][k]);
    row19 = _mm256_loadu_ps(&matrix2[j+5][k]);
    row20 = _mm256_loadu_ps(&matrix2[j+6][k]);
    row21 = _mm256_loadu_ps(&matrix2[j+7][k]); //loading next  4 rows of matrix 2 to take transpose of the 8*8 tile

    row4 = _mm256_unpacklo_ps(row18, row19);
    row5 = _mm256_unpacklo_ps(row20, row21);

    row6 = _mm256_unpacklo_ps(row4, row5);
    row7 = _mm256_unpackhi_ps(row4, row5);

    permuteOrder = _mm256_set_epi32(7, 5, 6, 4, 3, 1, 2, 0);

    row4 = _mm256_permutevar8x32_ps(row6, permuteOrder);
    row5 = _mm256_permutevar8x32_ps(row7, permuteOrder);

    row0 = _mm256_permute2f128_ps(row0, row4, 0x20);//row 0  of transpose matrix
    row1 = _mm256_permute2f128_ps(row1, row5, 0x20);//row 1 of transpose matrix
    row2 = _mm256_permute2f128_ps(row2, row4, 0x30);//row 4 of transpose matrix
    row3 = _mm256_permute2f128_ps(row3, row5, 0x30);//row 5 of transpose matrix

   

    row4 = _mm256_unpackhi_ps(row14, row15);
    row5 = _mm256_unpackhi_ps(row16, row17);

    row6 = _mm256_unpacklo_ps(row4, row5);
    row7 = _mm256_unpackhi_ps(row4, row5);

    permuteOrder = _mm256_set_epi32(7, 5, 6, 4, 3, 1, 2, 0);

    row4 = _mm256_permutevar8x32_ps(row6, permuteOrder);
    row5 = _mm256_permutevar8x32_ps(row7, permuteOrder);

    permuteOrder = _mm256_set_epi32(3, 1, 2, 0, 7, 6, 5, 4);
    row6 = _mm256_permutevar8x32_ps(row4, permuteOrder);
    row7 = _mm256_permutevar8x32_ps(row5, permuteOrder);


    row12 = _mm256_unpackhi_ps(row18, row19);
    row13 = _mm256_unpackhi_ps(row20, row21);

    row8 = _mm256_unpacklo_ps(row12, row13);
    row9 = _mm256_unpackhi_ps(row12, row13);

    permuteOrder = _mm256_set_epi32(7, 5, 6, 4, 3, 1, 2, 0);

    row12 = _mm256_permutevar8x32_ps(row8, permuteOrder);
    row13 = _mm256_permutevar8x32_ps(row9, permuteOrder);

    row4 = _mm256_permute2f128_ps(row4, row12, 0x20);//row 2 of transpose matrix
    row5 = _mm256_permute2f128_ps(row5, row13, 0x20);//row 3 of transpose matrix
    row6 = _mm256_permute2f128_ps(row6, row12, 0x30);//row 6 of transpose matrix
    row7 = _mm256_permute2f128_ps(row7, row13, 0x30);//row 7 of transpose matrix

 std::vector<AVXVector> mat2;
     mat2.push_back(AVXVector(row0));
     mat2.push_back(AVXVector(row1));
     mat2.push_back(AVXVector(row4));
     mat2.push_back(AVXVector(row5));
    mat2.push_back(AVXVector(row2));
    mat2.push_back(AVXVector(row3));
    mat2.push_back(AVXVector(row6));
    mat2.push_back(AVXVector(row7));
 std::vector<AVXVector> mat1;
     mat1.push_back(AVXVector(row23));
     mat1.push_back(AVXVector(row24));
     mat1.push_back(AVXVector(row25));
     mat1.push_back(AVXVector(row26));
    mat1.push_back(AVXVector(row27));
    mat1.push_back(AVXVector(row28));
    mat1.push_back(AVXVector(row29));
    mat1.push_back(AVXVector(row30));
    cout<<endl;

    cout<<endl;
 float an;

for (int l = 0; l < 8; l++) {
    for (int t = 0; t < 8; t++) {
        row31 = _mm256_mul_ps(mat1[l].toM256(), mat2[t].toM256());

        __m128 sum128 = _mm256_extractf128_ps(row31, 0);
        sum128 = _mm_add_ps(sum128, _mm256_extractf128_ps(row31, 1));
        sum128 = _mm_hadd_ps(sum128, sum128);
        sum128 = _mm_hadd_ps(sum128, sum128);

        ans[l+i][t+k] = _mm_cvtss_f32(sum128) + ans[l+i][t+k ];

    }
           
}



        }
    }
}
     auto t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double = t2 - t1;
    std::cout << ms_double.count() << "ms\n";

// for(int s=0;s<64;s++)
//        {
//         for(int n=0;n<64;n++)
//         {
//             cout<<ans[s][n]<<"\t";
//         }
//         cout<<endl;
       
//        }


}