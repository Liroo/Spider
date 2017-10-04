// network

#include "network.hpp"


Network::Network(short port) : acceptor_(io_service_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)), socket_(io_service_){
  do_accept();
}

Network::~Network(){


}

void Network::do_accept(){
  acceptor_.async_accept(socket_,
      [this](boost::system::error_code ec)
      {
        if (!ec)
        {
          std::make_shared<Session>(std::move(socket_))->start();
        }

        do_accept();
      });

}
