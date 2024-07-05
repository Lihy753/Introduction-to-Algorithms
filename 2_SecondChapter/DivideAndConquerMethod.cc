#include "DivideAndConquerMethod.h"

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
    DivideAndConquerMethod sort_1;
    sort_1.mergeSort(input_list, 0, input_list.size() - 1);

    std::cout << "The reordered result is :" << std::endl;
    std::cout << "[ ";
    for (int n : input_list) {
        std::cout << n << " ";
    }
    std::cout << "]";


    return 0;
}
