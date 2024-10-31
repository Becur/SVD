
#include "test_SVD.h"
#include "assert.h"
#include "matrix.h"
#include "svd.h"

#include <chrono>
#include <random>
#include <iostream>

int main/*TestSVD*/(){
    const float ERROR_RATE = 5e-2;

    TestSVD(ERROR_RATE);
}

void TestSVD(const float error_rate){
{
    Matrix<float> m({{-26, -33, -25}, {31, 42, 23}, {-11, -15, -4}});
    SVD res = CalculateSVD<float>(m, 3, 1e-6);
    Matrix<float> check_m = res.left_singular_vectors * res.eigenvalues * Transp(res.right_singular_vectors);
    for(int i = 0; i < m.SizeColumn(); ++i){
        for(int j = 0; j < m.SizeRow(); ++j){
            ASSERT(std::abs(m[i][j] - check_m[i][j]) < error_rate);
        }
    }
}
{
    Matrix<float> m({
        {57.69, 69.80, 59.83, 23.46, 42.81},
        {49.72, 15.01, 46.06, 18.61, 68.30},
        {81.41, 83.09, 22.49, 61.73, 19.47},
        {96.27, 53.69, 18.59, 77.11, 30.69},
        {49.84, 73.97, 15.68, 69.09, 43.63}});
    SVD res = CalculateSVD<float>(m, 5, 1e-6);
    Matrix<float> check_m = res.left_singular_vectors * res.eigenvalues * Transp(res.right_singular_vectors);
    std::cout << check_m;
    for(int i = 0; i < m.SizeColumn(); ++i){
        for(int j = 0; j < m.SizeRow(); ++j){
            ASSERT(std::abs(m[i][j] - check_m[i][j]) < error_rate);
        }
    }
}
}