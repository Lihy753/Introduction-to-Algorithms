#ifndef LINERTIMESORT_H
#define LINERTIMESORT_H


#include <iostream> 
#include <vector>
#include <algorithm> 
#include <random>
#include <list>

#include "../2_SecondChapter/InsertationAlgorithm.h"

class countSort
{
public:
    countSort(){}
    countSort(std::vector<int> input) : A(input) {}

    //O(k+n)
    void COUNTING_SORT(int k)
    {
        std::vector<int> C(k, 0);
        B.resize(A.size());
        for (int j = 0; j < A.size(); ++j)
        {
            C[A[j]] = C[A[j]] + 1;
        }
        //C[i] now contains the number of elements equal to i

        for (int i = 1; i < k; ++i)
        {
            C[i] = C[i] + C[i - 1];
        }
        //C[i] now contains the number of elements less than or equal to i

        for (int j = A.size() - 1; j > -1; --j)
        {
            B[C[A[j]] - 1] = A[j];
            C[A[j]] = C[A[j]] - 1;
        }
    }

    void fetch_result(std::vector<int>& result)
    {
        result = B;
    }

public:
    std::vector<int> A;
    std::vector<int> B;
};

class radixSort : public countSort
{
public:
    void RADIX_SORT(std::vector<int> A)
    {
        int d;
        for (int i = 1; i <= d; ++i)
            "use a stable sort to sort array A on digit i";
    }
};

class bucketSort : public countSort
{
public:
    bucketSort(std::vector<float> input) : A(input){}

    void BUCKET_SORT(std::list<float>& result)
    {
        int n = A.size();
        std::vector<std::list<float>> B(n);
        for (int i = 0; i < n; ++i)
        {
            B[i].clear();
        }
        for (int i = 0; i < n; ++i)
        {
            int location = std::floor(n * A[i]);
            B[location].push_back(A[i]);
        }

        for (int i = 0; i < n; ++i)
        {
            InsertationSort insert_sort(B[i]);
            insert_sort.sortFunction(B[i]);
        }

        for (const auto fi : B)
        {
            std::copy(fi.begin(), fi.end(), std::back_inserter(result));
        }
    }

public:
    std::vector<float> A;
};


#endif