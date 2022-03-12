#include <algorithm>

#include "buffer.hpp"

template <typename T>
Buffer<T>::Buffer(size_t size):
    m_size(size) {
    m_array = new T[m_size];
    clear();
}

template <typename T>
Buffer<T>::~Buffer<T>(){
    delete[] m_array;
}

template<typename T>
const size_t& Buffer<T>::size(){
    return m_size;
}

template <typename T>
void Buffer<T>::clear(){
    std::fill(m_array, m_array+m_size, T());
}

template <typename T>
T& Buffer<T>::operator[](size_t idx){
    return m_array[idx];
}

template <typename T>
const T& Buffer<T>::operator[](size_t idx) const{
    return m_array[idx];
}

//Explicit instantiation
template class Buffer<double>;
