#include "Heap.h"

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