- [Value Initialization](#value-initialization)
  - [Value-Initialization is Performed in these situations](#value-initialization-is-performed-in-these-situations)
    - [1. A Nameless Temporary Object](#1-a-nameless-temporary-object)
    - [2. An Object with Dynamic Storage Duration](#2-an-object-with-dynamic-storage-duration)
    - [3. A Non-static Data Member or a Base Class](#3-a-non-static-data-member-or-a-base-class)
    - [4. A Named Object](#4-a-named-object)
  - [The Rules of value-initialization](#the-rules-of-value-initialization)
    - [1. T is a Class Type](#1-t-is-a-class-type)
    - [1.1. There is a Default Constructor](#11-there-is-a-default-constructor)
    - [1.2. There is a User-Defined Constructor](#12-there-is-a-user-defined-constructor)
    - [2. T is a Array Type](#2-t-is-a-array-type)
    - [3. ELSE](#3-else)


<br><br>

[ cppreference - Value-initialization ](https://en.cppreference.com/w/cpp/language/value_initialization)   
# Value Initialization
This is the initialization performed when an object is constructed with an empty initializer.   
`C++에서 object를 생성하는 초기화 방법 중 하나`로, object의 모든 member variables가 적절하게 초기화되도록 보장한다.   

## Value-Initialization is Performed in these situations

### 1. A Nameless Temporary Object
when `a nameless temporary object is created` with the initializer consisting of an `empty` pair of parentheses or braces.   
```
T()
T {}
```
```cpp
MyClass obj = MyClass();
```
`MyClass()`는 MyClass의 임시 객체를 생성하여 반환하며, 이를 obj에 복사한다.   

### 2. An Object with Dynamic Storage Duration
when `an object with dynamic storage duration is created` by a new expression with the initializer consisting of an `empty` pair of parentheses or braces.   
```
new T()
new T{}
```
```cpp
MyClass* objPtr = new MyClass();
```

### 3. A Non-static Data Member or a Base Class
when `a non-static data member or a base class is initialized` using a `member initializer` with an `empty` pair of parentheses or braces.   
```
Class::Class(...) : member() {...}
Class::Class(...) : member{} {...}
```

```cpp
// Static Array
public:
  MyArray() : _array{} {};

private:
  T _array[N];

int main() {
  MyArray<int, 10> array;   // all elements initialize 0.
}
```

### 4. A Named Object
when `a named object (automatic, static, or thread-local) is declared` with the initializer consisting of a pair of braces.   
```
T object {};
```
```cpp
MyClass obj();    // does not initialization an object
MyClass obj{};
```
참고로 `T object();`는 object를 초기화하지 않는다.   
이는 arguments가 없고 T를 반환하는 함수를 의미한다.   
C++11 이전에는 `T object = T();`로 value-initialization을 수행했다.   

<br>

## The Rules of value-initialization
```
IF ( T is a (possibly cv-qualified) class type ):
  IF ( the default-initialization for T selects a constructor, and the constructor is not user-declared, user-provided ):
    the object is first zero-initialized.
  ELSE
    the object is default-initialized.
ELSE IF ( T is an array type )
  each element of the array is value-initialized.
ELSE
  the object is zero-initialized.
```
T type에 따라 value-initialization이 어떻게 수행되는지 단계별로 결정한다.   

### 1. T is a Class Type
`possibly cv-qualified`는 const 또는 volatile keywords를 가질 가능성이 있다는 의미다.    

### 1.1. There is a Default Constructor
T의 default-initialization이 constructor를 선택했을 때, 그 constructor를 사용자가 선언하지 않은 경우를 의미한다.   
즉, `compiler가 implicitly 제공한 Constructor를 선택함`을 의미한다.   
위 상황인 경우, object는 zero-initialized를 수행한다.   
```cpp
// zero-initialized
struct MyClass {
  int a;
  double b;
};

int main() {
  MyClass obj = MyClass();    // value-initialization
  // obj.a == 0, obj.b == 0.0
}
```
object의 모든 member variables가 0 또는 그에 상응하는 초기값으로 설정된다.   

### 1.2. There is a User-Defined Constructor
T의 default-initialization이 user-defined constructor를 선택한 경우를 의미한다.   
해당 constructor를 따라 member variables를 초기화한다.   

### 2. T is a Array Type
배열의 각 elements가 개별적으로 value-initialization 된다.   

### 3. ELSE
T가 Class 또는 Array Type이 아니라면, 기본적으로 primitive type이나 pointer type이 해당된다.   
object는 `zero-initialized` 된다. 즉, `memory가 0으로 설정되어 모든 bit가 0`이다.   