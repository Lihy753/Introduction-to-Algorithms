#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class heap
{
public:
    int PARENT(int i)
    {
        return std::floor(i/2);
    }

    int LEFT(int i)
    {
        return (2 * i);
    }

    int RIGHT(int i)
    {
        return (2 * i + 1);
    }

    void MAX_HEAPIFY(std::vector<int> A, int i)
    {
        int l = LEFT(i);
        int r = RIGHT(i);
        int length = A.size();
        int largest = 0;
        if (l <= length && A[l] > A[i])
            largest = l;
        else
            largest =i;
        
        if (largest != i)
        {
            std::swap(A[largest], A[i]);
            MAX_HEAPIFY(A, largest);
        }
    }

    void BUILD_MAX_HEAP(std::vector<int>& A)
    {
        int heap_size = A.size();
        for (int i = std::floor(heap_size/2) - 1; i > 0; --i)
        {
            MAX_HEAPIFY(A, i);
        }
    }
};

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

    heap test;

    test.BUILD_MAX_HEAP(input_list);
    
    std::cout << "reordered array is :" << std::endl;
    std::cout << "[ ";
    for (int n : input_list) {
        std::cout << n << " ";
    }
    std::cout << "]" << std::endl;

}