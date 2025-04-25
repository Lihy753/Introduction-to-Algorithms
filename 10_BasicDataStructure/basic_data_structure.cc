#include "basic_data_structure.h"



int main()
{
    int n = 9;
    std::vector<int> input(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 100);
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

    queue<9> m_test;
    for (const auto& fi : input)
    {
        m_test.ENQUEUE(fi);
    }

    std::array<int, 9> result;
    m_test.fetch_array(result);
    std::cout << "Begin output deque" << std::endl;
    for (const auto& fi : result)
        std::cout << fi << ", ";
    std::cout << std::endl;

    for (int i = 0; i < n; ++i)
    {
        int del_num = m_test.DEQUEUE();
        std::cout << "delete num : " << del_num << std::endl;
    }
    int head = m_test.head;
    int tail = m_test.tail;

    std::cout << "head : " << head << ", tail : " << tail << std::endl;

    return 0;
}