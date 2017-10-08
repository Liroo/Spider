
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
  std::string theKeys = msg.substr(msg.find(" ") + 1);
  theKeys.erase(theKeys.size() - 1);

  std::vector<std::string> keys;
  std::string::size_type prev_pos = 0, pos = 0;
  while((pos = theKeys.find(" ", pos)) != std::string::npos)
  {
      std::string substring( theKeys.substr(prev_pos, pos-prev_pos) );
      keys.push_back(substring);
      prev_pos = ++pos;
  }
  keys.push_back(theKeys.substr(prev_pos, pos-prev_pos)); // Last word

  std::cout << "The client [" << session->getUniqueId() << "] is using : ";
  std::cout << "Keys : ";

  for(int unsigned i=0;i<keys.size();i++){
    std::cout << " " << keys.at(i);
  }
  std::cout << std::endl;
  return (0);
}
