cmake -B build
cmake --build build
cmake --build build --config Release
cpack -G WIX --config build/CPackConfig.cmake