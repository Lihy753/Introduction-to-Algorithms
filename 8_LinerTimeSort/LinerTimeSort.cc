#include <iostream> 
#include <vector>
#include <algorithm> 
#include <random>
#include <list>

#include "../2_SecondChapter/InsertationAlgorithm.cc"


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

int main()
{
    // std::vector<int> input_list;
    // std::cout << "Please input a string of numbers which you want to recorder" << std::endl;
    // int num;
    // while (std::cin >> num)
    // {
    //     input_list.push_back(num);
    // }

    // std::cout << "Your array is :" << std::endl;
    // std::cout << "[ ";
    // for (int n : input_list) {
    //     std::cout << n << " ";
    // }
    // std::cout << "]" << std::endl;

    // std::vector<int> result;
    // countSort test(input_list);
    // test.COUNTING_SORT(10);
    // test.fetch_result(result);

    // std::cout << "Your result is :" << std::endl;
    // std::cout << "[ ";
    // for (int n : result) {
    //     std::cout << n << " ";
    // }
    // std::cout << "]" << std::endl;

    int n = 10;
    std::vector<float> input(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);
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

    std::list<float> result;
    bucketSort test(input);
    test.BUCKET_SORT(result);

    std::cout << "The result is :" << std::endl;
    std::cout << "[ ";
    for (float n : result) {
        std::cout << n << " ";
    }
    std::cout << "]" << std::endl;

    return 0;
}