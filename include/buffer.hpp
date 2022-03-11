template <typename T>
class Buffer {
    public:
        Buffer<T>(size_t size);
        ~Buffer<T>();
        void clear();
        T& operator[](size_t idx);
        const T& operator[](size_t idx) const;
    private:
        T* m_array;
        const size_t m_size;
};
