cmake_minimum_required(VERSION 3.9)

# Proeject name - should not contain whitespace 
project(OpengGL_CPP)

#========== Global Configurations =============#
#----------------------------------------------#

# Set the C++ standard for all targets (It sets the flags
# (-std=c++11, -std=c++14 ...) on Clang or GCC. and /std=c++17 on MSVC
# OPTIONAL:
#---------------------------------
set(CMAKE_CXX_STANDARD 17)     
set(CMAKE_VERBOSE_MAKEFILE ON)

#========== Targets Configurations ============#

# Build an executable (Unix-like OSes generates ./openglDemo1, on
# Windows ./opengDemo1.exe)
# ..........................................
add_executable(openglDemo1 opengl1.cpp)

# Set executable dependency libraries
# Equivalent to pass flags -lGL, -lGLU and -lglut 
target_link_libraries(openglDemo1 GL GLU glut)

# Add extension .bin to executable name to make it easier
# to identify that the binary file is an executable.
# So, it turns  openglDemo1 becomes openglDemo1.bin 
if(UNIX)
  set_target_properties(openglDemo1 PROPERTIES SUFFIX ".bin")
endif()

# Add target to run executable 
add_custom_target(run-ex1
    COMMAND openglDemo1 
    DEPENDS openglDemo1 
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
