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
#include <boost/asio.hpp>
#include "session.hpp"

class Network {

public:
  Network(short port);
  ~Network();

  void run();

  boost::asio::io_service         io_service_;

private:

  void do_accept();

  boost::asio::ip::tcp::acceptor  acceptor_;
  boost::asio::ip::tcp::socket    socket_;
};

#endif
