// core

#ifndef CORE_HPP
# define CORE_HPP

# include <string>
# include <map>
# include <vector>
# include "plugin.hpp"

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
namespace MSU {
  class Core {

  public:
    Core(const int serverPort = 1024);
    Core(const int serverPort = 1024, const std::string dbIp = "localhost:27017", const std::string dbName = "tmp");
    ~Core();
  public:
    void all(std::vector<MSU::pluginFunc>, const int);
    void use(std::vector<MSU::pluginFunc>);
    // void req(); // plug-in to req a client using chrono
    bool listen();
  //   static requestRaw(ip, req); // static util to request a client

  private:
    int _serverPort;
    std::string _dbIp;
    std::string _dbName;

    std::map<std::string, std::vector<std::vector<MSU::pluginFunc>>> _plugins;
  }; // class Core
}; // namespace MSU

#endif
