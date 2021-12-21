cmake_minimum_required(VERSION 3.6)

project(part1)

aux_source_directory(src SRC)

add_executable(part1.out ${SRC})
target_include_directories(part1.out PUBLIC include)
