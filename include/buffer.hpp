#include <stddef.h>

template <typename T>
class Buffer {
    public:
        Buffer<T>(size_t size);
        ~Buffer<T>();
        const size_t& size();
        void clear();
        T& operator[](size_t idx);
        const T& operator[](size_t idx) const;
    private:
        T* m_array;
        const size_t m_size;
};
