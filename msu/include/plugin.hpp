// plugin

#ifndef PLUGIN_HPP
# define PLUGIN_HPP

# include <functional>
# include <map>

namespace MSU {
  typedef std::map<std::string, std::string> req;
  typedef std::function<int (MSU::req &req, void *)> pluginFunc;

  class Plugin {
  public:
    virtual int plugin(MSU::req &, void *) = 0;
  };
};

#endif
