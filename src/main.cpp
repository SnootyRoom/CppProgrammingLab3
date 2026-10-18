#include <container/VectorIterator.hpp>
#include <algorithm>
#include <iostream>
#include <iterator>

static_assert(std::random_access_iterator<lab3::VectorIterator<int>>);
static_assert(std::random_access_iterator<lab3::VectorIterator<const int>>);

int main()
{
    int arr[] = {5, 3, 1, 4, 2};
    lab3::VectorIterator<int> first(arr), last(arr + 5);

    std::sort(first, last);

    for (auto it = first; it != last; ++it)
        std::cout << *it << ' ';
    std::cout << '\n';
}