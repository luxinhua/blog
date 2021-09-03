cmake_minimum_required(VERSION 3.5)

project(myprint)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O2 -Wall -g")

include_directories(
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/library/easylogger/inc)

# aux_source_directory(${CMAKE_SOURCE_DIR}/src   DIR_SRCS)
# MESSAGE(STATUS  "${DIR_SRCS}")
# add_executable(
#     myprint
#     $(DIR_SRCS)
# )

add_executable(
    myprint 
    src/main.c
    src/myprintf.c
)

