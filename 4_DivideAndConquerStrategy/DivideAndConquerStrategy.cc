#include "DivideAndConquerStrategy.h"


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
    int size = input_list.size() - 1;
    std::array<int, 3> output_result;
    maxSunarrayProblem sort_1(input_list);
    output_result = sort_1.findMaximumSubarray(0, size);

    std::cout << "The reordered result is :" << std::endl;
    std::cout << "max_left = " << output_result[0] << ", max_right = " << output_result[1] << ", max_value = " << output_result[2];
    return 0;
}