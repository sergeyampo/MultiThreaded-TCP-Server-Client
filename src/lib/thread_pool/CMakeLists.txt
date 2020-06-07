cmake_minimum_required(VERSION 3.1)
project(TCPServerClient LANGUAGES C)

add_library(thread_pool STATIC thpool.c thpool.h)

target_include_directories(thread_pool PUBLIC ./)

find_package(Threads REQUIRED)
target_link_libraries(thread_pool ${CMAKE_THREAD_LIBS_INIT})