cmake_minimum_required(VERSION 3.11)
project(qsim)

set(CMAKE_VERBOSE_MAKEFILE ON)

ADD_SUBDIRECTORY(pybind_interface/sse4_1)
ADD_SUBDIRECTORY(pybind_interface/avx512)
ADD_SUBDIRECTORY(pybind_interface/avx2)
ADD_SUBDIRECTORY(pybind_interface/basic)
ADD_SUBDIRECTORY(pybind_interface/decide)
