cmake_minimum_required(VERSION 3.10)

project(DnsCache_Tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCE
    AddrItem_Tests.cpp
    Tests.cpp
    DnsCache_Tests.cpp
    DnsCachePtr_Tests.cpp
    Integrity_Tests.cpp
    UnityBuild.cpp)

add_executable(DnsCache_Tests ${SOURCE})

set(gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll" FORCE)
add_subdirectory(gtest)
enable_testing()

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${gtest_SOURCE_DIR}/include
    ${gtest_SOURCE_DIR}
)

link_directories(
    ${CMAKE_BINARY_DIR}/src/${CMAKE_BUILD_TYPE}
    ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}
)

target_link_libraries(DnsCache_Tests gtest)
