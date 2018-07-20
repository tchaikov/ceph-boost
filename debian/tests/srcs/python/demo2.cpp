// https://www.boost.org/doc/libs/1_67_0/libs/python/doc/html/tutorial/tutorial/exposing.html
#include <boost/python.hpp>

struct World
{
    void set(std::string msg) { this->msg = msg; }
    std::string greet() { return msg; }
    std::string msg;
};

struct Var
{
    Var(std::string name) : name(name), value() {}
    std::string const name;
    float value;
};

#include <boost/python.hpp>
using namespace boost::python;

BOOST_PYTHON_MODULE(libdemo2)
{
    class_<World>("World").def("greet", &World::greet).def("set", &World::set);
    class_<Var>("Var", init<std::string>())
        .def_readonly("name", &Var::name)
        .def_readwrite("value", &Var::value);
}
