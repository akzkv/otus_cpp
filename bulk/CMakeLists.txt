add_executable(bulk bulk.cpp)

target_compile_features(bulk PUBLIC cxx_std_20)
target_include_directories(bulk INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
