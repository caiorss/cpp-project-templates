# Brief: CMakeLists.txt script for building WxWidgets with Conan Package Manager 
#
#-----------------------------------------------------------
cmake_minimum_required(VERSION 3.5)
project(wx_widgets_app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Set this option to OFF in order to not use Conan
# and use a locally installed Boost. 
set(BUILD_WITH_CONAN OFF)

#========== Functions =======================================#

# Copy target file to path ${CURRENT DIRECTORY}/bin whenever it is rebuilt.
# It is easier to find and run executable targets from the command line.
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

                      # Recipe references: 
                      #  =>> https://bintray.com/bincrafters/public-conan/wxwidgets
		      #  =>> https://github.com/bincrafters/conan-wxwidgets
                      wxwidgets/3.1.2@bincrafters/stable

                      BASIC_SETUP
                      BUILD missing )
ENDIF()

#========= Find Packages =========================#
#

# SET(wxWidgets_USE_LIBS)
set(wxWidgets_CONFIG_OPTIONS_DEFAULT "--toolkit=gtk3")

find_package(wxWidgets COMPONENTS net gl core base REQUIRED)
include( "${wxWidgets_USE_FILE}" )

execute_process(COMMAND bash -c "wx-config --libs" 
OUTPUT_VARIABLE wx_libraries)
string(STRIP ${wx_libraries} wx_libraries)

message([TRACE] " wx_libraries = ${wx_libraries}")


#========== Target Configurations ================#
#

# <<--- Target: SingleFileApp - App with just a single file
# ........................................................

add_executable(singleFileApp singleFileApp/main.cpp)
target_link_libraries(singleFileApp ${wx_libraries})
copy_after_build(singleFileApp)


#  <<--- Target: SampleApp - App with multiple file. ----->>
# ........................................................
add_executable(sampleApp
                  sampleApp/wxwidgets_sampleMain.cpp
                  sampleApp/wxwidgets_sampleMain.h
	          sampleApp/wxwidgets_sampleApp.cpp
                  sampleApp/wxwidgets_sampleApp.h        
                  )
target_link_libraries(sampleApp ${wx_libraries})
                
# Note: It will link against all libraries imported in: conan_cmake_run 
#target_link_libraries(sampleApp ${CONAN_LIBS})
copy_after_build(sampleApp)
