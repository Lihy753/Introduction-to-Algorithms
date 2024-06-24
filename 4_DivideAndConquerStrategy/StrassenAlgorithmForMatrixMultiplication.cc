#include <iostream>
#include <iostream>
#include <vector>
#include <random>
#include <array>

template<typename T>
class Matrix
{
public:
    Matrix(){};
    Matrix(int row, int col) : rows(row), cols(col), dates(row, std::vector<T>(col)){};
    void fillRandom(T minvalue, T maxvalue);
    void print() const;

public:
    int rows, cols;
    std::vector<std::vector<T>> dates;
};

template <typename T>
void Matrix<T>::fillRandom(T minvalue, T maxvalue)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> dis(minvalue, maxvalue);

    for (auto& row : dates) {
        for (auto& element : row) {
            element = dis(gen);
        }
    }
}

template <typename T>
void Matrix<T>::print() const
{
    for (const auto& row : dates)
    {
        for (const auto& element : row)
        {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

template <typename T>
class MatrixMultiply : public Matrix<T>
{
public:
    MatrixMultiply(const Matrix<T>& a, const Matrix<T>& b) : A(a), B(b){};

    Matrix<T> MatrixMult(Matrix<T> A, Matrix<T> B);
public:
    Matrix<T> A;
    Matrix<T> B;
};

template<typename T>
Matrix<T> MatrixMultiply<T>::MatrixMult(Matrix<T> A, Matrix<T> B)
{
    int result_row = A.rows;
    int result_col = B.cols;
    Matrix<T> C (result_row, result_col);
    std::vector<std::vector<T>>& result_dates = C.dates;

    for (int i = 0; i < result_row; ++i)
    {
        for (int j = 0; j < result_col; ++j)
        {
            result_dates[i][j] = 0;
            for (int k = 0; k < A.cols; ++k)
            {
                result_dates[i][j] += A.dates[i][k] * B.dates[k][j];
            }
        }
    }

    return C;
}

int main()
{
    std::cout << "Please input the two random matrix row and col" << std::endl;
    std::vector<int> matrix_row_and_col;
    int num;
    while (std::cin >> num)
    {
        matrix_row_and_col.push_back(num);
    }

    if (matrix_row_and_col.size() > 4)
        throw std::invalid_argument("The input rol and col num is wrong");

    int row_0 = matrix_row_and_col[0];
    int col_0 = matrix_row_and_col[1];

    int row_1 = matrix_row_and_col[2];
    int col_1 = matrix_row_and_col[3];

    if (col_0 != row_1)
        throw std::invalid_argument("these two matrxi can't multi");

    Matrix<int> A(row_0, col_0);
    Matrix<int> B(row_1, col_1);
    Matrix<int> C(row_0, col_1);

    A.fillRandom(0, 100);
    B.fillRandom(0, 100);
    std::cout << "A = " << std::endl;
    A.print();
    std::cout << "B = " << std::endl;
    B.print();

    MatrixMultiply<int> MatrixMul(A, B);
    C = MatrixMul.MatrixMult(A, B);
    std::cout << "C = " << std::endl;
    C.print();
    return 0;
}