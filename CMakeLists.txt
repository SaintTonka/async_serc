cmake_minimum_required(VERSION 3.15.0)
cmake_policy(SET CMP0016 NEW)

project(async_server VERSION 1.0.0 DESCRIPTION "Знакомство с асинхронным вводом/выводом на C++")

include_directories(${CMAKE_SOURCE_DIR}/src)

find_package(Boost 1.58 REQUIRED COMPONENTS system thread)

add_executable(server ${CMAKE_CURRENT_SOURCE_DIR}/src/async_server/async_tcp_server.cpp)
target_link_libraries(server Boost::system Boost::thread)

add_executable(client ${CMAKE_CURRENT_SOURCE_DIR}/src/async_client/multi_threaded_client.cpp)
target_link_libraries(client Boost::system Boost::thread)



