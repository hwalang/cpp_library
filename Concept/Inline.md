- [Inline](#inline)
  - [1. Implicitly Inline Function](#1-implicitly-inline-function)
  - [2. Implicitly Inline Variable](#2-implicitly-inline-variable)
  - [3. Multiple Definitions 허용](#3-multiple-definitions-허용)
    - [3.1. 코드 예시](#31-코드-예시)
  - [4. Modern Inline](#4-modern-inline)

[inline specifier - cppreference](https://en.cppreference.com/w/cpp/language/inline)   

# Inline
Function 또는 Variable을 정의할 때 사용하는 keyword르서, **함수 호출의 overhead를 줄이고 optimization을 통해 실행 속도를 높이기 위한 용도로 사용**된다.   

일반적으로 함수가 호출( call )될 때는 Call Process( 호출 과정 )와 Stack Allocation( 스택 할당 ) 등 일정한 overhead가 발생한다.   
하지만 `inline`으로 지정된 function은 compiler가 해당 함수의 body를 Call Site( 호출 지점 )에 직접 삽입하거나 확장하는 방식으로 처리할 수 있기 때문에, 별도의 function call 없이 Macro처럼 동작하도록 만든다.   
참고로 `inline`은 반드시 inline expansion을 보장하는 것이 아니라 compiler가 상황에 따라 결정한다.   

Modern C++에서 inline의 사용 목적이 조금 달라졌다.   

## 1. Implicitly Inline Function
Class, Struct, Union 내부에 완전하게 정의된 함수는 묵시적으로 `inline` function이다.   
`constexpr`이나 `consteval`로 선언된 함수는 처음 선언시 자동으로 `inline` function이 된다.   

## 2. Implicitly Inline Variable
Static Storage Duration( 정적 저장 기간 )을 갖는 변수, 예를 들어 Global Variable이나 Namespace-scope에 선언된 변수를 `inline`으로 지정할 수 있다.   
`constexpr`로 선언된 Static Data Member는 자동으로 `inline` 변수로 취급한다.   

## 3. Multiple Definitions 허용
External Linkage( 외부 연결 )이 있는 inline function 또는 inline variable은 program 내에서 여러 번역 단위에 동일한 정의가 존재할 수 있다.   

**일반적으로 Global Function 또는 Variable을 header file에 정의하고, 그 header를 여러 source file에서 포함하면, Linker가 link 단계에서 동일한 함수나 변수가 여러 번 정의됐다는 error를 발생**시킬 수 있다.   
하지만 `inline` keyword는 이러한 function, variable을 여러 translation unit에 동일한 정의를 두어도 허용하며, 이 경우 compiler와 linker는 이를 하나의 동일한 정의로 취급한다.   

즉, **`inline` keyword는 동일한 코드 정의를 여러 source file에서 공유할 수 있게 도와준다**.   

### 3.1. 코드 예시
```cpp
#ifndef ADD_H
#define ADD_H

#include <atomic>

inline int sum(int a, int b) { return a + b; }
inline std::atomic<int> counter(0);

#endif
```
```cpp
#include "add.h"

int main() {
  int result = sum(3, 4);
  ++counter;
}
```
```cpp
#include "add.h"

int AnotherFunction() { 
  ++counter;
  return sum(10, 20); 
}
```
**`add.h`에 있는 `sum()`과 `counter`를 main.cpp과 other.cpp에서 header file을 포함하여 중복으로 정의**됐다.   
원래라면 Linker가 해당 함수 또는 변수가 둘 이상의 Translation Unit에 정의됐다고 판단하여 Multiple Definition Error를 발생시킨다. 하지만 `inline` function, variable이기 때문에 이 정의를 하나의 동일한 함수나 변수로 취급하고, 프로그램 전체에서 공유 가능한 형태로 관리할 수 있다.   

**즉, `inline`으로 정의된 function 또는 variable은 여러 파일에서 중복으로 정의되도 문제가 없다**.   


## 4. Modern Inline
`inline` keyword는 compiler에게 function call 대신 함수 body를 직접 insertion 함으로써, call overhead를 줄이는 힌트였다.   
하지만 Modern C++에서는 compiler가 `inline` keyword와 무관하게 inline optimization을 수행할 수 있고, `inline`이 붙은 function이라도 꼭 inline Expansion이 일어나지 않을 수 있다.   

**`inline`은 주로 여러 번 정의 가능한 개념을 나타내고, inline expansion은 선택적인 optimization 단계**다.   
즉, 함수나 변수를 프로그램 전체에서 공유 가능한 형태로 만들며, 여러 번역 단위( translation unit )에서 동일한 정의를 유지할 수 있도록 한다. 또한 compiler가 필요에 따라 inline expansion을 제공하여 call overhead를 줄일 수 있다.   
