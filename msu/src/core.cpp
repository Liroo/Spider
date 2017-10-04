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

#include <iostream>
#include "bsoncxx/builder/stream/document.hpp"
#include "bsoncxx/json.hpp"

#include "mongocxx/client.hpp"
#include "mongocxx/instance.hpp"

bool Core::listen() {
  mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{}};

    bsoncxx::builder::stream::document document{};

    auto collection = conn["testdb"]["testcollection"];
    document << "hello" << "world";

    collection.insert_one(document.view());
    auto cursor = collection.find({});

    for (auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
  return true;
}
