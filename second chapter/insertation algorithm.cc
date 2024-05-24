#include <iostream>
#include <list>
#include <vector>


//插入排序算法
class InsertationSort
{
public:
    InsertationSort(std::vector<int> list)
    {
        m_list = list;
    };

    ~InsertationSort()
    {
        m_list.clear();
    };

    void sortFunction(std::vector<int>& result)
    {
        result.clear();
        for (int j = 1; j < m_list.size(); ++j)
        {
            int key = m_list[j];
            int i = j -1;
            while(i > -1 && m_list[i] > key)
            {
                m_list[i+1] = m_list[i];
                --i;
            }
            m_list[i + 1] = key;

        }
        result = m_list;
    }

public:
    std::vector<int> m_list;
};

//练习 2.1-2 按照非升序排序
class InsertationSortDown
{
public:
    InsertationSortDown(std::vector<int>& list)
    {
        m_list = list;
    }

    ~InsertationSortDown()
    {
        m_list.clear();
    }

    void sortFunctionDown(std::vector<int>& result)
    {
        result.clear();
        for (int j = 1; j < m_list.size(); ++j)
        {
            int key = m_list[j];
            int i = j -1;
            while(i > -1 && m_list[i] < key)
            {
                m_list[i+1] = m_list[i];
                --i;
            }
            m_list[i + 1] = key;

        }
        result = m_list;
    }

public:
    std::vector<int> m_list;
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


