# CMakeList.txt: hyNet 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("hyClient")

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} /MT")

include_directories("../../../boost/boost_1_80_0" "../include")
link_directories("../../../boost/boost_1_80_0/stage/lib")

add_executable (hyClient hyClient.cpp)

# TODO: 如有需要，请添加测试并安装目标。
