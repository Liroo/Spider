// main

//#include "msu.hpp"
#include "network.hpp"
#include <boost/asio.hpp>
// int argc __attribute__((unused)), char const *argv[] __attribute__((unused))
int main() {
  //MSU::Core test(123);
  //test.listen();
  boost::asio::io_service io_service;
  Network server(io_service, std::atoi("4242"));
  io_service.run();
  io_service.poll();
  return (0);
}
