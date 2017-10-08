#ifndef MOUSE_HPP
# define MOUSE_HPP

# include <string>
# include "plugin.hpp"

class Mouse: public MSU::Plugin {
public:
  Mouse();
  ~Mouse();
public:
  std::string name;
public:
  virtual bool test(std::string);
  virtual int exec(mongocxx::database, Session *, std::string);
};

#endif
