#include "StrassenAlgorithmForMatrixMultiplication.h"

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