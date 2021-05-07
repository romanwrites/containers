cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

add_executable(main
        main.cpp
        TestList.cpp
        TestVector.cpp
        TestRunner.cpp
        TestMap.cpp
        TestMultiMap.cpp
        TestSet.cpp
        TestQueue.cpp
        TestStack.cpp)
