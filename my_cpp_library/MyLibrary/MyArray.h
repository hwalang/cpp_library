#pragma once
#include <cstddef>
#include <algorithm>

template <class T, std::size_t N>
class MyArray {
public:
  using value_type = T;
  using size_type = std::size_t;

public:
  MyArray(){};
  MyArray(const MyArray& other) {
    std::copy(other._array, other._array + N, _array);
  }
  MyArray(MyArray&& other) {
    std::move(other._array, other._array + N, _array);
  }

  MyArray& operator=(const MyArray& other) {
    if (this == &other)
      return *this;

    std::copy(other._array, other._array + N, _array);
    return *this;
  }

private:
  value_type _array[N];
  // size_type _size = N ? N : 1;
};