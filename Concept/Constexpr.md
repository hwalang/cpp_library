- [`constexpr` specifier](#constexpr-specifier)
  - [Constant Expression](#constant-expression)
  - [`constexpr` vs `const`](#constexpr-vs-const)
  - [constexpr `variable`, `function`](#constexpr-variable-function)
    - [1. constexpr variable](#1-constexpr-variable)

<br><br>

[cppreference - constexpr specifier since C++11](https://en.cppreference.com/w/cpp/language/constexpr)   
[cppreference - Constant expressions](https://en.cppreference.com/w/cpp/language/constant_expression)   
[씹어먹는 C++ 16-2 ](https://modoocode.com/293)   

# `constexpr` specifier
constexpr - specifies that the value of a variables or function can appear in constant expressions.   

## Constant Expression
Constant expression defines an expression that can be evaluated at compile time.   
constant expression의 이러한 성질을 이용해서 compile time에 어떠한 상수식에도 사용할 수 있도록 만들 수 있다.   
```cpp
// Integral constant expression
int n = 10;
std::array<int, n> a1;    // error: n is not a constant expression

const int cn = 10;
std::array<int, cn> a2;   // Ok
```
Integral constant expression은 주로 non-type template arguments, array sizes, and enumerator에서 사용한다.   

## `constexpr` vs `const`
```CPP
int a;

// Do something ...

const int b = a;
const int c = 1;
constexpr int d = a;
```
const로 정의된 상수들은 compile-time에 반드시 그 값을 결정하지 않아도 된다. 즉, `b의 값을 compile-time에 알 수 없다`.   
하지만 b의 값을 지정하면 바꿀 수 없다는 점은 같다.   

constexpr은 반드시 오른쪽에 constant expression이 필요하다.   

const가 상수식으로 초기화 됐더라도 compiler에 따라 run-time, compile-time에 초기화되는 시점이 결정된다.   

따라서 `compile-time에 상수를 확실히 사용하고 싶다면 constexpr specifier을 사용`한다.   

<br>

## constexpr `variable`, `function`
The `constexpr specifier declares` that it is possible to evaulate the value of the function or variable `at compile time`.   

<hr>

```cpp
// number is const int, not changed.
constexpr int number = 42;

// add function is implicitly const member function.
struct Calculator {
  constexpr int add(int a, int b) { return a + b; }
};
```
A constexpr specifier used in `an object declaration` or `non-static member function( until C++14 )` implies const.   
[ object 선언이나 C++14 이전의 non-static member function에 사용된 constexpr은 `const`를 의미한다. ]   

`number`는 compile-time에 결정되며, 이후 값을 변경할 수 없다.   
C++14 이전에는 constexpr member function은 자동으로 const member function으로 취급하기 때문에, member variable의 값을 변경할 수 없다.   

<hr>

```cpp
struct Constants {
  static constexpr int MAX = 100;   // implicitly inline since C++17.
};

// implicitly inline function
constexpr int multiply(int x, int y) { return x * y; }
```
A constexpr specifier used in `a function` or `static data member( since C++17 )` declaration implies `inline`.   

<hr>

```cpp
// 선언부
constexpr int substract(int a, int b);

// 정의부
constexpr int substract(int a, int b) { return a - b; }
```
If any declaration of a function or function template has a constexpr specifier, then every declaration must contain that specifier.   
[ 만약 function 또는 template 선언에 constexpr이 있으면, 모든 선언에 해당 specifier가 포함되어야 한다. ]   

### 1. constexpr variable
