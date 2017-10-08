
#include <iostream>
#include "plugin/addrMac.hpp"

AddrMac::AddrMac() {
  name = std::string("ADDR_MAC");
}
AddrMac::~AddrMac() {}

bool AddrMac::test(std::string res) {
  return (res.compare(0, name.length(), name) == 0);
}

int AddrMac::exec(mongocxx::database, Session *, std::string) {
  std::cout << "addr_mac" << std::endl;
  return (0);
}
