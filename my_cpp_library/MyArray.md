[ cppreference ](https://en.cppreference.com/w/cpp/container/array)   
[ github 참고 자료1 ](https://github.com/ardipazij/s21_containers/blob/main/src/array/array.h)   
[ github 참고 자료1 ](https://github.com/Creris/cpp_array/blob/master/Array.hpp)   

<br><br>

# Implementation

## 1. Member Types
```cpp
using value_type T;
using size_type std::size_t;
```
cppreference의 Member Types를 참고하여 구현했다.   

<br>

## 2. Member Functions
### 2.1. Constructor
```cpp
MyArray(){};
MyArray(const MyArray& other) {
  std::copy(other._array, other._array + N, _array);
}
MyArray(MyArray&& other) {
  std::move(other._array, other._array + N, _array);
}
```

<br>

### 2.2. Overloaded Operators
#### 2.2.1. Copy Assignment Operator
```cpp
MyArray& operator=(const MyArray& other) {
  if (this == &other)
    return *this;

  std::copy(other._array, other._array + N, _array);
  return *this;
}
```
template으로 MyArray의 크기를 N으로 고정시켰기 때문에 this와 other의 크기는 같다.   
```cpp
// before code
if (other._size != _size) {
  value_type temp = new value_type[other._size];
  delete[] _array;
  _array = temp;
  _size = other._size;
}

std::copy(other._array, other._array + other._size, _array);
```
처음에 이러한 사실을 몰라서 크기를 비교하고 이에 따라 새로운 배열을 생성했다.   

<br>

## 3. Member Variables
```cpp
private:
  value_type _array[N];
  // size_type _size = N ? N : 1;
```
### 3.1. Why Avoid Using the `_size` Member Varialbe?
MyArray는 template 매개변수 N을 사용해서 배열의 크기를 고정한다.   
이는 클래스의 `모든 instance가 동일한 타입( T )과 동일한 크기( N )를 가지도록 보장`한다.   
예를 들면, `MyArray<int, 5>`와 `MyArray<int, 10>`은 서로 다른 TYPE으로 취급되며, 서로 대입할 수 없다.   
때문에 MyArray의 크기 변수( `_size` )는 중복되는 정보이기에 `N`을 직접 사용한다.   