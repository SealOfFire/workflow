/**
 * 导出给python的接口
 */
#define BOOST_PYTHON_STATIC_LIB

#include <boost/python.hpp>
#include "activities/BaseActivity.h"

using namespace boost::python;

struct World {
    void set(std::string msg) { this->msg = msg; }

    std::string greet() { return msg; }

    std::string msg;
};

BOOST_PYTHON_MODULE(workflow) {
    class_<World>("World").def("greet", &World::greet).def("set", &World::set);
    class_<workflow::activities::BaseActivity>("BaseActivity");
}