#include "MyArray.h"

int main() {
  MyArray<int, 10> test;
  for (int i = 0; i < test.size(); ++i) {
    test[i] = i;
  }

  for (int i = 0; i < test.size(); ++i) {
    std::cout << test[i] << " ";
  }
  std::cout << '\n';

  MyArray<int, -1> test2;
  if (test2.empty()) {
    std::cout << "empty" << '\n';
  }
}