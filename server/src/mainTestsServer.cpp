// main

#include <vector>
#include <boost/asio.hpp>
#include "msu.hpp"
#include "plugin/key.hpp"
#include "plugin/timestamp.hpp"

int main() {
  MSU::Core core(1024);
  Timestamp *pluginTimestamp;
  Key *pluginKey;

  pluginTimestamp = new Timestamp();
  core.use(pluginTimestamp, PLUGIN_ENDPOINT);
  pluginKey = new Key();
  core.use(pluginKey, PLUGIN_ENDPOINT);
  core.run();
  return (0);
}
