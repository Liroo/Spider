// network

#ifndef NETWORK_HPP
# define NETWORK_HPP

/*
  class network

  This class will connect the server to the client.

  Constructor:
    Network();

  public:

*/
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include "session.hpp"

class Network {

public:
  Network(boost::asio::io_service& io_service, unsigned short port);
  ~Network();

  void run();
  std::string get_password() const;
  void start_accept();
  void handle_accept(Session* new_session, const boost::system::error_code& error);


private:

  void do_accept();

  boost::asio::ip::tcp::acceptor  acceptor_;
  boost::asio::io_service& io_service_;
  boost::asio::ssl::context context_;
};

#endif
