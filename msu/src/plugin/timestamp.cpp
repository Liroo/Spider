
#include <iostream>
#include "plugin/timestamp.hpp"

Timestamp::Timestamp() {
  name = std::string("TIMESTAMP");
}
Timestamp::~Timestamp() {}

bool Timestamp::test(std::string res) {
  return (res.compare(0, name.length(), name) == 0);
}

int Timestamp::exec(Session *, std::string) {
  std::cout << "Timestamp" << std::endl;
  return (1);
}
