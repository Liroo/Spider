
#include <iostream>
#include "plugin/mouse.hpp"

Mouse::Mouse() {
  name = std::string("MOUSE");
}
Mouse::~Mouse() {}

bool Mouse::test(std::string res) {
  return (res.compare(0, name.length(), name) == 0);
}

int Mouse::exec(mongocxx::database, Session * session, std::string msg) {
  std::string mouse = msg.substr(msg.find(" ") + 1);
  mouse.erase(mouse.size() - 1);

  std::vector<std::string> vMouse;
  std::string::size_type prev_pos = 0, pos = 0;
  while((pos = mouse.find(" ", pos)) != std::string::npos)
  {
      std::string substring( mouse.substr(prev_pos, pos-prev_pos) );
      vMouse.push_back(substring);
      prev_pos = ++pos;
  }
  vMouse.push_back(mouse.substr(prev_pos, pos-prev_pos));

////////
  std::cout << "The client [" << session->getUniqueId() << "] is using : ";
  std::cout << "Mouse : [key: ";
  std::cout << vMouse.at(0) << ", pos_x : ";
  std::cout << vMouse.at(1) << ", pos_y : ";
  std::cout << vMouse.at(2) << "]";
  std::cout << std::endl;
////////
  return (0);
}
