add_executable(async_tcp_server_main ${CMAKE_CURRENT_SOURCE_DIR}/async_tcp_server.cpp)
target_link_libraries(async_tcp_server_main Boost::system Boost::thread)
