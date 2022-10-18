#include <pybind11/pybind11.h>

#include "FilteringCore.hpp"
#include "RelationalCore.hpp"
#include "NormalCore.hpp"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;

PYBIND11_MODULE(midas, m)
{
  m.doc() = R"pbdoc(
  A python wrapper of C++ midas
  -----------------------
      class NormalCore(int numRow, int numColumn, unsigned seed)
      class RelationalCore(int numRow, int numColumn, unsigned seed, float factor)
      class FilteringCore(int numRow, int numColumn, unsigned seed, float threshold, float factor)
)pbdoc";

  py::class_<MIDAS::NormalCore>(m, "NormalCore")
      .def(py::init<int, int, unsigned>())
      .def("__call__", &MIDAS::NormalCore::operator(),
           R"pbdoc(
  midas(int source, int destination, int timestamp)

  Arguments
    `source`: source node start from 0
    `destination`: destination node start from 0
    `timestamp`: timestamp start from 1

  Return
    score
)pbdoc");

  py::class_<MIDAS::RelationalCore>(m, "RelationalCore")
      .def(py::init<int, int, unsigned, float>())
      .def("__call__", &MIDAS::RelationalCore::operator(),
           R"pbdoc(
  midas(int source, int destination, int timestamp)

  Arguments
    `source`: source node start from 0
    `destination`: destination node start from 0
    `timestamp`: timestamp start from 1

  Return
    score
)pbdoc");

  py::class_<MIDAS::FilteringCore>(m, "FilteringCore")
      .def(py::init<int, int, unsigned, float, float>())
      .def("__call__", &MIDAS::FilteringCore::operator(),
           R"pbdoc(
  midas(int source, int destination, int timestamp)

  Arguments
    `source`: source node start from 0
    `destination`: destination node start from 0
    `timestamp`: timestamp start from 1

  Return
    score
)pbdoc");

#ifdef VERSION_INFO
  m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
  m.attr("__version__") = "dev";
#endif
}
