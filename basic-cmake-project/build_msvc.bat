REM Build script for compiling with MSVC (aka Visual C++, cl.exe) on Windows
@echo OFF

REM Automate CMake Compilation on Windows     

cmake -H. -B_build -G "Visual Studio 15 2017 Win64"
cmake --build _build --target    
