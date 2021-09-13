cmake_minimum_required(VERSION 3.10)

project(otus_cpp
  LANGUAGES CXX
  VERSION 0.0.1
)

set(CMAKE_BUILD_TYPE Debug)

#include_directories(${CMAKE_BINARY_DIR})

add_subdirectory(custom_tie)

#install(TARGETS custom_tie RUNTIME DESTINATION bin)

#set(CPACK_GENERATOR DEB)
#set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
#set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
#set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

#set(CPACK_PACKAGE_CONTACT example@example.com)

#include(CPack)

