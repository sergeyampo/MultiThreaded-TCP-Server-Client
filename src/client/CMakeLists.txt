cmake_minimum_required(VERSION 3.1)
project(TCPServerClient LANGUAGES C)

add_executable(client client.c utils/extract_ip_port_from_string.c utils/opt_arg.c  ../lib/check_port.c  ../lib/set_sockaddr_in.c)

target_include_directories(client PUBLIC ./)

find_package(Threads REQUIRED)
target_link_libraries(client ${CMAKE_THREAD_LIBS_INIT})
#target_include_directories(client PUBLIC ../lib)
#target_link_libraries(client nikita_and_sonya_lib)