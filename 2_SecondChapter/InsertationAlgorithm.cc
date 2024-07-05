#include "InsertationAlgorithm.h"

int main()
{
    std::vector<int> input_list;
    std::cout << "Please input a string of numbers which you want to recorder" << std::endl;
    int num;
    while (std::cin >> num)
    {
        input_list.push_back(num);
    }

    std::cout << "Your list is :" << std::endl;
    std::cout << "[ ";
    for (int n : input_list) {
        std::cout << n << " ";
    }
    std::cout << "]" << std::endl;

    std::vector<int> output_result;
    InsertationSortDown sort_1(input_list);
    sort_1.sortFunctionDown(output_result);

    std::cout << "The reordered result is :" << std::endl;
    std::cout << "[ ";
    for (int n : output_result) {
        std::cout << n << " ";
    }
    std::cout << "]";


    return 0;
}


