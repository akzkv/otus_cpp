cmake_minimum_required(VERSION 3.10)

if(DEFINED ENV{GITHUB_RUN_NUMBER})
  set(PATCH_NUM $ENV{GITHUB_RUN_NUMBER})
else()
  set(PATCH_NUM "0")
endif()

project(otus_cpp
  LANGUAGES CXX
  VERSION 0.0.${PATCH_NUM}
)

if(DEFINED ENV{BUILD_TYPE})
  set(CMAKE_BUILD_TYPE $ENV{BUILD_TYPE})
else()
  set(CMAKE_BUILD_TYPE Debug)
endif()

message(STATUS "Build type: " ${CMAKE_BUILD_TYPE})

configure_file(version.h.in version.h)
include_directories(${CMAKE_BINARY_DIR})

add_subdirectory(custom_tie)
add_subdirectory(hello)
add_subdirectory(ip_filter)
add_subdirectory(bulk)

install(TARGETS hello custom_tie ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

