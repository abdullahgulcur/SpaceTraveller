#include <cstddef>
#include <initializer_list>
#include <algorithm>

template<typename T, std::size_t N>
class StaticArray {
public:
    
    using size_type = std::size_t;
    using reference = T&;
    using const_reference = const T&;
    using iterator = T*;
    using const_iterator = const T*;

    StaticArray() : m_size(0) {}

    StaticArray(std::initializer_list<T> init) {
        std::copy(init.begin(), init.end(), m_data);
    }

    reference operator[](size_type index) {
        return m_data[index];
    }

    const_reference operator[](size_type index) const {
        return m_data[index];
    }

    reference at(size_type index) {
        return m_data[index];
    }

    const_reference at(size_type index) const {
        return m_data[index];
    }

    reference front() {
        return m_data[0];
    }

    const_reference front() const {
        return m_data[0];
    }

    reference back() {
        return m_data[m_size - 1];
    }

    const_reference back() const {
        return m_data[m_size - 1];
    }

    void push(T element) {
        m_data[m_size++] = element;
    }

    //void push(T& element) {
    //    m_data[m_size++] = element;
    //}

    void pop() {
        m_size--;
    }

    void clean() {
        m_size = 0;
    }

    T* data() noexcept { return m_data; }
    const T* data() const noexcept { return m_data; }

    iterator begin() noexcept { return m_data; }
    const_iterator begin() const noexcept { return m_data; }
    const_iterator cbegin() const noexcept { return m_data; }

    iterator end() noexcept { return m_data + m_size; }
    const_iterator end() const noexcept { return m_data + m_size; }
    const_iterator cend() const noexcept { return m_data + m_size; }

    constexpr size_type size() const noexcept { return m_size; }
    constexpr size_type capacity() const noexcept { return N; }
    constexpr bool empty() const noexcept { return m_size == 0; }

    // Modifiers
    void fill(const T& value) {
        std::fill(begin(), end(), value);
    }

private:
    T m_data[N];
    std::size_t m_size;
};


// Boolean Container

template<std::size_t N>
class StaticArray<bool, N> {
public:
    using size_type = std::size_t;

private:
    static constexpr size_type bits_per_block = 64;
    static constexpr size_type block_count = (N + bits_per_block - 1) / bits_per_block;

    uint64_t m_data[block_count]{};
    size_type m_size = 0;

public:
    StaticArray() = default;

    StaticArray(size_type size) {
        for (int i = 0; i < size; i++)
            set(i, false);
        m_size = size;
    }

    StaticArray(size_type size, bool value) {
        for (int i = 0; i < size; i++)
            set(i, value);
        m_size = size;
    }

    StaticArray(std::initializer_list<bool> init) {
        for (bool value : init) {
            push(value);
        }
    }

    // Fast explicit access
    bool get(size_type index) const {
        return (m_data[index / bits_per_block] >> (index % bits_per_block)) & 1;
    }

    void set(size_type index, bool value) {
        if (value)
            m_data[index / bits_per_block] |= (1 << (index % bits_per_block));
        else
            m_data[index / bits_per_block] &= ~(1 << (index % bits_per_block));
    }

    bool front() const {
        return get(0);
    }

    bool back() const {
        return get(m_size - 1);
    }

    void push(bool value) {
        if (value)
            m_data[m_size / bits_per_block] |= (1 << (m_size % bits_per_block));
        else
            m_data[m_size / bits_per_block] &= ~(1 << (m_size % bits_per_block));
        ++m_size;
    }

    void pop() {
        if (m_size > 0)
            --m_size;
    }

    void clean() {
        std::fill(std::begin(m_data), std::end(m_data), 0);
        m_size = 0;
    }

    void fill(bool value) {
        std::fill(std::begin(m_data), std::end(m_data), value ? 0xFF : 0x00);
    }

    constexpr size_type size() const noexcept { return m_size; }
    constexpr size_type capacity() const noexcept { return N; }
    constexpr bool empty() const noexcept { return m_size == 0; }
};