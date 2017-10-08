
#include <iostream>
#include "plugin/addrMac.hpp"

AddrMac::AddrMac() {
  name = std::string("ADDR_MAC");
}
AddrMac::~AddrMac() {}

bool AddrMac::test(std::string res) {
  return (res.compare(0, name.length(), name) == 0);
}

int AddrMac::exec(mongocxx::database, Session * session, std::string msg) {
  std::string mac = msg.substr(msg.find(" ") + 1);
  mac.erase(mac.size() - 1);

  std::cout << "The client [" << session->getUniqueId() << "] is using : ";
  std::cout << "addr_mac [" << mac << "]" << std::endl;
  session->setMacAddress(mac);
  return (0);
}
