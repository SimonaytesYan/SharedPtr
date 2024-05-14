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
    MyClass2()
    {} 

    MyClass2(int n) 
    { 
        printf("My class 2 (%d) %p constructor\n", n, this); 
    }

    ~MyClass2() 
    { 
        printf("My class 2 %p destructor\n", this); 
    }
};

struct MyClass3
{
    public:
    MyClass3()
    {}

    MyClass3(int n) :
    value (n) 
    {  
    }

    ~MyClass3() 
    { 
    }

    int value;
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
    SharedPtr<MyClass2, Owner> array2(MakeShared<MyClass2, int>(10));
    array2.reset();

    printf("End test\n");
}

void Test()
{
    MyClass3 my_class(10);
    SharedPtr<MyClass3> ptr(&my_class);
    ptr->value = 11;

    printf("my_class.value = %d\n", my_class.value);
}

int main()
{
    printf("TEST SHARED PTR\n");
    TestSharedPtr();
    printf("============================\n");
    printf("TEST MAKE SHARED\n");
    TestMakeShared();
    printf("============================\n");
    printf("TEST\n");
    Test();
}
