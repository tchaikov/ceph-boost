// https://www.boost.org/doc/libs/1_67_0/libs/iostreams/doc/tutorial/container_sink.html

#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <cassert>
#include <string>

namespace io = boost::iostreams;

int main() {
  using namespace std;

  string result;
  io::filtering_ostream out(io::back_inserter(result));
  out << "Hello World!";
  out.flush();
  assert(result == "Hello World!");
}
