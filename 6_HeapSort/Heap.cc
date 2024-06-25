#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <array>




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

    void MAX_HEAPIFY()
    {
        
    }
};

int main()
{

}