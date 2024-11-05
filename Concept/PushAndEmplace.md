- [The Difference Between `Push` and `Emplace`](#the-difference-between-push-and-emplace)
  - [Push](#push)
  - [Emplace](#emplace)
    - [Add Initializer\_list](#add-initializer_list)


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

### Add Initializer_list
```cpp
// 잘못된 예시
emplace_back({int, int});
```
`initializer_list는 compiler에게 임시 객체를 생성하도록 지시`하기 때문에 emplace_back의 인자로 받아들일 수 없다.   

```cpp
// 옳바른 예시
emplace_back(int, int);
push_back(make_pair(int, int));
```
emplace_back은 객체 생성에 필요한 인자를 직접 사용하기 때문에 initializer_list 대신 pair 생성자에 필요한 인자를 직접 전달한다.   
아니면 임시 객체를 생성한 후, push_back으로 추가한다.   