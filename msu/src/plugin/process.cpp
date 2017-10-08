
#include <iostream>
#include "plugin/process.hpp"

Process::Process() {
  name = std::string("PROCESS_BEGIN");
}
Process::~Process() {}

bool Process::test(std::string res) {
  return (res.compare(0, name.length(), name) == 0);
}

int Process::exec(mongocxx::database, Session * session, std::string msg) {
  std::cout << msg << std::endl;
  std::string theProcess = msg.substr(msg.find("PROCESS_BEGIN") + 2);
  theProcess.erase(theProcess.size() - 1);

  std::vector<std::string> Process;
  std::string::size_type prev_pos = 0, pos = 0;
  while((pos = theProcess.find(" ", pos)) != std::string::npos)
  {
      std::string substring( theProcess.substr(prev_pos, pos-prev_pos) );
      Process.push_back(substring);
      prev_pos = ++pos;
  }
////////
//  Process.push_back(theProcess.substr(prev_pos, pos-prev_pos)); // Last word
////////

////////
  std::cout << "The client [" << session->getUniqueId() << "] is using : ";
  std::cout << "Process : ";

  for(int unsigned i=0;i<Process.size();i++){
    std::cout << " " << Process.at(i);
  }
  std::cout << std::endl;
////////
  return (0);
}
