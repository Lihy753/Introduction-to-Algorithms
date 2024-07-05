#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <iostream>
#include <algorithm> 
#include <vector>



class quickSort
{
public:
    quickSort(std::vector<int> input) : A(input) {}

    void QUICKSORT(int p, int r)
    {
        if (p < r)
        {
            int q = PARTITION(p, r);
            QUICKSORT(p, q - 1);
            QUICKSORT(q + 1, r);
        }
    }

    //O(n), n = r - p + 1
    int PARTITION(int p, int r)
    {
        int x = A[r];
        int i = p - 1;
        for (int j = p; j < r; ++j)
        {
            if (A[j] <= x)
            {
                ++i;
                std::swap(A[i], A[j]);
            }
        } 
        std::swap(A[i + 1], A[r]);
        return i + 1;
    }

    void RANDOMIZED_QUICKSORT(int p, int r)
    {
        if (p < r)
        {
            int q = RANDOMIZED_PARTITION(p , r);
            RANDOMIZED_QUICKSORT(p, q - 1);
            RANDOMIZED_QUICKSORT(q + 1, r);
        }
    }

    int RANDOMIZED_PARTITION(int p, int r)
    {
        int i = std::rand() % (r - p + 1) + p;
        std::swap(A[r], A[i]);
        return PARTITION(p, r);
    }



    void fetch_result(std::vector<int>& result)
    {
        result = A;
    }

public:
    std::vector<int> A;
};

#endif