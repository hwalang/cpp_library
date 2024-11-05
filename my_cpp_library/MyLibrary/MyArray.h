#pragma once // .cpp파일에 여러 번 include 되지 않도록 하는 include guard

// Integer에 대한 std::array를 먼저 구현한다.
class MyArray {
public:
  /* == == == == = Implicitly-defined Member Functions == == == == == == */
  MyArray();
  ~MyArray();
  // copy constructor: operator=

  /* == == == == = Element Access == == == == == == */
  int at(int pos) const;
  int operator[](int pos);
  const int operator[](int pos) const;
  int front();
  const int front() const;
  int back();
  const int back() const;
  int* data() noexcept;
  const int* data() const noexcept;

  /* == == == == = Capacity == == == == == == */
  constexpr bool empty() const noexcept;
  constexpr int size() const noexcept;

  /* == == == == = Operations == == == == == == */
  void fill(const int& value);
  void swap(MyArray& other) noexcept;

  /* == == == == = Non-member Functions == == == == == == */
  // operator overload ( ==, !=, <, <=, >, >=, <=> )
  int& get(MyArray& a) noexcept;
  int&& get(MyArray&& a) noexcept;
  const int& get(const MyArray& a) noexcept;
  const int&& get(const MyArray&& a) noexcept;

private:

};