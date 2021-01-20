cmake_minimum_required(VERSION 3.16)

project(steadlang)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-O3 -march=native")

include_directories(${CMAKE_SOURCE_DIR})

add_executable(stead
  utils/filehelpers.c
  utils/logger.c  
  steadlang/lexer.c

  main.c
)