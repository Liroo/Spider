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
namespace MSU {
  class Network {

  public:
    Network(int port, boost::asio::io_service& io_service);
    ~Network();

    std::string get_password() const;
    void handle_accept(Session* new_session, const boost::system::error_code& error);
    void run(std::function<void(Session *)> handle_session);

  private:
    boost::asio::io_service& _io_service;
    boost::asio::ip::tcp::acceptor _acceptor;
    boost::asio::ssl::context _context;
    std::function<void(Session *)> _handle_session;
  }; // class Network
}; // namespace MSU

#endif
