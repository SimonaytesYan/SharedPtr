#include "SharedPtr.hpp"

template <class T>
void SharedPtr<T>::reset()
{
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
    wrapper.DecrementCnt();
}
