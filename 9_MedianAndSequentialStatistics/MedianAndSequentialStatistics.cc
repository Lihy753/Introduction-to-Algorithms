#include "MedianAndSequentialStatistics.h"


int main()
{
    int n = 10;
    std::vector<int> input(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 100);
    for (int i = 0; i < n; ++i)
    {
        float num = dis(gen);
        input[i] = num;
    }

    std::cout << "The random input is :" << std::endl;
    std::cout << "[ ";
    for (float n : input) {
        std::cout << n << " ";
    }
    std::cout << "]" << std::endl;

    sequentialStatistics m_test(input);
    int result = m_test.RANDOMIZED_SELECT(0, 9, 4);
    std::cout << "The 4th minimal number in input list is : " << result;

    return 0;
}