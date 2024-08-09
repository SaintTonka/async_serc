add_executable(async_client_main ${CMAKE_CURRENT_SOURCE_DIR}/multi_threaded_client.cpp)
target_link_libraries(async_client_main Boost::system Boost::thread)