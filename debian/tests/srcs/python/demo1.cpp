// https://www.boost.org/doc/libs/1_67_0/libs/python/doc/html/tutorial/index.html#tutorial.quickstart
#include <boost/python.hpp>

char const *greet() { return "hello, world"; }

BOOST_PYTHON_MODULE(libdemo1)
{
    using namespace boost::python;
    def("greet", greet);
}