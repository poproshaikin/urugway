cmake_minimum_required(VERSION 3.16)
project(urugway LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES
    src/*.c
)

file(GLOB_RECURSE ALL_DIRS LIST_DIRECTORIES true src/*)
list(FILTER ALL_DIRS INCLUDE REGEX ".*/$")

add_executable(urugway ${SOURCES})

target_include_directories(urugway PRIVATE src)
foreach(DIR ${ALL_DIRS})
    target_include_directories(urugway PRIVATE ${DIR})
endforeach()
