#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <array>



template <typename Size>
class heap
{
public:
    int PARENT(int i)
    {
        return std::floor(i/2);
    }

    int LEFT(int i)
    {
        return (2 * i);
    }

    int RIGHT(int i)
    {
        return (2 * i + 1);
    }

    void MAX_HEAPIFY(std::array<int, Size> A, int i)
    {
        int l = LEFT(i);
        int r = RIGHT(i);
        int length = Size;
        int largest = 0;
        if (l <= length && A[l] > A[i])
            largest = l;
        else
            largest =i;
        
        if (largest != i)
        {
            std::swap(A[largest], A[i]);
            MAX_HEAPIFY(A, largest);
        }
    }
};

int main()
{

}