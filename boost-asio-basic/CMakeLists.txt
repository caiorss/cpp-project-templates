cmake_minimum_required(VERSION 3.5)
project(basic_boost_asio_server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Set this option to OFF in order to not use Conan
# and use a locally installed Boost. 
set(BUILD_WITH_CONAN ON)


#========= Conan Bootstrap ======================#

IF(BUILD_WITH_CONAN)
     message( [INFO] " =>> Building with CONAN OK.")

     # Download automatically, you can also just copy the conan.cmake file
     if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
        message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
        file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.13/conan.cmake"
                      "${CMAKE_BINARY_DIR}/conan.cmake")
     endif()

     include(${CMAKE_BINARY_DIR}/conan.cmake)

     # Add all dependencies here 
     conan_cmake_run( REQUIRES
                      boost/1.70.0@conan/stable

                      BASIC_SETUP
                      BUILD missing )
ENDIF()

#========= Find Packages =========================#

# Set this option to ON for using static linking instead of dynamic
# linking
set(Boost_USE_STATIC_LIBS ON)

find_package(Boost COMPONENTS system coroutine REQUIRED)

#========== Target Configurations ================#


add_executable(echo-server echo-server.cpp)
target_link_libraries(echo-server Boost::system pthread)

