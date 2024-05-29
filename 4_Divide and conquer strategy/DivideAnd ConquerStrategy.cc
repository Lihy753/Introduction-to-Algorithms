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
        int sum = 0;
        int max_left = 0;
        for (int i = mid; i != low - 1; --i)
        {
            sum = sum + m_array[i];
            if (sum > left_sum)
            {
                left_sum = sum;
                max_left = i;
            }
        }
    }


private:
    std::array<int, Size> m_array;
};


int main()
{

    return 0;
}
