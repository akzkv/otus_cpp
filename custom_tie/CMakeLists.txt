add_executable(custom_tie custom_tie.cpp)

target_compile_features(custom_tie PUBLIC cxx_std_17)
target_include_directories(custom_tie INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
