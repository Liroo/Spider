// network

#include "network.hpp"


Network::Network(boost::asio::io_service& io_service, unsigned short port)
    : io_service_(io_service),
      acceptor_(io_service,
          boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
      context_(boost::asio::ssl::context::sslv23)
  {
    context_.set_options(
        boost::asio::ssl::context::default_workarounds
        | boost::asio::ssl::context::no_sslv2
        | boost::asio::ssl::context::single_dh_use);
    context_.set_password_callback(boost::bind(&Network::get_password, this));
    context_.use_certificate_chain_file("ssl/server.crt");
    context_.use_private_key_file("ssl/server.key", boost::asio::ssl::context::pem);
    context_.use_tmp_dh_file("ssl/dh512.pem");

    start_accept();
  }

Network::~Network(){

}

std::string Network::get_password() const{
  return "test";
}

void Network::start_accept()
{
  Session* new_session = new Session(io_service_, context_);
  acceptor_.async_accept(new_session->socket(),
      boost::bind(&Network::handle_accept, this, new_session,
        boost::asio::placeholders::error));
}

void Network::handle_accept(Session* new_session, const boost::system::error_code& error){
  if (!error)
  {
    new_session->start();
  }
  else
  {
    delete new_session;
  }

  start_accept();
}
