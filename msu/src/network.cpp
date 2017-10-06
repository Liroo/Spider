// network

#include "network.hpp"

Network::Network(boost::asio::io_service& io_service, unsigned short port)
    : io_service_(io_service),
      acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
      context_(io_service, boost::asio::ssl::context::sslv23)
{
    std::cout << "Server is Booting." << std::endl;
    this->context_.set_options(
        boost::asio::ssl::context::default_workarounds
        | boost::asio::ssl::context::no_sslv2
        | boost::asio::ssl::context::single_dh_use);
    this->context_.set_password_callback(boost::bind(&Network::get_password, this));
    this->context_.use_certificate_chain_file("ssl/server.crt");
    this->context_.use_private_key_file("ssl/server.key", boost::asio::ssl::context::pem);
    this->context_.use_tmp_dh_file("ssl/dh512.pem");

    Session* new_session = new Session(this->io_service_, this->context_);
    this->acceptor_.async_accept(new_session->socket(),
        boost::bind(&Network::handle_accept, this, new_session,
          boost::asio::placeholders::error));
}

Network::~Network(){

}

std::string Network::get_password() const{
  return "12345";
}



void Network::handle_accept(Session* new_session, const boost::system::error_code& error){
  if (!error)
  {
    new_session->start();
    new_session = new Session(this->io_service_, this->context_);
    acceptor_.async_accept(new_session->socket(),
        boost::bind(&Network::handle_accept, this, new_session,
          boost::asio::placeholders::error));
  }
  else
  {
    delete new_session;
  }

}
