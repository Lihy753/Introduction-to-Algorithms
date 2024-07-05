#ifndef MEDIANANDSEQUENTIALSTATISTICS_H
#define MEDIANANDSEQUENTIALSTATISTICS_H

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
        m_partition_vector.clear();
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

    //返回数组 m_array 中第 i 小的元素, 最坏运行时间为 O(n^2), 但是当所有的元素都不相同的时候， 其运行时间的期望值是 O(n); 
    int RANDOMIZED_SELECT(int p , int r, int i)
    {
        if (p == r)
            return m_array[r];
        
        quickSort test(m_array);
        int q = test.RANDOMIZED_PARTITION(p, r);
        test.fetch_result(m_array);
        int k = q - p + 1;
        if (i == k)
            return m_array[q];
        else if (i < k)
            return RANDOMIZED_SELECT(p, q - 1, i);
        else 
            return RANDOMIZED_SELECT(q + 1, r, i - k);
    }

    int SELECT()
    {
        
    }

public:
    std::vector<int> m_array;
    std::vector<std::vector<int>> m_partition_vector;
};

#endif