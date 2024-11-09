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
MyArray() : _array{} {};
MyArray(const MyArray& other) {
  std::copy(other._array, other._array + N, _array);
}
MyArray(MyArray&& other) {
  std::move(other._array, other._array + N, _array);
}
```
default constructor에서 T의 TYPE에 따라 default value로 초기화한다.   
T가 class type이라면 각 요소의 default consructor가 자동으로 호출되지만, primitive type이라면 각 요소들이 초기화되지 않아서 garbage value을 가진다.   
이 문제점은 [Value Initialization](/Concept/ValueInitialization.md)을 이용해서 해결했다.   
`: _array{}`는 _array를 value initialization하며, class type은 default consructor를 호출하고 primitive type은 각 elements가 0으로 초기화한다.   



### 2.2. De-constructor
```cpp
~MyArray() {
  // delete[] _array;
};
```
처음에는 _array를 동적 배열과 착각하여 memory leak을 방지하기 위해 _array의 memory를 해제했다.   
하지만 에러가 발생하여 로그를 추적해보니 정적 배열이기 때문에 memory를 해제하면 런타임 에러가 발생했다.   
`정적 배열은 stack 또는 member variable에 저장되기 때문에 instance가 소멸될 때 자동으로 해제`된다.   

<br>

### 2.3. Overloaded Operators
#### 2.3.1. Copy Assignment Operator
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

#### 2.3.2. Subscript Operator
```cpp
value_type& operator[](size_type pos) { return _array[pos]; }
```

<br>

### 2.4. Capacity
```cpp
constexpr bool empty() const noexcept { return N == 0; }
constexpr size_type size() const noexcept { return N; }
```
변수 N의 TYPE은 `std::size_t`고, `typedef unsigned long long`를 나타내기 때문에 양수 값만 가진다.   
이 점을 이용해서 emtpy()는 N == 0이면 true를 반환했다.   

<br>

## 3. Member Variables
```cpp
private:
  value_type _array[N];
  // size_type _size = N ? N : 1;
```
### 3.1. Why Avoid Using the `_size` Member Variable?
MyArray는 template 매개변수 N을 사용해서 배열의 크기를 고정한다.   
이는 클래스의 `모든 instance가 동일한 타입( T )과 동일한 크기( N )를 가지도록 보장`한다.   
예를 들면, `MyArray<int, 5>`와 `MyArray<int, 10>`은 서로 다른 TYPE으로 취급되며, 서로 대입할 수 없다.   
때문에 MyArray의 크기 변수( `_size` )는 중복되는 정보이기에 `N`을 직접 사용한다.   