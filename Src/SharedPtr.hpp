#pragma once

template <class T>
class Wrapper
{
    int counter;
    T*  ptr;

    Wrapper(T* object)
    {
        ptr = object;
    }

    void IncrementCnt()
    {
        counter++;
    }

    void DecrementCnt() 
    { 
        counter--;

        if (counter == 0)
            delete ptr;
    }
};

template <class T>
class SharedPtr
{
    Wrapper<T>* wrapper;

    void reset();

    T operator*  ();
    T* operator()();
    
    SharedPtr<T>& operator=(const SharedPtr<T>& other);
    SharedPtr<T>& operator=(SharedPtr<T>&& other);
    
    SharedPtr(T* object);
    SharedPtr(const SharedPtr<T>& other);
    SharedPtr(SharedPtr<T>&& other);

    ~SharedPtr();
};
