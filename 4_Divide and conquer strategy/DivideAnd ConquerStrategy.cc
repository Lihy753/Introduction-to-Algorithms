#include <iostream>
#include <limits>
#include <stdexcept>
#include <array>

//最大子数组问题
template<size_t Size>
class maxSunarrayProblem
{
public:
    maxSunarrayProblem(std::array<int, Size>& array) : m_array(array) {}

    std::array<int, 3> findMaxCrossingSubarray(int low, int mid, int high)
    {
        if (!(low <= mid && mid <= high))
            throw std::invalid_argument("The input sequence of low, mid and high is wrong");

        int left_sum = std::numeric_limits<int>::min();
        int sum_1 = 0;
        int max_left = 0;
        int max_right = high;
        for (int i = mid; i != low - 1; --i)
        {
            sum_1 = sum_1 + m_array[i];
            if (sum_1 > left_sum)
            {
                left_sum = sum_1;
                max_left = i;
            }
        }

        int right_sum = std::numeric_limits<int>::min();
        int sum_2 = 0;
        for (int j = mid + 1; j != high + 1; ++j)
        {
            sum_2 = sum_2 + m_array[j];
            if (sum_2 > right_sum)
            {
                right_sum = sum_2;
                max_right = j;
            }
        }

        return std::array<int, 3>{max_left, max_right, left_sum + right_sum};
        
    }

private:
    std::array<int, Size> m_array;
};


int main()
{

    return 0;
}
