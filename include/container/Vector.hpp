#pragma once
#include "VectorIterator.hpp"
#include "Numeric.hpp"
#include <cstddef>
#include <type_traits>
#include <utility>
#include <stdexcept>

namespace lab3 
{
    template <Numeric T>
    class Vector
    {
    private:
        *T data_ = nullptr;
        std::size_t size_ = 0;
        std::size_t capacity_ = 0;

        void reallocate(std::size_t newCapacity);

    public:
        explicit Vector();
        Vector(Vector&& other) noexcept
        Vector(const Vector&);
        ~Vector();
    
        Vector& operator=(const Vector& other);
        Vector& operator=(Vector&& other) noexcept(std::is_nothrow_move_assignable_v<T>);
    

        size_t size() const;
        size_t capacity() const;
        bool isEmpty() const;
    
        void push_back(const T& value)
        void pop_back();
        void erase(size_t index)
        void clear();

        T& operator[](size_t index);
        const T& operator[](size_t index) const;

        using iterator       = VectorIterator<T>;
        using const_iterator = VectorIterator<const T>;

        iterator begin() noexcept { return iterator(data_); }
        iterator end() noexcept { return iterator(data_ + size_); }

        const_iterator begin() const noexcept { return const_iterator(data_); }
        const_iterator end() const noexcept { return const_iterator(data_ + size_); }
    };
}