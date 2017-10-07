// network

#include "network.hpp"

using namespace MSU;

Network::Network(int port, boost::asio::io_service& io_service)
  : _io_service(io_service),
    _acceptor(_io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
    _context(_io_service, boost::asio::ssl::context::sslv23) {
  std::cout << "Server is Booting." << std::endl;
  this->_context.set_options(
    boost::asio::ssl::context::default_workarounds
    | boost::asio::ssl::context::no_sslv2
    | boost::asio::ssl::context::single_dh_use);
  this->_context.use_certificate_chain_file("ssl/server.crt");
  this->_context.use_private_key_file("ssl/server.key", boost::asio::ssl::context::pem);
  this->_context.use_tmp_dh_file("ssl/dh512.pem");
}

Network::~Network() {}

void Network::handle_accept(Session* new_session, const boost::system::error_code& error) {
  if (!error)
  {
    _handle_session(new_session);
    new_session = new Session(this->_io_service, this->_context);
    _acceptor.async_accept(new_session->socket(),
        boost::bind(&Network::handle_accept, this, new_session,
          boost::asio::placeholders::error));
  }
  else
  {
    delete new_session;
  }
}

void Network::run(std::function<void(Session *)> handle_session) {
  Session* new_session = new Session(this->_io_service, this->_context);

  _handle_session = handle_session;
  this->_acceptor.async_accept(new_session->socket(),
      boost::bind(&Network::handle_accept, this, new_session,
        boost::asio::placeholders::error));
  _io_service.run();
}
