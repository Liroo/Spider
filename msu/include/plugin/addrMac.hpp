#ifndef ADDRMAC_HPP
# define ADDRMAC_HPP

# include <string>
# include "plugin.hpp"

class AddrMac: public MSU::Plugin {
public:
  AddrMac();
  ~AddrMac();
public:
  std::string name;
public:
  virtual bool test(std::string);
  virtual int exec(mongocxx::database, Session *, std::string);
};

#endif
