#include "test_matrix.h"
#include "assert.h"
#include "matrix.h"

#include <vector>
#include <sstream>
#include <string>
#include <random>
#include <chrono>

void TestMatrix(){
    TestPrint();

    TestEqual();
    TestCopyMove();
    TestGetSize();
    TestRandomAccess();
    TestSwap();
    // TestPushBack();
    // TestPopBack();
    // TestTransp();
    // TestAdding();
    // TestMultiplication();
    // TestGetNorma();
    // TestNormalize();

    // TestParceRowNumbers();

    // TestParceCSRFormat();
}

void TestEqual(){
{
    std::vector<std::vector<int>> mat({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m(mat);
    ASSERT(m == m);
}
{
    std::vector<std::vector<int>> mat({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m_lhs(mat), m_rhs(mat);
    ASSERT(m_lhs == m_rhs);
}
{
    std::vector<std::vector<int>> l_mat({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    std::vector<std::vector<int>> r_mat({{1, 2, 3}, {4, 5, 6}, {7, 8, 10}});
    Matrix<int> m_lhs(l_mat), m_rhs(r_mat);
    ASSERT(!(m_lhs == m_rhs));
}
{
    std::vector<std::vector<int>> l_mat({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    std::vector<std::vector<int>> r_mat({{1, 2, 3, 4, 5, 6, 7, 8, 9}});
    Matrix<int> m_lhs(l_mat), m_rhs(r_mat);
    ASSERT(!(m_lhs == m_rhs));
}
{
    std::vector<std::vector<int>> mat({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m_lhs(mat), m_rhs(mat);
    ASSERT(!(m_lhs != m_rhs));
}
{
    std::vector<std::vector<int>> l_mat({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    std::vector<std::vector<int>> r_mat({{1, 2, 3}, {4, 5, 6}, {7, 8, 10}});
    Matrix<int> m_lhs(l_mat), m_rhs(r_mat);
    ASSERT(m_lhs != m_rhs);
}
{
    std::vector<std::vector<int>> l_mat({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    std::vector<std::vector<int>> r_mat({{1, 2, 3, 4, 5, 6, 7, 8, 9}});
    Matrix<int> m_lhs(l_mat), m_rhs(r_mat);
    ASSERT(m_lhs != m_rhs);
}
}

void TestCopyMove(){
    {
        std::vector<std::vector<int>> mat({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        Matrix<int> m_copy(mat), m_move(std::move(mat));
        ASSERT_EQUAL(m_copy, m_move);
    }
    {
        std::vector<std::vector<int>> mat({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        Matrix<int> m(mat);
        Matrix<int> m_copy = m, m_move = std::move(m);
        ASSERT_EQUAL(m_copy, m_move);
    }
}

void TestGetSize(){
    {
        Matrix<int> a;
        ASSERT_EQUAL(a.SizeRow(), 0);
        ASSERT_EQUAL(a.SizeColumn(), 0);
        ASSERT_EQUAL(a.Size(), 0);
    }
    {
        Matrix<int> a(5);
        ASSERT_EQUAL(a.SizeRow(), 0);
        ASSERT_EQUAL(a.SizeColumn(), 5);
        ASSERT_EQUAL(a.Size(), 0);
    }
    {
        Matrix<int> a(0);
        ASSERT_EQUAL(a.SizeRow(), 0);
        ASSERT_EQUAL(a.SizeColumn(), 0);
        ASSERT_EQUAL(a.Size(), 0);
    }
    {
        Matrix<int> a(5, 0, 6);
        ASSERT_EQUAL(a.SizeRow(), 0);
        ASSERT_EQUAL(a.SizeColumn(), 5);
        ASSERT_EQUAL(a.Size(), 0);
    }
    {
        Matrix<int> a(0, 5, 6);
        ASSERT_EQUAL(a.SizeRow(), 0);
        ASSERT_EQUAL(a.SizeColumn(), 0); // because the Matrix class is row-oriented
        ASSERT_EQUAL(a.Size(), 0);
    }
    {
        Matrix<int> a(3, 4, 5);
        ASSERT_EQUAL(a.SizeRow(), 4);
        ASSERT_EQUAL(a.SizeColumn(), 3);
        ASSERT_EQUAL(a.Size(), 12);
    }
    {
        Matrix<int> a(9, 9, 0);
        ASSERT_EQUAL(a.SizeRow(), 9);
        ASSERT_EQUAL(a.SizeColumn(), 9);
        ASSERT_EQUAL(a.Size(), 81);
    }
    {
        std::vector<std::vector<int>> mat({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        Matrix<int> a(mat);
        ASSERT_EQUAL(a.SizeRow(), 3);
        ASSERT_EQUAL(a.SizeColumn(), 3);
        ASSERT_EQUAL(a.Size(), 9);
    }
    {
        std::vector<std::vector<int>> mat({});
        Matrix<int> a(mat);
        ASSERT_EQUAL(a.SizeRow(), 0);
        ASSERT_EQUAL(a.SizeColumn(), 0);
        ASSERT_EQUAL(a.Size(), 0);
    }

    {
        std::vector<std::vector<int>> mat({{}});
        Matrix<int> a(mat);
        ASSERT_EQUAL(a.SizeRow(), 0);
        ASSERT_EQUAL(a.SizeColumn(), 0);
        ASSERT_EQUAL(a.Size(), 0);
    }
    {
        std::vector<std::vector<int>> mat({{1}});
        Matrix<int> a(mat);
        ASSERT_EQUAL(a.SizeRow(), 1);
        ASSERT_EQUAL(a.SizeColumn(), 1);
        ASSERT_EQUAL(a.Size(), 1);
    }
    {
        std::vector<std::vector<int>> mat({{1, 2, 3}});
        Matrix<int> a(mat);
        ASSERT_EQUAL(a.SizeRow(), 3);
        ASSERT_EQUAL(a.SizeColumn(), 1);
        ASSERT_EQUAL(a.Size(), 3);
    }
    {
        std::vector<std::vector<int>> mat({{1}, {2}, {3}});
        Matrix<int> a(mat);
        ASSERT_EQUAL(a.SizeRow(), 1);
        ASSERT_EQUAL(a.SizeColumn(), 3);
        ASSERT_EQUAL(a.Size(), 3);
    }
}

void TestRandomAccess(){
{
    std::vector<std::vector<int>> mat({{1}});
    Matrix<int> m(mat);
    ASSERT_EQUAL(m[0][0], mat[0][0]);
}
{
    std::vector<std::vector<int>> mat({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m(mat);
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            ASSERT_EQUAL(mat[i][j], m[i][j]);
        }
    }
}
{
    std::vector<std::vector<int>> mat({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m(mat);
    std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution unifom_dist(0, 2);
    for(int k = 0; k < 100; ++k){
        int random_i = unifom_dist(generator);
        int random_j = unifom_dist(generator);
        ASSERT_EQUAL(mat[random_i][random_j], m[random_i][random_j]);
    }
}
}
void TestSwap(){
{
    std::vector<std::vector<int>> a({{1, 2, 3}});
    Matrix<int> m_a(a);
    m_a.Swap(m_a);
    ASSERT_EQUAL(m_a, Matrix<int>(a));

}
{
    std::vector<std::vector<int>> a({{1, 2, 3}}), b({{4}, {5}, {6}});
    Matrix<int> m_a(b), m_b(a);
    m_a.Swap(m_b);
    ASSERT_EQUAL(m_a, Matrix<int>(a));
    ASSERT_EQUAL(m_b, Matrix<int>(b));
    m_b.Swap(m_a);
    ASSERT_EQUAL(m_a, Matrix<int>(b));
    ASSERT_EQUAL(m_b, Matrix<int>(a));

}
}

void TestPushBack(){
{
    std::vector<std::vector<int>> mat({{1}});
    std::vector<int> row({3});
    Matrix<int> m(mat);
    m.PushBackRow(row);
    Matrix<int> res({{1}, {3}});
    ASSERT_EQUAL(m, res);
}
{
    std::vector<std::vector<int>> mat({{1}, {3}}), column({{2}, {4}});
    Matrix<int> m(mat);
    m.PushBackColumn(column);
    Matrix<int> res({{1, 2}, {3, 4}});
    ASSERT_EQUAL(m, res);
}
}
void TestPopBack(){

}
void TestTransp(){

}
void TestAdding(){

}
void TestMultiplication(){

}
void TestGetNorma(){

}
void TestNormalize(){

}

void TestPrint(){
    const std::string SPACE = "    ";
    {
        std::vector<std::vector<int>> mat({{1}});
        std::string equal_out = "1";
        Matrix<int> m(mat);
        std::ostringstream out;
        out << m;
        ASSERT_EQUAL(out.str(), equal_out);
    }
    {
        std::vector<std::vector<int>> mat({{1, 2, 3}});
        std::string equal_out = "1" + SPACE + "2" + SPACE + "3";
        Matrix<int> m(mat);
        std::ostringstream out;
        out << m;
        ASSERT_EQUAL(out.str(), equal_out);
    }
    {
        std::vector<std::vector<int>> mat({{1}, {2}, {3}});
        std::string equal_out = "1\n2\n3";
        Matrix<int> m(mat);
        std::ostringstream out;
        out << m;
        ASSERT_EQUAL(out.str(), equal_out);
    }
    {
        std::vector<std::vector<int>> mat({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        std::string equal_out 
        = "1" + SPACE + "2" + SPACE + "3" + "\n"
        + "4" + SPACE + "5" + SPACE + "6" + "\n"
        + "7" + SPACE + "8" + SPACE + "9";
        Matrix<int> m(mat);
        std::ostringstream out;
        out << m;
        ASSERT_EQUAL(out.str(), equal_out);
    }
}

void TestParceRowNumbers(){

}

void TestParceCSRFormat(){

}