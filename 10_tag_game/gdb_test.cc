#include <iostream>

int add(int a, int b) {
  int result = a + b;
  return result;
}

int subtract(int a, int b) {
  int result = a - b;
  return result;
}

int my_operation(int a, int b) {
  int num1 = add(a, b);
  int num2 = subtract(num1, 1);
  int num3 = add(num1, num2);
  int* num4 = new int(10);
  int num5 = subtract(*num4, num3);

  return num3;
}

int main(int argc, char** argv) {
  int a = 1;
  int b = 2;
  int result = my_operation(a, b);

  std::cout << "my result: " << result << std::endl;

  return 0;
}
