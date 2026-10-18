#pragma once
#include "VectorIterator.hpp"
#include "Numeric.hpp"
#include <cstddef>
#include <type_traits>
#include <utility>
#include <stdexcept>
#include <memory>

namespace lab3 
{
    template <Numeric T>
    class Vector
    {
    private:
        T* data_ = nullptr;
        std::size_t size_ = 0;
        std::size_t capacity_ = 0;

        void reallocate(std::size_t newCapacity)
        {
            T* newData = static_cast<T*>(::operator new(newCapacity * sizeof(T)));

            for (std::size_t i = 0; i < size_; ++i)
            {
                std::construct_at(newData + i, std::move(data_[i])); 
                std::destroy_at(data_ + i);                             
            }

            ::operator delete(data_); 

            data_ = newData;
            capacity_ = newCapacity;
        }

    public:
        explicit Vector() = default;

        Vector(Vector&& other) noexcept : data_(std::exchange(other.data_, nullptr)),
              size_(std::exchange(other.size_, 0)),
              capacity_(std::exchange(other.capacity_, 0)) {}


        Vector(const Vector& other) : size_(other.size_), capacity_(other.size_)
        {
            if (capacity_ > 0)
            {
                data_ = static_cast<T*>(::operator new(capacity_ * sizeof(T)));
                for (std::size_t i = 0; i < size_; ++i)
                    std::construct_at(data_ + i, other.data_[i]);
            }
        }

        ~Vector() 
        {
            clear();                
            ::operator delete(data_);
        }
    
        Vector& operator=(const Vector& other)
        {
            if (this != &other)        
            {
                Vector copy(other);    
                swap(copy);            
            }                         
            return *this;
        }

        Vector& operator=(Vector&& other) noexcept(std::is_nothrow_move_assignable_v<T>)
        {
            if (this != &other)
            {
                clear();
                ::operator delete(data_);

                data_     = std::exchange(other.data_, nullptr);
                size_     = std::exchange(other.size_, 0);
                capacity_ = std::exchange(other.capacity_, 0);
            }
            return *this;
        }

         void swap(Vector& other) noexcept
        {
            std::swap(data_, other.data_);
            std::swap(size_, other.size_);
            std::swap(capacity_, other.capacity_);
        }

        void reserve(std::size_t newCapacity)
        {
            if (newCapacity > capacity_)
                reallocate(newCapacity);
        }
    

        std::size_t size() const noexcept {return size_;}

        std::size_t capacity() const noexcept {return capacity_;}

        bool empty() const noexcept {return size_ == 0;}
    
        void push_back(const T& value)
        {
            if (size_ == capacity_)
            {
                T copy = value;
                reallocate(capacity_ == 0 ? 1 : capacity_ * 2);
                std::construct_at(data_ + size_, std::move(copy));
            }
            else
            {
                std::construct_at(data_ + size_, value); 
            }

            ++size_;
        }

        void pop_back() 
        {
             if (empty())
                throw std::out_of_range("Vector::pop_back: vector is empty");
            --size_;
            std::destroy_at(data_ + size_);  
        }

        void erase(size_t index)
        {
            if (index >= size_)
                throw std::out_of_range("Vector::erase: index out of range");

            for (std::size_t i = index; i + 1 < size_; ++i)
                data_[i] = std::move(data_[i + 1]);

            --size_;
            std::destroy_at(data_ + size_); 
        }

        void clear() 
        {
            for (std::size_t i = 0; i < size_; ++i)
            std::destroy_at(data_ + i);
            size_ = 0;
        }

        T& operator[](size_t index) {return data_[index];}
        const T& operator[](size_t index) const {return data_[index];}

        T& at(std::size_t index)
        {
            if (index >= size_)
                throw std::out_of_range("Vector::at: index out of range");
            return data_[index];
        }

        const T& at(std::size_t index) const
        {
            if (index >= size_)
                throw std::out_of_range("Vector::at: index out of range");
            return data_[index];
        }

        T& front() { return data_[0]; }
        const T& front() const { return data_[0]; }
        T& back() { return data_[size_ - 1]; }
        const T& back() const { return data_[size_ - 1]; }

        using iterator       = VectorIterator<T>;
        using const_iterator = VectorIterator<const T>;

        iterator begin() noexcept { return iterator(data_); }
        iterator end() noexcept { return iterator(data_ + size_); }

        const_iterator begin() const noexcept { return const_iterator(data_); }
        const_iterator end() const noexcept { return const_iterator(data_ + size_); }
    };
}