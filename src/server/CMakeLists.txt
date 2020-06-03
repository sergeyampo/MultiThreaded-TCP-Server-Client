cmake_minimum_required(VERSION 3.1)
project(TCPServerClient LANGUAGES C)

add_executable(server server.c)

find_package(Threads REQUIRED)
target_link_libraries(server ${CMAKE_THREAD_LIBS_INIT})

target_include_directories(server PUBLIC ../utils)
#target_link_libraries(server nikita_and_sonya_lib)
