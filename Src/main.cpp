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

class MyClass2
{
    public:
    MyClass2(int n) 
    { 
        printf("My class 2 (%d) %p constructor\n", n, this); 
    }

    ~MyClass2() 
    { 
        printf("My class 2 %p destructor\n", this); 
    }
};

void TestSharedPtr()
{
    MyClass class_ex;

    SharedPtr<MyClass> array2(&class_ex);
    array2.reset();

    printf("End test\n");
}

void TestMakeShared()
{
    SharedPtr<MyClass2, Owner> array2(make_shared<MyClass2, int>(10));
    array2.reset();

    printf("End test\n");
}

int main()
{
    printf("TEST SHARED PTR\n");
    TestSharedPtr();
    printf("============================\n");
    printf("TEST MAKE SHARED\n");
    TestMakeShared();
}
