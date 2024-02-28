#include "SharedPtr.hpp"

class MyClass
{
    public:
    MyClass() 
    { 
        printf("My class %p constructor\n", this); 
    }

    ~MyClass() 
    { 
        printf("My class %p destructor\n", this); 
    }
};

void TestSharedPtr()
{
    MyClass class_ex;

    SharedPtr<MyClass> array2(&class_ex);
    array2.reset();

    printf("End test\n");
}

int main()
{
    TestSharedPtr();
}
