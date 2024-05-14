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

    SharedPtr<T, Default>& operator=(const SharedPtr<T, Default>& other)
    {
        other.wrapper = wrapper;
        wrapper->IncrementCnt();
    }

    SharedPtr(T* object)
    {
        wrapper = new Wrapper<T>(object);
        wrapper->IncrementCnt();
    }

    SharedPtr(const SharedPtr<T, Default>& other)
    {
        wrapper = other.wrapper;
        wrapper->IncrementCnt();
    }

    ~SharedPtr()
    { 
        wrapper->DecrementCnt();
        if (wrapper->GetCnt() == 0)
            delete wrapper;
    }

private:    
    Wrapper<T>* wrapper;
};

template <class T>
class SharedPtr<T, Owner>
{
public:
    void reset()
    {
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

    SharedPtr<T, Default>& operator=(const SharedPtr<T, Default>& other)
    {
        other.wrapper = wrapper;
        wrapper->IncrementCnt();
    }

    SharedPtr(const SharedPtr<T, Default>& other)
    {
        wrapper = other.wrapper;
        wrapper->IncrementCnt();
    }

    ~SharedPtr()
    { 
        wrapper->DecrementCnt();
        if (wrapper->GetCnt() == 0)
            delete wrapper;
    }
    

    template <class U, class ...CtorArgsT>
    friend SharedPtr<U, Owner> make_shared(CtorArgsT... CtorArgs);

private:    

    SharedPtr(OwnerWrapper<T>* wrapper) : 
    wrapper (wrapper)
    {}

    OwnerWrapper<T>* wrapper;
};

template <class T, class ...CtorArgsT>
SharedPtr<T, Owner> make_shared(CtorArgsT... CtorArgs)
{
    return SharedPtr<T, Owner>(new OwnerWrapper<T>(T(CtorArgs...)));
}

