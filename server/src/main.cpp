// main

#include "msu.hpp"

int main(int argc __attribute__((unused)), char const *argv[] __attribute__((unused))) {
  MSU::Core test(123);
  test.listen();
  return (0);
}
