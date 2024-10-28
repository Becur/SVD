#pragma once

#include <vector>
#include <utility>
#include <ostream>
#include <stdexcept>
#include <cmath>
#include <string>
#include <sstream>
#include <iterator>
#include <numeric>
#include <algorithm>

template <typename T>
class Matrix final{
public:
    explicit Matrix(const size_t num_row = 0);
    explicit Matrix(const size_t num_row, const size_t size_row, const T& val);

    Matrix(const std::vector<std::vector<T>>& data);
    Matrix(std::vector<std::vector<T>>&& data);


    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;

    size_t SizeRow() const noexcept;
    size_t SizeColumn() const noexcept;
    size_t Size() const noexcept;
    size_t ActualSize() const;

    const std::vector<T>& operator[](size_t index) const noexcept;
    std::vector<T>& operator[](size_t index) noexcept;

    void Swap(Matrix& other) noexcept;

    Matrix& operator=(const Matrix& rhs);
    Matrix& operator=(Matrix&& rhs) noexcept;

    std::vector<T>& FrontRow();
    const std::vector<T>& FrontRow() const;

    std::vector<T>& BackRow();
    const std::vector<T>& BackRow() const;

    void PushBackRow(const std::vector<T>& row);
    void PushBackRow(std::vector<T>&& row);
    void PushBackRow(const Matrix<T>& mat);
    void PushBackRow(Matrix<T>&& mat);

    void PushBackColumn(const Matrix& mat);
    void PushBackColumn(Matrix&& mat);

    void PopBackRow() noexcept;

    void PopBackColumn() noexcept;

    Matrix operator*=(const T& other);
    Matrix operator*=(const Matrix& other);

    Matrix operator+=(const T& other);
    Matrix operator+=(const Matrix& other);

    Matrix operator-=(const Matrix& other);
    Matrix operator-=(const T& other);

    Matrix operator/=(const T& other);

    bool operator==(const Matrix& rhs) const;
    bool operator!=(const Matrix& rhs) const;

    bool Empty() const;
    bool Correct() const;

private:
    std::vector<std::vector<T>> data_;
};

template<typename T>
Matrix<T> Transp(const Matrix<T>& m);
template<typename T>
Matrix<T> Transp(Matrix<T>&& m);


template <typename T>
std::ostream& operator<<(std::ostream& output, const Matrix<T>& val);

template <typename T>
Matrix<T> operator-(Matrix<T> m);
template<typename T>
Matrix<T> operator-(Matrix<T> lhs, const Matrix<T>& rhs);
template <typename T>
Matrix<T> operator-(Matrix<T> lhs, const T& rhs);

template <typename T>
Matrix<T> operator+(Matrix<T> m);
template<typename T>
Matrix<T> operator+(Matrix<T> lhs, const Matrix<T>& rhs);
template <typename T>
Matrix<T> operator+(const T& lhs, Matrix<T> rhs);
template <typename T>
Matrix<T> operator+(Matrix<T> lhs, const T& rhs);

template<typename T>
Matrix<T> operator*(Matrix<T> lhs, const Matrix<T>& rhs);
template <typename T>
Matrix<T> operator*(const T& lhs, Matrix<T> rhs);
template <typename T>
Matrix<T> operator*(Matrix<T> lhs, const T& rhs);

template <typename T>
Matrix<T> operator/(Matrix<T> lhs, const T& rhs);

template <typename T>
std::vector<T> ParceRowNumbers(std::istream& input);

template <typename T>
Matrix<T> ParceCSRFormat(std::istream& input);

template<typename T>
T Norma(const Matrix<T>& m, size_t num_column = 0);

template<typename T>
Matrix<T> Normalize(const Matrix<T>& m);


/*---------------------------------------------------------------------------------*/


template<typename T>
Matrix<T>::Matrix(const size_t num_row)
    : Matrix<T>(std::vector<std::vector<T>>(num_row)){}

template<typename T>
Matrix<T>::Matrix(const size_t num_row, const size_t size_row, const T& val)
    : Matrix<T>(std::vector<std::vector<T>>(num_row, std::vector<T>(size_row, val))){}

template<typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>>& data)
    : data_(data){}

template<typename T>
Matrix<T>::Matrix(std::vector<std::vector<T>>&& data)
    : data_(std::move(data)){}


template<typename T>
Matrix<T>::Matrix(const Matrix<T>& other)
    : data_(other.data_){}

template<typename T>
Matrix<T>::Matrix(Matrix&& other) noexcept
    : data_(std::move(other.data_)){}

template<typename T>
size_t Matrix<T>::SizeRow() const noexcept {
    return ((data_.size() == 0) ? 0 : data_.front().size());
}

template<typename T>
size_t Matrix<T>::SizeColumn() const noexcept {
    return data_.size();
}

template<typename T>
size_t Matrix<T>::Size() const noexcept {
    return SizeColumn() * SizeRow();
}

template<typename T>
size_t Matrix<T>::ActualSize() const{
    return std::accumulate(data_.begin(), data_.end(), 0, 
    [](size_t sum, const std::vector<T>& row){return sum += row.size();});
}

template<typename T>
const std::vector<T>& Matrix<T>::operator[](size_t index) const noexcept{
    return data_[index];
}

template<typename T>
std::vector<T>& Matrix<T>::operator[](size_t index) noexcept{
    return data_[index];
}

template<typename T>
void Matrix<T>::Swap(Matrix<T>& other) noexcept{
    if(this != &other){
        std::swap(data_, other.data_);
    }
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs){
    if(this != &rhs){
        Matrix rhs_copy(rhs);
        Swap(rhs_copy);
    }
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& rhs) noexcept{
    data_ = std::move(rhs.data_);
    return *this;
}

template<typename T>
std::vector<T>& Matrix<T>::FrontRow(){
    return data_.front();
}

template<typename T>
const std::vector<T>& Matrix<T>::FrontRow() const{
    return data_.front();
}

template<typename T>
std::vector<T>& Matrix<T>::BackRow(){
    return data_.back();
}

template<typename T>
const std::vector<T>& Matrix<T>::BackRow() const{
    return data_.back();
}

template<typename T>
void Matrix<T>::PushBackRow(const std::vector<T>& row){
    if(!row.empty()){
        data_.push_back(row);
    }
}

template<typename T>
void Matrix<T>::PushBackRow(std::vector<T>&& row){
    if(!row.empty()){
        data_.push_back(std::move(row));
    }
}

template<typename T>
void Matrix<T>::PushBackRow(const Matrix<T>& mat){
    for(const std::vector<T>& row : mat.data_){
        if(!row.empty()){
            data_.push_back(row);
        }
    }
}

template<typename T>
void Matrix<T>::PushBackRow(Matrix<T>&& mat){
    for(std::vector<T>&& row : mat.data_){
        if(!row.empty()){
            data_.push_back(std::move(row));
        }
    }
}

template<typename T>
void Matrix<T>::PushBackColumn(const Matrix& mat){
    data_.resize(std::max(SizeColumn(), mat.SizeColumn()));
    for(size_t i = 0; i < SizeColumn(); ++i){
        data_[i].insert(data_[i].end(), mat[i].begin(), mat[i].end());
    }
}

template<typename T>
void Matrix<T>::PushBackColumn(Matrix&& mat){
    data_.resize(std::max(SizeColumn(), mat.SizeColumn()));
    for(size_t i = 0; i < SizeColumn(); ++i){
        data_[i].insert(data_[i].end(),
            std::make_move_iterator(mat[i].begin()), 
            std::make_move_iterator(mat[i].end()));
    }
}

template<typename T>
void Matrix<T>::PopBackRow() noexcept{
    if(SizeColumn()){
        data_.pop_back();
    }
}

template<typename T>
void Matrix<T>::PopBackColumn() noexcept{
    for(size_t i = 0; i < SizeColumn(); ++i){
        if(!data_[i].empty()){
            data_[i].pop_back();
        }
    }
}

template<typename T>
Matrix<T> Matrix<T>::operator*=(const Matrix<T>& other){
    if((SizeRow() != other.SizeColumn())
     || (other.SizeRow() == 0) || (SizeRow() == 0)){
        throw std::invalid_argument("The matrices are incorrect for multiplication");
    }
    Matrix res(SizeColumn(), other.SizeRow(), T());
    for(size_t i = 0; i < SizeColumn(); ++i){
        for(size_t j = 0; j < other.SizeRow(); ++j){
            T new_val = 0;
            for(size_t k = 0; k < SizeRow(); ++k){
                new_val += data_[i][k] * other[k][j];
            }
            res[i][j] = new_val;
        }
    }
    Swap(res);
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator*=(const T& other){
    if(Empty()){
        throw std::invalid_argument("The matrix is empty for multiplication");
    }
    for(size_t i = 0; i < SizeColumn(); ++i){
        for(size_t j = 0; j < data_[i].size(); ++j){
            data_[i][j] *= other;
        }
    }
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator+=(const T& other){
    if(Empty()){
        throw std::invalid_argument("The matrix is empty for addition");
    }
    for(size_t i = 0; i < SizeColumn(); ++i){
        for(size_t j = 0; j < data_[i].size(); ++j){
            data_[i][j] += other;
        }
    }
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator+=(const Matrix& other){
    if((SizeRow() != other.SizeRow()) 
    || (SizeColumn() != other.SizeColumn()) 
    || (other.SizeRow() == 0)|| (SizeRow() == 0)){
        throw std::invalid_argument("The matrices are incorrect for addition");
    }
    for(size_t i = 0; i < SizeColumn(); ++i){
        size_t size_row = std::min(data_[i].size(), other[i].size());
        for(size_t j = 0; j < size_row; ++j){
            data_[i][j] += other[i][j];
        }
    }
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator-=(const Matrix& other){
    return *this += -other;
}

template<typename T>
Matrix<T> Matrix<T>::operator-=(const T& other){
    return *this += -other;
}

template<typename T>
Matrix<T> Matrix<T>::operator/=(const T& other){
    return *this *= 1.0 / other;
}

template<typename T>
bool Matrix<T>::operator==(const Matrix& rhs) const{
    return (this == &rhs) || (data_ == rhs.data_);
}

template<typename T>
bool Matrix<T>::operator!=(const Matrix& rhs) const{
    return !(*this == rhs);
}

template<typename T>
bool Matrix<T>::Empty() const{
    return (std::find_if(data_.begin(), data_.end(), 
    [](const std::vector<T>& row){return row.size();}) 
    == data_.end());
}

template<typename T>
bool Matrix<T>::Correct() const{
    for(const std::vector<T>& row : data_){
        if(row.size() != SizeRow()){
            return false;
        }
    }
    return SizeRow();
}

template<typename T>
Matrix<T> Transp(const Matrix<T>& m){
    Matrix<T> res;
    for(size_t i = 0; i < m.SizeRow(); ++i){
        std::vector<T> new_row;
        for(size_t j = 0; j < m.SizeColumn(); ++j){
            new_row.push_back(m[j][i]);
        }
        res.PushBackRow(std::move(new_row));
    }
    return res;
}

template<typename T>
Matrix<T> Transp(Matrix<T>&& m){
    Matrix<T> res;
    for(size_t i = 0; i < m.SizeRow(); ++i){
        std::vector<T> new_row;
        new_row.reserve(m.SizeColumn());
        for(size_t j = 0; j < m.SizeColumn(); ++j){
            new_row.push_back(std::move(m[j][i]));
        }
        res.PushBackRow(std::move(new_row));
    }
    return res;
}

template <typename T>
std::ostream& operator<<(std::ostream& output, const Matrix<T>& val) {
    for(size_t i = 0; i < val.SizeColumn(); ++i){
        for(size_t j = 0; j < val.SizeRow(); ++j){
            output << ((j == 0) ? "" : "    ");
            output << val[i][j];
        }
        output << ((i == val.SizeColumn() - 1) ? "" : "\n");
    }
    return output;
}

template <typename T>
Matrix<T> operator-(Matrix<T> m){
    return m *= -1;
}
template <typename T>
Matrix<T> operator-(Matrix<T> lhs, const T& rhs){
    return lhs -= rhs;
}
template<typename T>
Matrix<T> operator-(Matrix<T> lhs, const Matrix<T>& rhs) {
    return lhs -= rhs;
}

template <typename T>
Matrix<T> operator+(Matrix<T> m){
    return m;
}
template <typename T>
Matrix<T> operator+(const T& lhs, Matrix<T> rhs){
    return rhs += lhs;
}
template <typename T>
Matrix<T> operator+(Matrix<T> lhs, const T& rhs){
    return lhs += rhs;
}
template<typename T>
Matrix<T> operator+(Matrix<T> lhs, const Matrix<T>& rhs) {
    return lhs += rhs;
}

template <typename T>
Matrix<T> operator*(const T& lhs, Matrix<T> rhs){
    return rhs *= lhs;
}
template <typename T>
Matrix<T> operator*(Matrix<T> lhs, const T& rhs){
    return lhs *= rhs;
}
template<typename T>
Matrix<T> operator*(Matrix<T> lhs, const Matrix<T>& rhs) {
    return lhs *= rhs;
}

template <typename T>
Matrix<T> operator/(Matrix<T> lhs, const T& rhs){
    return lhs /= rhs;
}


template <typename T>
std::vector<T> ParceRowNumbers(std::istream& input){
    std::vector<T> res;
    std::string line;
    std::getline(input, line);
    std::stringstream numbers;
    numbers << std::move(line);
    for(T num; !numbers.eof(); ){
        numbers >> num;
        res.push_back(std::move(num));
    }
    return res;
}

template <typename T>
Matrix<T> ParceCSRFormat(std::istream& input){
    size_t size_row, size_column;
    input >> size_row >> size_column;
    input.get();
    std::vector<size_t> indices = ParceRowNumbers<size_t>(input);
    std::vector<size_t> indptr = ParceRowNumbers<size_t>(input);
    std::vector<T> data = ParceRowNumbers<T>(input);
    Matrix<T> res(size_column, size_row, T());
    for(size_t i = 1; i < size_column + 1; ++i){
        for(size_t j = indptr[i - 1]; j < indptr[i]; ++j){
            res[i - 1][indices[j]] = data[j];
        }
    }
    return res;
}

template<typename T>
T Norma(const Matrix<T>& m, size_t num_column){
    T res = 0;
    for(size_t j = 0; j < m.SizeColumn(); ++j){
        res += std::pow(m[j][num_column], 2);
    }
    res = std::sqrt(res);
    return res;
}

template<typename T>
Matrix<T> Normalize(const Matrix<T>& m){
    Matrix res(m.SizeColumn(), m.SizeRow(), T());
    for(size_t i = 0; i < m.SizeRow(); ++i){
        T coef = Norma(m, i);
        for(size_t j = 0; j < m.SizeColumn(); ++j){
            res[j][i] = m[j][i] / coef;
        }
    }
    return res;
}