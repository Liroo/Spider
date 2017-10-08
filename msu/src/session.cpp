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
  if (!error) {
    boost::uuids::uuid uniqueId = boost::uuids::random_generator()();
    this->_uniqueId = uniqueId;
    std::cout << "[" << this->_uniqueId << "] is now authentified." << std::endl;
    boost::asio::async_read_until(this->socket_, this->msg, "",
      boost::bind(&Session::handle_read, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
  }
  else {
    delete this;
  }
}

void Session::set_read_callback(std::function<std::string(Session *, std::string)> read_callback) {
  _read_callback = read_callback;
}

static std::string  buffer_to_string(boost::asio::streambuf &sbuf){
  std::string result((std::istreambuf_iterator<char>(&sbuf)),
                    std::istreambuf_iterator<char>());
  return result;
}

//
// la le callback est fait "normallement" a check
//
void Session::handle_read(const boost::system::error_code& error, size_t bytes_transferred){
  if (!error) {
    std::string res = _read_callback(this, buffer_to_string(this->msg));
    boost::asio::streambuf sbuf;
    std::iostream os(&sbuf);
    os << res;
    boost::asio::async_write(this->socket_, sbuf,
        boost::bind(&Session::handle_write, this,
          boost::asio::placeholders::error));
  }
  else
    delete this;
}

void Session::handle_write(const boost::system::error_code& error){
  if (!error) {
    boost::asio::async_read_until(this->socket_, this->msg, "",
        boost::bind(&Session::handle_read, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }
  else
    delete this;
}
