#pragma once

template <class T>
class Wrapper
{
public:
    Wrapper(T* object)
    {
        ptr = object;
        #ifdef DUMP_SHARED_PTR
            printf("Object %p wrapper lifetime\n", ptr);
        #endif
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
            #ifdef DUMP_SHARED_PTR
                printf("Object %p end lifetime\n", ptr);
            #endif

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
        #ifdef DUMP_SHARED_PTR
            printf("Object %p owner wrapper() lifetime\n", &object);
        #endif
    }

    OwnerWrapper(T new_object) :
    object (new_object) 
    {
        #ifdef DUMP_SHARED_PTR
            printf("Object %p owner wrapper (object) lifetime\n", &object);
        #endif
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
