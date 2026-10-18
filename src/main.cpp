#include <container/Vector.hpp>

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <random>
#include <stdexcept>
#include <string>
#include <utility>

static_assert(std::random_access_iterator<lab3::Vector<int>::iterator>);
static_assert(std::random_access_iterator<lab3::Vector<int>::const_iterator>);

static_assert(lab3::Numeric<int>);
static_assert(lab3::Numeric<long long>);
static_assert(lab3::Numeric<double>);
static_assert(!lab3::Numeric<bool>);
static_assert(!lab3::Numeric<char>);
static_assert(!lab3::Numeric<std::string>);

template <typename T>
void print(const std::string& name, const lab3::Vector<T>& v)
{
    std::cout << name << ": size=" << v.size() << ", capacity=" << v.capacity() << ", [ ";
    for (const auto& x : v)
        std::cout << x << ' ';
    std::cout << "]\n";
}

void section(const std::string& title)
{
    std::cout << "\n===== " << title << " =====\n";
}

int main()
{
    section("1. Creation and filling (push_back, capacity growth)");

    lab3::Vector<int> v;
    std::cout << "Empty vector: size=" << v.size() << ", capacity=" << v.capacity()
              << ", empty=" << std::boolalpha << v.empty() << '\n';

    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 100);

    for (int i = 0; i < 10; ++i)
    {
        v.push_back(dist(gen));
        std::cout << "push_back -> size=" << v.size() << ", capacity=" << v.capacity() << '\n';
    }
    print("v", v);

    section("2. Element access");

    std::cout << "v[0] = " << v[0] << '\n';
    std::cout << "v.at(3) = " << v.at(3) << '\n';
    std::cout << "v.front() = " << v.front() << '\n';
    std::cout << "v.back() = " << v.back() << '\n';

    v[0] = 0;
    std::cout << "After v[0] = 0: v.front() = " << v.front() << '\n';

    try
    {
        std::cout << v.at(100) << '\n';
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "v.at(100) -> exception: " << e.what() << '\n';
    }

    section("3. Removal (pop_back, erase)");

    print("Before removal", v);
    v.pop_back();
    print("After pop_back()", v);
    v.erase(2);
    print("After erase(2)", v);

    section("4. Copying");

    lab3::Vector<int> copyCtor = v;
    copyCtor[0] = -1;
    print("v (original)", v);
    print("copyCtor ([0] changed)", copyCtor);
    std::cout << "Original is unchanged -> deep copy\n";

    lab3::Vector<int> copyAssign;
    copyAssign.push_back(42);
    copyAssign = v;
    print("copyAssign = v", copyAssign);

    section("5. Moving");

    lab3::Vector<int> moveCtor = std::move(copyCtor);
    print("moveCtor", moveCtor);
    print("copyCtor after move", copyCtor);

    lab3::Vector<int> moveAssign;
    moveAssign = std::move(copyAssign);
    print("moveAssign", moveAssign);
    print("copyAssign after move", copyAssign);

    section("6. clear() and reserve()");

    lab3::Vector<int> r;
    r.reserve(20);
    print("After reserve(20)", r);
    for (int i = 1; i <= 5; ++i)
        r.push_back(i);
    print("After 5 push_back calls", r);
    r.clear();
    print("After clear() (capacity kept)", r);

    section("7. Iterator traversal");

    std::cout << "Forward:  ";
    for (auto it = v.begin(); it != v.end(); ++it)
        std::cout << *it << ' ';
    std::cout << '\n';

    std::cout << "Backward: ";
    for (auto it = v.end(); it != v.begin();)
        std::cout << *--it << ' ';
    std::cout << '\n';

    auto it = v.begin();
    std::cout << "Arithmetic: *(begin + 2) = " << *(it + 2)
              << ", begin[3] = " << it[3]
              << ", end - begin = " << (v.end() - v.begin()) << '\n';

    section("8. std::sort");

    print("Before sort", v);
    std::sort(v.begin(), v.end());
    print("Ascending", v);
    std::sort(v.begin(), v.end(), std::greater<int>());
    print("Descending", v);

    section("9. std::find");

    int target = v[2];
    auto found = std::find(v.begin(), v.end(), target);
    if (found != v.end())
        std::cout << "Element " << target << " found at position " << (found - v.begin()) << '\n';

    auto notFound = std::find(v.begin(), v.end(), 1000);
    std::cout << "Element 1000 " << (notFound == v.end() ? "not found" : "found") << '\n';

    section("10. std::for_each");

    std::for_each(v.begin(), v.end(), [](int& x) { x *= 2; });
    print("After for_each (x *= 2)", v);

    long long sum = 0;
    std::for_each(v.begin(), v.end(), [&sum](int x) { sum += x; });
    std::cout << "Sum of elements via for_each: " << sum << '\n';

    section("11. Vector<double>");

    lab3::Vector<double> d;
    for (double x : {3.14, 2.71, 1.41, 1.73})
        d.push_back(x);
    std::sort(d.begin(), d.end());
    print("d after sort", d);

    return 0;
}