// plugin

#ifndef PLUGIN_HPP
# define PLUGIN_HPP

#include <mongocxx/client.hpp>

# include <functional>
# include <string>
# include "session.hpp"

namespace MSU {
  class Plugin {
  public:
    virtual bool test(std::string) = 0;
    virtual int exec(mongocxx::database, Session *, std::string) = 0;
  };
};

#endif
