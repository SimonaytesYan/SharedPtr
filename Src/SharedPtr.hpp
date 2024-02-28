#pragma once

#include <assert.h>
#include <stdio.h>

template <class T>
class Wrapper
{
    
public:
    Wrapper(T* object)
    {
        ptr = object;
        printf("Object %p wrapper lifetime\n", ptr);
    }

    ~Wrapper()
    {
        // ??
    }

    void IncrementCnt()
    {
        counter++;
    }

    void DecrementCnt() 
    { 
        assert(counter > 0);
        counter--;

        if (counter == 0)
        {
            printf("Object %p end lifetime\n", ptr);
            delete ptr; //???
        }
    }

    size_t GetCnt()
    { return counter; }

    T* GetPtr()
    { return ptr; }

private:
    size_t counter;
    T*  ptr;
};

template <class T>
class SharedPtr
{
    Wrapper<T>* wrapper;

    void   reset();
    size_t use_count();
    T*     get();

    T operator*  ();
    T* operator()();
    
    SharedPtr<T>& operator=(const SharedPtr<T>& other);
    SharedPtr<T>& operator=(SharedPtr<T>&& other);
    
    SharedPtr(T* object);
    SharedPtr(const SharedPtr<T>& other);
    SharedPtr(SharedPtr<T>&& other);

    ~SharedPtr();
};
