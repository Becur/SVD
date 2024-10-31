#include "test_matrix.h"
#include "assert.h"
#include "matrix.h"

#include <vector>
#include <sstream>
#include <string>
#include <random>
#include <chrono>
#include <stdexcept>
#include <cmath>


int main/*TestMatrix*/(){
    const float ERROR_RATE = 1e-6;

    TestPrint();

    TestEqual();
    TestCopyMove();
    TestGetSize();
    TestEmpty();
    TestCorrect();
    TestRandomAccess();
    TestSwap();
    TestPushBack();
    TestPopBack();
    TestAdding();
    TestMultiplication(ERROR_RATE);

    TestTransp();

    TestNormalize(ERROR_RATE);

    TestParceCSRFormat();

    return 0;
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
    ASSERT_EQUAL(a.ActualSize(), 0);
}
{
    Matrix<int> a(5);
    ASSERT_EQUAL(a.SizeRow(), 0);
    ASSERT_EQUAL(a.SizeColumn(), 5);
    ASSERT_EQUAL(a.Size(), 0);
    ASSERT_EQUAL(a.ActualSize(), 0);
}
{
    Matrix<int> a(0);
    ASSERT_EQUAL(a.SizeRow(), 0);
    ASSERT_EQUAL(a.SizeColumn(), 0);
    ASSERT_EQUAL(a.Size(), 0);
    ASSERT_EQUAL(a.ActualSize(), 0);
}
{
    Matrix<int> a(5, 0, 6);
    ASSERT_EQUAL(a.SizeRow(), 0);
    ASSERT_EQUAL(a.SizeColumn(), 5);
    ASSERT_EQUAL(a.Size(), 0);
    ASSERT_EQUAL(a.ActualSize(), 0);
}
{
    Matrix<int> a(0, 5, 6);
    ASSERT_EQUAL(a.SizeRow(), 0);
    ASSERT_EQUAL(a.SizeColumn(), 0); // because the Matrix class is row-oriented
    ASSERT_EQUAL(a.Size(), 0);
    ASSERT_EQUAL(a.ActualSize(), 0);
}
{
    Matrix<int> a(3, 4, 5);
    ASSERT_EQUAL(a.SizeRow(), 4);
    ASSERT_EQUAL(a.SizeColumn(), 3);
    ASSERT_EQUAL(a.Size(), 12);
    ASSERT_EQUAL(a.ActualSize(), 12);
}
{
    Matrix<int> a(9, 9, 0);
    ASSERT_EQUAL(a.SizeRow(), 9);
    ASSERT_EQUAL(a.SizeColumn(), 9);
    ASSERT_EQUAL(a.Size(), 81);
    ASSERT_EQUAL(a.ActualSize(), 81);
}
{
    std::vector<std::vector<int>> mat({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> a(mat);
    ASSERT_EQUAL(a.SizeRow(), 3);
    ASSERT_EQUAL(a.SizeColumn(), 3);
    ASSERT_EQUAL(a.Size(), 9);
    ASSERT_EQUAL(a.ActualSize(), 9);
}
{
    std::vector<std::vector<int>> mat({});
    Matrix<int> a(mat);
    ASSERT_EQUAL(a.SizeRow(), 0);
    ASSERT_EQUAL(a.SizeColumn(), 0);
    ASSERT_EQUAL(a.Size(), 0);
    ASSERT_EQUAL(a.ActualSize(), 0);
}

{
    std::vector<std::vector<int>> mat({{}});
    Matrix<int> a(mat);
    ASSERT_EQUAL(a.SizeRow(), 0);
    ASSERT_EQUAL(a.SizeColumn(), 1);
    ASSERT_EQUAL(a.Size(), 0);
    ASSERT_EQUAL(a.ActualSize(), 0);
}
{
    std::vector<std::vector<int>> mat({{1}});
    Matrix<int> a(mat);
    ASSERT_EQUAL(a.SizeRow(), 1);
    ASSERT_EQUAL(a.SizeColumn(), 1);
    ASSERT_EQUAL(a.Size(), 1);
    ASSERT_EQUAL(a.ActualSize(), 1);
}
{
    std::vector<std::vector<int>> mat({{1, 2, 3}});
    Matrix<int> a(mat);
    ASSERT_EQUAL(a.SizeRow(), 3);
    ASSERT_EQUAL(a.SizeColumn(), 1);
    ASSERT_EQUAL(a.Size(), 3);
    ASSERT_EQUAL(a.ActualSize(), 3);
}
{
    std::vector<std::vector<int>> mat({{1}, {2}, {3}});
    Matrix<int> a(mat);
    ASSERT_EQUAL(a.SizeRow(), 1);
    ASSERT_EQUAL(a.SizeColumn(), 3);
    ASSERT_EQUAL(a.Size(), 3);
    ASSERT_EQUAL(a.ActualSize(), 3);
}
{
    std::vector<std::vector<int>> mat({{1, 2}, {2, 3, 4, 5}, {3}});
    Matrix<int> a(mat);
    ASSERT_EQUAL(a.SizeRow(), 2);
    ASSERT_EQUAL(a.SizeColumn(), 3);
    ASSERT_EQUAL(a.Size(), 6);
    ASSERT_EQUAL(a.ActualSize(), 7);
}
{
    std::vector<std::vector<int>> mat({{1, 2, 3}, {2, 3}, {3}});
    Matrix<int> a(mat);
    ASSERT_EQUAL(a.SizeRow(), 3);
    ASSERT_EQUAL(a.SizeColumn(), 3);
    ASSERT_EQUAL(a.Size(), 9);
    ASSERT_EQUAL(a.ActualSize(), 6);
}
}

void TestEmpty(){
{
    Matrix<int> m;
    ASSERT(m.Empty());
}
{
    Matrix<int> m(6);
    ASSERT(m.Empty());
}
{
    Matrix<int> m(1, 1, 1);
    ASSERT(!m.Empty());
}
{
    Matrix<int> m({});
    ASSERT(m.Empty());
}
{
    Matrix<int> m({{}, {}});
    ASSERT(m.Empty());
}
{
    Matrix<int> m({{2}, {}});
    ASSERT(!m.Empty());
}
{
    Matrix<int> m({{}, {1}});
    ASSERT(!m.Empty());
}
}

void TestCorrect(){
{
    Matrix<int> m;
    ASSERT(!m.Correct());
}
{
    Matrix<int> m(6);
    ASSERT(!m.Correct());
}
{
    Matrix<int> m(1, 1, 1);
    ASSERT(m.Correct());
}
{
    Matrix<int> m({});
    ASSERT(!m.Correct());
}
{
    Matrix<int> m({{1}, {2}});
    ASSERT(m.Correct());
}
{
    Matrix<int> m({{2}, {}});
    ASSERT(!m.Correct());
}
{
    Matrix<int> m({{}, {1}});
    ASSERT(!m.Correct());
}
{
    Matrix<int> m({{1, 2, 3}, {1, 2}, {1, 2, 3}});
    ASSERT(!m.Correct());
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
    std::uniform_int_distribution uniform_dist(0, 2);
    for(int k = 0; k < 100; ++k){
        int random_i = uniform_dist(generator);
        int random_j = uniform_dist(generator);
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
    std::vector<std::vector<int>> mat({{}, {2}});
    std::vector<int> row({3});
    Matrix<int> m(mat);
    m.PushBackRow(row);
    Matrix<int> res({{}, {2}, {3}});
    ASSERT_EQUAL(m, res);
}
{
    std::vector<std::vector<int>> mat({{1}, {3}}), column({{2}, {4}});
    Matrix<int> m(mat);
    m.PushBackColumn(column);
    Matrix<int> res({{1, 2}, {3, 4}});
    ASSERT_EQUAL(m, res);
}
{
    std::vector<std::vector<int>> mat({{1}});
    Matrix<int> rows({{4, 5, 6}, {2}, {3, 5}});
    Matrix<int> m(mat);
    m.PushBackRow(rows);
    Matrix<int> res({{1}, {4, 5, 6}, {2}, {3, 5}});
    ASSERT_EQUAL(m, res);
}
{
    std::vector<std::vector<int>> mat({{1}, {3}});
    Matrix<int> columns({{4, 5, 6}, {2}, {3, 5}});
    Matrix<int> m(mat);
    m.PushBackColumn(columns);
    Matrix<int> res({{1, 4, 5, 6}, {3, 2}, {3, 5}});
    ASSERT_EQUAL(m, res);
}
}

void TestPopBack(){
{
    Matrix<int> m({}), res({});
    m.PopBackRow();
    m.PopBackColumn();
    ASSERT_EQUAL(m, res);
}
{
    Matrix<int> m({{}}), res({});
    m.PopBackRow();
    ASSERT_EQUAL(m, res);
}
{
    Matrix<int> m({{}, {}, {}}), res({{}, {}, {}});
    m.PopBackColumn();
    ASSERT_EQUAL(m, res);
}
{
    Matrix<int> m({{1}}), res({});
    m.PopBackRow();
    ASSERT_EQUAL(m, res);
}
{
    Matrix<int> m({{1}}), res({{}});
    m.PopBackColumn();
    ASSERT_EQUAL(m, res);
}
{
    Matrix<int> m({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}); 
    Matrix<int> res({{1, 2}, {4, 5}});
    m.PopBackRow();
    m.PopBackColumn();
    ASSERT_EQUAL(m, res);
}
}

void TestTransp(){
{
    Matrix<int> m, res;
    ASSERT_EQUAL(Transp(m), res);
}
{
    Matrix<int> m({{}, {}, {}}), res;
    ASSERT_EQUAL(Transp(m), res);
}
{
    Matrix<int> m({{1}}), res({{1}});
    ASSERT_EQUAL(Transp(m), res);
}
{
    Matrix<int> m({{1}, {2}, {3}}), res({{1, 2, 3}});
    ASSERT_EQUAL(Transp(m), res);
}
{
    Matrix<int> m({{1, 2, 3}}), res({{1}, {2}, {3}});
    ASSERT_EQUAL(Transp(m), res);
}
{
    Matrix<int> m({{1, 2}, {3, 4}}), res({{1, 3}, {2, 4}});
    ASSERT_EQUAL(Transp(m), res);
}
}

void TestAdding(){
    TestUnarySign();
    TestAddNum();
    TestAddMatrix();
}

void TestUnarySign(){
{
    Matrix<int> res({{1, -2}, {3, 4}});
    ASSERT_EQUAL(+res, res);
}
{
    Matrix<int> m({{1, 2}, {3, 4}}), res({{-1, -2}, {-3, -4}});
    ASSERT_EQUAL(-m, res);
}

}

void TestAddNum(){
{
    Matrix<int> m({{1, 2}, {3, 4}}), res({{2, 3}, {4, 5}});
    ASSERT_EQUAL(m += 1, res);
}
{
    Matrix<int> m({{1, 2, 3}, {0, 5, 6}});
    int a = 5;
    Matrix<int> res({{6, 7, 8}, {5, 10, 11}});
    ASSERT_EQUAL(m + a, res);
    ASSERT_EQUAL(a + m, res);
}
{
    Matrix<int> m({{}, {0, 5, 6}});
    int a = 5;
    Matrix<int> res({{}, {5, 10, 11}});
    ASSERT_EQUAL(m + a, res);
    ASSERT_EQUAL(a + m, res);
}
{
    bool is_throw = false;
    Matrix<int> m({{}, {}});
    int a = 5;
    try{
        m + a;
    }
    catch(const std::invalid_argument& e){
        is_throw = true;
    }
    ASSERT(is_throw);
}
{
    bool is_throw = false;
    Matrix<int> m({{}, {}});
    int a = 5;
    try{
        a + m;
    }
    catch(const std::invalid_argument& e){
        is_throw = true;
    }
    ASSERT(is_throw);
}
{
    Matrix<int> m({{1, 2}, {3, 4}}), res({{0, 1}, {2, 3}});
    ASSERT_EQUAL(m -= 1, res);
}
{
    Matrix<int> m({{1, 2, 3}, {0, 5, 6}});
    int a = 5;
    Matrix<int> res({{-4, -3, -2}, {-5, 0, 1}});
    ASSERT_EQUAL(m - a, res);
}
{
    Matrix<int> m({{}, {0, 5, 6}});
    int a = 5;
    Matrix<int> res({{}, {-5, 0, 1}});
    ASSERT_EQUAL(m - a, res);
}
{
    bool is_throw = false;
    Matrix<int> m({{}, {}});
    int a = 5;
    try{
        m - a;
    }
    catch(const std::invalid_argument& e){
        is_throw = true;
    }
    ASSERT(is_throw);
}
}

void TestAddMatrix(){
{
    Matrix<int> lhs({{1, 2}, {3, 4}}), rhs({{2, 3}, {4, 5}});
    Matrix<int> res({{3, 5}, {7, 9}});
    ASSERT_EQUAL(lhs + rhs, res);
    ASSERT_EQUAL(rhs + lhs, res);
}
{
    bool is_throw = false;
    Matrix<int> lhs({}), rhs({});
    try{
        lhs + rhs;
    }
    catch(const std::invalid_argument& e){
        is_throw = true;
    }
    ASSERT(is_throw);
}
{
    bool is_throw = false;
    Matrix<int> lhs({{1}}), rhs({{1, 2}});
    try{
        lhs + rhs;
    }
    catch(const std::invalid_argument& e){
        is_throw = true;
    }
    ASSERT(is_throw);
    
}
{
    bool is_throw = false;
    Matrix<int> lhs({{1}}), rhs({{1}, {2}});
    try{
        lhs + rhs;
    }
    catch(const std::invalid_argument& e){
        is_throw = true;
    }
    ASSERT(is_throw);
    
}
{
    bool is_throw = false;
    Matrix<int> lhs({{}, {1}}), rhs({{1}, {2}});
    try{
        lhs + rhs;
    }
    catch(const std::invalid_argument& e){
        is_throw = true;
    }
    ASSERT(is_throw);
    
}
{
    bool is_throw = false;
    Matrix<int> lhs({{1}, {2}}), rhs({{}, {2}});
    try{
        lhs + rhs;
    }
    catch(const std::invalid_argument& e){
        is_throw = true;
    }
    ASSERT(is_throw);
    
}
{
    Matrix<int> lhs({{1, 2}, {3, 4}}), rhs({{2, 3}, {4, 5}});
    Matrix<int> res({{-1, -1}, {-1, -1}});
    ASSERT_EQUAL(lhs - rhs, res);
}
{
    bool is_throw = false;
    Matrix<int> lhs({}), rhs({});
    try{
        lhs - rhs;
    }
    catch(const std::invalid_argument& e){
        is_throw = true;
    }
    ASSERT(is_throw);
    
}
{
    bool is_throw = false;
    Matrix<int> lhs({{1}}), rhs({{1, 2}});
    try{
        lhs - rhs;
    }
    catch(const std::invalid_argument& e){
        is_throw = true;
    }
    ASSERT(is_throw);
    
}
{
    bool is_throw = false;
    Matrix<int> lhs({{1}}), rhs({{1}, {2}});
    try{
        lhs - rhs;
    }
    catch(const std::invalid_argument& e){
        is_throw = true;
    }
    ASSERT(is_throw);
}
{
    bool is_throw = false;
    Matrix<int> lhs({{}, {1}}), rhs({{1}, {2}});
    try{
        lhs - rhs;
    }
    catch(const std::invalid_argument& e){
        is_throw = true;
    }
    ASSERT(is_throw);
    
}
{
    bool is_throw = false;
    Matrix<int> lhs({{1}, {2}}), rhs({{}, {2}});
    try{
        lhs - rhs;
    }
    catch(const std::invalid_argument& e){
        is_throw = true;
    }
    ASSERT(is_throw);
    
}
}

void TestMultiplication(const float error_rate){
    TestMultNum(error_rate);
    TestMultMatrix();
}

void TestMultNum(const float error_rate){
{
    Matrix<int> m({{1, 2, 3}, {0, 5, 6}});
    int a = 5;
    Matrix<int> res({{5, 10, 15}, {0, 25, 30}});
    ASSERT_EQUAL(m * a, res);
    ASSERT_EQUAL(a * m, res);
}
{
    Matrix<int> m({{}, {0, 5, 6}});
    int a = 5;
    Matrix<int> res({{}, {0, 25, 30}});
    ASSERT_EQUAL(m * a, res);
    ASSERT_EQUAL(a * m, res);
}
{
    bool is_throw = false;
    Matrix<int> m({{}, {}});
    int a = 5;
    try{
        m * a;
    }
    catch(const std::invalid_argument& e){
        is_throw = true;
    }
    ASSERT(is_throw);
}
{
    bool is_throw = false;
    Matrix<int> m({{}, {}});
    int a = 5;
    try{
        a * m;
    }
    catch(const std::invalid_argument& e){
        is_throw = true;
    }
    ASSERT(is_throw);
}
{
    Matrix<float> m({{1, 2, 3}, {0, 5, 6}});
    float a = 3;
    Matrix<float> res({{1/3.0, 2/3.0, 1}, {0, 5/3.0, 2}});
    m = m / a;
    
    for(int i = 0; i < m.SizeColumn(); ++i){
        for(int j = 0; j < m.SizeRow(); ++j){
            ASSERT(std::abs(m[i][j] - res[i][j]) < error_rate);
        }
    }
}
{
    bool is_throw = false;
    Matrix<int> m({{}, {}});
    int a = 5;
    try{
        m / a;
    }
    catch(const std::invalid_argument& e){
        is_throw = true;
    }
    ASSERT(is_throw);
}
}

void TestMultMatrix(){
{
    Matrix<int> lhs({{2}}), rhs({{3}});
    Matrix<int> res({{6}});
    ASSERT_EQUAL(lhs * rhs, res);
}
{
    Matrix<int> lhs({{1, 2, 3}, {4, 5, 6}}), rhs({{7}, {8}, {9}});
    Matrix<int> res({{50}, {122}});
    ASSERT_EQUAL(lhs * rhs, res);
}
{
    Matrix<int> lhs({{1, 2, 3}, {4, 5, 6}}), rhs({{7, 8, 9}, {10, 11, 12}, {13, 14, 15}});
    Matrix<int> res({{66, 72, 78}, {156, 171, 186}});
    ASSERT_EQUAL(lhs * rhs, res);
}
{
    bool is_throw = false;
    Matrix<int> lhs({}), rhs({});
    try{
        lhs * rhs;
    }
    catch(const std::invalid_argument& e){
        is_throw = true;
    }
    ASSERT(is_throw);
    
}
{
    bool is_throw = false;
    Matrix<int> lhs({{1, 2}}), rhs({{}, {2}});
    try{
        lhs * rhs;
    }
    catch(const std::invalid_argument& e){
        is_throw = true;
    }
    ASSERT(is_throw);
    
}
{
    bool is_throw = false;
    Matrix<int> lhs({{}, {1}}), rhs({{1}});
    try{
        lhs * rhs;
    }
    catch(const std::invalid_argument& e){
        is_throw = true;
    }
    ASSERT(is_throw);
    
}
{
    bool is_throw = false;
    Matrix<int> lhs({{1}}), rhs({{1}, {2}});
    try{
        lhs * rhs;
    }
    catch(const std::invalid_argument& e){
        is_throw = true;
    }
    ASSERT(is_throw);
    
}
{
    bool is_throw = false;
    Matrix<int> lhs({{1, 2, 3}}), rhs({{1}, {2}});
    try{
        lhs * rhs;
    }
    catch(const std::invalid_argument& e){
        is_throw = true;
    }
    ASSERT(is_throw);
    
}
}

void TestNormalize(const float error_rate){
{
    Matrix<float> m({{1, 2, 3, 1.5}});
    Matrix<float> res({{1, 1, 1, 1}});
    m = Normalize<float>(m);
    for(int i = 0; i < m.SizeColumn(); ++i){
        for(int j = 0; j < m.SizeRow(); ++j){
            ASSERT(std::abs(m[i][j] - res[i][j]) < error_rate);
        }
    }
}
{
    Matrix<float> m({{1}, {2}, {3}, {1.5}});
    Matrix<float> res({{0.248069}, {0.496139}, {0.744208}, {0.372104}});
    m = Normalize<float>(m);
    for(int i = 0; i < m.SizeColumn(); ++i){
        for(int j = 0; j < m.SizeRow(); ++j){
            ASSERT(std::abs(m[i][j] - res[i][j]) < error_rate);
        }
    }
}
{
    Matrix<float> m({{1, 0}, {2, 3}, {3, 7}, {1.5, 2}});
    Matrix<float> res({{0.248069, 0}, {0.496139, 0.381}, {0.744208, 0.889001}, {0.372104, 0.254}});
    m = Normalize<float>(m);
    for(int i = 0; i < m.SizeColumn(); ++i){
        for(int j = 0; j < m.SizeRow(); ++j){
            ASSERT(std::abs(m[i][j] - res[i][j]) < error_rate);
        }
    }
}
}

void TestParceCSRFormat(){
{
    std::stringstream input;
    input << "5 5\n";
    input << "0 1 3 1 2 1 2 3 3 3 4\n";
    input << "0 3 5 8 9 11\n";
    input << "1 2 11 3 4 5 6 7 8 9 10";
    Matrix<int> res({{1, 2, 0, 11, 0}, {0, 3, 4, 0, 0}, {0, 5, 6, 7, 0}, {0, 0, 0, 8, 0}, {0, 0, 0, 9, 10}});
    ASSERT_EQUAL(ParceCSRFormat<int>(input), res);
}
{
    std::stringstream input;
    input << "0 0\n";
    Matrix<int> res;
    ASSERT_EQUAL(ParceCSRFormat<int>(input), res);
}
}