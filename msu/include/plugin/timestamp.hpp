#ifndef TIMESTAMP_HPP
# define TIMESTAMP_HPP

# include <string>
# include "plugin.hpp"

class Timestamp: public MSU::Plugin {
public:
  Timestamp();
  ~Timestamp();
public:
  std::string name;
public:
  virtual bool test(std::string);
  virtual int exec(std::string);
};

#endif
