#      Author: Caio Rodrigues 
# Description:  Sample CMake + Conan + Pybind11 project
#        Note:  Requires Conan and Python Development files installed 
#----------------------------------------------------------

cmake_minimum_required(VERSION 2.8)
project(pybind11-template)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE ON)


# ============  Conan Boostrap  ======================#

# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.13/conan.cmake"
                 "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(REQUIRES      # List of dependencies 
                              pybind11/2.2.4@conan/stable
                BASIC_SETUP
                BUILD missing)

#============ Additional Commands =============#

# Copy target file to current directory whenever it has been rebuilt.
function(copy_after_build TARGET_NAME )
    # Note: CMAKE_CURRENT_LIST_DIR is the directory where is this
    # CMakeLists.txt file.
    set(DESTDIR ${CMAKE_CURRENT_LIST_DIR}/bin/)
    file(MAKE_DIRECTORY ${DESTDIR})

    # Copy binary file to <CMakeLists.txt didctory>./bin
    # after target is compiled.
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
                               $<TARGET_FILE:${TARGET_NAME}> ${DESTDIR}
                               )
endfunction()

# In Windows set this path to Anaconda 3 Install directory
if(WIN32)
    # set(PYTHON_INCLUDE_DIR "C:\\Users\\archbox\\Miniconda3\\pkgs\\python-3.6.5-h0c2934d_0\\include\\")
    # set(PYTHON_LIBRARY     "C:\\Users\\archbox\\Miniconda3\\pkgs\\python-3.6.5-h0c2934d_0\\python3.dll")
endif()

# set(Python_ADDITIONAL_VERSIONS 3.4)
#find_package(PythonLibs  3)
# find_package(PythonInterp 3)
find_package(pybind11 CONFIG REQUIRED)

#----------------------------------------------#
#    Target Configurations                     #
#----------------------------------------------#

pybind11_add_module(SampleModule SampleModule.cpp)
# Copy binary to ./bin directory after module is built
copy_after_build(SampleModule)
