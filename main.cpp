#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
using namespace std;

#include "print_ip.h"

int main() {
  char ip_char = -1;
  print_ip(ip_char);

  short ip_short = 0;
  print_ip(ip_short);

  int ip_int = 2130706433;
  print_ip(ip_int);

  long long ip_long = 8875824491850138409;
  print_ip(ip_long);

  std::string ip_string("9.69.222.182");
  print_ip(ip_string);

  std::vector<int> ip_vector{192, 168, 0, 100};
  print_ip(ip_vector);

  std::list<int> ip_list = {8, 16, 24, 32};
  print_ip(ip_list);
}
