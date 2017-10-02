// core

#include "core.hpp"

using namespace MSU;

// constructor
Core::Core(const int serverPort) {
  _serverPort = serverPort;
}
Core::Core(const int serverPort, const std::string dbIp, const std::string dbName) {
  _serverPort = serverPort;
  _dbIp = dbIp;
  _dbName = dbName;
}

// destructor
Core::~Core() {};

void Core::all(std::vector<MSU::pluginFunc>, const int) {

}

void Core::use(std::vector<MSU::pluginFunc>) {

}

bool Core::listen() {
  return true;
}
