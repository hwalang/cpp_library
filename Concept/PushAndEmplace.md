- [The Difference Between `Push` and `Emplace`](#the-difference-between-push-and-emplace)
  - [Push](#push)
  - [Emplace](#emplace)
    - [\[ Why `initializer_list` and `emplace` Cannot Be Used Together \]](#-why-initializer_list-and-emplace-cannot-be-used-together-)
      - [1. Ambiguity in Overload Resolution](#1-ambiguity-in-overload-resolution)
      - [2. Difference in Purpose](#2-difference-in-purpose)


<br><br>


# The Difference Between `Push` and `Emplace`
push와 emplace는 Container에 element를 추가할 때 사용하지만, `element를 추가하는 방식이 다르다`.   

## Push
`이미 생성된 객체를 container에 복사 또는 이동하여 추가`한다.   
```cpp
std::vector<std::string> vec;
std::string str = "test";

// copy
vec.push_back(str);

// move
vec.push_back(std::move(str));
```

<br>

## Emplace
`Container 내부에서 직접 객체를 생성`한다.   
객체 생성에 필요한 arguments를 직접 전달하여 container 내부에서 객체가 생성된다. 이를 통해 불필요한 복사나 이동을 피할 수 있다.   
```cpp
std::vector<std::string> vec;

// 컨테이너 내부에서 직접 객체를 생성하여 추가
vec.emplace_back("Hello");
```

### [ Why `initializer_list` and `emplace` Cannot Be Used Together ]

#### 1. Ambiguity in Overload Resolution
C++ container는 emplace 함수와 intializer_list를 모두 지원한다.  
때문에 `compiler는 어떤 함수 overload를 호출할지 결정하는데 어려움`을 겪는다.   
```cpp
emplace_back({int, int});   // 모호성 발생
``` 
{int, int}를 전달하면, compiler는 이것을 initializer_list를 의미하는지, 아니면 단일 std::initialzier_list<int> 객체를 의미하는지 혼동할 수 있다.   

또한 `initializer_list는 이미 생성된 객체들을 list로 삽입`하기 때문에 emplace_back의 인자로 받아들일 수 없다.   
```cpp
emplace_back(int, int);
push_back(make_pair(int, int));
```
emplace_back은 객체 생성에 필요한 인자를 직접 사용하기 때문에 initializer_list 대신 pair 생성자에 필요한 인자를 직접 전달한다.   
아니면 임시 객체를 생성한 후, push_back으로 추가한다.   

#### 2. Difference in Purpose
emplace는 `개별 요소를 생성하고 추가`할 때 사용하며, initializer_list는 `여러 요소를 한 번에 초기화`하는 데 사용한다.   
```cpp
std::vector<std::pair<int, int>> vec;
vec.emplace_back(1, 2);

std::vector<std::pair<int, int>> vec2 = { {1, 2}, {3, 4} };
```