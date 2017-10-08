
#include <iostream>
#include "plugin/mouse.hpp"

Mouse::Mouse() {
  name = std::string("MOUSE");
}
Mouse::~Mouse() {}

bool Mouse::test(std::string res) {
  return (res.compare(0, name.length(), name) == 0);
}

int Mouse::exec(Session *, std::string) {
  std::cout << "Mouse" << std::endl;
  return (0);
}
