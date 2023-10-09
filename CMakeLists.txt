cmake_minimum_required(VERSION 3.11)

project(polynomials CXX)

set(CMAKE_CXX_STANDARD 23)

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()

add_library(vector STATIC "include/vector/vector.cpp")
add_library(class STATIC "include/class/class.cpp")
target_include_directories(vector PUBLIC "include/vector")
target_include_directories(class PUBLIC "include/class")

add_executable (${PROJECT_NAME} "main.cpp")
target_link_libraries(class PUBLIC vector)
target_link_libraries(${PROJECT_NAME} class)