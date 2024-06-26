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
        std::swap(A[r], A[r]);
        return PARTITION(p, r);
    }



    void fetch_result(std::vector<int>& result)
    {
        result = A;
    }

public:
    std::vector<int> A;
};


//  3 1 5 3 7 9 0;
int main()
{
    std::vector<int> input_list;
    std::cout << "Please input a string of numbers which you want to recorder" << std::endl;
    int num;
    while (std::cin >> num)
    {
        input_list.push_back(num);
    }

    std::cout << "Your array is :" << std::endl;
    std::cout << "[ ";
    for (int n : input_list) {
        std::cout << n << " ";
    }
    std::cout << "]" << std::endl;

    std::vector<int> result;

    quickSort test(input_list);
    test.QUICKSORT(0, input_list.size() - 1);
    test.fetch_result(result);

    std::cout << "Your result is :" << std::endl;
    std::cout << "[ ";
    for (int n : result) {
        std::cout << n << " ";
    }
    std::cout << "]" << std::endl;


    std::vector<int> rand_result;
    quickSort rand_test(input_list);
    rand_test.RANDOMIZED_QUICKSORT(0, input_list.size() - 1);
    rand_test.fetch_result(rand_result);
    std::cout << "Your rand result is :" << std::endl;
    std::cout << "[ ";
    for (int n : rand_result) {
        std::cout << n << " ";
    }
    std::cout << "]" << std::endl;
}