- [Operator Overloading](#operator-overloading)
  - [1. Overloaded Operators](#1-overloaded-operators)
    - [1.1. `member function` vs `non-member function`](#11-member-function-vs-non-member-function)
    - [1.2. `Examples` : Overloaded Operators](#12-examples--overloaded-operators)
    - [1.3. Copy and Move Assignment Operator](#13-copy-and-move-assignment-operator)

<br><br>

[ cppreference - operator overloading ](https://en.cppreference.com/w/cpp/language/operators)   
# Operator Overloading
C++에는 6가지 종류의 operator functions가 존재한다. 그 중 `overloaded operators`에 대해 알아본다.   

## 1. Overloaded Operators
Class나 Struct에 대해 operator overloading으로 해당 TYPE의 Object 간에 연산을 수행할 수 있다.   

### 1.1. `member function` vs `non-member function`
C++에서 overloaded operators를 `member function`과 `non-member function`으로 나눠서 정의한다.   
```cpp
class Complex {
public:
  double real, imag;
  Complex(double r = 0, double i = 0) : real(r), imag(i) {}

  Complex operator- (const Complex& other) const {
    return Complex(real + other.real, imag + other.imag);
  }
};

Complex operator+ (const Complex& a, const Complex& b) {
  return Complex(a.real + b.real, a.imag + b.imag);
}
```
첫 번째 operand가 해당 Class의 Object인 경우 주로 member function이 사용되며, 해당 Class의 Object가 아닌 경우 non-member function을 사용한다.   
만약 a가 Complex가 아닌 다른 TYPE인 경우, compiler가 non-member function을 탐색하여 알맞은 함수를 선택한다.   
 
### 1.2. `Examples` : Overloaded Operators

| Expression | As member function | As non-member function | Example |
|:---:|:---:|:---:|:---:|
| @a | (a).operator@ () | operator@ (a) | `!std::cin` calls `std::cin.operator!()` |
| a @ b | (a).operator@ (b) | operator@ (a, b) | `std::cout << 42` calls `std::cout.operator<<(42)` |
| a@ | (a).operator@ (0) | operator@ (a, 0) | Given `std::vector<int>::iterator i;`, `i++` calls `i.operator++(0)` |

이외에도 다양한 종류의 operators를 overloading 할 수 있다.   
참고로 4가지 종류의 operators는 non-member function으로 존재할 수 없다.   

| Expression | As member function | As non-member function | Example |
|:---:|:---:|:---:|:---:|
| a = b | (a).operator= (b) | `cannot` | Given `std::string s;`, `s = "abc";` calls `s.operator=("abc")` |
| a(b...) | (a).operator()(b...) | `cannot` | Given `std::random_device r;`, `auto n = r()";` calls `r.operator()()` |
| a[b...] | (a).operator[](b...) | `cannot` | Given `std::map<int, int> m;`, `m[1] = 2;` calls `m.operator[](1)` |
| a-> | (a).operator-> () | `cannot` | Given `std::unique_ptr<S> p;`, `p->bar()";` calls `p.operator->()` |

```cpp
std::string str = "Hello, ";
str.operator+=("world");    // same as str += "world";
operator<<(operator<<(std::cout, str), '\n');   // same as std::cout << str << '\n';
```

### 1.3. Copy and Move Assignment Operator
```cpp
// Copy
T& operator= (const T& other) {
  // Guard self assignment
  if (this == &other)
    return *this;

  // assume *this manages a reusable resource, such as a heap-allocated buffer mArray
  if (size != other.size) {
    temp = new int[other.size];   // allocate resource, if throws, do noting
    delete[] mArray;  // release resource in *this
    mArray = temp;
    size = other.size;
  }

  std::copy(other.mArray, other.mArray + other.size, mArray);
  return *this;
}
```
```cpp
// Move
T& operator= (T&& other) noexcept {
  // Guard self assignment
  if (this == &other) 
    return *this;

  delete[] mArray;
  mArray = std::exchange(other.mArray, nullptr);
  size = std::exchange(other.size, 0);
  return *this;
}
```