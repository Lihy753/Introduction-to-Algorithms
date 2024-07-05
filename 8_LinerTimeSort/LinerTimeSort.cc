#include "LinerTimeSort.h"




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