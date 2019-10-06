cmake_minimum_required(VERSION 3.5)
project(basic_boost_asio_server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(Boost COMPONENTS system coroutine REQUIRED)
add_executable(echo-server echo-server.cpp)
target_link_libraries(echo-server Boost::system pthread)
