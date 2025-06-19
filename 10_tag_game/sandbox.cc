#include <cmath>
#include <iostream>

using namespace std;

int main() {
  float angle = asin(1);
  cout << "asin(1) = " << angle << endl;

  // user input
  int input_num;
  cin >> input_num;
  std::cout << "User input: " << input_num << std::endl; 

  // Lambda expression
  enum MyEnum { val_1, val_2 };
  auto LambdaExp = [&](int& a, int& b, MyEnum enum_obj){
    if (enum_obj == val_1) {
      std::cout << "val_1 enum" << std::endl;
      return a;
    } else if (enum_obj == val_2) {
      std::cout << "val_2 enum" << std::endl;
      return b;
    }
    return 0;
  };

  int num1 = 1;
  int num2 = 2;
  MyEnum test_enum = val_1;
  std::cout << LambdaExp(num1, num2, test_enum) << std::endl;
  test_enum = val_2;
  std::cout << LambdaExp(num1, num2, test_enum) << std::endl;

  // Seg fault
  int* int_ptr = new int(6);
  std::cout << "Value of number: " << *int_ptr << std::endl;

  return 0;
}
