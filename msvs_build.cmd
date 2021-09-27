cmake -B build
cmake --build build
cmake --build build --config Release
cpack -G ZIP --config build/CPackConfig.cmake