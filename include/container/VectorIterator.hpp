#pragma once

#include <iterator>
#include <cstddef>
#include <type_traits>
#include <compare>


namespace lab3
{
    template<typename T>
    class VectorIterator  
    { 
        private: 
            T* ptr_ = nullptr; 
        public: 
            using value_type = std::remove_cv_t<T>; 
            using difference_type = std::ptrdiff_t; 
            using pointer = T*; 
            using reference = T&; 
            using iterator_category = std::random_access_iterator_tag;

            VectorIterator() noexcept = default;

            explicit VectorIterator(T* ptr) : ptr_(ptr) {} 

            reference operator*() const  { return *ptr_; } 

            pointer operator->() const noexcept {return ptr_;}

            reference operator[](difference_type n) const noexcept { return *(ptr_ + n); }

            VectorIterator& operator++()  { ++ptr_; return *this; }

            VectorIterator operator++(int) noexcept { VectorIterator temp{*this}; ++ptr_; return temp; }
            
            VectorIterator& operator--() { --ptr_; return *this; }

            VectorIterator operator--(int) noexcept { VectorIterator temp{*this}; --ptr_; return temp; }

            VectorIterator& operator+=(difference_type n) noexcept {ptr_ += n; return *this;}
            VectorIterator& operator-=(difference_type n) noexcept {ptr_ -= n; return *this;}

            VectorIterator operator+(difference_type n) const noexcept {VectorIterator temp{*this}; return temp += n;}
            VectorIterator operator-(difference_type n) const noexcept {VectorIterator temp{*this}; return temp -= n;}
            friend VectorIterator operator+(difference_type n, const VectorIterator& it) noexcept {return it + n;}

            difference_type operator-(const VectorIterator& other) const noexcept {return ptr_ - other.ptr_;}

            auto operator<=>(const VectorIterator&) const noexcept = default;

    }; 
}