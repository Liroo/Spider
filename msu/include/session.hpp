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

namespace MSU {

  typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_socket;

  class Session : public std::enable_shared_from_this<Session> {

    public:
      Session(boost::asio::io_service&, boost::asio::ssl::context&);
      ~Session();

      void          start();
      void          handle_handshake(const boost::system::error_code&);
      void          handle_read(const boost::system::error_code&, size_t );
      void          handle_write(const boost::system::error_code&);
      ssl_socket::lowest_layer_type& socket();

    private:


      enum          { max_length = 1024 };
      ssl_socket   socket_;
      boost::asio::streambuf msg;
      std::string msg_st;
      std::string _ip;

  };
};

#endif
