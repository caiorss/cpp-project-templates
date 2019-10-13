@echo OFF

REM Automate CMake Compilation on Windows     
cmake -H. -Bbuild -G "Visual Studio 15 2017 Win64" -DCMAKE_BUILD_TYPE=Debug
cmake --build build --target    
