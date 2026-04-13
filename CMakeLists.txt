cmake_minimum_required(VERSION 3.10)

project(2048)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set(variables 
        CMAKE_CXX_FLAGS_RELEASE 
        CMAKE_CXX_FLAGS_DEBUG)
    foreach(variable ${variables})
        if(${variable} MATCHES "/MD")
            string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
        endif()
    endforeach()
endif()


add_executable(2048 main.cpp)