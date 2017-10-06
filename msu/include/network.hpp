// network
/*
  class network

  This class will connect the server to the client.

  Constructor:
    Network();

  public:

*/

#ifndef NETWORK_HPP
# define NETWORK_HPP


# include <cstdlib>
# include <iostream>
# include <memory>
# include <utility>
# include <boost/bind.hpp>
# include <boost/asio.hpp>
# include <boost/asio/ssl.hpp>
# include <boost/date_time/posix_time/posix_time.hpp>
# include "session.hpp"

class Network {

public:
  Network(boost::asio::io_service& io_service, unsigned short port);
  ~Network();

  void run();
  std::string get_password() const;
  void handle_accept(Session* new_session, const boost::system::error_code& error);


private:

  boost::asio::io_service& io_service_;
  boost::asio::ip::tcp::acceptor  acceptor_;
  boost::asio::ssl::context context_;
};

#endif
