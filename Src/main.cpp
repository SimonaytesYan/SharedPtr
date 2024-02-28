#include "SharedPtr.hpp"

void TestSharedPtr()
{
    int* array = new int[100];
    for (int i = 0; i < 100; i++)
        array[i] = 100 - i;

    
}

int main()
{
    TestSharedPtr();
}
