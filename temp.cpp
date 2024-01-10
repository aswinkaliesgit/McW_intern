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
    float matrix1[16][16] ;
    float matrix2[16][16];
    float ans[16][16]={0};
    float ans2[16][16]={0};
int value=0;
    for(int i=0;i<16;i++)
    {
        for(int j=0;j<16;j++)
        {
            matrix1[i][j]=++value;
            matrix2[i][j]=value;
        }
    }
__m256 row0, row1, row2, row3, row4, row5, row6, row7, row8, row9, row10, row11, row12, row13,row14,row15,row16,row17,row18,row19,row20,row21,row22,row23,row24,row25,row26,row27,row28,row29,row30,row31,row32,row33,row34,row35,row36,row37,row38;
for(int i=0;i<16;i+=8)
{
    for(int k=0;k<16;k+=8){
    for(int j=0;j<16;j+=8)
    {
       
           
           row23=_mm256_loadu_ps(&matrix1[i][j]);
           row24=_mm256_loadu_ps(&matrix1[i+1][j]);
           row25=_mm256_loadu_ps(&matrix1[i+2][j]);
           row26=_mm256_loadu_ps(&matrix1[i+3][j]);
           row27=_mm256_loadu_ps(&matrix1[i+4][j]);
           row28=_mm256_loadu_ps(&matrix1[i+5][j]);
           row29=_mm256_loadu_ps(&matrix1[i+6][j]);
           row30=_mm256_loadu_ps(&matrix1[i+7][j]);

 row14 = _mm256_loadu_ps(&matrix2[j][k]);
    row15= _mm256_loadu_ps(&matrix2[j+1][k]);
    row16 = _mm256_loadu_ps(&matrix2[j+2][k]);
    row17 = _mm256_loadu_ps(&matrix2[j+3][k]);
    
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
    row21 = _mm256_loadu_ps(&matrix2[j+7][k]);

    row4 = _mm256_unpacklo_ps(row18, row19);
    row5 = _mm256_unpacklo_ps(row20, row21);

    row6 = _mm256_unpacklo_ps(row4, row5);
    row7 = _mm256_unpackhi_ps(row4, row5);

    permuteOrder = _mm256_set_epi32(7, 5, 6, 4, 3, 1, 2, 0);

    row4 = _mm256_permutevar8x32_ps(row6, permuteOrder);
    row5 = _mm256_permutevar8x32_ps(row7, permuteOrder);

    row0 = _mm256_permute2f128_ps(row0, row4, 0x20);//row 0
    row1 = _mm256_permute2f128_ps(row1, row5, 0x20);//1
    row2 = _mm256_permute2f128_ps(row2, row4, 0x30);//4
    row3 = _mm256_permute2f128_ps(row3, row5, 0x30);//5

   

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

    row4 = _mm256_permute2f128_ps(row4, row12, 0x20);//row 2
    row5 = _mm256_permute2f128_ps(row5, row13, 0x20);//3
    row6 = _mm256_permute2f128_ps(row6, row12, 0x30);//6
    row7 = _mm256_permute2f128_ps(row7, row13, 0x30);//7

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
//    for (const auto& avxVec : mat1) {
//         // float elements[8];
//         // _mm256_storeu_ps(elements, avxVec.vector);
//         // for (int i = 0; i < 8; ++i) {
//         //     std::cout << elements[i] << "\t";
//         // }
//         // std::cout << std::endl;

//         // Convert AVXVector back to __m256 and print
//         __m256 convertedVector = avxVec.toM256();
//         float convertedElements[8];
//         _mm256_storeu_ps(convertedElements, convertedVector);
//         // std::cout << "Converted back to __m256: ";
//         for (int i = 0; i < 8; ++i) {
//             std::cout << convertedElements[i] << "\t";
//         }
//         std::cout << std::endl;
//     }
//     cout<<endl;
//      for (const auto& avxVec : mat2) {
//         // float elements[8];
//         // _mm256_storeu_ps(elements, avxVec.vector);
//         // for (int i = 0; i < 8; ++i) {
//         //     std::cout << elements[i] << "\t";
//         // }
//         // std::cout << std::endl;

//         // Convert AVXVector back to __m256 and print
//         __m256 convertedVector = avxVec.toM256();
//         float convertedElements[8];
//         _mm256_storeu_ps(convertedElements, convertedVector);
//         // std::cout << "Converted back to __m256: ";
//         for (int i = 0; i < 8; ++i) {
//             std::cout << convertedElements[i] << "\t";
//         }
//         std::cout << std::endl;
//     }
//   float an;
//      for(int l=0;l<8;l++)
//      {
//         row31 = _mm256_mul_ps(mat2[l].toM256(), row23);
//         float elements[8];

//         // Convert AVXVector back to __m256 and print
//         // __m256 convertedVector = mat1[l].toM256();
//         // float convertedElements[8];
//         // _mm256_storeu_ps(convertedElements, row23);
//         // std::cout << "Converted back to __m256: ";
//         // for (int i = 0; i < 8; ++i) {
//         //     std::cout << convertedElements[i] << "\t";
//         // }
//         // std::cout << std::endl;
    
//     // float elements[8];
//     // _mm256_storeu_ps(elements, row31);
//     // for(int f=0;f<8;f++)
//     // cout<<elements[f]<<" ";
//         __m128 sum128 = _mm256_extractf128_ps(row31, 0);
//             sum128 = _mm_add_ps(sum128, _mm256_extractf128_ps(row31, 1));
//             sum128 = _mm_hadd_ps(sum128, sum128);
//             sum128 = _mm_hadd_ps(sum128, sum128);
//              _mm_store_ss(&an, sum128);
//              ans[i+l][k]=an+ans[i+l][k];
//             //  ans2[k+l][j]=an;
//         row32 = _mm256_mul_ps(mat2[l].toM256(), row24);
//         sum128 = _mm256_extractf128_ps(row32, 0);
//             sum128 = _mm_add_ps(sum128, _mm256_extractf128_ps(row32, 1));
//             sum128 = _mm_hadd_ps(sum128, sum128);
//             sum128 = _mm_hadd_ps(sum128, sum128);
//               _mm_store_ss(&an, sum128);
//              ans[i+l][k+1]=an+ans[i+l][k+1];
//             //   ans2[k+l][j+1]=an;
//         row33 = _mm256_mul_ps(mat2[l].toM256(), row25);
//       sum128 = _mm256_extractf128_ps(row33, 0);
//             sum128 = _mm_add_ps(sum128, _mm256_extractf128_ps(row33, 1));
//             sum128 = _mm_hadd_ps(sum128, sum128);
//             sum128 = _mm_hadd_ps(sum128, sum128);
//              _mm_store_ss(&an, sum128);
//              ans[i+l][k+2]=an+ans[i+l][k+2];
//             //   ans2[k+l][j+2]=an;
//         row34= _mm256_mul_ps(mat2[l].toM256(), row26);
//          sum128 = _mm256_extractf128_ps(row34, 0);
//             sum128 = _mm_add_ps(sum128, _mm256_extractf128_ps(row34, 1));
//             sum128 = _mm_hadd_ps(sum128, sum128);
//             sum128 = _mm_hadd_ps(sum128, sum128);
//              _mm_store_ss(&an, sum128);
//              ans[i+l][k+3]=an+ans[i+l][k+3];
//             //   ans2[k+l][j+3]=an;
//         row35 = _mm256_mul_ps(mat2[l].toM256(), row27);
//         sum128 = _mm256_extractf128_ps(row35, 0);
//             sum128 = _mm_add_ps(sum128, _mm256_extractf128_ps(row35, 1));
//             sum128 = _mm_hadd_ps(sum128, sum128);
//             sum128 = _mm_hadd_ps(sum128, sum128);
//              _mm_store_ss(&an, sum128);
//              ans[i+l][k+4]=an+ans[i+l][k+4];
//             //   ans2[k+l][j+4]=an;
//         row36 = _mm256_mul_ps(mat2[l].toM256(), row28);
//         sum128 = _mm256_extractf128_ps(row36, 0);
//             sum128 = _mm_add_ps(sum128, _mm256_extractf128_ps(row36, 1));
//             sum128 = _mm_hadd_ps(sum128, sum128);
//             sum128 = _mm_hadd_ps(sum128, sum128);
//              _mm_store_ss(&an, sum128);
//              ans[i+l][k+5]=an+ans[i+l][k+5];
//             //   ans2[k+l][j+5]=an;
//         row37 = _mm256_mul_ps(mat2[l].toM256(), row29);
//         sum128 = _mm256_extractf128_ps(row37, 0);
//             sum128 = _mm_add_ps(sum128, _mm256_extractf128_ps(row37, 1));
//             sum128 = _mm_hadd_ps(sum128, sum128);
//             sum128 = _mm_hadd_ps(sum128, sum128);
//             _mm_store_ss(&an, sum128);
//              ans[i+l][k+6]=an+ans[i+l][k+6];
//             //   ans2[k+l][j+6]=an;
//         row38 = _mm256_mul_ps(mat2[l].toM256(), row30);
//        sum128 = _mm256_extractf128_ps(row38, 0);
//             sum128 = _mm_add_ps(sum128, _mm256_extractf128_ps(row38, 1));
//             sum128 = _mm_hadd_ps(sum128, sum128);
//             sum128 = _mm_hadd_ps(sum128, sum128);
//              _mm_store_ss(&an, sum128);
//              ans[i+l][k+7]=an+ans[i+l][k+7];
//             //    ans2[k+l][j+7]=an;

//        for(int t=0;t<16;t++)
//        {
//         for(int n=0;n<16;n++)
//         {
//             cout<<ans[t][n]<<"\t";
//         }
//         cout<<endl;
       
//        }
//         cout<<"gap"<<endl;  
//      }
    cout<<endl;
 float an;
for (int l = 0; l < 8; l++) {
    for (int t = 0; t < 8; t++) {
        row31 = _mm256_mul_ps(mat1[l].toM256(), mat2[t].toM256());

        // Sum the elements horizontally within each 128-bit lane
        __m128 sum128 = _mm256_extractf128_ps(row31, 0);
        sum128 = _mm_add_ps(sum128, _mm256_extractf128_ps(row31, 1));
        sum128 = _mm_hadd_ps(sum128, sum128);
        sum128 = _mm_hadd_ps(sum128, sum128);

        // Store the result in the ans array
        ans[l + i][t + j] = _mm_cvtss_f32(sum128) + ans[l + i][t + j];
    }
           for(int s=0;s<16;s++)
       {
        for(int n=0;n<16;n++)
        {
            cout<<ans[s][n]<<"\t";
        }
        cout<<endl;
       
       }
        cout<<"gap"<<endl; 
}

// for(int ii=0;ii<8;ii++)
// {
//     for(int jj=0;jj<8;jj++)
//     cout<<ans[ii][jj]<<" ";
//     cout<<endl;
// }
    //  ans2[8][8]={0};



//         float rowValues[8][8];
    
//         _mm256_storeu_ps(&rowValues[0][0], row0);
//   _mm256_storeu_ps(&rowValues[1][0], row1);
//     _mm256_storeu_ps(&rowValues[2][0], row4); 
//       _mm256_storeu_ps(&rowValues[3][0], row5);
//         _mm256_storeu_ps(&rowValues[4][0], row2);

//           _mm256_storeu_ps(&rowValues[5][0], row3);
//             _mm256_storeu_ps(&rowValues[6][0], row6);
//               _mm256_storeu_ps(&rowValues[7][0], row7);

                 

//         cout<<"the gap"<<endl;     
// for(int p=0;p<8;p++)
// {
//     for(int q=0;q<8;q++){
//     cout<<rowValues[p][q]<<"\t";
//     }
//     cout<<endl;
// }

// cout<<"the gap"<<endl;

//         _mm256_storeu_ps(&rowValues[0][0], row23);
//   _mm256_storeu_ps(&rowValues[1][0], row24);
//     _mm256_storeu_ps(&rowValues[2][0], row25);
//       _mm256_storeu_ps(&rowValues[3][0], row26);
//         _mm256_storeu_ps(&rowValues[4][0], row27);
//           _mm256_storeu_ps(&rowValues[5][0], row28);
//             _mm256_storeu_ps(&rowValues[6][0], row29);
//               _mm256_storeu_ps(&rowValues[7][0], row30);
             
//          for(int p=0;p<8;p++)
// {
//     for(int q=0;q<8;q++){
//     cout<<rowValues[p][q]<<"\t";
//     }
//     cout<<endl;
// }


        }
    }
}


}