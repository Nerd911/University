cmake_minimum_required(VERSION 3.3)
project(SimpleSniffer)

set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -lpcap")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lpcap")

set(SOURCE_FILES main.c snifferInit.c snifferInit.h packetCapturing.c packetCapturing.h packetPrinting.c packetPrinting.h)
add_executable(SimpleSniffer ${SOURCE_FILES})

target_link_libraries(SimpleSniffer ${CMAKE_SOURCE_DIR}/libpcap.a)