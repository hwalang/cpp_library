#pragma once
#include <iostream>
#include <cstddef>
#include <algorithm>

template <class T, std::size_t N>
class MyArray {
public:
  using value_type = T;
  using size_type = std::size_t;

public:
  MyArray() : _array{} { 
    std::cout << "call MyArray(): ";
    for (int i = 0; i < N; ++i) {
      std::cout << _array[i] << " ";
    }
    std::cout << '\n';
  };
  MyArray(const MyArray& other) {
    std::cout << "call MyArray(const MyArray& other)" << '\n';
    std::copy(other._array, other._array + N, _array);
  }
  MyArray(MyArray&& other) {
    std::cout << "call MyArray(MyArray&& other)" << '\n';
    std::move(other._array, other._array + N, _array);
  }
  ~MyArray() {
    std::cout << "call ~MyArray()" << '\n';
  }

  /*---------------------------------------------------------------*/

  MyArray& operator=(const MyArray& other) {
    if (this == &other)
      return *this;

    std::copy(other._array, other._array + N, _array);
    return *this;
  }

  value_type& operator[](size_type pos) { return _array[pos]; }
  constexpr size_type size() const noexcept { return N; }

private:
  value_type _array[N];
  // size_type _size = N ? N : 1;
};