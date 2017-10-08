
#include <iostream>
#include "plugin/process.hpp"

Process::Process() {
  name = std::string("PROCESS");
}
Process::~Process() {}

bool Process::test(std::string res) {
  return (res.compare(0, name.length(), name) == 0);
}

int Process::exec(mongocxx::database, Session *, std::string) {
  std::cout << "Process" << std::endl;
  return (0);
}
