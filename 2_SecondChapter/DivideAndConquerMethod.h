#ifndef DIVIDEANDCONQUERMETHOD_H
#define DIVIDEANDCONQUERMETHOD_H
#include <iostream>
#include <array>
#include <vector>
#include <limits>

class DivideAndConquerMethod
{
public:
    DivideAndConquerMethod(){}

    DivideAndConquerMethod(std::vector<int> list)
    {
        m_list = list;
    }

    ~DivideAndConquerMethod()
    {
        m_list.clear();
    }

    void merge(std::vector<int>& A, int p, int q, int r)
    {
        int n_1 = q - p + 1;
        int n_2 = r - q;
        std::vector<int> L, R;
        L.resize(n_1 + 1);
        R.resize(n_2 + 1);
        for (int i = 0; i < L.size() - 1; ++i)
            L[i] = A[p + i];

        for (int j = 0; j < R.size() - 1; ++j)
            R[j] = A[q + j + 1];

        L[n_1] = std::numeric_limits<int>::max();
        R[n_2] = std::numeric_limits<int>::max();

        int count_i = 0,  count_j = 0;

        for (int k = p; k < r + 1; ++k)
        {
            if (L[count_i] < R[count_j])
            {
                A[k] = L[count_i];
                count_i++;
            }
            else
            {
                A[k] = R[count_j];
                count_j++;
            }
        }
    }

    void mergeSort(std::vector<int>& A, int p, int r)
    {
        if (p < r)
        {
            int q = (p + r)/2;
            mergeSort(A, p, q);
            mergeSort(A, q + 1, r);
            merge(A, p, q, r);
        }
    }

public:
    std::vector<int> m_list;
};
#endif