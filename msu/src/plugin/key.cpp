
#include <iostream>
#include "plugin/key.hpp"

Key::Key() {
  name = std::string("KEY");
}
Key::~Key() {}

bool Key::test(std::string res) {
  return (res.compare(0, name.length(), name) == 0);
}

int Key::exec(std::string) {
  std::cout << "Key" << std::endl;
  return (0);
}
