cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

add_executable(main
        src/main.cpp
        src/TestList.cpp
        src/TestVector.cpp
        src/TestRunner.cpp
        src/TestMap.cpp
        src/TestMultiMap.cpp
        src/TestSet.cpp
        src/TestMultiSet.cpp
        src/TestQueue.cpp
        src/TestStack.cpp)
