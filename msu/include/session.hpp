// Session

#ifndef SESSION_HPP
# define SESSION_HPP

/*
  class Session

    This class will help the Network class to read and write data.

    Constructor:
      Session();

    public:
      void start();

    private:
      void read();
      void do_write();

*/

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

class Session : public std::enable_shared_from_this<Session> {

public:
  Session(boost::asio::ip::tcp::socket socket);
  ~Session();
  void          start();
private:
  void          do_read();
  void          do_write(std::size_t length);

  boost::asio::ip::tcp::socket   socket_;
  enum          { max_length = 1024 };
  char          data_[max_length];

};

#endif
