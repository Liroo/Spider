// main

#include <vector>
#include <boost/asio.hpp>
#include "msu.hpp"
#include "plugin/key.hpp"

int main() {
  MSU::Core core(1024);
  Key *pluginKey;

  pluginKey = new Key();
  core.use(pluginKey, PLUGIN_ENDPOINT);
  core.run();
  return (0);
}
