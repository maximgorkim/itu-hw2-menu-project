cmake_minimum_required(VERSION 3.16)
project(hw2_restaurant CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# json'u bulabilmesi için
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/external)
include_directories(${CMAKE_SOURCE_DIR}/external/nlohmann)

include_directories("${CMAKE_SOURCE_DIR}/include")

add_executable(hw2
    ${CMAKE_CURRENT_SOURCE_DIR}/src/hw2_main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/hw2_menu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/hw2_recommender.cpp
)

add_custom_command(TARGET hw2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/menu_copy.json"
        $<TARGET_FILE_DIR:hw2>
)

if (APPLE)
    target_compile_options(hw2 PRIVATE -Wall -Wextra -Wpedantic)
endif()
