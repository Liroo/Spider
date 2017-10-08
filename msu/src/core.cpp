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
Core::Core(const int serverPort, const std::string dbIp, const std::string dbName):
  _network(serverPort, _io_service) {
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

//
// le std::function je sais pas comment l utiliser et quoi en faire cf: handle_read dans session
//
std::string Core::callback_read(std::string msg, std::function<void(std::string)> callback) {
  // need a treatment of msg
  return (msg);
}


void Core::_handle_session(Session *session) {
  session->start();
  // session->set_read_callback();
}

void Core::run() {
  try {
    _network.run([&](Session *session) -> void {
      _handle_session(session);
    });
  } catch (boost::system::system_error& e) {
    std::cout << "nigga" << std::endl;
  }
}
