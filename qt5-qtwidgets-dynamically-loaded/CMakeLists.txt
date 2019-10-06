cmake_minimum_required(VERSION 3.9)
project(Qt5_Widgets_Template)

#====== Global Configurations ==================#

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt5 COMPONENTS Core Widgets Network UiTools REQUIRED)

#========== Functions =======================================#

# Copy target file to current directory whenerver it is rebuilt
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

#=============== Target Configurations ============#

add_executable(qtWidgetsApp app.cpp FormLoader.hpp resources.qrc)
target_link_libraries(qtWidgetsApp Qt5::Core Qt5::Widgets Qt5::UiTools Qt5::Network)

