cmake_minimum_required(VERSION 3.9)
project(Simple_Cmake_Project)

#========== Global Configurations =============#
#----------------------------------------------#

set(CMAKE_CXX_STANDARD 17)     
set(CMAKE_VERBOSE_MAKEFILE ON)

#========== Targets Configurations ============#

add_executable(app1 application1.cpp)
add_executable(app2 application2.cpp)

