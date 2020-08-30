project(lsbase64)

cmake_minimum_required(VERSION 3.10)

aux_source_directory(src/ls SRC)
aux_source_directory(sample SRC_SAMPLE)

include_directories(src)

add_library(lsbase64 SHARED ${SRC})
add_executable(testcase ${SRC_SAMPLE} ${SRC})
