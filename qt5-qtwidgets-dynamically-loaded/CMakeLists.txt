cmake_minimum_required(VERSION 3.9)
project(Qt5_Widgets_Template)

#====== Global Configurations ==================#

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# If CMake fails to find CMake Qt5 CMake Modules, replace FALSE for TRUE
# and spefify QT5 Installation directory
if(MINGW AND TRUE)
    set (CMAKE_PREFIX_PATH "C:\\Qt\\5.12.2\\mingw73_64")
endif()


# Static Link MINGW Dependencies for avoiding missing DLLs errors
# Static link libgcc (MinGW C-Runtime Library) and LIBSTDC (MinGW C++ Runtime Library)
# Reference: https://stackoverflow.com/questions/19450722/include-mingw-libraries-in-compiled-file
IF(MINGW)
  set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
ENDIF()

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

# Copy all dependencies QT DLLs for the directory ${THIS DIRECTORY}/bin/
# ${THIS DIRECTORY}/bin/ (Note: It is only for MSWindows)
#
# https://gist.github.com/Rod-Persky/e6b93e9ee31f9516261b
macro(copy_qtwidgets_dlls APP LIBS)
    set(QTDLL_DESTDIR ${CMAKE_CURRENT_LIST_DIR}/bin/)

    IF(WIN32)
       FOREACH(LIB  ${LIBS})
          STRING(REGEX REPLACE "^Qt5::" "" DLL ${LIB})
          message(" [TRACE] LIB = ${LIB} DLL = ${DLL}")

          # find the release *.dll file
          get_target_property(Qt5_${DLL}Location Qt5::${DLL} LOCATION)
          # find the debug *d.dll file
          get_target_property(Qt5_${DLL}LocationDebug Qt5::${DLL} IMPORTED_LOCATION_DEBUG)

          add_custom_command(TARGET ${APP} POST_BUILD
             COMMAND ${CMAKE_COMMAND} -E
                    copy_if_different $<$<CONFIG:Debug>:${Qt5_${DLL}LocationDebug}>
                                      $<$<NOT:$<CONFIG:Debug>>:${Qt5_${DLL}Location}> ${QTDLL_DESTDIR}  # $<TARGET_FILE_DIR:${APP}>
                    )
       ENDFOREACH()
   ENDIF()
endmacro()

#=============== Target Configurations ============#
SET(QT5_LINK_LIBRARIES Qt5::Core Qt5::Gui Qt5::Widgets Qt5::UiTools Qt5::Network)

add_executable(qtWidgetsApp app.cpp FormLoader.hpp resources.qrc)
target_link_libraries(qtWidgetsApp "${QT5_LINK_LIBRARIES}")
copy_after_build(qtWidgetsApp)
copy_qtwidgets_dlls(qtWidgetsApp "${QT5_LINK_LIBRARIES}")
