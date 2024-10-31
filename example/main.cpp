#include "matrix.h"
#include "svd.h"

#include <iostream>
#include <string>


int main(){
    Matrix<float> mat({{7, 2, -5}, {-9, 8, -5}, {24, -6, 8}});
    SVD<float> res = CalculateSVD<float>(mat, 3, 1e-6);
    std::cout << res.left_singular_vectors << '\n';
    std::cout << std::string(16, ' ') << '*' << '\n';
    std::cout << res.eigenvalues << '\n';
    std::cout << std::string(16, ' ') << '*' << '\n';
    std::cout << Transp(res.right_singular_vectors) << '\n';
    std::cout << std::string(16, ' ') << '=' << '\n';

    Matrix<float> check_mat = res.left_singular_vectors * res.eigenvalues * Transp(res.right_singular_vectors);
    std::cout << check_mat << '\n';
}