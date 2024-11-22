[#pragram once - embarcadero](https://docwiki.embarcadero.com/RADStudio/Athens/en/Pragma_once)   
[#pragram once - wiki](https://en.wikipedia.org/wiki/Pragma_once)   

# pragma once
`#pragma once` is a preprocessor directive( 전처리기 지시어 ) used to prevent header files from being included multiple time.   

The directive, once present in a file, assures that the file will not be included multiple times in the current project.   
Using directive in file **prevents the preprocessor from including the file a second time**.   
In other words, #pragma once supported preprocessor directive designed to cause the current header file to be included only once in a single compilation.   
Thus, the directvie serves the same purpose as `#include guards`.   

The guards is several advantages, including **less code**, **avoidance of name clashes**, and sometimes **improvement in compilation speed**.   

## Example : less code, compilation speed
The most common alternative to `#pragma once` is to use `#define` to set an **#include guard macro**.   
```cpp
#ifndef GRANDPARENT_H
#define GRANDPARENT_H
// TODO
#endif /* !GRANDPARENT_H */
```
기본적으로 pragma once와 같은 역할을 하지만, 하나 이상의 파일에서 프로그래머가 지정한 매크로 이름을 실수로 동일하게 짓는 경우를 방지하는 compile option이 없기 때문에 프로그래머 오류가 발생하기 쉽다.   

The compiler itself can **compare filenames without having to invoke the C preprocessor to scan the header** for `#ifndef` and `#endif`.   
Yet, since **include guards( macro )** appear **very often and the overhead of opening files is significant**, it is common for compilers to optimize the handling of include guards, making them as fast as `#pragma once`.   

## Example : name clash
```cpp
// grandparent.h
#pragma once

struct foo {
  int member;
};
```
```cpp
// parnet.h
#include "grandparent.h"
```
```cpp
// child.cpp
#include "grandparent.h"
#include "parent.h"
```
The inclusion of `grandparent.h` in both `parent.h` and `child.cpp` would ordinarily cause a **compilation error**, becuase **a struct with a given name can only be defined a single time in a given compilation**.   
The `#pragme once` directive **serves to avoid this( name clash ) by ignoring subsequent inclusions** of `grandparent.h`.   

## Caveats( 주의사항 )
### 파일 시스템이 파일을 식별하는 방법
Identifying the same file on a file system is not a trivial task.   

파일 시스템이 파일을 식별하는 4가지 방법이 존재한다.   
**Absolute PATH**: 파일의 전체 경로를 사용하여 파일을 식별한다. `/home/user/project/include/header.h`로 파일의 위치를 명확하게 지정한다.   

**Relative PATH**: 현재 작업 디렉토리를 기준으로 파일을 식별한다. 서로 다른 경로로 하나의 파일을 표현할 수 있다. `./include/header.h`와 `../project/include/header.h`   

**Symbolic LINK**: 파일이나 디렉토리에 대한 참조를 제공하는 특수한 파일이다. `/usr/include/header.h`가 `/home/user/project/include/header.h`에 대한 Symbolic link일 경우, 두 경로는 동일한 파일을 가리키지만 다른 경로로 표현한다.   

**Hard LINK**: 파일 시스템 내에서 동일한 파일에 대한 여러 경로를 제공한다. 파일의 데이터 블록을 직접 참조하기 때문에 경로와 상관없이 동일한 파일로 식별한다.   

### pragma once 동작 방식
`#pragma once`는 compiler에게 특정 header file을 한 번만 포함하도록 지시한다. 이를 위해서 compiler는 파일의 고유 식별자를 저장하고, 동일한 파일이 다시 포함될 때 이를 인식하여 중복 포함을 방지한다.   
이러한 고유 식별자는 앞에서 설명한 `파일 시스템이 파일을 식별하는 방법`을 기반으로 한다.   

### 파일 경로 의존성 문제
`#pragma once`는 동일한 파일이 파일 시스템 내에서 여러 가지 경로로 참조될 때, **파일 경로 의존성 문제**가 발생할 수 있다.
이는 `#pragma once`가 의도한 대로 중복 포함을 방지하지 못하여 동일한 파일을 다른 파일로 인식할 수 있다.   
```cpp
// 파일 A가 절대 경로로 포함됨
#include "/home/user/project/include/header.h"

// 파일 B가 상대 경로로 포함됨
#include "../project/include/header.h"
```
이 경우, compiler를 두 경로가 동일한 파일을 가리키는지 알 수 없다.   
```cpp
// 실제 파일 경로
#include "/home/user/project/include/header.h"

// Symbolinc Link를 통한 경로
#include "/usr/include/header.h"
```
두 경로가 같은 파일에 대한 경로임에도, compiler는 이를 다른 파일로 인식할 수 있다.   

이외에도 **파일 시스템의 차이**( Windows의 NTFS는 파일 이름을 대소문자로 구분하지 않지만, Linus의 ext4는 구분함 ) 또는 **빌드 시스템 설정 차이**( 빌드 시스템이 서로 다른 디렉토리 구조를 사용하여 동일한 헤더 파일을 포함하는 경우 )로 인해 다른 파일로 인식할 수 있다.   

### 해결법
```cpp
#pragma once
#ifndef HEADER_H
#define HEADER_H

// 헤더 파일 내용

#endif // HEADER_H
```
`#pragma once`와 `include guard`를 함께 사용해서 preprocessor directive가 실패할 경우 include guard가 중복 포함을 방지한다.   