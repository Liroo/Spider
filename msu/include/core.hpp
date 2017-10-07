// core

#ifndef CORE_HPP
# define CORE_HPP

# include <string>
# include <map>
# include <vector>
# include "plugin.hpp"
# include "network.hpp"

/*
  class Core - MUTLIPLE SERVER USAGE

    This class will handle the global behavior of a TCP server. You can connect a mongo database inside.

    constructor:
      Core(const int serverPort) - create a server on a port serverPort

      Core(const int serverPort, const std::string dbIp, const std::string dbName) - create a server on a port serverPort
        and connect to the database dbIp

    public:

      all(); // as all route (ssl)
      use(); // as plugin (key, etc...)

      listen(); // spawn the server

*/
# define PLUGIN_BEFORE 0x00
# define PLUGIN_ENDPOINT 0x02
# define PLUGIN_AFTER 0x03
namespace MSU {
  class Core {

  public:
    Core(const int serverPort = 1024, const std::string dbIp = "localhost:27017", const std::string dbName = "tmp");
    ~Core();
  public:
    void use(std::vector<MSU::pluginFunc>, const int);
    // void req(); // plug-in to req a client using chrono
    void run();
    void _handle_session(Session *session);
  //   static requestRaw(ip, req); // static util to request a client

  public:
    typedef std::vector<std::vector<MSU::pluginFunc> > pluginVector;
    typedef std::map<int, MSU::Core::pluginVector> pluginMap;
  private:
    int _serverPort;
    std::string _dbIp;
    std::string _dbName;
    boost::asio::io_service _io_service;
    MSU::Network _network;

    MSU::Core::pluginMap _plugins;
  }; // class Core
}; // namespace MSU

#endif
