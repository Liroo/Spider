// core

#include "core.hpp"
#include "exception/coreException.hpp"

using namespace MSU;

static MSU::Core::pluginMap defaultPluginMap() {
  MSU::Core::pluginMap plugins;

  plugins[PLUGIN_BEFORE] = MSU::Core::pluginVector();
  plugins[PLUGIN_ENDPOINT] = MSU::Core::pluginVector();
  plugins[PLUGIN_AFTER] = MSU::Core::pluginVector();

  return plugins;
}

// constructor
Core::Core(const int serverPort) {
  _serverPort = serverPort;
  _plugins = defaultPluginMap();
}
Core::Core(const int serverPort, const std::string dbIp, const std::string dbName) {
  _serverPort = serverPort;
  _dbIp = dbIp;
  _dbName = dbName;
  _plugins = defaultPluginMap();
}

// destructor
Core::~Core() {};

void Core::use(std::vector<MSU::pluginFunc> plugins, const int position) {
  if (position < PLUGIN_BEFORE || position > PLUGIN_AFTER) {
    throw MSU::Exception::CoreException(PLUGIN_POSITION_ERROR);
  }
  _plugins[position].push_back(plugins);
}

bool Core::listen() {
  return true;
}
