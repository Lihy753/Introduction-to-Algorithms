#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

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
        std::cout << "build max heap" << std::endl;
        for (int i = std::floor(heap_size/2) - 1; i > -1; --i)
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

    //O(lgn)
    void HEAP_INCREASE_KEY(int i, int key)
    {
        if (key < arr[i])
        {
            throw std::invalid_argument("new key is smaller than current key");
        }

        arr[i] = key;
        while (i > 0 && arr[PARENT(i)] < arr[i])
        {
            std::swap(arr[i], arr[PARENT(i)]);
            i = PARENT(i);
        }
    }

    //O(lgn)
    void MAX_HEAP_INSERT(int key)
    {
        ++heap_size;
        arr[heap_size - 1] = std::numeric_limits<int>::min();
        HEAP_INCREASE_KEY(heap_size - 1, key);
    }

    void fetch_result_arr(std::vector<int>& result)
    {
        // std::cout << "fetch result" << std::endl;
        // std::cout << "heap_size = " << heap_size << ", arr.size() = " << arr.size() <<  std::endl;
        if (heap_size > arr.size())
            heap_size = arr.size();

        result.resize(heap_size);
        std::copy(arr.begin(), arr.begin() + heap_size, result.begin());
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
    std::vector<int> result;
    test.BUILD_MAX_HEAP();
    test.fetch_result_arr(result);
    std::cout << "BUILD_MAX_HEAP array is :" << std::endl;
    std::cout << "[ ";
    for (int n : result) {
        std::cout << n << " ";
    }
    std::cout << "]" << std::endl;

    int maxnum;
    maxnum = test.HEAP_MAXMUM();
    std::cout << "maxnum = " << maxnum << std::endl;



    test.HEAP_EXTRACT_MAX();

    test.fetch_result_arr(result);
    std::cout << "HEAP_EXTRACT_MAX array is :" << std::endl;
    std::cout << "[ ";
    for (int n : result) {
        std::cout << n << " ";
    }
    std::cout << "]" << std::endl;


    test.HEAP_INCREASE_KEY(2, 16);
    test.fetch_result_arr(result);
    std::cout << "HEAP_INCREASE_KEY array is :" << std::endl;
    std::cout << "[ ";
    for (int n : result) {
        std::cout << n << " ";
    }
    std::cout << "]" << std::endl;


    test.MAX_HEAP_INSERT(18);
    test.fetch_result_arr(result);
    std::cout << "MAX_HEAP_INSERTs array is :" << std::endl;
    std::cout << "[ ";
    for (int n : result) {
        std::cout << n << " ";
    }
    std::cout << "]" << std::endl;
}