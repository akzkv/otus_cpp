cmake -G "MinGW Makefiles" -B mingw_build
cmake --build mingw_build
cpack -G DEB --config mingw_build/CPackConfig.cmake