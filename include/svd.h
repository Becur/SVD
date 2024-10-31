#pragma once

#include "matrix.h"

#include <utility>
#include <cmath>

template<typename T>
struct SVD{
    Matrix<T> left_singular_vectors;
    Matrix<T> eigenvalues;
    Matrix<T> right_singular_vectors;
};

template <typename T>
T ScalarMultiplication(const Matrix<T>& lhs, const Matrix<T>& rhs){
    if((lhs.SizeRow() != 1) || (rhs.SizeRow() != 1) || (rhs.SizeColumn() != lhs.SizeColumn())){
            throw std::invalid_argument("The dimensions of the matrices are incorrect for scalar multiplication");
        }
    T res = 0;
    for(size_t i = 0; i < lhs.SizeColumn(); ++i){
        res += lhs[i].front() * rhs[i].front();
    }
    return res;
}

template <typename T>
std::pair<T, Matrix<T>> CalculateMaxEigenval(const Matrix<T>& mat, const T error_rate){
    Matrix<T> y(mat.SizeRow(), 1, 1);
    Matrix<T> u = Normalize(y);
    T l;
    size_t i = 0;
    do {
        y = mat * u;
        l = ScalarMultiplication(y, u) / ScalarMultiplication(u, u);
        u = Normalize(y);
    } while((Norma(mat * u - u * l) > error_rate) &&  (i++ < 1000));
    return {l, std::move(u)};
}

template <typename T>
SVD<T> CalculateSVD(const Matrix<T>& mat, const size_t num_vec, const T error_rate){
    Matrix<T> m = Transp(mat) * mat;
    SVD<T> res;
    res.eigenvalues = Matrix<T>(num_vec, num_vec, 0);
    for(size_t i = 0; i < num_vec; ++i){
        auto [new_eigenval, new_eigenvec] = CalculateMaxEigenval(m, error_rate);
        m = m - new_eigenvec * Transp(new_eigenvec) * new_eigenval;
        res.eigenvalues[i][i] = std::sqrt(new_eigenval);
        res.left_singular_vectors.PushBackColumn(mat * new_eigenvec / res.eigenvalues[i][i]);
        res.right_singular_vectors.PushBackColumn(std::move(new_eigenvec));
    }
    return res;
}