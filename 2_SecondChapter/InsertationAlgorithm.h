#ifndef INSERTATIONALGORITHM_H
#define INSERTATIONALGORITHM_H

#include <iostream>
#include <list>
#include <vector>


//插入排序算法
class InsertationSort
{
public:
    InsertationSort(std::vector<int> vector)
    {
        m_vector = vector;
    };

    InsertationSort(std::list<float> list)
    {
        m_list = list;
    }


    ~InsertationSort()
    {
        m_vector.clear();
        m_list.clear();
    };

    void sortFunction(std::vector<int>& result)
    {
        result.clear();
        for (int j = 1; j < m_vector.size(); ++j)
        {
            int key = m_vector[j];
            int i = j -1;
            while(i > -1 && m_vector[i] > key)
            {
                m_vector[i+1] = m_vector[i];
                --i;
            }
            m_vector[i + 1] = key;

        }
        result = m_vector;
    }

    void sortFunction(std::list<float>& result)
    {
        result.clear();
        for (auto it = std::next(m_list.begin()); it != m_list.end(); ++it)
        {
            float key = *it;
            auto prev_it  = it;
            if (prev_it != m_list.begin())
            {
                --prev_it;
            }
            while(prev_it != m_list.begin() && *prev_it > key)
            {
                std::iter_swap(std::next(prev_it), prev_it);
                --prev_it;
            }
            if (prev_it == m_list.begin() && *prev_it > key)
            {
                std::iter_swap(std::next(prev_it), prev_it);
                // *prev_it = key;
            }
        }
        result = m_list;
    }

    

public:
    std::vector<int> m_vector;
    std::list<float> m_list;

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

#endif