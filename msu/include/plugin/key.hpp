#ifndef KEY_HPP
# define KEY_HPP

# include <string>
# include "plugin.hpp"

class Key: public MSU::Plugin {
public:
  Key();
  ~Key();
public:
  std::string name;
public:
  virtual bool test(std::string);
  virtual int exec(std::string);
};

#endif
