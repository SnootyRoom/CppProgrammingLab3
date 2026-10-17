#pragma once

#include <cstddef>
#include <type_traits>
#include <utility>
#include <stdexcept>

namespace lab3 
{
    template <typename T>
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

        using iterator = T*;
        using const_iterator = const T*;

        iterator begin() {}
        iterator end() {}
        const_iterator begin() const {}
        const_iterator end() const {}
    };
}