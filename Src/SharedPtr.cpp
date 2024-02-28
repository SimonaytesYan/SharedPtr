#include "SharedPtr.hpp"

template <class T>
void SharedPtr<T>::reset()
{
    wrapper->DecrementCnt();
}

template <class T>
T SharedPtr<T>::operator*()
{
    return *object.ptr;
}

template <class T>
T* SharedPtr<T>::operator() ()
{
    return object.ptr;
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
