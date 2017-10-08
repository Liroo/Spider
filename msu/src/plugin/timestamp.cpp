
#include <iostream>
#include "plugin/timestamp.hpp"


Timestamp::Timestamp() {
  name = std::string("TIMESTAMP");
}
Timestamp::~Timestamp() {}

bool Timestamp::test(std::string res) {
  return (res.compare(0, name.length(), name) == 0);
}

int Timestamp::exec(Session *session, std::string msg) {
  std::cout << msg << std::endl;
  std::map<boost::uuids::uuid, std::string>::iterator it;
  for (it = lastTimestamp.begin(); it != lastTimestamp.end(); ++it){
    if (it->first == session->getUniqueId()){
      lastTimestamp.at(session->getUniqueId()) = msg;
      std::cout << "Timestamp" << std::endl;
      return (1);
    }
  }
  lastTimestamp.insert (it, std::pair<boost::uuids::uuid, std::string>(session->getUniqueId(),msg));
  std::cout << "Timestamp"  <<  std::endl;
  return (1);
}

std::string Timestamp::getLastTT(Session *session) {
  std::map<boost::uuids::uuid, std::string>::iterator it;
  for (it = lastTimestamp.begin(); it != lastTimestamp.end(); ++it){
    if (it->first == session->getUniqueId())
      return (it->second);
  }
  return ("NONE");
}
