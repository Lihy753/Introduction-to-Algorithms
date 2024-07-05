#include <iostream>
#include <vector>
#include <random>
#include "../7_QuickSort/QuickSort.h"


class sequentialStatistics
{
public:
    sequentialStatistics(std::vector<int> input) 
        : m_array(input)
    {
    }

    int MINIMUM()
    {
        int min = m_array[0];
        for (int i = 1; i < m_array.size(); ++i)
        {
            if (min > m_array[i])
                min = m_array[i];
        }
        return min;
    }

    //返回数组 m_array 中第 i 小的元素
    int RANDOMIZED_SELECT(int p , int r, int i)
    {
        if (p == r)
            return m_array[r];
        
        quickSort test(m_array);
        int q = test.RANDOMIZED_PARTITION(p, r);
        int k = q - p + 1;
        if (i == k)
            return m_array[q];
        else if (i < k)
            return RANDOMIZED_SELECT(p, q - 1, i);
        else 
            return RANDOMIZED_SELECT(q + 1, r, i - k);
    }



public:
    std::vector<int> m_array;
};


int main()
{
    int n = 10;
    std::vector<int> input(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<int> dis(0, 100);
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