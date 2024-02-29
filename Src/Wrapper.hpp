#pragma once

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
    { ptr->~T(); }

    void IncrementCnt()
    { counter++; }

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

protected:
    size_t counter;
    T*  ptr;
};

template <class T>
class OwnerWrapper
{
public:

    OwnerWrapper() 
    {
        printf("Object %p owner wrapper() lifetime\n", &object);
    }

    OwnerWrapper(T new_object) :
    object (new_object) 
    {
        printf("Object %p owner wrapper (object) lifetime\n", &object);
    }

    ~OwnerWrapper()
    { }

    void IncrementCnt()
    { counter++; }

    void DecrementCnt()
    { 
        assert(counter > 0);
        counter--;
    }

    size_t GetCnt()
    { return counter; }

    T* GetPtr()
    { return &object; }

protected:
    size_t counter;
    T      object;
};
