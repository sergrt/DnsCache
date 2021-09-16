cmake_minimum_required(VERSION 3.10)

project(DnsCache)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCE
    AddrItem.cpp
    main.cpp
    DnsCache.cpp
    DnsCachePtr.cpp)

set(HEADER
    AddrItem.h
    DnsCache.h
    DnsCachePtr.h)

add_executable(DnsCache ${SOURCE} ${HEADER})
