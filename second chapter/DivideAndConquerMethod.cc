#include <iostream>
#include <array>
#include <vector>
#include <limits>

class DivideAndConquerMethod
{
public:
    DivideAndConquerMethod(){}

    DivideAndConquerMethod(std::vector<int> list)
    {
        m_list = list;
    }

    ~DivideAndConquerMethod()
    {
        m_list.clear();
    }

    void merge(std::vector<int>& A, int p, int q, int r)
    {
        int n_1 = q - p + 1;
        int n_2 = r - q;
        std::vector<int> L, R;
        L.resize(n_1 + 1);
        R.resize(n_2 + 1);
        for (int i = 0; i < L.size() - 1; ++i)
            L[i] = A[p + i];

        for (int j = 0; j < R.size() - 1; ++j)
            R[j] = A[q + j + 1];

        L[n_1] = std::numeric_limits<int>::max();
        R[n_2] = std::numeric_limits<int>::max();

        int count_i = 0,  count_j = 0;

        for (int k = p; k < r + 1; ++k)
        {
            if (L[count_i] < R[count_j])
            {
                A[k] = L[count_i];
                count_i++;
            }
            else
            {
                A[k] = R[count_j];
                count_j++;
            }
        }
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
    DivideAndConquerMethod sort_1;
    sort_1.merge(input_list, 0, 3, 5);

    std::cout << "The reordered result is :" << std::endl;
    std::cout << "[ ";
    for (int n : input_list) {
        std::cout << n << " ";
    }
    std::cout << "]";


    return 0;
}
