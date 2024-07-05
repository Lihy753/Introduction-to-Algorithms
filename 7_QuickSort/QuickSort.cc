#include "QuickSort.h"




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