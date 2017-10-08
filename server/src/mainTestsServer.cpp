// main

#include <vector>
#include <boost/asio.hpp>
#include "msu.hpp"
#include "plugin/key.hpp"
#include "plugin/timestamp.hpp"
#include "plugin/mouse.hpp"
#include "plugin/addrMac.hpp"
#include "plugin/process.hpp"

int main() {
  MSU::Core core(1024);
  Timestamp *pluginTimestamp;
  Key *pluginKey;
  Mouse *pluginMouse;
  AddrMac *pluginAddrMac;
  Process *pluginProcess;

  pluginTimestamp = new Timestamp();
  core.use(pluginTimestamp, PLUGIN_ENDPOINT);

  pluginKey = new Key();
  core.use(pluginKey, PLUGIN_ENDPOINT);

  pluginMouse = new Mouse();
  core.use(pluginMouse, PLUGIN_ENDPOINT);

  pluginAddrMac = new AddrMac();
  core.use(pluginAddrMac, PLUGIN_ENDPOINT);

  pluginProcess = new Process();
  core.use(pluginProcess, PLUGIN_ENDPOINT);

  core.run();
  return (0);
}
