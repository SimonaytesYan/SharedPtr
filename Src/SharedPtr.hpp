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
        ptr->~T();
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
            ptr->~T();
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
public:
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
    
private:
    Wrapper<T>* wrapper;
};

template <class T>
void SharedPtr<T>::reset()
{
    printf("SharedPtr reset. Object %p\n", wrapper->GetPtr());
    wrapper->DecrementCnt();
}

template <class T>
size_t SharedPtr<T>::use_count()
{
    return wrapper->GetCnt();
}

template <class T>
T* SharedPtr<T>::get()
{
    return wrapper->ptr;
}

template <class T>
T SharedPtr<T>::operator*()
{
    return *wrapper->GetPtr();
}

template <class T>
T* SharedPtr<T>::operator() ()
{
    return wrapper->GetPtr();
}

template <class T>
SharedPtr<T>::SharedPtr(T* object)
{
    wrapper = new Wrapper<T>(object);
    wrapper->IncrementCnt();
}

template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other)
{
    other.wrapper = wrapper;
    wrapper->IncrementCnt();
}

template <class T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other)
{
    wrapper = other.wrapper;
    wrapper->IncrementCnt();
}

template <class T>
SharedPtr<T>::~SharedPtr()
{
    wrapper->DecrementCnt();
}
