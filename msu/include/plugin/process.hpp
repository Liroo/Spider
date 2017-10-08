#ifndef PROCESS_HPP
# define PROCESS_HPP

# include <string>
# include "plugin.hpp"

class Process: public MSU::Plugin {
public:
  Process();
  ~Process();
public:
  std::string name;
public:
  virtual bool test(std::string);
  virtual int exec(Session *, std::string);
};

#endif
