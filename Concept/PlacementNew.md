# What is `Placement-new`?
`특정 메모리 위치에 객체를 생성하는 new`   
주로 memory pool이나 custom memory management가 필요할 때 유용하다.   
```cpp
// 새로운 메모리를 할당하고 객체 생성( 생성자 호출 )
new Point(1, 2);

// 이미 할당된 메모리(p)에 객체 생성( 생성자만 호출 )
new (p) Point(1, 2);      // placement new
```

Memory에 Object를 생성하는 3가지 방법을 살펴본다.   

## 1. malloc
C언어의 memory allocation 함수로, 지정된 크기의 메모리를 할당하고 해당 메모리의 포인터를 반환한다.   

```cpp
#include <cstdlib>      // malloc, free
#include <new>          // placement new

MyClass* buffer = (MyClass*)malloc(sizeof(MyClass));    // memory allocation
if (buffer == nullptr) return -1;
new (buffer) MyClass();                                 // object creation
free(buffer);                                           // memory de-allocation
```

`void*`을 `MyClass*`로 casting하여 사용한다.   
c++ style이 아니며, new-delete를 사용하는 것이 일반적이다.   

## 2. operator new
operator new는 memory를 할당하는 함수다.   
단순히 memory를 할당하기 때문에, new 연산자와는 다르다.   
new 연산자는 memory 할당과 동시에 객체를 생성( 생성자 호출 )한다.   

```cpp
#include <new>    // operator new

void* buffer = operator new(sizeof(MyClass)); // memory allocation
MyClass* obj = new (buffer) MyClass();        // object creation
```

`void*`는 메모리 주소를 가리킨다.   

## 3. placement-new
placement-new는 지정된 메모리 위치에서 생성자를 호출하여 객체를 초기화한다.   

```cpp
#include <new>      // placement new

char buffer[sizeof(MyClass)];           // 충분한 크기의 buffer 생성
MyClass* obj = new (buffer) MyClass();  // buffer에 obj 생성
obj->~MyClass();
```

buffer는 고정 크기의 char 배열로, stack memory에 할당된다.   
stack은 heap 보다 핟당과 해제가 빠르며, memory를 자동으로 관리한다.   

placement-new를 사용하여 객체를 생성했다면, 객체 소멸자를 명시적으로 호출해야 한다.   
또한 `char buffer[]`는 객체의 올바른 정렬을 보장하지 않는다.   

```cpp
// memory alignment
#include <new>
#include <type_traits>

typename std::aligned_storage<sizeof(MyClass), alignof(MyClass)>::type buffer;
MyClass* obj = new (&buffer) MyClass();

obj->~MyClass();
```

MyClsas의 정렬 요구사항을 충족하는 buffer를 할당한다.   