// main

#include "msu.hpp"
#include <boost/asio.hpp>

int main() {
  MSU::Core test(1024);

  test.run();
  return (0);
}
