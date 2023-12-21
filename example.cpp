#include "bigint.hpp"
#include <iostream>
int main(){
  bigint x, y;
  std::cin >> x;
  std::cout << x << std::endl;
  x = 123;
  y = 456;
  std::cout << std::boolalpha;
  std::cout << "x == y: " << (x == y) << std::endl; //false
  std::cout << "x != y: " << (x != y) << std::endl; //true
  std::cout << "x < y: " << (x < y) << std::endl; //true
  std::cout << "x <= y: " << (x <= y) << std::endl; //true
  std::cout << "x > y: " << (x > y) << std::endl; //false
  std::cout << "x >= y: " << (x >= y) << std::endl; //false
  std::cout << +x << std::endl; //123
  std::cout << -x << std::endl; //-123
  std::cout << x + y << std::endl; //579
  std::cout << x - y << std::endl; //-333
  std::cout << x * y << std::endl; //56088
  x += y;
  std::cout << x << std::endl; //579
  x -= y;
  std::cout << x << std::endl; //123
  x *= y;
  std::cout << x << std::endl; //56088
  //x = 12345678901234567890;
  x = std::string("12345678901234567890");
  std::cout << x << std::endl; //12345678901234567890
}