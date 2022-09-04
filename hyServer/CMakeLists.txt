# CMakeList.txt: hyNet 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("hyServer")

set(CMAKE_CXX_STANDARD 20)

include_directories("../../../boost/boost_1_80_0")
link_directories("../../../boost/boost_1_80_0/stage/lib")

add_executable (hyServer hyServer.cpp  tcp_server.h tcp_server.cpp tcp_session.h tcp_session.cpp)

# TODO: 如有需要，请添加测试并安装目标。
