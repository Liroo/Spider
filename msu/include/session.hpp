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
#include <boost/bind.hpp>
#include <boost/asio/ssl.hpp>

typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_socket;

class Session {

public:
  Session(boost::asio::io_service& io_service, boost::asio::ssl::context& context);
  ~Session();
  ssl_socket::lowest_layer_type& socket();
  void handle_handshake(const boost::system::error_code& error);
  void          start();
  void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
  void handle_write(const boost::system::error_code& error);

private:


  ssl_socket   socket_;
  enum          { max_length = 1024 };
  char          data_[max_length];

};

#endif
