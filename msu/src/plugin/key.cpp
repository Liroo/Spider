
#include <iostream>
#include "plugin/key.hpp"

Key::Key() {
  name = std::string("KEY");
}
Key::~Key() {}

bool Key::test(std::string res) {
  return (res.compare(0, name.length(), name) == 0);
}

int Key::exec(mongocxx::database, Session * session, std::string msg) {
  std::string theKey = msg.substr(msg.find(" ") + 1);
  theKey.erase(theKey.size() - 1);

  std::cout << "The client [" << session->getUniqueId() << "] is using : ";
  std::cout << "Key [" << theKey << "]" << std::endl;
  return (0);
}
