cmake_minimum_required(VERSION 3.1)
project(TCPServerClient LANGUAGES C)

add_executable(server server.c utils/opt_arg.c utils/factorial.c  ../lib/check_port.c ../lib/set_sockaddr_in.c)

target_include_directories(server PUBLIC ./)
find_package(Threads REQUIRED)
target_link_libraries(server ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(server thread_pool)