#ifndef TIMESTAMP_HPP
# define TIMESTAMP_HPP

# include <string>
# include <map>
# include <boost/uuid/uuid.hpp>
# include "plugin.hpp"

static std::map<boost::uuids::uuid, std::string> lastTimestamp;

class Timestamp: public MSU::Plugin {
public:
  Timestamp();
  ~Timestamp();

public:
  std::string name;

public:
  virtual bool test(std::string);
  virtual int exec(mongocxx::database, Session *, std::string);
  std::string getLastTT(Session *session);

};

#endif
