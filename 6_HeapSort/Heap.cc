#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class heap
{
public:
    heap(std::vector<int> input) : arr(input) {heap_size = input.size();}
    int PARENT(int i)
    {
        return (std::floor((i + 1)/2) - 1);
    }

    int LEFT(int i)
    {
        return (2 * i + 1);
    }

    int RIGHT(int i)
    {
        return (2 * i + 2);
    }

    //O(lgn)
    void MAX_HEAPIFY(std::vector<int>& arr, int i)
    {
        int l = LEFT(i);
        int r = RIGHT(i);
        int length = heap_size;
        int largest = 0;
        if (l < length && arr[l] > arr[i])
            largest = l;
        else
            largest =i;

        if (r < length && arr[r] > arr[largest])
            largest = r;
        if (largest != i)
        {
            std::swap(arr[largest], arr[i]);
            MAX_HEAPIFY(arr, largest);
        }
    }

    //O(n)
    void BUILD_MAX_HEAP()
    {
        for (int i = std::floor(heap_size/2) - 1; i > 0; --i)
        {
            MAX_HEAPIFY(arr, i);
        }
    }

    // O(nlgn)
    void HEAPSORT()
    {
        BUILD_MAX_HEAP();
        for (int i = arr.size() - 1; i > 0; --i)
        {
            std::swap(arr[0], arr[i]);
            --heap_size;
            if (heap_size != 0)
                MAX_HEAPIFY(arr, 0);
        }
    }

    //priority queue
    int HEAP_MAXMUM()
    {
        return arr[0];
    }

    //O(lgn)
    int HEAP_EXTRACT_MAX()
    {
        if (heap_size < 0)
            throw std::invalid_argument("heap underflow");

        int max = arr[0];
        arr[0] = arr[heap_size - 1];
        --heap_size;
        MAX_HEAPIFY(arr, 0);
        return max;
    }

    void fetch_result_arr(std::vector<int>& result)
    {
        result = arr;
    }

public:
    int heap_size;
    std::vector<int> arr;
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

    heap test(input_list);

    test.HEAPSORT();
    std::vector<int> result;
    test.fetch_result_arr(result);
    
    std::cout << "reordered array is :" << std::endl;
    std::cout << "[ ";
    for (int n : result) {
        std::cout << n << " ";
    }
    std::cout << "]" << std::endl;
}