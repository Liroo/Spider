// session

#include "session.hpp"


Session::Session(boost::asio::io_service& io_service, boost::asio::ssl::context& context)
    : socket_(io_service, context){
}

Session::~Session(){

}

ssl_socket::lowest_layer_type& Session::socket(){
  return this->socket_.lowest_layer();
}

void Session::start(){
  std::cout << "client Connected." << std::endl << "Client ip is: " << this->socket_.lowest_layer().remote_endpoint().address().to_string() << std::endl;
  this->socket_.async_handshake(boost::asio::ssl::stream_base::server,
    boost::bind(&Session::handle_handshake, this,
      boost::asio::placeholders::error));
}

void Session::handle_handshake(const boost::system::error_code& error){
  if (!error)
  {
    boost::asio::async_read_until(this->socket_, this->msg, "",
        boost::bind(&Session::handle_read, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }
  else
    delete this;
}

static std::string  buffer_to_string(const boost::asio::streambuf &buffer){
  using boost::asio::buffers_begin;

  auto bufs = buffer.data();
  std::string result(buffers_begin(bufs), buffers_begin(bufs) + buffer.size());
  return result;
}

//
// la le callback est fait "normallement" a check
//
void Session::handle_read(const boost::system::error_code& error, size_t bytes_transferred){
  if (!error)
  {
    _core.callback_read(this->msg, [&](std::string result) -> void {
      boost::asio::async_write(this->socket_, result,
            boost::bind(&Session::handle_write, this,
              boost::asio::placeholders::error));
    });
  }
  else
    delete this;
}

void Session::handle_write(const boost::system::error_code& error){
  if (!error)
  {
    boost::asio::async_read_until(this->socket_, this->msg, "",
        boost::bind(&Session::handle_read, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }
  else
    delete this;
}
