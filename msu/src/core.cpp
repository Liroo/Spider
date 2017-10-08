// core

#include <boost/algorithm/string.hpp>
#include "core.hpp"
#include "exception/coreException.hpp"

using namespace MSU;

static MSU::Core::pluginMap defaultPluginMap() {
  MSU::Core::pluginMap plugins;

  plugins[PLUGIN_ENDPOINT] = MSU::Core::pluginVector();
  plugins[PLUGIN_AFTER] = MSU::Core::pluginVector();

  return plugins;
}

// constructor
Core::Core(const int serverPort, const std::string dbIp, const std::string dbName):
  _network(serverPort, _io_service),
  _instance{},
  _pool{mongocxx::uri{dbIp}} {
  _serverPort = serverPort;
  _dbName = dbName;
  _plugins = defaultPluginMap();
}

// destructor
Core::~Core() {};

void Core::use(MSU::Plugin* plugins, const int position) {
  if (position < PLUGIN_ENDPOINT || position > PLUGIN_AFTER) {
    throw MSU::Exception::CoreException(PLUGIN_POSITION_ERROR);
  }
  _plugins[position].push_back(plugins);
}

std::string Core::_handle_log(Session *s, std::string req) {
  boost::char_separator<char> sep("\n");
  std::vector<std::string> tokens;
  boost::split(tokens, req, boost::is_any_of("\n\r"));
  std::string res = "";
  pluginVector::iterator it;
  auto client = _pool.acquire();
  mongocxx::database db = (*client)[_dbName];

  int next = 0;
  // how works next
  // 0 -> OK
  // 1 -> continue with the next line
  // 2 -> error

  int i = 0;
  while (i < (int)tokens.size()) {
    if (!tokens[i].empty()) {
      for (it = _plugins[PLUGIN_ENDPOINT].begin(); it < _plugins[PLUGIN_ENDPOINT].end(); it++) {
        if ((*it)->test(req) == true) {
          next = (*it)->exec(db, s, req);
          break;
        }
      }
      if (it == _plugins[PLUGIN_ENDPOINT].end()) {
        res += "UNKOWN\n";
      } else if (next == 0) {
        res += "OK\n";
      } else if (next == 2) {
        res += "KO\n";
      }
    }
    i++;
  }
  return res;
}

void Core::_handle_session(Session *session) {
  session->set_read_callback([&](Session *s, std::string req) -> std::string {
    return _handle_log(s, req);
  });
  session->start();
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
