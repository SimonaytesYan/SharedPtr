#pragma once

#include <assert.h>
#include <stdio.h>
#include <type_traits>

#include "Wrapper.hpp"

// #define DUMP_SHARED_PTR

enum SharedPtrType {
    Default,
    Owner
};

template <class T, SharedPtrType Type = Default>
class SharedPtr
{
public:
    void reset()
    {
        reset = true;
        #ifdef DUMP_SHARED_PTR
            printf("SharedPtr reset. Object %p\n", wrapper->GetPtr());
        #endif
        
        wrapper->DecrementCnt();
        if (wrapper->GetCnt() == 0)
            delete wrapper;
    }

    size_t use_count()
    { return wrapper->GetCnt(); }
    
    T* get()
    { return wrapper->ptr; }

    T operator*  ()
    { return *wrapper->GetPtr(); }

    T* operator()()
    { return wrapper->GetPtr(); }

    T* operator->()
    { return wrapper->GetPtr(); }

    SharedPtr<T, Default>& operator=(const SharedPtr<T, Default>& other)
    {
        if (!reset)
        {
            wrapper->DecrementCnt();
            if (wrapper->GetCnt() == 0)
                delete wrapper;
        }

        wrapper = other.wrapper();
        reset   = other.reset;
        if (!reset)
            wrapper->IncrementCnt();
    }

    SharedPtr(T* object) : 
    reset (false)
    {
        wrapper = new Wrapper<T>(object);
        wrapper->IncrementCnt();
    }
    

    SharedPtr(const SharedPtr<T, Default>& other) : 
    reset (other.reset)
    {
        wrapper = other.wrapper;
        if (!reset)
            wrapper->IncrementCnt();
    }

    ~SharedPtr()
    { 
        if (!reset)
        {
            wrapper->DecrementCnt();
            if (wrapper->GetCnt() == 0)
                delete wrapper;
        }
    }

private:    
    Wrapper<T>* wrapper;
    bool        reset;
};

template <class T>
class SharedPtr<T, Owner>
{
public:
    void reset()
    {
        reset = true;
        #ifdef DUMP_SHARED_PTR
            printf("SharedPtr reset. Object %p\n", wrapper->GetPtr());
        #endif
        
        wrapper->DecrementCnt();
        if (wrapper->GetCnt() == 0)
            delete wrapper;
    }

    size_t use_count()
    { return wrapper->GetCnt(); }
    
    T* get()
    { return wrapper->ptr; }

    T operator*  ()
    { return *wrapper->GetPtr(); }

    T* operator()()
    { return wrapper->GetPtr(); }

    T* operator->()
    { return wrapper->GetPtr(); }

    SharedPtr<T, Owner>& operator=(const SharedPtr<T, Owner>& other)
    {
        if (!reset)
        {
            wrapper->DecrementCnt();
            if (wrapper->GetCnt() == 0)
                delete wrapper;
        }

        wrapper = other.wrapper();
        reset   = other.reset;
        if (!reset)
            wrapper->IncrementCnt();
    }

    SharedPtr(const SharedPtr<T, Owner>& other) : 
    reset (other.reset)
    {
        wrapper = other.wrapper;
        if (!reset)
            wrapper->IncrementCnt();
    }

    ~SharedPtr()
    { 
        wrapper->DecrementCnt();
        if (wrapper->GetCnt() == 0)
            delete wrapper;
    }
    

    template <class U, class ...CtorArgsT>
    friend SharedPtr<U, Owner> MakeShared(CtorArgsT&&... CtorArgs);

private:    

    SharedPtr(OwnerWrapper<T>* wrapper) : 
    wrapper (wrapper), 
    reset (false)
    {
        wrapper->IncrementCnt();
    }

    OwnerWrapper<T>* wrapper;
    bool             reset;
};

#include <utility>

template <class T, class ...CtorArgsT>
SharedPtr<T, Owner> MakeShared(CtorArgsT&&... CtorArgs)
{
    return SharedPtr<T, Owner>(new OwnerWrapper<T>(CtorArgs...));
}

